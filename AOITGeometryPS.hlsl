// Copyright 2011 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.

//#include "AOIT.hlsli"
#include "AOITFragmentList.hlsli"
#include "Header.hlsli"
#include "Shading.hlsli"

void main(VOut input)
{

	/*float intens = light_count / 32.0f;

	return lerp(float4(out_color, diffuse.a), float4(intens,intens,intens,intens), 0.5f);*/
	//return float4(out_color, diffuse.a) + diffuse;

	
	float surfaceDepth = input.clippos.w;

	float4 surfaceColor = saturate(ComputeShading(input));

	uint coverageMask = 0;

	uint newNodeAddress;

	int2 screenAddress = int2(input.position.xy);

	if (FL_AllocNode(newNodeAddress)) {       
        // Fill node
        FragmentListNode node;            
        node.color    = FL_PackColor(surfaceColor);
        node.depth    = FL_PackDepthAndCoverage(surfaceDepth, coverageMask);                 
            
        // Insert node!
        FL_InsertNode(screenAddress, newNodeAddress, node);
	}
}