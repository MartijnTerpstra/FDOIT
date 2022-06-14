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

#include "Mesh.h"
#include "Renderer.h"

using namespace Demo;

Mesh::Mesh(string&& name)
	: NamedObject(move(name))
{
}

Mesh::~Mesh()
{
}

shared_ptr<Mesh> Mesh::Create(string name, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, 
		std::vector<SubMesh>& submeshes)
{
	auto retval = make_shared<Mesh>(move(name));

	retval->SetData(vertices, indices);

	retval->m_SubMeshes = submeshes;

	return retval;
}

void Mesh::SetData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = vertices.size() * sizeof(Vertex);
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertices.data();

	com_ptr<ID3D11Device> device = Renderer::Get().GetDevice();

	device->CreateBuffer(&desc, &data, mst::initialize(m_VertexBuffer));

	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = indices.size() * sizeof(uint32_t);

	data.pSysMem = indices.data();

	device->CreateBuffer(&desc, &data, mst::initialize(m_IndexBuffer));
}

void Mesh::UpdateVertexBuffer(const std::vector<Vertex>& vertices)
{
	com_ptr<ID3D11Device> device = Renderer::Get().GetDevice();
	com_ptr<ID3D11DeviceContext> context;
	device->GetImmediateContext(mst::initialize(context));

	D3D11_BOX box = {};

	box.bottom = 1;
	box.back = 1;
	box.right = vertices.size() * sizeof(Vertex);

	context->UpdateSubresource(m_VertexBuffer.get(), 0, &box, vertices.data(), 0, 0);
}

shared_ptr<Material> Mesh::material(size_t index) const
{
	if(index >= m_SubMeshes.size())
	{
		throw std::out_of_range("Mesh::materials[]: index out of range");
	}
	return m_SubMeshes[index].material;
}

void Mesh::material(size_t index, const shared_ptr<Material>& value)
{
	if(index >= m_SubMeshes.size())
	{
		throw std::out_of_range("Mesh::materials[]: index out of range");
	}
	m_SubMeshes[index].material = value;
}