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
#include "RenderStochastic.h"
#include "Scene.h"
#include "Window.h"
#include "Camera.h"
#include "GPUStructs.h"
#include "Timings.h"

#include <random>

// shaders
#include "ShaderHeaders\StochasticResolve1.h"
#include "ShaderHeaders\StochasticResolve2.h"
#include "ShaderHeaders\StochasticResolve3.h"
#include "ShaderHeaders\StochasticResolve4.h"
#include "ShaderHeaders\StochasticResolve5.h"
#include "ShaderHeaders\StochasticResolve6.h"
#include "ShaderHeaders\StochasticResolve7.h"
#include "ShaderHeaders\StochasticResolve8.h"
#include "ShaderHeaders\StochasticResolve9.h"
#include "ShaderHeaders\StochasticResolve10.h"
#include "ShaderHeaders\StochasticResolve11.h"
#include "ShaderHeaders\StochasticResolve12.h"
#include "ShaderHeaders\StochasticResolve13.h"
#include "ShaderHeaders\StochasticResolve14.h"
#include "ShaderHeaders\StochasticResolve15.h"
#include "ShaderHeaders\StochasticResolve16.h"

#include "ShaderHeaders\StochasticResolve1C.h"
#include "ShaderHeaders\StochasticResolve2C.h"
#include "ShaderHeaders\StochasticResolve3C.h"
#include "ShaderHeaders\StochasticResolve4C.h"
#include "ShaderHeaders\StochasticResolve5C.h"
#include "ShaderHeaders\StochasticResolve6C.h"
#include "ShaderHeaders\StochasticResolve7C.h"
#include "ShaderHeaders\StochasticResolve8C.h"
#include "ShaderHeaders\StochasticResolve9C.h"
#include "ShaderHeaders\StochasticResolve10C.h"
#include "ShaderHeaders\StochasticResolve11C.h"
#include "ShaderHeaders\StochasticResolve12C.h"
#include "ShaderHeaders\StochasticResolve13C.h"
#include "ShaderHeaders\StochasticResolve14C.h"
#include "ShaderHeaders\StochasticResolve15C.h"
#include "ShaderHeaders\StochasticResolve16C.h"

#include "ShaderHeaders\StochasticAlpha.h"
#include "ShaderHeaders\StochasticDepth.h"
#include "ShaderHeaders\StochasticColor.h"

using namespace Demo;
using namespace Demo::Implementation;

#define STOCHASTIC_MSAA_SAMPLES 8
#define RANDOM_SIZE 2048
#define ALPHA_VALUES 256

void __stdcall OnSetAlphaCorrection(__in const void* value, __inout_opt void* data)
{
	reinterpret_cast<RenderStochastic*>(data)->alphaCorrection = *(bool*)value;
}

void __stdcall OnGetAlphaCorrection(__inout void* value, __inout_opt void* data)
{
	*(bool*)value = reinterpret_cast<RenderStochastic*>(data)->alphaCorrection;
}


void __stdcall OnSetNumPasses(__in const void* value, __inout_opt void* data)
{
	reinterpret_cast<RenderStochastic*>(data)->numPasses = *(uint32*)value;
}

void __stdcall OnGetNumPasses(__inout void* value, __inout_opt void* data)
{
	*(uint32*)value = reinterpret_cast<RenderStochastic*>(data)->numPasses;
}


RenderStochastic::RenderStochastic(uint RTVindex, const shared_ptr<Window>& window)
	: RenderBase(RTVindex)
{

	m_Params.data.randMaskSizePowOf2MinusOne = RANDOM_SIZE - 1;
	m_Params.data.randMaskAlphaValues = ALPHA_VALUES;
	m_NumPasses = 4;
	m_AlphaCorrection = true;

	InitTextures(window->size);
	InitBlendStates();
	InitShaders();
	InitDSS();

	TwAddVarCB(GetGUIBar(), "Num passes", TW_TYPE_UINT32,
		OnSetNumPasses, OnGetNumPasses, this, null);

	TwAddVarCB(GetGUIBar(), "Alpha correction", TW_TYPE_BOOLCPP,
		OnSetAlphaCorrection, OnGetAlphaCorrection, this, null);
}

