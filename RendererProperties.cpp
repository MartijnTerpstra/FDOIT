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

namespace {

void __stdcall OnSetCompRenderMode(const void* value, void* data)
{
	Renderer::Get().comparisonRenderMode(RenderMode(*(int32_t*)value));
}

void __stdcall OnGetCompRenderMode(void* value, void* data)
{
	*(int32_t*)value = (int32_t)Renderer::Get().comparisonRenderMode();
}

void __stdcall OnClickRecalculate(void* data)
{
	Renderer::Get().RecalculateRMSD();
}

}

shared_ptr<Window> Renderer::window() const
{
	return shared_ptr<Window>(m_Window);
}

shared_ptr<Camera> Renderer::camera() const
{
	return m_Camera;
}

shared_ptr<Shader> Renderer::defaultShader() const
{
	return m_DefShader;
}

float Renderer::globalAmbient() const
{
	return Implementation::RenderBase::s_LightingBuffer.data.globalAmbient;
}

void Renderer::globalAmbient(const float& ambient)
{
	Implementation::RenderBase::s_LightingBuffer.data.globalAmbient = ambient;
}

void Renderer::renderMode(const RenderMode& mode)
{
	if(m_Mode != mode)
	{
		m_Mode = mode;
		m_RendererImpls[0] = CreateRenderMode(mode);
	}
}

RenderMode Renderer::renderMode() const
{
	return m_Mode;
}

void Renderer::comparisonRenderMode(const RenderMode& mode)
{
	if(m_CompMode != mode)
	{
		m_CompMode = mode;

		if(m_CompMode == -1)
		{
			m_RendererImpls[1] = nullptr;
			Implementation::RenderBase::s_RTVs[0] = m_RTV;
			Implementation::RenderBase::s_RTVs[1] = m_RTV;
			Implementation::RenderBase::s_RTVs[2] = m_RTV;
		}
		else
		{
			errorCalculation(true);
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

				m_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));
				m_Device->CreateRenderTargetView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_RTVs[0]));
				m_Device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_SRVs[0]));

				m_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));
				m_Device->CreateRenderTargetView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_RTVs[1]));
				m_Device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_SRVs[1]));

				m_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));
				m_Device->CreateRenderTargetView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_RTVs[2]));
				m_Device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_SRVs[2]));

				m_HQ = make_unique<Implementation::RenderHQ>(2, window());
			}
		}
	}
}

RenderMode Renderer::comparisonRenderMode() const
{
	return m_CompMode;
}

bool Renderer::debugMode() const
{
	return m_DebugMode;
}

void Renderer::debugMode(const bool& mode)
{
	m_DebugMode = mode;
}

void Renderer::errorCalculation(const bool& enabled)
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

			TwAddButton(errorCalc, "Recalculate RMSD", OnClickRecalculate, nullptr, nullptr);
			TwAddVarRO(errorCalc, "RMS deviation", TW_TYPE_FLOAT, &m_RMSD, nullptr);

			TwEnumVal renderModesEnum[] = { {-1, "None"}, {0, "Fixed Depth OIT"}, {1, "Dual depth peeling"},
			{ 2, "Intel's Adaptive OIT" } , {3, "Stochastic Transparency"}, 
			{4, "Unsorted Alpha Blending"}, {5, "High Quality" }};

			TwType rmEnum = TwDefineEnum("CompRenderModes", renderModesEnum, std::extent_v<decltype(renderModesEnum)>);

			m_CompMode = (RenderMode)-1;
			TwAddVarCB(errorCalc, "Compare with", rmEnum, OnSetCompRenderMode, OnGetCompRenderMode,
				nullptr, nullptr);


		}
		else
		{
			TwDeleteBar(TwGetBarByName("Error calculation"));
			comparisonRenderMode((RenderMode)-1);
		}
	}
}

bool Renderer::errorCalculation() const
{
	return m_CalcError;
}

float Renderer::rootMeanSquareDeviation() const
{
	return m_RMSD;
}