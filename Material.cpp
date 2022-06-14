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

#include "Material.h"

#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

using namespace Demo;

Material::Material(string&& name)
	: NamedObject(move(name))
{
}

Material::~Material()
{
}

shared_ptr<Material> Material::Create(string name, shared_ptr<Shader> shader)
{
	auto retval = make_shared<Material>(move(name));

	retval->shader(move(shader));

	return retval;
}

shared_ptr<Shader> Material::shader() const
{
	return m_Shader;
}

void Material::shader(const shared_ptr<Shader>& new_shader)
{
	m_Shader = new_shader;

	for(auto& it : m_Buffers)
	{
		_aligned_free(it.data);
	}
	m_Buffers.resize(new_shader->m_Buffers.size());
	m_Textures.resize(new_shader->m_Textures.size());

	auto device = Renderer::Get().GetDevice();

	for(size_t i = 0; i < m_Buffers.size(); ++i)
	{
		m_Buffers[i].dirty = false;
		m_Buffers[i].slot = new_shader->m_Buffers[i].first;
		m_Buffers[i].data_size = new_shader->m_Buffers[i].second;
		m_Buffers[i].data = _aligned_malloc(m_Buffers[i].data_size, 16);
		memset(m_Buffers[i].data, 0, m_Buffers[i].data_size);
		D3D11_BUFFER_DESC bdesc = {};
		bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bdesc.ByteWidth = m_Buffers[i].data_size;
		bdesc.Usage = D3D11_USAGE_DEFAULT;
		device->CreateBuffer(&bdesc, nullptr, mst::initialize(m_Buffers[i].buffer));
	}

	for(size_t i = 0; i < m_Textures.size(); ++i)
	{
		m_Textures[i].first = nullptr;
		m_Textures[i].second = new_shader->m_Textures[i].slot;
	}
}

void Material::fillingMode(const D3D11_FILL_MODE& mode)
{
	D3D11_RASTERIZER_DESC desc;
	m_Rasterizer->GetDesc(&desc);
	desc.FillMode = mode;
	com_ptr<ID3D11Device> device;
	m_Rasterizer->GetDevice(mst::initialize(device));
	device->CreateRasterizerState(&desc, mst::initialize(m_Rasterizer));
}

void Material::cullingMode(const D3D11_CULL_MODE& mode)
{
	D3D11_RASTERIZER_DESC desc;
	m_Rasterizer->GetDesc(&desc);
	desc.CullMode = mode;
	com_ptr<ID3D11Device> device;
	m_Rasterizer->GetDevice(mst::initialize(device));
	device->CreateRasterizerState(&desc, mst::initialize(m_Rasterizer));
}

void Material::Upload(const com_ptr<ID3D11DeviceContext>& context)
{
	for(uint i = 0; i < m_Buffers.size(); ++i)
	{
		if(m_Buffers[i].dirty)
		{
			m_Buffers[i].dirty = false;
			context->UpdateSubresource(m_Buffers[i].buffer.get(), 0, nullptr, m_Buffers[i].data,0,0);

		}
		context->PSSetConstantBuffers(m_Buffers[i].slot, 1, &m_Buffers[i].buffer);
	}

	for(uint i = 0; i < m_Textures.size(); ++i)
	{
		if(m_Textures[i].first)
		{
			context->PSSetShaderResources(m_Textures[i].second, 1, &m_Textures[i].first->m_Texture);
		}
	}
}

void Material::SetTexture(const string& name_in_shader, shared_ptr<Texture> texture)
{
	for(size_t i = 0; i < m_Shader->m_Textures.size(); ++i)
	{
		if(m_Shader->m_Textures[i].name == name_in_shader)
		{
			m_Textures[i].first = move(texture);
			return;
		}
	}

	throw std::exception("Material::SetTexture(): no texture is found with that name");
}

shared_ptr<Texture> Material::GetTexture(const string& name_in_shader) const
{
	for(size_t i = 0; i < m_Shader->m_Textures.size(); ++i)
	{
		if(m_Shader->m_Textures[i].name == name_in_shader)
		{
			return m_Textures[i].first;
		}
	}

	throw std::exception("Material::GetTexture(): no texture is found with that name");
}

bool Material::HasTexture(const string& name_in_shader) const
{
	for(size_t i = 0; i < m_Shader->m_Textures.size(); ++i)
	{
		if(m_Shader->m_Textures[i].name == name_in_shader)
		{
			return m_Textures[i].first != nullptr;
		}
	}

	throw std::exception("Material::HasTexture(): no texture is found with that name");
}