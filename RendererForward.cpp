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
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Window.h"
#include "Camera.h"
#include "Light.h"
#include "Timings.h"

#include "GPUStructs.h"

using namespace Demo;

void Renderer::RenderForward(const shared_ptr<Window>& window)
{
	Implementation::Timings::BeginFrame();

	//Implementation::RenderBase::Clear();


	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT)window->m_Size.x;
	vp.Height = (FLOAT)window->m_Size.y;
	vp.MaxDepth = 1.0f;
	m_Context->RSSetViewports(1, &vp);

	//m_Context->OMSetRenderTargets(1, &m_RTV, m_DSV.get());


	const auto& meshes = Scene::Get().m_Meshes;

	//const matrix view = inverse(m_Camera->m_Matrix);

	const matrix view = m_Camera->m_Matrix.inverse;
	
	/*
	{ // upload lights

		m_DirLights.Clear();

		uint spot_light_offset = 0;
		uint point_light_offset = 0;
		uint num_point_lights = 0;
		uint num_spot_lights = 0;
		for(const auto& it : Scene::Get().m_Lights)
		{
			switch(it.first->m_Type)
			{
			case POINT_LIGHT:
				{
					const float3 position = (view * float4(it.second.position, 1)).xyz;
					Graphics::GPUPointLight light;
					light.position = position;
					light.radius = it.first->m_Radius;
					light.color = it.first->m_Color;
					light.intensity = it.first->m_Intensity;

					num_point_lights++;
				}
				break;
			case SPOT_LIGHT:
				{
					const float3 position = (view * float4(it.second.position, 1)).xyz;
					const float3 direction = -(view * float4(it.second[0].z, it.second[1].z, it.second[2].z, 0)).xyz;
					Graphics::GPUSpotLight light;
					light.position = position;
					light.direction = direction;
					light.cosAngle = it.first->m_CosIntensAngle;
					light.cosPenumbra = it.first->m_CosMaxAngle;
					light.color = it.first->m_Color;
					light.intensity = it.first->m_Intensity;

					num_spot_lights++;
				}
				break;
			case DIRECTIONAL_LIGHT:
				{
					const float3 position = (view * float4(it.second.position, 1)).xyz;
					const float3 direction = -(view * float4(it.second[0].z, it.second[1].z, it.second[2].z, 0)).xyz;
					Graphics::GPUDirectionalLight light;
					light.direction = direction;
					light.color = it.first->m_Color;
					light.intensity = it.first->m_Intensity;

					m_DirLights.PushBack(light);
				}
				break;
			default:
				// not implemented
				_MST_BREAK;
				break;
			}
		}
		m_LightingBuffer.data.globalAmbient = 0.0f;
		m_LightingBuffer.data.numPointLights = num_point_lights;
		m_LightingBuffer.data.numSpotLights = num_spot_lights;
		m_LightingBuffer.data.invDistancePerIntensity = 1.0f / RADIUS_PER_INTENSITY;
		m_LightingBuffer.Update(m_Context);
		
	}
	*/

	//m_LightingBuffer.AttachToPipeline(m_Context);
	
	//m_DirLights.PSSetShaderResource(0);

	Implementation::Timings::BeginQuery("Total time");

	m_RendererImpls[0]->Render(view, window);

	Implementation::Timings::EndQuery("Total time");

	if(m_RendererImpls[1])
	{
		m_RendererImpls[1]->Render(view, window);

		m_HQ->Render(view, window);

		m_Context->OMSetRenderTargets(1, &m_RTV, null);

		m_HQ->RenderCompare();
	}

	if(errorCalculation && m_RMSD == -1)
	{
		// calculate RMSD

		CalcRMSD(view, window);
	}

	Implementation::Timings::EndFrame();
}