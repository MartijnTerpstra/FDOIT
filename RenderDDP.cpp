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
#include "RenderDDP.h"
#include "Scene.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Window.h"
#include "Camera.h"
#include "Light.h"
#include "Timings.h"

#include "GPUStructs.h"

#include "ShaderHeaders\DDPInitPS.h"
#include "ShaderHeaders\DDPMergePS.h"
#include "ShaderHeaders\DDPPeelingPS.h"

/*
	NVidia's dual depth peeling technique
	this is mostly a direct copy of their dual depth peeling code
	http://developer.download.nvidia.com/SDK/10/opengl/src/dual_depth_peeling/doc/DualDepthPeeling.pdf

// Copyright (c) 2011 NVIDIA Corporation. All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, NONINFRINGEMENT,IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA 
// OR ITS SUPPLIERS BE  LIABLE  FOR  ANY  DIRECT, SPECIAL,  INCIDENTAL,  INDIRECT,  OR  
// CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS 
// OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY 
// OTHER PECUNIARY LOSS) ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, 
// EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
// Please direct any bugs or questions to SDKFeedback@nvidia.com
*/

using namespace Demo;
using namespace Demo::Implementation;

#define MAX_NUM_PEELING_LAYERS 32U

void __stdcall OnSetPeelingLayers(__in const void* value, __inout_opt void* data)
{
	reinterpret_cast<RenderDDP*>(data)->numLayers(*(uint32_t*)value);
}

void __stdcall OnGetPeelingLayers(__inout void* value, __inout_opt void* data)
{
	*(uint32_t*)value = reinterpret_cast<RenderDDP*>(data)->numLayers();
}

RenderDDP::RenderDDP(uint RTVindex, const shared_ptr<Window>& window)
	: RenderBase(RTVindex)
{
	m_NumPeelingLayers = 4;

	s_Device->CreatePixelShader(g_DDPInitPS, sizeof(g_DDPInitPS), nullptr, mst::initialize(m_InitPass));
	s_Device->CreatePixelShader(g_DDPMergePS, sizeof(g_DDPMergePS), nullptr, mst::initialize(m_MergePass));
	s_Device->CreatePixelShader(g_DDPPeelingPS, sizeof(g_DDPPeelingPS), nullptr, mst::initialize(m_PeelPass));

	CreateTextures(window->size());
	CreateStates();

	TwAddVarCB(GetGUIBar(), "Num peeling layers", TW_TYPE_UINT32,
		OnSetPeelingLayers, OnGetPeelingLayers, this, nullptr);
}

RenderDDP::~RenderDDP()
{
	float blendFactor[] = {1,1,1,1};
	s_Context->OMSetBlendState(nullptr, blendFactor, 0xFFFFFFFF);

	TwRemoveVar(GetGUIBar(), "Num peeling layers");
}

void RenderDDP::Resize(uint2 new_size)
{
	CreateTextures(new_size);
}

void RenderDDP::Render(const matrix& view, const shared_ptr<Window>& window)
{
	Implementation::Timings::BeginQuery("Init");
	float resetFront[4] = { 0, 0, 0, 1 };
	s_Context->ClearRenderTargetView(m_FrontRTV.get(), resetFront);

	float resetBack[4] = { 0, 0, 0, 1 };
	s_Context->ClearRenderTargetView(GetRTV().get(), resetBack);

	float resetDepth[4] = { -1, -1, 0, 0 };
	s_Context->ClearRenderTargetView(m_DepthsRTV[0].get(), resetDepth);

	float blendFactor[4] = { 1,1,1,1 };

	s_Context->OMSetBlendState(m_MaxBlend.get(), blendFactor, 0xFFFFFFFF);
	s_Context->OMSetDepthStencilState(m_NoDSS.get(), 0);

	s_Context->OMSetRenderTargets(1, &m_DepthsRTV[0], nullptr);

	RenderMeshes(view, window, m_InitPass);

	Implementation::Timings::EndQuery("Init");

	Implementation::Timings::BeginQuery("Peeling");

	uint currId = 0;
	for(uint peelingLayer = 1; peelingLayer <= m_NumPeelingLayers; ++peelingLayer)
	{
		currId = peelingLayer % 2;
        UINT prevId = 1 - currId;

		s_Context->ClearRenderTargetView( m_DepthsRTV[currId].get(), resetDepth );

        ID3D11RenderTargetView *MRTs[3] = {
            m_DepthsRTV[currId].get(),
            m_FrontRTV.get(),
			GetRTV().get(),
        };
		s_Context->OMSetRenderTargets(3, MRTs, nullptr);

		s_Context->PSSetShaderResources(3, 1, &m_DepthsSRV[prevId]);
		s_Context->OMSetBlendState( m_PeelBlend.get(), blendFactor, 0xffffffff );

        RenderMeshes(view, window, m_PeelPass);

		ID3D11ShaderResourceView* nullview = nullptr;
		s_Context->PSSetShaderResources(3, 1, &nullview);
	}

	Implementation::Timings::EndQuery("Peeling");
	
	ID3D11ShaderResourceView *pSRVs[3] = {};
	s_Context->PSSetShaderResources(0, 3, pSRVs);
	
	Implementation::Timings::BeginQuery("Merge");
	
	s_Context->PSSetShader(m_MergePass.get(), nullptr, 0);
	s_Context->OMSetRenderTargets(1, &GetRTV(), nullptr);
	s_Context->PSSetShaderResources(0, 1, &m_FrontSRV);
	s_Context->OMSetBlendState( m_FinalBlend.get(), blendFactor, 0xffffffff );
	
	RenderQuad();
	
	s_Context->OMSetBlendState( nullptr, blendFactor, 0xffffffff );
	s_Context->OMSetDepthStencilState(nullptr, 0);

	Implementation::Timings::EndQuery("Merge");
}

