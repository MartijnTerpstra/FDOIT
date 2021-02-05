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

struct VIn
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv_coord : TEXCOORD0;
	float3 tangent : TANGENT;
	float3 bitangent : BINORMAL;
};

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

cbuffer CameraBuffer : register(b0)
{
	matrix g_Projection;
	matrix g_InvProjection;
	matrix g_InvView;
};

cbuffer ModelBuffer : register(b1)
{
	matrix g_ModelView;
	matrix g_ModelViewProj;
}

VOut main(VIn input)
{
	VOut output = (VOut)0;

	output.view_position = mul(float4(input.position, 1), g_ModelView).xyz;
	output.normal = mul(float4(input.normal, 0), g_ModelView).xyz;
	output.uv_coord = input.uv_coord;
	output.tangent = mul(float4(input.tangent, 0), g_ModelView).xyz;
	output.bitangent = mul(float4(input.bitangent, 0), g_ModelView).xyz;
	output.clippos = output.position = mul(float4(input.position, 1), g_ModelViewProj);
	
	return output;
}