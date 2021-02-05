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

Texture2D<float4> Tex1 :	register(t0);
Texture2D<float4> Tex2 :	register(t1);
Texture2D<float4> HQTex :	register(t2);

bool comp(float3 left, float3 right)
{
	return left[0] == right[0] &&
		left[1] == right[1] &&
		left[2] == right[2];
}

float4 main(float2 uv : TEXCOORD0, float4 pos : SV_POSITION) : SV_TARGET
{
	uint2 index = uint2(pos.xy);
	float3 colorHQ = HQTex[index].rgb;
	float3 color1  =  Tex1[index].rgb;
	float3 color2  =  Tex2[index].rgb;

	if(comp(color1, colorHQ) && comp(color2, colorHQ))
	{
		return float4(0,0,0,0);
	}

	float diff1 = dot(abs(color1 - colorHQ),abs(color1 - colorHQ));
	float diff2 = dot(abs(color2 - colorHQ),abs(color2 - colorHQ));

	if(diff1 == diff2)
	{
		return float4(diff1 * 4000,diff1 * 1000,0,0);
	}

	if(diff1 > diff2)
	{
		return float4(diff1 * 4000,0,0,0);
	}

	return float4(0,diff2 * 4000,0,0);
}