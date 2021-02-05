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

cbuffer FDOITBuffer : register(b2)
{
	uint2 g_Resolution;
	float2 g_Resolutionf;
	float2 g_HalfSizef;
	float g_Far;
	uint g_MaxLinkedListCount;
	uint g_Debug;
};

struct FDOITFragment
{
	uint color;
	float depth;
	uint next;
};

float4 Unpack(uint packed)
{
	return float4((packed & 0xFF) / 255.0f,
					((packed >> 8) & 0xFF) / 255.0f,
					((packed >> 16) & 0xFF) / 255.0f,
					((packed >> 24) & 0xFF) / 255.0f);
}

uint Pack(float4 color)
{
	return uint(int(color.r * 255.0f) | 
				(int(color.g * 255.0f) << 8) | 
				(int(color.b * 255.0f) << 16) | 
				(int(color.a * 255.0f) << 24));
}