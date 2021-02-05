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

using namespace Demo;

const void* Shader::GetVariable(const string& var_name, size_t array_index, Graphics::VariableType type, size_t size, const std::vector<Graphics::ShaderBuffer>& buffers) const
{
	foreach(const auto& it, m_Variables)
	{
		if(var_name == it.name)
		{
			if(it.type != Graphics::UNKNOWN_TYPE && it.type != type)
			{
				throw std::exception("Shader::GetVariable<T>(): invalid template argument T");
			}
			if(array_index >= it.array_size)
			{
				throw std::exception("Shader::GetVariable<T>(): invalid argument array_index");
			}
			if(size * array_index + size > it.size)
			{
				throw std::exception("Shader::GetVariable<T>(): variable requested is out of range");
			}
			const char* dat = (const char*)buffers[it.buffer].data;
			dat = dat + it.offset;
			dat += array_index * size;
			return dat;
		}
	}

	throw std::exception("Shader::GetVariable<T>(): variable not found");
}

void Shader::SetVariable(const string& var_name, size_t array_index, const void* src, size_t size, Graphics::VariableType type, std::vector<Graphics::ShaderBuffer>& buffers)
{
	foreach(const auto& it, m_Variables)
	{
		if(var_name == it.name)
		{
			if(it.type != Graphics::UNKNOWN_TYPE && it.type != type)
			{
				throw std::exception("Shader::SetVariable<T>(): invalid template argument T");
			}
			if(array_index >= it.array_size)
			{
				throw std::exception("Shader::SetVariable<T>(): invalid argument array_index");
			}
			if(size * array_index + size > it.size)
			{
				throw std::exception("Shader::SetVariable<T>(): variable requested is out of range");
			}
			char* dat = (char*)buffers[it.buffer].data;
			dat = dat + it.offset;
			dat += array_index * size;
			memcpy(dat, src, size);
			buffers[it.buffer].dirty = true;
			return;
		}
	}

	throw std::exception("Shader::SetVariable<T>(): variable not found");
}

bool Shader::HasVariable(const string& var_name) const
{
	foreach(const auto& it, m_Variables)
	{
		if(var_name == it.name)
		{
			return true;
		}
	}

	return false;
}