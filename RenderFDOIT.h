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

enum FDOITDepth
{
	FDOIT_DEPTH_4,
	FDOIT_DEPTH_8,
	FDOIT_DEPTH_16,
	FDOIT_DEPTH_32,

	FDOIT_NUM_DEPTHS
};

class RenderFDOIT : public RenderBase
{
public:
	RenderFDOIT(uint RTVindex, const shared_ptr<Window>& window);
	~RenderFDOIT();

	void Render(const matrix& view, const shared_ptr<Window>& window) final override;
	void Resize(uint2 new_size) final override;

	FDOITDepth layerDepth() const; void layerDepth(const FDOITDepth& value);

private:
	Graphics::ConstantBuffer<Graphics::GPUFDOITBuffer> m_OITBuffer;
	Texture2D m_FragmentStartIndices;
	GPUarray<Graphics::GPUFDOITFragment> m_FragmentList;
	FDOITDepth m_CurrentDepth;
	com_ptr<ID3D11PixelShader> m_ResolvePS[4], m_GeometryPS;
};

}; }; // namespace Demo::Implementation