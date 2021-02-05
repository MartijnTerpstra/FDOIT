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

#include "Header.hlsli"
#include "FDOIT.hlsli"
#include "Shading.hlsli"

RWTexture2D<uint> g_FDOITStartIndices :					register(u0);
RWStructuredBuffer<FDOITFragment> g_FDOITFragments :	register(u1);

void FDOITAddFragment(float4 projpos, float4 color)
{
	uint idx = g_FDOITFragments.IncrementCounter();

	// insert fragment
	uint next_index;

	//projpos.xyz /= projpos.w;

	//uint2 pixel = uint2((projpos.xy * float2(0.5,-0.5) + float2(0.5,0.5)) * g_Resolutionf);

	uint2 pixel = uint2(projpos.xy);

	FDOITFragment frag;
	frag.color = Pack(color);
	frag.depth = 1 - projpos.z;

	if(idx < g_MaxLinkedListCount)
	{

		InterlockedExchange(g_FDOITStartIndices[pixel], idx, next_index);

		frag.next = next_index;

		g_FDOITFragments[idx] = frag;
	}
	/*else
	{
		// to set the size of the next render
		//InterlockedCompareExchange(g_OITStartIndices[g_Resolution.x * g_Resolution.y], 0xFFFFFFFF, 0);
		InterlockedAdd(g_FDOITStartIndices[g_Resolution.x * g_Resolution.y], 1);
	}*/
}

void main(VOut input)
{
	/* remove saturate for HDR */
	float4 color = saturate(ComputeShading(input));

	FDOITAddFragment(input.position, color);
}