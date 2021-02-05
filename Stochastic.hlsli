// Copyright (c) 2011 NVIDIA Corporation. All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, NONINFRINGEMENT,IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA 
// OR ITS SUPPLIERS BE  LIABLE  FOR  ANY  DIRECT, SPECIAL,  INCIDENTAL,  INDIRECT,  OR  
// CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS 
// OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY 
// OTHER PECUNIARY LOSS) ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, 
// EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
// Please direct any bugs or questions to SDKFeedback@nvidia.com

#include "Header.hlsli"
#include "Shading.hlsli"

cbuffer StochasticBuffer : register(b2)
{
	uint g_randMaskSizePowOf2MinusOne;
    uint g_randMaskAlphaValues;
    uint g_randomOffset;
    uint g_pad;
};

// Assuming that tTransmittance and tBackground have 8 samples per pixel
#define NUM_MSAA_SAMPLES 8

// Alpha correction (Section 3.2 of the paper)
// Removes noise for pixels with low depth complexity (1-2 layers / pixel)

//#define USE_ALPHA_CORRECTION 0

#define Geometry_VSOut VOut

struct FullscreenVSOut
{
	float2 uv : TEXCOORD0;
	float4 pos : SV_POSITION;
};

Texture2D<uint> tRandoms                : register(t4);
Texture2DArray<float4> tResolvedColor   : register(t4);
Texture2DMS<float> tTransmittance       : register(t5);
Texture2DMS<float3> tBackground         : register(t6);

// from http://www.concentric.net/~Ttwang/tech/inthash.htm
uint ihash(uint seed)
{
    seed = (seed+0x7ed55d16u) + (seed<<12);
    seed = (seed^0xc761c23cu) ^ (seed>>19);
    seed = (seed+0x165667b1u) + (seed<<5);
    seed = (seed+0xd3a2646cu) ^ (seed<<9);
    seed = (seed+0xfd7046c5u) + (seed<<3);
    seed = (seed^0xb55a4f09u) ^ (seed>>16);
    return seed;
}

// pixelPos = 2D screen-space position for the current fragment
// primID = auto-generated primitive id for the current fragment
uint getlayerseed(uint2 pixelPos, int primID)
{
    // Seeding by primitive id, as described in Section 5 of the paper.
    uint layerseed = primID * 32;

    // For simulating more than 8 samples per pixel, the algorithm
    // can be run in multiple passes with different random offsets.
    layerseed += g_randomOffset;

    layerseed += (pixelPos.x << 10) + (pixelPos.y << 20);
    return layerseed;
}

// Compute mask based on primitive id and alpha
uint randmaskwide(uint2 pixelPos, float alpha, int primID)
{
    // Generate seed based on fragment coords and primitive id
    uint seed = getlayerseed(pixelPos, primID);

    // Compute a hash with uniform distribution
    seed = ihash(seed);

    // Modulo operation
    seed &= g_randMaskSizePowOf2MinusOne;

    // Quantize alpha from [0.0,1.0] to [0,ALPHA_VALUES]
    uint2 coords = uint2(seed, alpha * g_randMaskAlphaValues);

    return tRandoms.Load(int3(coords, 0)).r;
}

float4 CompositeStochasticColors ( FullscreenVSOut IN, int numLayers )
{
    int2 pos2d = int2(IN.pos.xy);

	//return tResolvedColor.Load(int4(pos2d, 3, 0));

    float3 backgroundColor = 0.0;
    float trueTransmittance = 0.0;
    // The MSAA background colors must be multiplied with 1-alpha per sample
    [unroll]
    for (int sampleId = 0; sampleId < NUM_MSAA_SAMPLES; ++sampleId)
    {
        float T = tTransmittance.Load(pos2d, sampleId).r;
        backgroundColor += T * tBackground.Load(pos2d, sampleId).rgb;
        trueTransmittance += T;
    }
    backgroundColor *= 1.0/NUM_MSAA_SAMPLES;
    trueTransmittance *= 1.0/NUM_MSAA_SAMPLES;

    // Compute average transparent color ("R/S" in the paper)
    float4 transparentColor = 0;
    [unroll]
    for (int layerId = 0; layerId < numLayers; ++layerId)
    {
        transparentColor += tResolvedColor.Load(int4(pos2d, layerId, 0));
    }
    transparentColor /= numLayers;

#if USE_ALPHA_CORRECTION
    if (transparentColor.a > 0.0)
    {
        transparentColor *= ((1.0 - trueTransmittance) / transparentColor.a);
    }
#endif

    return float4(transparentColor.rgb + backgroundColor.rgb, 1.0);
}