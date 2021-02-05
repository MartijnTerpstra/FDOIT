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

#include "HQ.hlsli"

Texture2D<uint> g_HQStartIndices :				register(t0);
StructuredBuffer<HQFragment> g_HQFragments :	register(t1);

float4 HQGetFragments(uint2 uv)
{
	// fullscreen pass, so use UV

	uint index = g_HQStartIndices[uv];

	float4 color = float4(0,0,0,0);

	const uint startIndex = index;

	float minDepth = 1;
	float maxDepth = 0;

	if(index == 0xFFFFFFFF)
	{
		minDepth = 0;
	}

	//uint slot = 0;
	while(index != 0xFFFFFFFF)
	{
		HQFragment frag = g_HQFragments[index];

		minDepth = min(frag.depth, minDepth);
		maxDepth = max(frag.depth, maxDepth);

		index = frag.next;

	}

	while(minDepth != maxDepth)
	{
		index = startIndex;

		float nextDepth = maxDepth;

		while(index != 0xFFFFFFFF)
		{
			HQFragment frag = g_HQFragments[index];

			index = frag.next;

			//nextDepth = (frag.depth > minDepth) ? ((frag.depth - minDepth) < ) : nextDepth;

			if(frag.depth > minDepth)
			{
				if(frag.depth - minDepth < nextDepth - minDepth)
				{
					nextDepth = frag.depth;
				}
			}

			if(frag.depth == minDepth)
			{
				color.rgb = lerp(color.rgb, frag.color.rgb, frag.color.a);
			}

		}

		minDepth = nextDepth;
	}

	index = startIndex;

	while(index != 0xFFFFFFFF)
	{
		HQFragment frag = g_HQFragments[index];

		index = frag.next;

		//nextDepth = (frag.depth > minDepth) ? ((frag.depth - minDepth) < ) : nextDepth;

		if(frag.depth == minDepth)
		{
			color.rgb = lerp(color.rgb, frag.color.rgb, frag.color.a);
		}

	}

	return color;
}


struct Pin
{
	float2 uv : TEXCOORD0;
	float4 position : SV_POSITION;
};

float4 main(Pin input) : SV_TARGET
{
	const uint2 uv = uint2(input.position.xy);

#if _DEBUG
	if(g_Debug)
	{
		return HQDebugFragments(uv);
	}
#endif
	return HQGetFragments(uv);
}