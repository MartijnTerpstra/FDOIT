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


Texture2D DiffuseTex : register(t0);
Texture2D SpecTex : register(t1);
Texture2D BumpTex : register(t2);

cbuffer Material : register(b1)
{
	float3 Diffuse;
	float3 Specular;
	float Shininess;
	float3 Emissive;
};

float4 ComputeShading(VOut input)
{
	float4 diffuse = DiffuseTex.Sample(Sampler, input.uv_coord) * float4(Diffuse, 1);
	clip(diffuse.a - 0.05);
	float3 out_color = g_GlobalAmbient * diffuse.rgb + Emissive;

	//input.normal = normalize(input.normal);

	/*if(input.clippos.w != .525)
	{
		return float4(input.uv_coord, 0, 0.5f);
	}*/
	return float4(out_color + diffuse.rgb, min(diffuse.a, 0.5f));
}