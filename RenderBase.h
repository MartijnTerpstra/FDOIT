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

namespace Demo { namespace Implementation {

class RenderHQ;

class RenderBase
{
	friend class Renderer;
	friend class RenderHQ;
public:
	RenderBase(uint RTVindex);
	virtual ~RenderBase();

	virtual void Render(const matrix& view, const shared_ptr<Window>& window) = 0;

	virtual void Resize(uint2 new_size) {};

	void Clear();

protected:

	static void InitStatics(const com_ptr<ID3D11Device>& device);
	static void ReleaseStatics();
	static void RenderQuad();
	static void RenderMeshes(const matrix& view, const shared_ptr<Window>& window, com_ptr<ID3D11PixelShader> pixel = null);

	const com_ptr<ID3D11RenderTargetView>& GetRTV();

	TwBar* GetGUIBar();

private:
	uint m_RTVindex;

protected:

	static com_ptr<ID3D11DepthStencilView> s_DSV;
	static com_ptr<ID3D11Device> s_Device;
	static com_ptr<ID3D11DeviceContext> s_Context;

private:
	static com_ptr<ID3D11RenderTargetView> s_RTVs[3];
	static com_ptr<ID3D11ShaderResourceView> s_SRVs[3];
	static Graphics::ConstantBuffer<Graphics::GPULightingBuffer> s_LightingBuffer;
	static Graphics::ConstantBuffer<Graphics::GPUModelBuffer> s_ModelBuffer;
	static com_ptr<ID3D11VertexShader> s_VertexShader, s_QuadVS;
};

}; }; // namespace Demo::Implementation