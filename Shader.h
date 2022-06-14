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

class Shader : public NamedObject
{
	friend class Renderer;
	friend class Implementation::RenderBase;
	friend class Material;
public:
	// ctor & dtor
	Shader(string&& name);
	~Shader();

public:
	// creation

	static shared_ptr<Shader> Create(string file);

public:
	// main functionality

	bool HasVariable(const string& name_in_shader) const;

	bool HasTexture(const string& name_in_shader) const;

	//void PrintVariables();

private:
	// internal structs

private:
	// internal implementation

	const void* GetVariable(const string&, size_t, Graphics::VariableType, size_t, const std::vector<Graphics::ShaderBuffer>&) const;

	void SetVariable(const string&, size_t, const void*, size_t, Graphics::VariableType, std::vector<Graphics::ShaderBuffer>&);

private:
	com_ptr<ID3D11PixelShader> m_Pixel;
	std::vector<Graphics::ShaderVariable> m_Variables;
	std::vector<Graphics::ShaderTexture> m_Textures;
	std::vector<std::pair<uint, size_t>> m_Buffers;

}; // class Shader

}; // namespace Demo