void RenderDDP::CreateTextures(uint2 size)
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.ArraySize = 1;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	desc.Width = size.x;
	desc.Height = size.y;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;

	desc.Format = DXGI_FORMAT_R32G32_FLOAT;
	com_ptr<ID3D11Texture2D> tex;
	s_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));
	s_Device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(m_DepthsSRV[0]));
	s_Device->CreateRenderTargetView(tex.get(), nullptr, mst::initialize(m_DepthsRTV[0]));
	s_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));
	s_Device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(m_DepthsSRV[1]));
	s_Device->CreateRenderTargetView(tex.get(), nullptr, mst::initialize(m_DepthsRTV[1]));

	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	s_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));
	s_Device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(m_FrontSRV));
	s_Device->CreateRenderTargetView(tex.get(), nullptr, mst::initialize(m_FrontRTV));
}

void RenderDDP::CreateStates()
{
	D3D11_BLEND_DESC blendState;
	blendState.AlphaToCoverageEnable = FALSE;
	// If IndependentBlendEnable==FALSE, only the RenderTarget[0] members are used.
	blendState.IndependentBlendEnable = TRUE;
	for (int i = 0; i < 3; ++i)
	{
		blendState.RenderTarget[i].BlendEnable = TRUE;
		blendState.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	for (int i = 3; i < 8; ++i)
	{
		blendState.RenderTarget[i].BlendEnable = FALSE;
		blendState.RenderTarget[i].RenderTargetWriteMask = 0;
	}

	// Max blending
	blendState.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
	blendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;

	// Front-to-back blending
	blendState.RenderTarget[1].SrcBlend = D3D11_BLEND_DEST_ALPHA;
	blendState.RenderTarget[1].DestBlend = D3D11_BLEND_ONE;
	blendState.RenderTarget[1].BlendOp = D3D11_BLEND_OP_ADD;
	blendState.RenderTarget[1].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendState.RenderTarget[1].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendState.RenderTarget[1].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	// Back-to-front blending
	blendState.RenderTarget[2].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendState.RenderTarget[2].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendState.RenderTarget[2].BlendOp = D3D11_BLEND_OP_ADD;
	blendState.RenderTarget[2].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendState.RenderTarget[2].DestBlendAlpha = D3D11_BLEND_ONE;
	blendState.RenderTarget[2].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	s_Device->CreateBlendState( &blendState, mst::initialize(m_PeelBlend));

	// Max blending

	for (int i = 0; i < 3; ++i)
	{
		blendState.RenderTarget[i].BlendEnable = TRUE;
		blendState.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		blendState.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
		blendState.RenderTarget[i].DestBlend = D3D11_BLEND_ONE;
		blendState.RenderTarget[i].BlendOp = D3D11_BLEND_OP_MAX;
		blendState.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendState.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
		blendState.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	}
	s_Device->CreateBlendState( &blendState, mst::initialize(m_MaxBlend));

	{
		D3D11_BLEND_DESC desc;
		mst::zeromem(desc);
		desc.AlphaToCoverageEnable = FALSE;
		desc.IndependentBlendEnable = FALSE;
		desc.RenderTarget[0].BlendEnable = TRUE;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].RenderTargetWriteMask = 0xF;

		s_Device->CreateBlendState(&desc, mst::initialize(m_FinalBlend));
	}

	D3D11_DEPTH_STENCIL_DESC desc = {};

	s_Device->CreateDepthStencilState(&desc, mst::initialize(m_NoDSS));
}

void RenderDDP::numLayers(const uint& passes)
{
	m_NumPeelingLayers = max(1U, min(passes, MAX_NUM_PEELING_LAYERS));
}

uint RenderDDP::numLayers() const
{
	return m_NumPeelingLayers;
}