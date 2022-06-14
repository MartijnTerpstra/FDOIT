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

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Renderer.h"

using namespace Demo;

Scene& Scene::Get()
{
	WTRACE;
	static Scene scene;
	return scene;
}

Scene::Scene()
{
	WTRACE;
	mst::zeromem(m_NumLights);
}

Scene::~Scene()
{
}

void Scene::AddMesh(shared_ptr<Mesh> mesh, const matrix& mat)
{
	WTRACE;
	if(!mesh)
	{
		throw std::invalid_argument("Scene::AddMesh(): mesh does not point to a valid object");
	}
	m_Meshes.push_back(std::make_pair(move(mesh), mat));
}

void Scene::AddLight(shared_ptr<Light> light, const matrix& mat)
{
	WTRACE;
	if(!light)
	{
		throw std::invalid_argument("Scene::AddLight(): light does not point to a valid object");
	}

	LightType type = light->type();

	switch(type)
	{
	case DIRECTIONAL_LIGHT:
		m_Lights.insert(m_Lights.begin(), std::make_pair(move(light), mat));
		break;
	case POINT_LIGHT:
		m_Lights.insert(m_Lights.begin() + (m_NumLights[DIRECTIONAL_LIGHT]), std::make_pair(move(light), mat));
		break;
	case SPOT_LIGHT:
		m_Lights.insert(m_Lights.begin() + (m_NumLights[DIRECTIONAL_LIGHT] + m_NumLights[POINT_LIGHT]), std::make_pair(move(light), mat));
		break;
	default:
		// unimplemented type
		_asm { int 3 };
		return;
	}
	m_NumLights[type]++;
}

void Scene::RemoveAllMeshesWithName(string name)
{
	m_Meshes.erase(std::remove_if(m_Meshes.begin(), m_Meshes.end(), [&name](std::pair<shared_ptr<Mesh>, matrix>& it)
	{
		return it.first->name() == name;
	} ), m_Meshes.end());
}

void Scene::LightTypeChanged(const shared_ptr<Light>& light, LightType old_type)
{
	uint from = 0;
	uint to = 0;
	int i = 0;
	for(; i < old_type; ++i)
	{
		from +=m_NumLights[i];
		to +=m_NumLights[i];
	}
	to +=m_NumLights[i];

	for(uint it = from; it < to; ++it)
	{
		if(m_Lights[it].first == light)
		{
			auto pair = m_Lights[it];
			m_Lights.erase(m_Lights.begin() + it);
			m_NumLights[old_type]--;
			AddLight(pair.first, pair.second);
		}
	}
}