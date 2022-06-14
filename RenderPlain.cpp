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
#include "RenderPlain.h"
#include "Scene.h"
#include "Window.h"
#include "Camera.h"

#include "GPUStructs.h"

using namespace Demo;
using namespace Demo::Implementation;

RenderPlain::RenderPlain(uint RTVindex, const shared_ptr<Window>& window)
	: RenderBase(RTVindex)
{
	D3D11_BLEND_DESC blendState;
	blendState.AlphaToCoverageEnable = FALSE;
	// If IndependentBlendEnable==FALSE, only the RenderTarget[0] members are used.
	blendState.IndependentBlendEnable = FALSE;
	

	// Back-to-front blending
	blendState.RenderTarget[0].BlendEnable = TRUE;
	blendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	s_Device->CreateBlendState(&blendState, mst::initialize(m_AlphaBlend));

}

RenderPlain::~RenderPlain()
{
	float blendFactor[] = {1,1,1,1};
	s_Context->OMSetBlendState(nullptr, blendFactor, 0xFFFFFFFF);
}

void RenderPlain::Render(const matrix& view, const shared_ptr<Window>& window)
{
	float blendFactor[] = {1,1,1,1};
	s_Context->OMSetBlendState(m_AlphaBlend.get(), blendFactor, 0xFFFFFFFF);
	//s_Context->OMSetBlendState(nullptr, blendFactor, 0xFFFFFFFF);

	s_Context->OMSetRenderTargets(1, &GetRTV(), nullptr);
	//s_Context->omse

	RenderMeshes(view, window);
}

void RenderPlain::Resize(uint2 new_size)
{
}