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

shared_ptr<Camera> Scene::camera() const
{
	return shared_ptr<Camera>(m_Camera);
}

shared_ptr<Mesh> Scene::mesh(size_t idx) const
{
	return m_Meshes[idx].first;
}

shared_ptr<Mesh> Scene::mesh(const string& name) const
{
	for(const auto& it : m_Meshes)
	{
		if(it.first->name() == name)
		{
			return it.first;
		}
	}

	return nullptr;
}

void Scene::meshMatrix(size_t idx, const matrix& mat)
{
	m_Meshes[idx].second = mat;
}

uint Scene::meshCount() const
{
	return m_Meshes.size();
}

shared_ptr<Light> Scene::light(size_t idx) const
{
	return m_Lights[idx].first;
}

shared_ptr<Light> Scene::light(const string& name) const
{
	for(const auto& it : m_Lights)
	{
		if(it.first->name() == name)
		{
			return it.first;
		}
	}

	return nullptr;
}

matrix Scene::lightMatrix(size_t idx) const
{
	return m_Lights[idx].second;
}

void Scene::lightMatrix(size_t idx, const matrix& mat)
{
	m_Lights[idx].second = mat;
}

uint Scene::lightCount() const
{
	return m_Lights.size();
}

uint Scene::pointLightCount() const
{
	return m_NumLights[POINT_LIGHT];
}

uint Scene::spotLightCount() const
{
	return m_NumLights[SPOT_LIGHT];
}

uint Scene::directionalLightCount() const
{
	return m_NumLights[DIRECTIONAL_LIGHT];
}