#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer LightingBuffer
// {
//
//   uint g_NumDirectionalLights;       // Offset:    0 Size:     4 [unused]
//   uint g_NumPointLights;             // Offset:    4 Size:     4 [unused]
//   uint g_NumSpotLights;              // Offset:    8 Size:     4 [unused]
//   float g_InvDistancePerIntensity;   // Offset:   12 Size:     4 [unused]
//   float g_GlobalAmbient;             // Offset:   16 Size:     4
//
// }
//
// cbuffer Material
// {
//
//   float3 Diffuse;                    // Offset:    0 Size:    12
//   float3 Specular;                   // Offset:   16 Size:    12 [unused]
//   float Shininess;                   // Offset:   28 Size:     4 [unused]
//   float3 Emissive;                   // Offset:   32 Size:    12
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// Sampler                           sampler      NA          NA             s0      1 
// DiffuseTex                        texture  float4          2d             t0      1 
// LightingBuffer                    cbuffer      NA          NA            cb0      1 
// Material                          cbuffer      NA          NA            cb1      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyz         0     NONE   float       
// NORMAL                   0   xyz         1     NONE   float       
// TEXCOORD                 0   xy          2     NONE   float   xy  
// TANGENT                  0   xyz         3     NONE   float       
// BINORMAL                 0   xyz         4     NONE   float       
// TEXCOORD                 1   xyzw        5     NONE   float       
// SV_POSITION              0   xyzw        6      POS   float       
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Target                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[2], immediateIndexed
dcl_constantbuffer CB1[3], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_input_ps linear v2.xy
dcl_output o0.xyzw
dcl_temps 2
sample_indexable(texture2d)(float,float,float,float) r0.xyzw, v2.xyxx, t0.wxyz, s0
add r1.x, r0.x, l(-0.050000)
min r0.x, r0.x, l(0.500000)
lt r1.x, r1.x, l(0.000000)
discard_nz r1.x
mul r1.xyz, r0.yzwy, cb1[0].xyzx
mad r1.xyz, cb0[1].xxxx, r1.xyzx, cb1[2].xyzx
mad r0.yzw, r0.yyzw, cb1[0].xxyz, r1.xxyz
mul o0.xyz, r0.xxxx, r0.yzwy
mov o0.w, r0.x
ret 
// Approximately 11 instruction slots used
#endif

