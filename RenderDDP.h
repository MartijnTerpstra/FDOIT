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

class RenderDDP : public RenderBase
{
public:
	RenderDDP(uint RTVindex, const shared_ptr<Window>& window);
	~RenderDDP();

	void Render(const matrix& view, const shared_ptr<Window>& window) final override;
	void Resize(uint2 new_size) final override;

	uint numLayers() const; void numLayers(const uint& value);

private:
	void CreateTextures(uint2 size);
	void CreateStates();

private:
	com_ptr<ID3D11PixelShader> m_PeelPass, m_InitPass, m_MergePass;
	com_ptr<ID3D11ShaderResourceView> m_DepthsSRV[2], m_FrontSRV;
	com_ptr<ID3D11RenderTargetView> m_DepthsRTV[2], m_FrontRTV;
	com_ptr<ID3D11BlendState> m_MaxBlend, m_PeelBlend, m_FinalBlend;
	com_ptr<ID3D11DepthStencilState> m_NoDSS;
	uint m_NumPeelingLayers;
};

}; }; // namespace Demo::Implementation