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


struct VOut
{
	float3 view_position : POSITION;
	float3 normal : NORMAL;
	float2 uv_coord : TEXCOORD0;
	float3 tangent : TANGENT;
	float3 bitangent : BINORMAL;
	float4 clippos : TEXCOORD1;
	float4 position : SV_POSITION;
};

struct DirectionalLight
{
	float3 direction;
	float intensity;
	float3 color;
	float dummy;
};

struct PointLight
{
	float3 position;
	float intensity;
	float3 color;
	float radius;
};

struct SpotLight
{
	float3 position;
	float intensity;
	float3 color;
	float cosAngle;
	float3 direction;
	float cosPenumbra;
};

#define SIZEOFDIRLIGHT 32
#define SIZEOFPOINTLIGHT 32
#define SIZEOFSPOTLIGHT 48

cbuffer LightingBuffer : register(b0)
{
	uint g_NumDirectionalLights;
	uint g_NumPointLights;
	uint g_NumSpotLights;
	float g_InvDistancePerIntensity;
	float g_GlobalAmbient;
};

StructuredBuffer<DirectionalLight> g_DirLights :	register(t0);

SamplerState Sampler : register(s0);

#define TILE_SIZE 8