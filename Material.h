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

#include "ShaderVariableTypes.h"

namespace Demo {

class Material : public NamedObject
{
	friend class Renderer;
	friend class Implementation::RenderBase;
	friend class Mesh;
	friend class std::_Ref_count_obj<Material>;
private:
	// ctor & dtor
	Material(string&& name);
	~Material();

public:
	// creation
	static shared_ptr<Material> Create(string name, shared_ptr<Shader> shader);

public:
	// properties

	declare_property(shared_ptr<Shader>, shader);

	declare_property(D3D11_FILL_MODE, fillingMode);

	declare_property(D3D11_CULL_MODE, cullingMode);

public:
	// main functionality

	void SetTexture(const string& name_in_shader, shared_ptr<Texture> texture);

	shared_ptr<Texture> GetTexture(const string& name_in_shader) const;

	bool HasTexture(const string& name_in_shader) const;

	template<typename T>
	T GetVariable(const string& name_in_shader, size_t array_index = 0) const;

	template<typename T>
	void SetVariable(const string& name_in_shader, const T& var, size_t array_index = 0);

private:
	// implementation

	void _Upload(const com_ptr<ID3D11DeviceContext>& context);

private:
	shared_ptr<Shader> m_Shader;
	std::vector<std::pair<shared_ptr<Texture>, uint>> m_Textures;
	std::vector<Graphics::ShaderBuffer> m_Buffers;
	com_ptr<ID3D11RasterizerState> m_Rasterizer;

}; // Material

#include "Material.inl"

}; // namespace Demo