const BYTE g_StochasticColor[] =
{
     68,  88,  66,  67,  65, 213, 
     24,  14,  12, 126, 159,   3, 
    228,  22, 236, 219,  20, 135, 
    175,  70,   1,   0,   0,   0, 
     84,   7,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    240,   3,   0,   0, 224,   4, 
      0,   0,  20,   5,   0,   0, 
    184,   6,   0,   0,  82,  68, 
     69,  70, 180,   3,   0,   0, 
      2,   0,   0,   0, 232,   0, 
      0,   0,   4,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
    255, 255,   0,   1,   0,   0, 
    140,   3,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
    188,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 196,   0,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 207,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    222,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  83,  97, 109, 112, 
    108, 101, 114,   0,  68, 105, 
    102, 102, 117, 115, 101,  84, 
    101, 120,   0,  76, 105, 103, 
    104, 116, 105, 110, 103,  66, 
    117, 102, 102, 101, 114,   0, 
     77,  97, 116, 101, 114, 105, 
     97, 108,   0, 171, 207,   0, 
      0,   0,   5,   0,   0,   0, 
     24,   1,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 222,   0, 
      0,   0,   4,   0,   0,   0, 
    156,   2,   0,   0,  48,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 224,   1, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   2,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  36,   2,   0,   0, 
      4,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   2,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     53,   2,   0,   0,   8,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   2, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  69,   2, 
      0,   0,  12,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0, 104,   2,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 140,   2,   0,   0, 
     16,   0,   0,   0,   4,   0, 
      0,   0,   2,   0,   0,   0, 
    104,   2,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    103,  95,  78, 117, 109,  68, 
    105, 114, 101,  99, 116, 105, 
    111, 110,  97, 108,  76, 105, 
    103, 104, 116, 115,   0, 100, 
    119, 111, 114, 100,   0, 171, 
    171, 171,   0,   0,  19,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 247,   1, 
      0,   0, 103,  95,  78, 117, 
    109,  80, 111, 105, 110, 116, 
     76, 105, 103, 104, 116, 115, 
      0, 103,  95,  78, 117, 109, 
     83, 112, 111, 116,  76, 105, 
    103, 104, 116, 115,   0, 103, 
     95,  73, 110, 118,  68, 105, 
    115, 116,  97, 110,  99, 101, 
     80, 101, 114,  73, 110, 116, 
    101, 110, 115, 105, 116, 121, 
      0, 102, 108, 111,  97, 116, 
      0, 171, 171, 171,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     95,   2,   0,   0, 103,  95, 
     71, 108, 111,  98,  97, 108, 
     65, 109,  98, 105, 101, 110, 
    116,   0,  60,   3,   0,   0, 
      0,   0,   0,   0,  12,   0, 
      0,   0,   2,   0,   0,   0, 
     76,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    112,   3,   0,   0,  16,   0, 
      0,   0,  12,   0,   0,   0, 
      0,   0,   0,   0,  76,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 121,   3, 
      0,   0,  28,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0, 104,   2,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 131,   3,   0,   0, 
     32,   0,   0,   0,  12,   0, 
      0,   0,   2,   0,   0,   0, 
     76,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     68, 105, 102, 102, 117, 115, 
    101,   0, 102, 108, 111,  97, 
    116,  51,   0, 171,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     68,   3,   0,   0,  83, 112, 
    101,  99, 117, 108,  97, 114, 
      0,  83, 104, 105, 110, 105, 
    110, 101, 115, 115,   0,  69, 
    109, 105, 115, 115, 105, 118, 
    101,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  49,  48,  46,  49,   0, 
     73,  83,  71,  78, 232,   0, 
      0,   0,   7,   0,   0,   0, 
      8,   0,   0,   0, 176,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      7,   0,   0,   0, 185,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      7,   0,   0,   0, 192,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      3,   3,   0,   0, 201,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
      7,   0,   0,   0, 209,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   4,   0,   0,   0, 
      7,   0,   0,   0, 192,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   5,   0,   0,   0, 
     15,   0,   0,   0, 218,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   6,   0,   0,   0, 
     15,   0,   0,   0,  80,  79, 
     83,  73,  84,  73,  79,  78, 
      0,  78,  79,  82,  77,  65, 
     76,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  84, 
     65,  78,  71,  69,  78,  84, 
      0,  66,  73,  78,  79,  82, 
     77,  65,  76,   0,  83,  86, 
     95,  80,  79,  83,  73,  84, 
     73,  79,  78,   0, 171, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  97, 114, 103, 101, 
    116,   0, 171, 171,  83,  72, 
     69,  88, 156,   1,   0,   0, 
     80,   0,   0,   0, 103,   0, 
      0,   0, 106,   8,   0,   1, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,  90,   0,   0,   3, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   0,   0, 
      0,   0,  85,  85,   0,   0, 
     98,  16,   0,   3,  50,  16, 
     16,   0,   2,   0,   0,   0, 
    101,   0,   0,   3, 242,  32, 
     16,   0,   0,   0,   0,   0, 
    104,   0,   0,   2,   2,   0, 
      0,   0,  69,   0,   0, 139, 
    194,   0,   0, 128,  67,  85, 
     21,   0, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  16, 
     16,   0,   2,   0,   0,   0, 
     54, 121,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0, 205, 204, 
     76, 189,  51,   0,   0,   7, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
     49,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  13,   0, 
      4,   3,  10,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   8, 114,   0,  16,   0, 
      1,   0,   0,   0, 150,   7, 
     16,   0,   0,   0,   0,   0, 
     70, 130,  32,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     50,   0,   0,  11, 114,   0, 
     16,   0,   1,   0,   0,   0, 
      6, 128,  32,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  70, 130,  32,   0, 
      1,   0,   0,   0,   2,   0, 
      0,   0,  50,   0,   0,  10, 
    226,   0,  16,   0,   0,   0, 
      0,   0,  86,  14,  16,   0, 
      0,   0,   0,   0,   6, 137, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   6,   9, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7, 114,  32, 
     16,   0,   0,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0, 150,   7,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 130,  32,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 148,   0,   0,   0, 
     11,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   7,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};