RenderStochastic::~RenderStochastic()
{
	TwRemoveVar(GetGUIBar(), "Num passes");
	TwRemoveVar(GetGUIBar(), "Alpha correction");
}

void RenderStochastic::Resize(uint2 newSize)
{
	InitTextures(newSize);
}

void RenderStochastic::Render(const matrix& view, const shared_ptr<Window>& window)
{
	Timings::BeginQuery("Transmittance");

	float blendFactor[4] = {1,1,1,1};
	
	float ClearColorBack[4] = { 0, 0, 0, 0 };
	s_Context->ClearRenderTargetView( m_BackBuffer.GetRTV().get(), ClearColorBack );

	m_Transmittance.ClearRTV(float4(1,1,1,1));
	//s_Context->ClearRenderTargetView( s_RTV.get(), blendFactor );
	
    // Update the constant buffer
	m_Params.Update(s_Context);
	//s_Context->UpdateSubresource(m_pParamsCB, 0, null, &CBData, 0, 0);


	m_Params.PSSetConstantBuffer(s_Context, 2);
	s_Context->OMSetDepthStencilState(m_NoDepth.get(), 0);

	s_Context->OMSetBlendState(m_TransmittanceBS.get(), blendFactor, -1);
	s_Context->OMSetRenderTargets(1, &m_Transmittance.GetRTV(), null);
	//s_Context->OMSetRenderTargets(1, &s_RTV, null);

	RenderMeshes(view, window, m_AlphaPS);

	Timings::EndQuery("Transmittance");

	Timings::BeginQuery("Geometry (depth + color)");

	for(uint layerID = 0; layerID < m_NumPasses; ++layerID)
	{
		Timings::BeginQuery("Depth");

		m_Params.data.randomOffset = layerID;
		m_Params.Update(s_Context);

		s_Context->ClearDepthStencilView(m_DSV.get(), D3D11_CLEAR_DEPTH, 1.0, 0);

		s_Context->OMSetRenderTargets(0, null, m_DSV.get());
		s_Context->OMSetBlendState(null, blendFactor, 0xffffffff);
		s_Context->OMSetDepthStencilState(m_DepthRW.get(), 0);
		s_Context->PSSetShaderResources(4, 1, &m_RandTex);

		RenderMeshes(view, window, m_DepthPS);

		Timings::EndQuery("Depth");

		Timings::BeginQuery("Color");

		float Zero[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		s_Context->ClearRenderTargetView(m_StochasticColor.GetRTV().get(), Zero);

		s_Context->OMSetRenderTargets(1, &m_StochasticColor.GetRTV(), m_DSV.get());
		s_Context->OMSetBlendState(m_AdditiveBS.get(), blendFactor, 0xffffffff);
		s_Context->OMSetDepthStencilState(m_DepthR.get(), 0);

		RenderMeshes(view, window, m_ColorPS);

		Timings::EndQuery("Color");

		UINT MipSlice = 0;
		UINT MipLevels = 1;
		UINT DstSubresource = D3D11CalcSubresource(MipSlice, layerID, MipLevels);
		s_Context->ResolveSubresource(m_Fragments.GetResource().get(), DstSubresource,
										m_StochasticColor.GetResource().get(), 0,
										DXGI_FORMAT_R16G16B16A16_FLOAT);
	}

	Timings::EndQuery("Geometry (depth + color)");

	Timings::BeginQuery("Resolve");

	s_Context->OMSetRenderTargets(1, &GetRTV(), null);
    s_Context->OMSetBlendState(null, blendFactor, 0xffffffff);

	s_Context->PSSetShader(m_ResolvePS[m_NumPasses-1][m_AlphaCorrection].get(), null, 0);

    ID3D11ShaderResourceView *pSRVs[3] =
    {
		m_Fragments.GetSRV().get(),
		m_Transmittance.GetSRV().get(),
		m_BackBuffer.GetSRV().get(),
    };
    s_Context->PSSetShaderResources(4, 3, pSRVs);

	RenderQuad();

	Timings::EndQuery("Resolve");

	mst::zeromem(pSRVs);
	s_Context->PSSetShaderResources(4, 3, pSRVs);


}

void RenderStochastic::InitRandTexture()
{
	if(m_RandTex == 0)
	{
		std::mt19937 rng;

		rng.seed((unsigned)1729);

		std::uniform_real_distribution<float> randFloat(0, 1);

		int numbers[STOCHASTIC_MSAA_SAMPLES];
		unsigned int *allmasks = new unsigned int[RANDOM_SIZE * (ALPHA_VALUES + 1)];

		for (int y = 0; y <= ALPHA_VALUES; y++) // Inclusive, we need alpha = 1.0
		{
			for (int x = 0; x < RANDOM_SIZE; x++)
			{
				// Initialize array
				for (int i = 0; i < STOCHASTIC_MSAA_SAMPLES; i++)
				{
					numbers[i] = i;
				}

				// Scramble!
				for (int i = 0; i < STOCHASTIC_MSAA_SAMPLES * 2; i++)
				{
					std::swap(numbers[rng() % STOCHASTIC_MSAA_SAMPLES], numbers[rng() % STOCHASTIC_MSAA_SAMPLES]);
				}

				// Create the mask
				unsigned int mask = 0;
				float nof_bits_to_set = (float(y) / float(ALPHA_VALUES)) * STOCHASTIC_MSAA_SAMPLES;
				for (int bit = 0; bit < int(nof_bits_to_set); bit++)
				{
					mask |= (1 << numbers[bit]);
				}
				float prob_of_last_bit = (nof_bits_to_set - floor(nof_bits_to_set));
				if (randFloat(rng) < prob_of_last_bit)
				{
					mask |= (1 << numbers[int(nof_bits_to_set)]);
				}

				allmasks[y * RANDOM_SIZE + x] = mask;
			}
		}

		D3D11_TEXTURE2D_DESC texDesc;
		texDesc.Width            = RANDOM_SIZE;
		texDesc.Height           = ALPHA_VALUES + 1;
		texDesc.MipLevels        = 1;
		texDesc.ArraySize        = 1;
		texDesc.Format           = DXGI_FORMAT_R32_UINT;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage            = D3D11_USAGE_IMMUTABLE;
		texDesc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags   = 0;
		texDesc.MiscFlags        = 0;

		D3D11_SUBRESOURCE_DATA srDesc;
		srDesc.pSysMem          = allmasks;
		srDesc.SysMemPitch      = texDesc.Width * sizeof(unsigned int);
		srDesc.SysMemSlicePitch = 0;

		com_ptr<ID3D11Texture2D> tex;
		s_Device->CreateTexture2D(&texDesc, &srDesc, mst::initialize(tex));

		s_Device->CreateShaderResourceView(tex.get(), null, mst::initialize(m_RandTex));

		delete[] allmasks;
	}
}

void RenderStochastic::InitTextures(uint2 size)
{
	InitRandTexture();
	InitDSV(size);

	mst::flag<D3D11_BIND_FLAG> bindFlags(D3D11_BIND_SHADER_RESOURCE, D3D11_BIND_RENDER_TARGET);

	m_BackBuffer.Init(s_Device, bindFlags, DXGI_FORMAT_R8G8B8A8_UNORM, size, STOCHASTIC_MSAA_SAMPLES);
	m_Transmittance.Init(s_Device, bindFlags, DXGI_FORMAT_R8_UNORM, size, STOCHASTIC_MSAA_SAMPLES);
	m_StochasticColor.Init(s_Device, bindFlags, DXGI_FORMAT_R16G16B16A16_FLOAT, size, STOCHASTIC_MSAA_SAMPLES);

	m_Fragments.Init(s_Device, bindFlags, DXGI_FORMAT_R16G16B16A16_FLOAT, STOCHASTIC_MAX_NUM_PASSES, size);
}

void RenderStochastic::InitBlendStates()
{
	D3D11_BLEND_DESC BlendStateDesc;
    BlendStateDesc.AlphaToCoverageEnable = FALSE;
    BlendStateDesc.IndependentBlendEnable = FALSE;
    for (int i = 0; i < 8; ++i)
    {
        BlendStateDesc.RenderTarget[i].BlendEnable = FALSE;
        BlendStateDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    }

    BlendStateDesc.RenderTarget[0].BlendEnable = TRUE;
    BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    // Create m_pAdditiveBlendingBS
    // dst.rgba += src.rgba

    BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
    BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	s_Device->CreateBlendState(&BlendStateDesc, mst::initialize(m_AdditiveBS));

    // Create m_pTransmittanceBS
    // dst.r *= (1.0 - src.r)

    BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
    BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
    BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    s_Device->CreateBlendState(&BlendStateDesc, mst::initialize(m_TransmittanceBS));
}

void RenderStochastic::InitShaders()
{
	s_Device->CreatePixelShader(g_StochasticAlpha, sizeof(g_StochasticAlpha), null, mst::initialize(m_AlphaPS));
	s_Device->CreatePixelShader(g_StochasticDepth, sizeof(g_StochasticDepth), null, mst::initialize(m_DepthPS));
	s_Device->CreatePixelShader(g_StochasticColor, sizeof(g_StochasticColor), null, mst::initialize(m_ColorPS));

	s_Device->CreatePixelShader(g_StochasticResolve1, sizeof(g_StochasticResolve1), null, mst::initialize(m_ResolvePS[0][0]));
	s_Device->CreatePixelShader(g_StochasticResolve2, sizeof(g_StochasticResolve2), null, mst::initialize(m_ResolvePS[1][0]));
	s_Device->CreatePixelShader(g_StochasticResolve3, sizeof(g_StochasticResolve3), null, mst::initialize(m_ResolvePS[2][0]));
	s_Device->CreatePixelShader(g_StochasticResolve4, sizeof(g_StochasticResolve4), null, mst::initialize(m_ResolvePS[3][0]));
	s_Device->CreatePixelShader(g_StochasticResolve5, sizeof(g_StochasticResolve5), null, mst::initialize(m_ResolvePS[4][0]));
	s_Device->CreatePixelShader(g_StochasticResolve6, sizeof(g_StochasticResolve6), null, mst::initialize(m_ResolvePS[5][0]));
	s_Device->CreatePixelShader(g_StochasticResolve7, sizeof(g_StochasticResolve7), null, mst::initialize(m_ResolvePS[6][0]));
	s_Device->CreatePixelShader(g_StochasticResolve8, sizeof(g_StochasticResolve8), null, mst::initialize(m_ResolvePS[7][0]));
	s_Device->CreatePixelShader(g_StochasticResolve9, sizeof(g_StochasticResolve9), null, mst::initialize(m_ResolvePS[8][0]));

	s_Device->CreatePixelShader(g_StochasticResolve10, sizeof(g_StochasticResolve10), null, mst::initialize(m_ResolvePS[9][0]));
	s_Device->CreatePixelShader(g_StochasticResolve11, sizeof(g_StochasticResolve11), null, mst::initialize(m_ResolvePS[10][0]));
	s_Device->CreatePixelShader(g_StochasticResolve12, sizeof(g_StochasticResolve12), null, mst::initialize(m_ResolvePS[11][0]));
	s_Device->CreatePixelShader(g_StochasticResolve13, sizeof(g_StochasticResolve13), null, mst::initialize(m_ResolvePS[12][0]));
	s_Device->CreatePixelShader(g_StochasticResolve14, sizeof(g_StochasticResolve14), null, mst::initialize(m_ResolvePS[13][0]));
	s_Device->CreatePixelShader(g_StochasticResolve15, sizeof(g_StochasticResolve15), null, mst::initialize(m_ResolvePS[14][0]));
	s_Device->CreatePixelShader(g_StochasticResolve16, sizeof(g_StochasticResolve16), null, mst::initialize(m_ResolvePS[15][0]));

	s_Device->CreatePixelShader(g_StochasticResolve1C, sizeof(g_StochasticResolve1C), null, mst::initialize(m_ResolvePS[0][1]));
	s_Device->CreatePixelShader(g_StochasticResolve2C, sizeof(g_StochasticResolve2C), null, mst::initialize(m_ResolvePS[1][1]));
	s_Device->CreatePixelShader(g_StochasticResolve3C, sizeof(g_StochasticResolve3C), null, mst::initialize(m_ResolvePS[2][1]));
	s_Device->CreatePixelShader(g_StochasticResolve4C, sizeof(g_StochasticResolve4C), null, mst::initialize(m_ResolvePS[3][1]));
	s_Device->CreatePixelShader(g_StochasticResolve5C, sizeof(g_StochasticResolve5C), null, mst::initialize(m_ResolvePS[4][1]));
	s_Device->CreatePixelShader(g_StochasticResolve6C, sizeof(g_StochasticResolve6C), null, mst::initialize(m_ResolvePS[5][1]));
	s_Device->CreatePixelShader(g_StochasticResolve7C, sizeof(g_StochasticResolve7C), null, mst::initialize(m_ResolvePS[6][1]));
	s_Device->CreatePixelShader(g_StochasticResolve8C, sizeof(g_StochasticResolve8C), null, mst::initialize(m_ResolvePS[7][1]));
	s_Device->CreatePixelShader(g_StochasticResolve9C, sizeof(g_StochasticResolve9C), null, mst::initialize(m_ResolvePS[8][1]));

	s_Device->CreatePixelShader(g_StochasticResolve10C, sizeof(g_StochasticResolve10C), null, mst::initialize(m_ResolvePS[9][1]));
	s_Device->CreatePixelShader(g_StochasticResolve11C, sizeof(g_StochasticResolve11C), null, mst::initialize(m_ResolvePS[10][1]));
	s_Device->CreatePixelShader(g_StochasticResolve12C, sizeof(g_StochasticResolve12C), null, mst::initialize(m_ResolvePS[11][1]));
	s_Device->CreatePixelShader(g_StochasticResolve13C, sizeof(g_StochasticResolve13C), null, mst::initialize(m_ResolvePS[12][1]));
	s_Device->CreatePixelShader(g_StochasticResolve14C, sizeof(g_StochasticResolve14C), null, mst::initialize(m_ResolvePS[13][1]));
	s_Device->CreatePixelShader(g_StochasticResolve15C, sizeof(g_StochasticResolve15C), null, mst::initialize(m_ResolvePS[14][1]));
	s_Device->CreatePixelShader(g_StochasticResolve16C, sizeof(g_StochasticResolve16C), null, mst::initialize(m_ResolvePS[15][1]));
}

void RenderStochastic::InitDSV(uint2 size)
{
	D3D11_TEXTURE2D_DESC desc = {};

	desc.ArraySize = 1;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.Width = size.x;
	desc.Height = size.y;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = STOCHASTIC_MSAA_SAMPLES;
	desc.Usage = D3D11_USAGE_DEFAULT;

	com_ptr<ID3D11Texture2D> tex;
	s_Device->CreateTexture2D(&desc, null, mst::initialize(tex));

	s_Device->CreateDepthStencilView(tex.get(), null, mst::initialize(m_DSV));
}

void RenderStochastic::InitDSS()
{
	D3D11_DEPTH_STENCIL_DESC depthstencilState;
    depthstencilState.DepthEnable = TRUE;
    depthstencilState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthstencilState.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    depthstencilState.StencilEnable = FALSE;
	s_Device->CreateDepthStencilState( &depthstencilState, mst::initialize(m_DepthRW) );

    depthstencilState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    depthstencilState.DepthEnable = FALSE;
    depthstencilState.StencilEnable = FALSE;
	s_Device->CreateDepthStencilState( &depthstencilState, mst::initialize(m_NoDepth) );

    depthstencilState.DepthEnable = TRUE;
    depthstencilState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    depthstencilState.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    depthstencilState.StencilEnable = FALSE;
	s_Device->CreateDepthStencilState( &depthstencilState,mst::initialize(m_DepthR) );
}

void RenderStochastic::_numPasses(const uint& passes)
{
	m_NumPasses = max(1U, min(STOCHASTIC_MAX_NUM_PASSES, passes));
}

uint RenderStochastic::_numPasses() const
{
	return m_NumPasses;
}

void RenderStochastic::_alphaCorrection(const bool& correction)
{
	m_AlphaCorrection = correction;
}

bool RenderStochastic::_alphaCorrection() const
{
	return m_AlphaCorrection;
}