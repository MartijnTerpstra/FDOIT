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
#include "Scene.h"
#include "Timings.h"

using namespace Demo;

#include "GPUStructs.h"

shared_ptr<Window> Renderer::_window() const
{
	return shared_ptr<Window>(m_Window);
}

shared_ptr<Camera> Renderer::_camera() const
{
	return m_Camera;
}

shared_ptr<Shader> Renderer::_defaultShader() const
{
	return m_DefShader;
}

float Renderer::_globalAmbient() const
{
	return Implementation::RenderBase::s_LightingBuffer.data.globalAmbient;
}

void Renderer::_globalAmbient(const float& ambient)
{
	Implementation::RenderBase::s_LightingBuffer.data.globalAmbient = ambient;
}

void Renderer::_renderMode(const RenderMode& mode)
{
	if(m_Mode != mode)
	{
		m_Mode = mode;
		m_RendererImpls[0] = CreateRenderMode(mode);
	}
}

RenderMode Renderer::_renderMode() const
{
	return m_Mode;
}

void Renderer::_comparisonRenderMode(const RenderMode& mode)
{
	if(m_CompMode != mode)
	{
		m_CompMode = mode;

		if(m_CompMode == -1)
		{
			m_RendererImpls[1] = null;
			Implementation::RenderBase::s_RTVs[0] = m_RTV;
			Implementation::RenderBase::s_RTVs[1] = m_RTV;
			Implementation::RenderBase::s_RTVs[2] = m_RTV;
		}
		else
		{
			errorCalculation = true;
			m_RendererImpls[1] = CreateRenderMode(mode, 1);

			if(Implementation::RenderBase::s_RTVs[1] == m_RTV)
			{
				com_ptr<ID3D11Texture2D> tex;
				com_ptr<ID3D11Resource> res;
				Implementation::RenderBase::s_RTVs[0]->GetResource(mst::initialize(res));
				res->QueryInterface<ID3D11Texture2D>(mst::initialize(tex));
				D3D11_TEXTURE2D_DESC desc;
				tex->GetDesc(&desc);
				desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;

				m_Device->CreateTexture2D(&desc, null, mst::initialize(tex));
				m_Device->CreateRenderTargetView(tex.get(), null, mst::initialize(Implementation::RenderBase::s_RTVs[0]));
				m_Device->CreateShaderResourceView(tex.get(), null, mst::initialize(Implementation::RenderBase::s_SRVs[0]));

				m_Device->CreateTexture2D(&desc, null, mst::initialize(tex));
				m_Device->CreateRenderTargetView(tex.get(), null, mst::initialize(Implementation::RenderBase::s_RTVs[1]));
				m_Device->CreateShaderResourceView(tex.get(), null, mst::initialize(Implementation::RenderBase::s_SRVs[1]));

				m_Device->CreateTexture2D(&desc, null, mst::initialize(tex));
				m_Device->CreateRenderTargetView(tex.get(), null, mst::initialize(Implementation::RenderBase::s_RTVs[2]));
				m_Device->CreateShaderResourceView(tex.get(), null, mst::initialize(Implementation::RenderBase::s_SRVs[2]));

				m_HQ = make_unique<Implementation::RenderHQ>(2, window);
			}
		}
	}
}

RenderMode Renderer::_comparisonRenderMode() const
{
	return m_CompMode;
}

bool Renderer::_debugMode() const
{
	return m_DebugMode;
}

void Renderer::_debugMode(const bool& mode)
{
	m_DebugMode = mode;
}

void Renderer::_errorCalculation(const bool& enabled)
{
	if(m_CalcError != enabled)
	{
		m_CalcError = enabled;
		if(m_CalcError)
		{
			Implementation::Timings::SetEnabled(false);

			TwBar* errorCalc = TwNewBar("Error calculation");

			TwDefine(" 'Error calculation' color='100 17 50'");
			TwDefine("'Error calculation' size='320 320' ");
			TwDefine("'Error calculation' position='16 352' ");

			TwDefine(" 'Error calculation' resizable=false ");
			TwDefine(" 'Error calculation' movable=false ");

			RecalculateRMSD();

			TwAddButton(errorCalc, "Recalculate RMSD", OnClickRecalculate, null, null);
			TwAddVarRO(errorCalc, "RMS deviation", TW_TYPE_FLOAT, &m_RMSD, null);

			TwEnumVal renderModesEnum[] = { {-1, "None"}, {0, "Fixed Depth OIT"}, {1, "Dual depth peeling"},
			{ 2, "Intel's Adaptive OIT" } , {3, "Stochastic Transparency"}, 
			{4, "Unsorted Alpha Blending"}, {5, "High Quality" }};

			TwType rmEnum = TwDefineEnum("CompRenderModes", renderModesEnum, extentof(renderModesEnum));

			m_CompMode = (RenderMode)-1;
			TwAddVarCB(errorCalc, "Compare with", rmEnum, OnSetCompRenderMode, OnGetCompRenderMode,
				null, null);


		}
		else
		{
			TwDeleteBar(TwGetBarByName("Error calculation"));
			comparisonRenderMode = (RenderMode)-1;
		}
	}
}

bool Renderer::_errorCalculation() const
{
	return m_CalcError;
}

float Renderer::_rootMeanSquareDeviation() const
{
	return m_RMSD;
}