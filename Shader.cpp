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

#include "Shader.h"
#include "Renderer.h"

#if _IS_VC10_COMPILER
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3Dcompiler.h>
#else
#include <d3dcompiler.h>
#endif

using namespace Demo;

struct _Module
{
	_Module()
	{
		_module = LoadLibraryA("D3DCompiler_43.dll");
		if(!_module)
		{
			printf("ERROR! unable to open D3dCompiler_43.dll\n");
		}
	}
	~_Module()
	{
		FreeLibrary(_module);
	}
	operator HMODULE()
	{
		return _module;
	}
private:
	HMODULE _module;
} g_Module;

HRESULT __stdcall ::D3DReflect( LPCVOID pSrcData,_In_ SIZE_T SrcDataSize, _In_ REFIID pInterface,_Out_ void** ppReflector)
{
	typedef decltype(D3DReflect)* PFND3DReflect;
	static PFND3DReflect PD3DReflect = (PFND3DReflect)GetProcAddress(g_Module, "D3DReflect");

	return PD3DReflect(pSrcData, SrcDataSize, pInterface, ppReflector);
}

Shader::Shader(string&& name)
	: NamedObject(move(name))
{
}

Shader::~Shader()
{
}

shared_ptr<Shader> Shader::Create(string file)
{
	const string file_name = "ShaderObjects\\" + file + ".cso";
	auto shader = make_shared<Shader>(move(file));

	std::ifstream inf(file_name, std::ios::binary);
	if(inf.fail())
	{
		throw std::invalid_argument("Shader::Create(): invalid arg: file not found");
	}

	inf.seekg(0, std::ios::end);
	size_t data_size = (size_t)inf.tellg();
	inf.seekg(0);

	std::unique_ptr<char[]> data(new char[data_size]);

	inf.read(data.get(), data_size);

	auto device = Renderer::Get().GetDevice();

	device->CreatePixelShader(data.get(), data_size, nullptr, mst::initialize(shader->m_Pixel));

	//shader->PrintVariables();

	// IID_ID3D11ShaderReflection
	GUID guid = { 170080025,14688,17784,{157,124,32,59,139,29,156,193}};

	ID3D11ShaderReflection* _reflection;
	D3DReflect(data.get(), data_size, guid, (void**)&_reflection);
	com_ptr<ID3D11ShaderReflection> reflection(_reflection);
	
	D3D11_SHADER_DESC desc;
	reflection->GetDesc(&desc);

	for(uint i= 0; i < desc.BoundResources; ++i)
	{

		D3D11_SHADER_INPUT_BIND_DESC input_desc;
		reflection->GetResourceBindingDesc(i, &input_desc);

		Graphics::ShaderTexture tex;
		tex.name = input_desc.Name;
		tex.slot = input_desc.BindPoint;

		switch(input_desc.Type)
		{
		case D3D_SIT_TEXTURE:
			switch(input_desc.Dimension)
			{
			case D3D_SRV_DIMENSION_TEXTURE2D:
				shader->m_Textures.push_back(tex);
				break;
			default:
				_MST_BREAK;
				break;
			}
			break;
		}

	}

	//uint buffer_idx = 0;
	for(uint i = 0; i < desc.ConstantBuffers; ++i)
	{
		auto buffer = reflection->GetConstantBufferByIndex(i);
		D3D11_SHADER_BUFFER_DESC buffer_desc;
		buffer->GetDesc(&buffer_desc);
		if(buffer_desc.Type == D3D_CT_CBUFFER)
		{
			if(strcmp(buffer_desc.Name, "LightingBuffer") == 0)
			{
				// internal buffer
				continue;
			}
			if(strcmp(buffer_desc.Name, "OITBuffer") == 0)
			{
				// internal buffer
				continue;
			}
			//Graphics::ShaderBuffer buf;
			//buf.data = _aligned_malloc(buffer_desc.Size, 16);
			//memset(buf.data, 0, buffer_desc.Size);
			std::pair<uint, size_t> buf;
			buf.second = buffer_desc.Size;
			buf.first = -1;
			for(uint j = 0; j < desc.BoundResources; ++j)
			{
				D3D11_SHADER_INPUT_BIND_DESC input_desc;
				reflection->GetResourceBindingDesc(j, &input_desc);
				if(strcmp(buffer_desc.Name, input_desc.Name) == 0)
				{
					buf.first = input_desc.BindPoint;
					break;
				}
			}
			if(buf.first == -1)
			{
				throw std::exception("error mapping shader variables");
			}
			/*
			D3D11_BUFFER_DESC bdesc = {};
			bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bdesc.ByteWidth = buffer_desc.Size;
			bdesc.Usage = D3D11_USAGE_DEFAULT;
			device->CreateBuffer(&bdesc, nullptr, &buf.buffer);*/

			shader->m_Buffers.push_back(buf);
			for(uint j = 0; j < buffer_desc.Variables; ++j)
			{
				Graphics::ShaderVariable var;

				auto variable = buffer->GetVariableByIndex(j);

				D3D11_SHADER_VARIABLE_DESC variable_desc;
				variable->GetDesc(&variable_desc);

				auto type = variable->GetType();

				D3D11_SHADER_TYPE_DESC type_desc;
				type->GetDesc(&type_desc);

				var.name = variable_desc.Name;
				var.offset = variable_desc.StartOffset;
				var.buffer = shader->m_Buffers.size() - 1;
				var.array_size = type_desc.Elements != 0 ? type_desc.Elements : 1;
				var.size = variable_desc.Size;
				var.type = Graphics::CreateEnum(type_desc.Type, type_desc.Class, type_desc.Rows, type_desc.Columns);
				shader->m_Variables.push_back(var);

			}
		}
	}

	return shader;
}

bool Shader::HasTexture(const string& name_in_shader) const
{
	for(auto& it : m_Textures)
	{
		if(it.name == name_in_shader)
		{
			return true;
		}
	}
	return false;
}