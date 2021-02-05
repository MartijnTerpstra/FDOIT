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

namespace Demo { namespace Graphics {

struct MST_ALIGN(16) GPUDirectionalLight
{
	float3 direction;
	float intensity;
	float3 color;
	float dummy;
};

struct MST_ALIGN(16) GPUPointLight
{
	float3 position;
	float intensity;
	float3 color;
	float radius;
};

struct MST_ALIGN(16) GPUSpotLight
{
	float3 position;
	float intensity;
	float3 color;
	float cosAngle;
	float3 direction;
	float cosPenumbra;
};

struct MST_ALIGN(16) GPUModelBuffer
{
	matrix modelView, modelViewProj;
};

struct MST_ALIGN(16) GPULightingBuffer
{
	uint numDirectionalLights;
	uint numPointLights;
	uint numSpotLights;
	float invDistancePerIntensity;
	float globalAmbient;
};

struct MST_ALIGN(16) GPUFDOITBuffer
{
	uint2 g_Resolution;
	float2 g_Resolutionf;
	float2 g_HalfSizef;
	float g_Far;
	uint g_MaxLinkedListCount;
	uint g_Debug;
};

struct GPUFDOITFragment
{
	uint color;
	float depth;
	uint next;
};

struct GPUHQFragment
{
	float4 color;
	float depth;
	uint next;
};

struct GPUAOITFragment
{
	uint    next;  
    float   depth;    
    uint    color;
};

struct GPUFDOIT2Pack
{
	uint4 colors[16/4];
	float4 depths[16/4];
};

}; }; // namespace Demo::Graphics
