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

#pragma once

namespace Demo { 
namespace Implementation {

#define STOCHASTIC_MAX_NUM_PASSES 16U

class RenderStochastic : public RenderBase
{
public:
	RenderStochastic(uint RTVindex, const shared_ptr<Window>& window);
	~RenderStochastic();

	void Render(const matrix& view, const shared_ptr<Window>& window) final override;
	void Resize(uint2 new_size) final override;

	uint numPasses() const; void numPasses(const uint& value);

	bool alphaCorrection() const; void alphaCorrection(const bool& value);

private:

	void InitRandTexture();
	void InitTextures(uint2 size);
	void InitBlendStates();
	void InitShaders();
	void InitDSS();
	void InitDSV(uint2 size);

private:

	struct Params
	{
		uint randMaskSizePowOf2MinusOne;
		uint randMaskAlphaValues;
		uint randomOffset;
		uint pad;
	};

	Graphics::ConstantBuffer<Params> m_Params;
	Texture2D m_BackBuffer, m_Transmittance, m_StochasticColor;
	com_ptr<ID3D11BlendState> m_TransmittanceBS, m_AdditiveBS;
	com_ptr<ID3D11DepthStencilState> m_NoDepth, m_DepthR, m_DepthRW;
	Texture2DArray m_Fragments;
	com_ptr<ID3D11DepthStencilView> m_DSV;
	com_ptr<ID3D11ShaderResourceView> m_RandTex;
	com_ptr<ID3D11PixelShader> m_DepthPS, m_AlphaPS, m_ColorPS, m_ResolvePS[STOCHASTIC_MAX_NUM_PASSES][2];
	uint m_NumPasses;
	bool m_AlphaCorrection;
};

}; // namespace Implementation
}; // namespace Demo