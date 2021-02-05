//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//		Fixed Depth Order-Independent Transparency											//
//		Copyright (c)2014 Martinus Terpstra													//
//																							//
//		Permission is hereby granted, free of charge, to any person obtaining a copy		//
//		of this software and associated documentation files (the "Software"), to deal		//
//		in the Software without restriction, including without limitation the rights		//
//		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell			//
//		copies of the Software, and to permit persons to whom the Software is				//
//		furnished to do so, subject to the following conditions:							//
//																							//
//		The above copyright notice and this permission notice shall be included in			//
//		all copies or substantial portions of the Software.									//
//																							//
//		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR			//
//		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,			//
//		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE			//
//		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER				//
//		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,		//
//		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN			//
//		THE SOFTWARE.																		//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////

#include "Precomp.h"

#include "Renderer.h"
#include "RenderFDOIT.h"
#include "Scene.h"
#include "Window.h"
#include "Camera.h"
#include "Timings.h"

#include "GPUStructs.h"

// shaders
#include "ShaderHeaders\FDOITResolve4.h"
#include "ShaderHeaders\FDOITResolve8.h"
#include "ShaderHeaders\FDOITResolve16.h"
#include "ShaderHeaders\FDOITResolve32.h"
#include "ShaderHeaders\FDOITGeometryPS.h"

#include "FileBuffer.h"

using namespace Demo;
using namespace Demo::Implementation;

void __stdcall OnSetLayerDepth(__in const void* value, __inout_opt void* data)
{
	reinterpret_cast<RenderFDOIT*>(data)->layerDepth = FDOITDepth(*(uint32*)value);
}

void __stdcall OnGetLayerDepth(__inout void* value, __inout_opt void* data)
{
	*(uint32*)value = reinterpret_cast<RenderFDOIT*>(data)->layerDepth;
}

RenderFDOIT::RenderFDOIT(uint RTVindex, const shared_ptr<Window>& window)
	: RenderBase(RTVindex)
{
	m_CurrentDepth = FDOIT_DEPTH_16;

	m_FragmentList.Init(s_Device, mst::make_flag(D3D11_BIND_SHADER_RESOURCE, D3D11_BIND_UNORDERED_ACCESS), GPUARR_USE_COUNTER);
	
	m_FragmentStartIndices.Init(s_Device, mst::make_flag(D3D11_BIND_SHADER_RESOURCE, D3D11_BIND_UNORDERED_ACCESS)
		, DXGI_FORMAT_R32_UINT, window->size);

	//m_FragmentStartIndices.Resize(window->width * window->height); // + 1 for the overhead counter

	m_FragmentList.Resize(window->width * window->height * 16);

	s_Device->CreatePixelShader(g_FDOITResolve4, sizeof(g_FDOITResolve4), null, mst::initialize(m_ResolvePS[0]));
	s_Device->CreatePixelShader(g_FDOITResolve8, sizeof(g_FDOITResolve8), null, mst::initialize(m_ResolvePS[1]));
	s_Device->CreatePixelShader(g_FDOITResolve16, sizeof(g_FDOITResolve16), null, mst::initialize(m_ResolvePS[2]));
	s_Device->CreatePixelShader(g_FDOITResolve32, sizeof(g_FDOITResolve32), null, mst::initialize(m_ResolvePS[3]));
	
	s_Device->CreatePixelShader(g_FDOITGeometryPS, sizeof(g_FDOITGeometryPS), null, mst::initialize(m_GeometryPS));

	TwEnumVal renderModesEnum[] = { {FDOIT_DEPTH_4, "4"}, {FDOIT_DEPTH_8, "8"}, 
									{FDOIT_DEPTH_16, "16"}, {FDOIT_DEPTH_32, "32" } };

	TwType rmEnum = TwDefineEnum("LayerDepth", renderModesEnum, extentof(renderModesEnum));

	TwAddVarCB(GetGUIBar(), "Depth layers", rmEnum, 
		OnSetLayerDepth, OnGetLayerDepth, this, null);
}

RenderFDOIT::~RenderFDOIT()
{
	TwRemoveVar(GetGUIBar(), "Depth layers");
}

void RenderFDOIT::Render(const matrix& view, const shared_ptr<Window>& window)
{
	Timings::BeginQuery("Fill list");

	m_FragmentStartIndices.ClearUAV(0xFFFFFFFF);

	ID3D11UnorderedAccessView* accessviews[2] =
	{
		m_FragmentStartIndices.GetUAV().get(),
		m_FragmentList.GetUAV().get()
	};
	UINT initCounters[2] = { 0,0 };
	s_Context->OMSetRenderTargetsAndUnorderedAccessViews(0, null, null, 0, 2,
		accessviews, initCounters);


	m_OITBuffer.data.g_Far = Renderer::Get().camera->farDistance;
	m_OITBuffer.data.g_HalfSizef = float2(window->size) * 0.5f; 
	m_OITBuffer.data.g_Resolution = window->size;
	m_OITBuffer.data.g_Resolutionf = float2(window->size);
	m_OITBuffer.data.g_MaxLinkedListCount = m_FragmentList.GetCapacity();
	m_OITBuffer.data.g_Debug = Renderer::Get().debugMode;

	m_OITBuffer.Update(s_Context);

	m_OITBuffer.PSSetConstantBuffer(s_Context, 2);

	float blendFactor[]={1,1,1,1};
	s_Context->OMSetBlendState(null, blendFactor, -1);

	RenderMeshes(view, window, m_GeometryPS);

	Timings::EndQuery("Fill list");



	// Pass 2 resolve

	Timings::BeginQuery("Resolve");

	s_Context->OMSetRenderTargets(1, &GetRTV(), null);


	m_FragmentStartIndices.PSSetShaderResource(0);
	m_FragmentList.PSSetShaderResource(1);

	s_Context->PSSetShader(m_ResolvePS[m_CurrentDepth].get(), null, 0);

	RenderQuad();

	ID3D11ShaderResourceView* nullviews[2] = {};
	s_Context->PSSetShaderResources(0, extentof(nullviews), nullviews);

	Timings::EndQuery("Resolve");

	/*
	if(m_FragmentStartIndices.LoadFromGPU(false))
	{
		// memory is back, lets check if we need to resize
		uint val = m_FragmentStartIndices[window->size];
		if(val != 0)
		{
			printf("resize: %i\n", val);
		}
		m_FragmentList.AddSize(val);
	}
	*/
}

void RenderFDOIT::Resize(uint2 new_size)
{
	m_FragmentStartIndices.Resize(new_size);

	m_FragmentList.Resize(new_size.x * new_size.y * 32);
}

void RenderFDOIT::_layerDepth(const FDOITDepth& depth)
{
	m_CurrentDepth = depth;
}

FDOITDepth RenderFDOIT::_layerDepth() const
{
	return m_CurrentDepth;
}