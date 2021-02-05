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

#include "FDOIT.hlsli"

#define FDOIT_PACK_COUNT (FDOIT_FRAGMENT_DEPTH/4)

struct FDOITPack
{

	uint4 colors[FDOIT_PACK_COUNT];
	float4 depths[FDOIT_PACK_COUNT];

};

Texture2D<uint> g_FDOITStartIndices :				register(t0);
StructuredBuffer<FDOITFragment> g_FDOITFragments :	register(t1);

float4 FDOITDebugFragments(uint2 screenPos)
{
	uint index = g_FDOITStartIndices[screenPos];


	uint slot = 0;
	while(index != 0xFFFFFFFF)
	{
		FDOITFragment frag = g_FDOITFragments[index];

		index = frag.next;
		slot++;
	}

	return slot / (FDOIT_FRAGMENT_DEPTH * 4.0f);
}

float4 FDOITGetFragments(uint2 screenPosition)
{
	// fullscreen pass, so use UV

	uint index = g_FDOITStartIndices[screenPosition];

	FDOITPack fragments = (FDOITPack)0;

	float4 color = float4(0,0,0,0);

	while(index != 0xFFFFFFFF)
	{
		FDOITFragment frag = g_FDOITFragments[index];

		index = frag.next;

		[unroll]
		for(uint i = 0; i < FDOIT_PACK_COUNT; ++i)
		{
			if(frag.depth > fragments.depths[i][3])
			{
				[unroll] // push back the elements
				for(uint j = FDOIT_PACK_COUNT - 1; j > i; --j)
				{
					fragments.depths[j].yzw = fragments.depths[j].xyz;
					fragments.depths[j].x = fragments.depths[j - 1].w;

					fragments.colors[j].yzw = fragments.colors[j].xyz;
					fragments.colors[j].x = fragments.colors[j - 1].w;
				}

				
				[branch]if(frag.depth > fragments.depths[i][0])
				{
					fragments.depths[i].yzw = fragments.depths[i].xyz;
					fragments.colors[i].yzw = fragments.colors[i].xyz;
					fragments.depths[i][0] = frag.depth;
					fragments.colors[i][0] = frag.color;
					break;
				}
				[branch]if(frag.depth > fragments.depths[i][1])
				{
					fragments.depths[i].zw = fragments.depths[i].yz;
					fragments.colors[i].zw = fragments.colors[i].yz;
					fragments.depths[i][1] = frag.depth;
					fragments.colors[i][1] = frag.color;
					break;
				}
				[branch]if(frag.depth > fragments.depths[i][2])
				{
					fragments.depths[i].w = fragments.depths[i].z;
					fragments.colors[i].w = fragments.colors[i].z;
					fragments.depths[i][2] = frag.depth;
					fragments.colors[i][2] = frag.color;
					break;
				}
				fragments.depths[i][3] = frag.depth;
				fragments.colors[i][3] = frag.color;
				break;
			}
			
			// old & slow version
			/*
			if(frag.depth > fragments[i].depth)
			{
				//slot++;
				[unroll]
				for(uint j = FDOIT_FRAGMENT_DEPTH - 1; j > i; --j)
				{
					fragments[j] = fragments[j - 1];
				}
				fragments[i] = frag;
				
				break;
			}
			*/
			
		}

	}
	
	[unroll]for(uint i = 1; i <= FDOIT_PACK_COUNT; ++i)
	{
		[unroll] for(int j = 1; j <= 4; ++j)
		{
			const float4 frag_color = Unpack(fragments.colors[FDOIT_PACK_COUNT - i][4 - j]);
			color.rgb = lerp(color.rgb, frag_color.rgb, frag_color.a);
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
	uint2 screenPos = uint2(input.position.xy);

#if _DEBUG
	if(g_Debug)
	{
		return FDOITDebugFragments(screenPos);
	}
#endif
	return FDOITGetFragments(screenPos);
}