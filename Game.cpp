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

#include "IGame.h"
#include "Game.h"

#include "Scene.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Renderer.h"
#include "Camera.h"
#include "Light.h"
#include "Window.h"
#include "Particles.h"

using namespace Demo;

extern float g_TimeStep;

std::string ToString(uint val)
{
	char str[32];
	sprintf_s(str, "%i", val);
	return str;
}

float Random(float minim, float maxim)
{
	return rand() / (float)RAND_MAX * (maxim - minim) + minim;
}

shared_ptr<IGame> CreateGame()
{
	return make_shared<Game>();
}

void Game::Init()
{
	WTRACE;
	m_MouseActive = false;
	m_RenderLightVolumes = false;

	printf("initializing...\n");
	/*
	std::vector<Vertex> vertices(3);
	vertices[0].position = float3( 0, 1, 0);
	vertices[1].position = float3( 1,-1, 0);
	vertices[2].position = float3(-1,-1, 0);
	std::vector<uint32_t> indices(3);
	indices[0]=0;
	indices[1]=1;
	indices[2]=2;
	std::vector<SubMesh> sub_meshes(1);
	sub_meshes[0].num_indices = 3;
	sub_meshes[0].material = Material::Create("material", Renderer::Get().default_shader);

	auto mesh = Mesh::Create("Tri", vertices, indices, sub_meshes);
	*/

	shared_ptr<Mesh> mesh = nullptr;

	while(mesh == nullptr)
	{
		try
		{
			mesh = Mesh::Create("Sponza");
		}
		catch(std::exception error)
		{
			printf("%s\n", error.what());
			system("pause");
			mesh = nullptr;
		}
	}

	Scene::Get().AddMesh(mesh, matrix::identity);

	// create lights
	{
#define NUM_LIGHTS 512

		const std::array random_colors
		{
			float3(1,0,0),
			float3(0,1,0),
			float3(0,0,1),
			float3(0,1,1),
			float3(1,0,1),
			float3(1,1,0),
		};
		Scene::Get().AddLight(Light::Create("Test Light", 4, random_colors[rand() % random_colors.size()], SPOT_LIGHT),
				float3(0,200,0));
		for(uint i = 0; i < NUM_LIGHTS; ++i)
		{
			LightType type = (LightType)(1 + rand() % 2);
			Scene::Get().AddLight(Light::Create("Light" + ToString(i), type == SPOT_LIGHT ? 4.0f : 2.0f, random_colors[rand() % random_colors.size()], type),
				matrix(float3(Random(-1300, 1300), Random(0, 250), Random(-250, 250))).rotated_x(Random(0, 360.0f)).rotated_y(Random(-90,90)));
		}

#undef NUM_LIGHTS

		Scene::Get().AddLight(Light::Create("Dir light", 1, float3(1,1,1), DIRECTIONAL_LIGHT),
			matrix(float3(0,0,0)).rotated_x(PI/4).rotated_y(PI/4));
	}

	Scene::Get().AddMesh(Particles::Create("Parts"), matrix::identity);

	// init camera

	Scene::Get().camera()->position(float3(100, 150, 0));
	Scene::Get().camera()->eulerAngles(float3(0, -90, 0));

	Renderer::Get().globalAmbient(0.1f);

	printf("done initializing.\n");
	

	
}

void Game::Update()
{
	UpdateInput();
}

void Game::Exit()
{
}

