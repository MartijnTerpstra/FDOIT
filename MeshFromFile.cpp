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
#include "Texture.h"
#include "Material.h"
#include "Shader.h"

#include "FileBuffer.h"

using namespace Demo;

struct BMFHeader
{
	uint version;
	uint num_vertices;
	uint vertex_stride;
	uint num_tris;
	uint num_index_ranges;
	uint num_unique_materials;
	uint num_materials;
	uint mesh_type;
	uint data_size;
};

#define ADAM_MAX_NUM_TEXTURES_IN_MATERIAL 6

enum MeshType
{
	MESH_BASEMESH,
	MESH_ANIMATED,
	MESH_TERRAIN,
	MESH_INSTANCED,
};

shared_ptr<Mesh> Mesh::Create(string file)
{
	WTRACE;
	const string file_name = "Meshes\\" + file + ".bmf";
	auto retval = make_shared<Mesh>(move(file));

	//std::ifstream infile((m_ResourcePaths[ADAM_RESOURCE_MODELS] + file_name).c_str(), std::ios::binary);
		
	BMFHeader header;
	
	ADAM::FileBuffer buffer;

	bool success = buffer.ReadFromFile(file_name.c_str());

//#if _IS_DEBUGGING_ENABLED
	if(!success)
	{
		throw "file not found!";
	}
//#endif

	buffer.GetData(header);

	switch(header.version)
	{
	default:
		throw std::exception("invalid file version");
	case 1300:
		break;
	}

	if(header.vertex_stride != sizeof(Vertex))
	{
		throw std::exception("invalid mesh type");
	}

	std::vector<Vertex> vertices(header.num_vertices);
	std::vector<uint> triangles(header.num_tris * 3);
	std::vector<uint> index_ranges(header.num_index_ranges);

	buffer.GetData(vertices);
	buffer.GetData(triangles);
	buffer.GetData(index_ranges);

	float dummy[3];
	buffer.GetData(dummy);
	buffer.GetData(dummy);

	std::vector<shared_ptr<Material>> unique_materials(header.num_unique_materials);

	com_ptr<ID3D11Device> device = Renderer::Get().GetDevice();

	int idx = 0;

	for(uint i = 0; i < header.num_unique_materials; ++i)
	{
		string name = buffer.GetString();

		int mat_type = buffer.GetInt();

		string tex_name;

		shared_ptr<Material> mat = Material::Create(name.c_str(), Renderer::Get().defaultShader());

		const string texnames[ADAM_MAX_NUM_TEXTURES_IN_MATERIAL] =
		{
			"DiffuseTex",
			"SpecTex",
			"BumpTex",
			"NotUsed", // emissive?
			"NotUsed", // displacement?
			"NotUsed" // cube map?
		};

		for(uint j = 0; j < ADAM_MAX_NUM_TEXTURES_IN_MATERIAL; ++j)
		{
			tex_name = buffer.GetString();
			if(!tex_name.empty() && mat->m_Shader->HasTexture(texnames[j]))
			{
				mat->SetTexture(texnames[j], Texture::Create(tex_name));
			}
		}

		float3 color;
		buffer.GetData(color); // ambient not used
		//mat->SetAmbientColor(color);

		buffer.GetData(color);
		mat->SetVariable("Diffuse", color);
		//mat->SetDiffuseColor(color);

		buffer.GetData(color);
		mat->SetVariable("Specular", color);
		//mat->SetSpecularColor(color);

		buffer.GetData(color);
		mat->SetVariable("Emissive", color);
		//mat->SetEmissiveColor(color);

		float shininess;
		shininess = buffer.GetFloat();
		mat->SetVariable("Shininess", shininess);
		//mat->SetShininess(shininess);

		float offset;
		offset = buffer.GetFloat();
		//mat->SetDisplacementOffset(offset);

		float scale;
		scale = buffer.GetFloat();
		//mat->SetDisplacementScale(scale);

		float uv_scale[2];
		buffer.GetData(uv_scale);

		//mat->SetTextureUVScale(uv_scale);

		int transparency = buffer.GetInt();

		D3D11_RASTERIZER_DESC desc;

		buffer.GetData(desc);

		device->CreateRasterizerState(&desc, mst::initialize(mat->m_Rasterizer));


		unique_materials[i]= mat;
	}

	std::vector<shared_ptr<Material>> materials(header.num_materials);

	for(size_t i = 0; i < header.num_materials; ++i)
	{
		materials[i] = unique_materials[buffer.GetInt()];
	}

	std::vector<SubMesh> submeshes(header.num_materials);
	for(size_t i = 0; i < submeshes.size(); ++i)
	{
		submeshes[i].material = materials[i];
		submeshes[i].num_indices = index_ranges[i+1] - index_ranges[i];
	}

	retval->SetData(vertices, triangles);
	retval->m_SubMeshes = move(submeshes);

	switch(header.mesh_type)
	{
	default:
		MST_FATAL_ERROR("unhandled mesh type");
		break;

	case MESH_BASEMESH:
		{
			//return NativeMesh::Construct(name, move(vertices), move(triangles), move(materials), move(index_ranges), aabb);
		}
		break;
	case MESH_TERRAIN:
		throw std::exception("terrain meshes not supported");

	case MESH_ANIMATED:
		throw std::exception("animated meshes not supported");

	case MESH_INSTANCED:
		{
			// sure thing whatever
		}
		break;
	}

	return retval;
}