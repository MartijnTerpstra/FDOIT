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
#include "RenderAOIT.h"
#include "Scene.h"
#include "Window.h"
#include "Camera.h"
#include "Timings.h"

#include "GPUStructs.h"

// shaders
#include "ShaderHeaders\AOITGeometryPS.h"
#include "ShaderHeaders\AOITResolve4.h"
#include "ShaderHeaders\AOITResolve8.h"
#include "ShaderHeaders\AOITResolve16.h"
#include "ShaderHeaders\AOITResolve32.h"

#include "ShaderHeaders\AOITResolve4C.h"
#include "ShaderHeaders\AOITResolve8C.h"
#include "ShaderHeaders\AOITResolve16C.h"
#include "ShaderHeaders\AOITResolve32C.h"

using namespace Demo;
using namespace Demo::Implementation;

#define AOIT_NODE_COUNT 16

void __stdcall OnSetDontCompress(__in const void* value, __inout_opt void* data)
{
	reinterpret_cast<RenderAOIT*>(data)->dontCompress(*(bool*)value);
}

void __stdcall OnGetDontCompress(__inout void* value, __inout_opt void* data)
{
	*(bool*)value = reinterpret_cast<RenderAOIT*>(data)->dontCompress();
}


void __stdcall OnSetNodeCount(__in const void* value, __inout_opt void* data)
{
	reinterpret_cast<RenderAOIT*>(data)->nodeCount(AOITNodeCount(*(uint32_t*)value));
}

void __stdcall OnGetNodeCount(__inout void* value, __inout_opt void* data)
{
	*(uint32_t*)value = reinterpret_cast<RenderAOIT*>(data)->nodeCount();
}

RenderAOIT::RenderAOIT(uint RTVindex, const shared_ptr<Window>& window)
	: RenderBase(RTVindex)
{
	m_NodeCount = AOIT_NODE_COUNT_16;
	m_DontCompress = true;

	m_FragmentList.Init(s_Device, mst::make_flag(D3D11_BIND_SHADER_RESOURCE, D3D11_BIND_UNORDERED_ACCESS), GPUARR_USE_COUNTER);
	m_FragmentStartIndices.Init(s_Device, mst::make_flag(D3D11_BIND_SHADER_RESOURCE, D3D11_BIND_UNORDERED_ACCESS), DXGI_FORMAT_R32_UINT
		, window->size());
	
	Resize(window->size());

	s_Device->CreatePixelShader(g_AOITGeometryPS, sizeof(g_AOITGeometryPS), nullptr, mst::initialize(m_GeometryPS));
	s_Device->CreatePixelShader(g_AOITResolve4, sizeof(g_AOITResolve4), nullptr, mst::initialize(m_ResolvePS[0][0]));
	s_Device->CreatePixelShader(g_AOITResolve8, sizeof(g_AOITResolve8), nullptr, mst::initialize(m_ResolvePS[1][0]));
	s_Device->CreatePixelShader(g_AOITResolve16, sizeof(g_AOITResolve16), nullptr, mst::initialize(m_ResolvePS[2][0]));
	s_Device->CreatePixelShader(g_AOITResolve32, sizeof(g_AOITResolve32), nullptr, mst::initialize(m_ResolvePS[3][0]));

	s_Device->CreatePixelShader(g_AOITResolve4C, sizeof(g_AOITResolve4C), nullptr, mst::initialize(m_ResolvePS[0][1]));
	s_Device->CreatePixelShader(g_AOITResolve8C, sizeof(g_AOITResolve8C), nullptr, mst::initialize(m_ResolvePS[1][1]));
	s_Device->CreatePixelShader(g_AOITResolve16C, sizeof(g_AOITResolve16C), nullptr, mst::initialize(m_ResolvePS[2][1]));
	s_Device->CreatePixelShader(g_AOITResolve32C, sizeof(g_AOITResolve32C), nullptr, mst::initialize(m_ResolvePS[3][1]));

	std::array renderModesEnum = { TwEnumVal{AOIT_NODE_COUNT_4, "4"}, TwEnumVal{AOIT_NODE_COUNT_8, "8"},
									TwEnumVal{AOIT_NODE_COUNT_16, "16"}, TwEnumVal{AOIT_NODE_COUNT_32, "32" } };

	TwType rmEnum = TwDefineEnum("AOIT node count", renderModesEnum.data(), renderModesEnum.size());

	TwAddVarCB(GetGUIBar(), "Node count", rmEnum, 
		OnSetNodeCount, OnGetNodeCount, this, nullptr);

	TwAddVarCB(GetGUIBar(), "Don't compress first half", TW_TYPE_BOOLCPP, 
		OnSetDontCompress, OnGetDontCompress, this, nullptr);
}

RenderAOIT::~RenderAOIT()
{
	TwRemoveVar(GetGUIBar(), "Node count");
	TwRemoveVar(GetGUIBar(), "Don't compress first half");
}

void RenderAOIT::Render(const matrix& view, const shared_ptr<Window>& window)
{
	//m_FragmentStartIndices.Fill(0xFFFFFFFF);

	Timings::BeginQuery("Fill list");

	m_FragmentStartIndices.ClearUAV(0);

	ID3D11UnorderedAccessView* accessviews[2] =
	{
		m_FragmentStartIndices.GetUAV().get(),
		m_FragmentList.GetUAV().get()
	};
	UINT initCounters[2] = { 0,0 };
	s_Context->OMSetRenderTargetsAndUnorderedAccessViews(0, nullptr, nullptr, 0, 2,
		accessviews, initCounters);

	m_MaxListCount.PSSetConstantBuffer(s_Context, 2);

	RenderMeshes(view, window, m_GeometryPS);

	Timings::EndQuery("Fill list");

	Timings::BeginQuery("Resolve list");

	s_Context->OMSetRenderTargets(1, &GetRTV(), nullptr);


	m_FragmentStartIndices.PSSetShaderResource(0);
	m_FragmentList.PSSetShaderResource(1);

	s_Context->PSSetShader(m_ResolvePS[m_NodeCount][m_DontCompress].get(), nullptr, 0);

	RenderQuad();

	Timings::EndQuery("Resolve list");

	std::array<ID3D11ShaderResourceView*, 2> nullviews = {};
	s_Context->PSSetShaderResources(0, nullviews.size(), nullviews.data());
}

void RenderAOIT::Resize(uint2 newSize)
{
	uint pixels = newSize.x * newSize.y;

	m_FragmentStartIndices.Resize(newSize);

	pixels *= AOIT_NODE_COUNT;

	m_FragmentList.Resize(pixels);
	m_MaxListCount.data = pixels;

	m_MaxListCount.Update(s_Context);
}

void RenderAOIT::nodeCount(const AOITNodeCount& count)
{
	m_NodeCount = count;
}

AOITNodeCount RenderAOIT::nodeCount() const
{
	return m_NodeCount;
}

void RenderAOIT::dontCompress(const bool& compress)
{
	m_DontCompress = compress;
}

bool RenderAOIT::dontCompress() const
{
	return m_DontCompress;
}