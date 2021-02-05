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

enum LightType;

/*
	Handles objects in the world
*/
class Scene
{
	friend class Light;
	friend class Renderer;
	friend class Implementation::RenderBase;
private:
	Scene();
	~Scene();

public:
	// singleton
	static Scene& Get();

public:
	// properties

	declare_get_property(shared_ptr<Camera>, camera);

	declare_property_mapped_array(shared_ptr<Mesh>, meshes);

	declare_property_mapped_array(matrix, meshMatrices);

	declare_get_property(uint, meshCount);

	declare_property_mapped_array(shared_ptr<Light>, lights);

	declare_property_mapped_array(matrix, lightMatrices);

	declare_get_property(uint, lightCount);

	declare_get_property(uint, pointLightCount);

	declare_get_property(uint, spotLightCount);

	declare_get_property(uint, directionalLightCount);

public:
	// main functionality

	/* adds a mesh to the scene */
	void AddMesh(shared_ptr<Mesh> mesh, const matrix& matrix);

	void AddLight(shared_ptr<Light> light, const matrix& matrix);

	void ClearScene();

	void RemoveAllMeshes();

	void RemoveAllMeshesWithName(string name);

	void RemoveAllLights();

private:
	// internal

	void LightTypeChanged(const shared_ptr<Light>&, LightType);

private:
	std::vector<std::pair<shared_ptr<Mesh>, matrix>> m_Meshes;
	std::vector<std::pair<shared_ptr<Light>, matrix>> m_Lights;
	uint m_NumLights[3];
	weak_ptr<Camera> m_Camera;

}; // class Scene

}; // namespace Demo
