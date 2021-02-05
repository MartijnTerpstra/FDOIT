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

class Particles : public Mesh
{
	friend class std::_Ref_count_obj<Particles>;
private:
	// ctor & dtor
	Particles(string&& name);
	~Particles();

public:
	// creation
	static shared_ptr<Particles> Create(string name);

private:
	struct Particle
	{
		float3 position;
		float size;
		float3 velocity;
		float alpha;
	};

	void Update(const shared_ptr<Camera>& camera, const matrix& modelView) final override;

	void Init();

	void SpawnParticles();

private:
	LARGE_INTEGER m_StartTime, m_LastFrame, m_Frequency;
	float m_ParticlesToSpawn;
	std::vector<Particle> m_Particles;
	std::vector<Vertex> m_Vertices;

}; // class Particles

}; // namespace Demo