void Game::UpdateInput()
{
	if(!Renderer::Get().window()->active())
	{
		return;
	}

	auto camera =  Renderer::Get().camera();

	float speed = 40.0f;

	if(Common::IsKeyDown(VK_LSHIFT))
	{
		speed *= 6;
	}

	float3 angles = camera->eulerAngles();

	if(Common::IsKeyDown('W'))
	{
		camera->position(camera->position() + camera->forwardDirection() * speed * g_TimeStep);
	}
	if(Common::IsKeyDown('S'))
	{
		camera->position(camera->position() + camera->backwardDirection() * 40.0f * g_TimeStep);
	}
	if(Common::IsKeyDown('A'))
	{
		camera->position(camera->position() + camera->leftDirection() * 40.0f * g_TimeStep);
	}
	if(Common::IsKeyDown('D'))
	{
		camera->position(camera->position() + camera->rightDirection() * 40.0f * g_TimeStep);
	}
	if(Common::IsKeyDown('Q'))
	{
		camera->position(camera->position() + camera->downDirection() * 40.0f * g_TimeStep);
	}
	if(Common::IsKeyDown('E'))
	{
		camera->position(camera->position() + camera->upDirection() * 40.0f * g_TimeStep);
	}
	Renderer::Get().camera()->eulerAngles(angles);

	float3 light_pos = Scene::Get().lightMatrix(0).get_position();

	if(Common::IsKeyDown(VK_RETURN))
	{
		light_pos.y += g_TimeStep * 100.0f;
	}
	if(Common::IsKeyDown(VK_RSHIFT))
	{
		light_pos.y -= g_TimeStep * 100.0f;
	}
	if(Common::IsKeyDown(VK_UP))
	{
		light_pos.x -= g_TimeStep * 100.0f;
	}
	if(Common::IsKeyDown(VK_DOWN))
	{
		light_pos.x += g_TimeStep * 100.0f;
	}

	if(Common::IsKeyDown(VK_RIGHT))
	{
		light_pos.z += g_TimeStep * 100.0f;
	}
	if(Common::IsKeyDown(VK_LEFT))
	{
		light_pos.z -= g_TimeStep * 100.0f;
	}

	Scene::Get().lightMatrix(0, light_pos);

	if(m_MouseActive)
	{
		POINT p;
		GetCursorPos(&p);

		p.x -= GetSystemMetrics(SM_CXSCREEN) / 2;
		p.y -= GetSystemMetrics(SM_CYSCREEN) / 2;

		float3 angles = Scene::Get().camera()->eulerAngles();

		angles.x += p.y * 0.2f;
		angles.y += p.x * 0.2f;

		Scene::Get().camera()->eulerAngles(angles);

		SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
	}

	if(m_RenderLightVolumes)
	{
		uint light_idx = 0;
		for(uint i = 0; i < Scene::Get().meshCount(); ++i)
		{
			shared_ptr<Mesh> mesh = Scene::Get().mesh(i);

			if(mesh->name() == "cone" || mesh->name() == "sphere")
			{
				matrix mat = Scene::Get().lightMatrix(light_idx);
				auto l = Scene::Get().light(light_idx);
				switch(l->type())
				{
				case SPOT_LIGHT:
					mat.scale(float3(l->areaOfInflunce() * sin((l->coneAngle() + l->penumbraAngle()) * PI / 180),
						l->areaOfInflunce() * sin((l->coneAngle() + l->penumbraAngle()) * PI / 180), l->areaOfInflunce()));
					break;
				case POINT_LIGHT:
					mat.scale(l->areaOfInflunce());
					break;
				}

				Scene::Get().meshMatrix(i, mat);
				light_idx++;
			}
		}
	}
}

void Game::OnKeyDown(int keycode, bool repeating)
{
	static std::vector<std::pair<float3,float3>> cameraPositions;

	if(cameraPositions.empty())
	{
		std::ifstream inf("cameraPositions", std::ios::binary);
		uint count = cameraPositions.size();
		inf.read((char*)&count, sizeof(count));
		for(uint i = 0; i < count; ++i)
		{
			std::pair<float3, float3> p;
			inf.read((char*)p.first.data(), sizeof(float3));
			inf.read((char*)p.second.data(), sizeof(float3));
			cameraPositions.push_back(p);
		}
	}

	switch(keycode)
	{
	case 'V':
		if(!repeating)
		{
			m_MouseActive = !m_MouseActive;
			if(m_MouseActive)
			{
				ShowCursor(FALSE);
				SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
			}
			else
			{
				ShowCursor(TRUE);
			}
		}

		break;

	case 'P':
		Renderer::Get().CreateTestReport();
		exit(0);
		break;

	case '1':
		Renderer::Get().camera()->position(cameraPositions[0].first);
		Renderer::Get().camera()->eulerAngles(cameraPositions[0].second);
		break;
		
	case '2':
		Renderer::Get().camera()->position(cameraPositions[1].first);
		Renderer::Get().camera()->eulerAngles(cameraPositions[1].second);
		break;
		
	case '3':
		Renderer::Get().camera()->position(cameraPositions[2].first);
		Renderer::Get().camera()->eulerAngles(cameraPositions[2].second);
		break;
		
	case '4':
		Renderer::Get().camera()->position(cameraPositions[3].first);
		Renderer::Get().camera()->eulerAngles(cameraPositions[3].second);
		break;

	case 'L':
		if(!repeating)
		{
			static std::vector<std::pair<float3, float3>> cameraPositions2;
			cameraPositions2.push_back(std::make_pair(Renderer::Get().camera()->position(),
				Renderer::Get().camera()->eulerAngles()));
			std::ofstream of("cameraPositions", std::ios::binary);
			uint count = cameraPositions2.size();
			of.write((const char*)&count, sizeof(count));
			for(auto& it : cameraPositions2)
			{
				of.write((const char*)it.first.data(), sizeof(float3));
				of.write((const char*)it.second.data(), sizeof(float3));
			}
		}
		break;

	case 'J':
		Renderer::Get().renderMode(RenderMode(((int)Renderer::Get().renderMode() + 1) % NUM_RENDERMODES));
		break;

	case VK_F5:
		if(Common::IsKeyDown(VK_SHIFT) && !repeating)
		{
			exit(0);
		}
		break;
	case VK_ESCAPE:
		exit(0);
		break;
	}
}

void Game::OnKeyUp(int keycode)
{
#if USE_DX11_STATIC_LIB
	if(keycode == VK_SNAPSHOT)
	{
		Renderer::Get().ScreenShot();
	}
#endif
}