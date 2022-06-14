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

struct Vertex
{
	float3 position;
	float3 normal;
	float2 uv_coord;
	float3 tangent;
	float3 bitangent;
};

struct SubMesh
{
	shared_ptr<Material> material;
	uint num_indices;
};

class Mesh : public NamedObject
{
	friend class Renderer;
	friend class Implementation::RenderBase;
public:
	// ctor & dtor
	Mesh(string&& name);
	virtual ~Mesh();

public:
	// creation
	static shared_ptr<Mesh> Create(string file);

	static shared_ptr<Mesh> Create(string name, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, 
		std::vector<SubMesh>& submeshes);

public:
	// properties

	shared_ptr<Material> material(size_t idx) const;

	void material(size_t idx, const shared_ptr<Material>& value);

public:
	// main functionality
	
protected:
	// internal

	virtual void Update(const shared_ptr<Camera>& camera, const matrix& modelView) {}

	void UpdateVertexBuffer(const std::vector<Vertex>& vertices);

	void SetData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);

protected:
	com_ptr<ID3D11Buffer> m_VertexBuffer, m_IndexBuffer;
	std::vector<SubMesh> m_SubMeshes;

}; // class Mesh

}; // namespace Demo
