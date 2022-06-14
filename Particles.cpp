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
#include "Particles.h"

#include "Camera.h"
#include "Renderer.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

#include <random>

using namespace Demo;

static std::mt19937 g_RandomEngine(1729);

static float Random1f(float minim, float maxim)
{
	std::uniform_real_distribution<float> randFunc(minim, maxim);

	return randFunc(g_RandomEngine);
}

static float3 Random3f(float minim, float maxim)
{
	std::uniform_real_distribution<float> randFunc(minim, maxim);

	return float3(randFunc(g_RandomEngine), randFunc(g_RandomEngine), randFunc(g_RandomEngine));
}

Particles::Particles(string&& name)
	: Mesh(move(name))
{
}

Particles::~Particles()
{
}

shared_ptr<Particles> Particles::Create(string name)
{
	auto retval = make_shared<Particles>(move(name));

	retval->Init();

	return retval;
}

void Particles::Init()
{
	QueryPerformanceCounter(&m_StartTime);
	QueryPerformanceCounter(&m_LastFrame);
	QueryPerformanceFrequency(&m_Frequency);
	m_ParticlesToSpawn = 100;

	SubMesh sm;
	sm.num_indices = 600;
	sm.material = Material::Create("Particle material", 
		Renderer::Get().defaultShader());

	sm.material->SetTexture("DiffuseTex", Texture::Create("smoke_particle.btf"));

	sm.material->SetVariable("Diffuse", float3(0.8f,0.8f,0.8f));

	m_SubMeshes.push_back(sm);

	std::vector<uint> indices(600);
	m_Vertices.resize(400);

	for(int i= 0; i < 100; ++i)
	{
		indices[i * 6 + 0] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4 + 0;
		indices[i * 6 + 4] = i * 4 + 2;
		indices[i * 6 + 5] = i * 4 + 3;
	}

	SetData(m_Vertices, indices);

	SpawnParticles();
}

void Particles::Update(const shared_ptr<Camera>& camera, const matrix& modelView)
{
	const uint PARTICLES_PER_SECOND = 100;

	LARGE_INTEGER endTime;
	QueryPerformanceCounter(&endTime);

	float deltaTime = float((endTime.QuadPart - m_LastFrame.QuadPart) / double(m_Frequency.QuadPart));

	m_LastFrame = endTime;

	m_ParticlesToSpawn += deltaTime * PARTICLES_PER_SECOND;

	//SpawnParticles();

	const matrix inverseView = modelView.get_inverse();

	for(uint i = 0; i < m_Particles.size(); ++i)
	{
		Particle& p = m_Particles[i];

		const float4 viewPos = float4(p.position, 1) * modelView.get_transpose();

		m_Vertices[i * 4 + 0].position = swizzle::xyz((viewPos + float4(-p.size, p.size, 0, 0)) * inverseView.get_transpose());
		m_Vertices[i * 4 + 1].position = swizzle::xyz((viewPos + float4( p.size, p.size, 0, 0)) * inverseView.get_transpose());
		m_Vertices[i * 4 + 2].position = swizzle::xyz((viewPos + float4( p.size,-p.size, 0, 0)) * inverseView.get_transpose());
		m_Vertices[i * 4 + 3].position = swizzle::xyz((viewPos + float4(-p.size,-p.size, 0, 0)) * inverseView.get_transpose());

		m_Vertices[i * 4 + 0].uv_coord = float2(0,0);
		m_Vertices[i * 4 + 1].uv_coord = float2(1,0);
		m_Vertices[i * 4 + 2].uv_coord = float2(1,1);
		m_Vertices[i * 4 + 3].uv_coord = float2(0,1);
	}
	/*
	com_ptr<ID3D11DeviceContext> context;
	Renderer::Get().GetDevice()->GetImmediateContext(mst::initialize(context));

	D3D11_BOX box = {};

	box.back = 1;
	box.bottom = 1;
	box.right = m_Particles.size() * sizeof(Particle);

	context->UpdateSubresource(m_VertexBuffer.get(), 0, &box, m_Particles.data(), 0,0);
	*/

	UpdateVertexBuffer(m_Vertices);
}

void Particles::SpawnParticles()
{
	float particlesToSpawn = floor(m_ParticlesToSpawn);

	size_t prevSize = m_Particles.size();

	m_Particles.resize(prevSize + (uint)particlesToSpawn);

	for(auto it = m_Particles.begin() + prevSize; it != m_Particles.end(); ++it)
	{
		it->position = Random3f(-10, 10);
		it->size = 10;
		it->velocity = Random3f(-1, 1) + float3(0,1,0);
		it->alpha = 1;
	}

	m_ParticlesToSpawn -= particlesToSpawn;
}