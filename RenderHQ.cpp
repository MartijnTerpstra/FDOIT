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
#include "RenderHQ.h"
#include "Scene.h"
#include "Window.h"
#include "Camera.h"
#include "Timings.h"

#include "GPUStructs.h"

#include "ShaderHeaders\HQGeometryPS.h"
#include "ShaderHeaders\HQResolvePS.h"
#include "ShaderHeaders\CombineComparePS.h"

using namespace Demo;
using namespace Demo::Implementation;

RenderHQ::RenderHQ(uint RTVindex, const shared_ptr<Window>& window)
	: RenderBase(RTVindex)
{
	m_FragmentList.Init(s_Device, mst::make_flag(D3D11_BIND_SHADER_RESOURCE, D3D11_BIND_UNORDERED_ACCESS), GPUARR_USE_COUNTER);
	
	m_FragmentStartIndices.Init(s_Device, mst::make_flag(D3D11_BIND_SHADER_RESOURCE, D3D11_BIND_UNORDERED_ACCESS)
		, DXGI_FORMAT_R32_UINT, window->size);

	//m_FragmentStartIndices.Resize(window->width * window->height); // + 1 for the overhead counter

	m_FragmentList.Resize(window->width * window->height * 16);

	s_Device->CreatePixelShader(g_HQResolvePS, sizeof(g_HQResolvePS), null, mst::initialize(m_ResolvePS));
	s_Device->CreatePixelShader(g_HQGeometryPS, sizeof(g_HQGeometryPS), null, mst::initialize(m_GeometryPS));

	s_Device->CreatePixelShader(g_CombineComparePS, sizeof(g_CombineComparePS), null, mst::initialize(m_CombineComparePS));
}

RenderHQ::~RenderHQ()
{
}

void RenderHQ::Render(const matrix& view, const shared_ptr<Window>& window)
{
	m_FragmentStartIndices.ClearUAV(0xFFFFFFFF);

	ID3D11UnorderedAccessView* accessviews[2] =
	{
		m_FragmentStartIndices.GetUAV().get(),
		m_FragmentList.GetUAV().get()
	};
	UINT initCounters[2] = { 0,0 };
	s_Context->OMSetRenderTargetsAndUnorderedAccessViews(0, null, null, 0, 2,
		accessviews, initCounters);


	
	m_Buffer.data = m_FragmentList.GetCapacity();

	m_Buffer.Update(s_Context);

	m_Buffer.PSSetConstantBuffer(s_Context, 2);

	float blendFactor[]={1,1,1,1};
	s_Context->OMSetBlendState(null, blendFactor, -1);

	RenderMeshes(view, window, m_GeometryPS);



	// Pass 2 resolve

	s_Context->OMSetRenderTargets(1, &GetRTV(), null);


	m_FragmentStartIndices.PSSetShaderResource(0);
	m_FragmentList.PSSetShaderResource(1);

	s_Context->PSSetShader(m_ResolvePS.get(), null, 0);

	RenderQuad();

	ID3D11ShaderResourceView* nullviews[2] = {};
	s_Context->PSSetShaderResources(0, extentof(nullviews), nullviews);

}

void RenderHQ::Resize(uint2 new_size)
{
	m_FragmentStartIndices.Resize(new_size);

	m_FragmentList.Resize(new_size.x * new_size.y * 32);
}

void RenderHQ::RenderCompare()
{
	ID3D11ShaderResourceView* views[3] =
	{
		s_SRVs[0].get(),
		s_SRVs[1].get(),
		s_SRVs[2].get(),
	};

	s_Context->PSSetShaderResources(0, 3, views);

	s_Context->PSSetShader(m_CombineComparePS.get(), null, 0);

	RenderQuad();

	mst::zeromem(views);
	s_Context->PSSetShaderResources(0, 3, views);

}