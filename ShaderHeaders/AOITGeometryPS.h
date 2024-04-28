#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer FL_Constants
// {
//
//   uint mMaxListNodes;                // Offset:    0 Size:     4
//
// }
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
// Resource bind info for gFragmentListNodesUAV
// {
//
//   struct FragmentListNode
//   {
//       
//       uint next;                     // Offset:    0
//       float depth;                   // Offset:    4
//       uint color;                    // Offset:    8
//
//   } $Element;                        // Offset:    0 Size:    12
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
// gFragmentListFirstNodeAddressUAV        UAV    uint          2d             u0      1 
// gFragmentListNodesUAV                 UAV  struct     r/w+cnt             u1      1 
// LightingBuffer                    cbuffer      NA          NA            cb0      1 
// Material                          cbuffer      NA          NA            cb1      1 
// FL_Constants                      cbuffer      NA          NA            cb2      1 
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
// TEXCOORD                 1   xyzw        5     NONE   float      w
// SV_POSITION              0   xyzw        6      POS   float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// no Output
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB2[1], immediateIndexed
dcl_constantbuffer CB0[2], immediateIndexed
dcl_constantbuffer CB1[3], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_uav_typed_texture2d (uint,uint,uint,uint) u0
dcl_uav_structured_opc u1, 12
dcl_input_ps linear v2.xy
dcl_input_ps linear v5.w
dcl_input_ps_siv linear noperspective v6.xy, position
dcl_temps 3
sample_indexable(texture2d)(float,float,float,float) r0.xyzw, v2.xyxx, t0.wxyz, s0
add r1.x, r0.x, l(-0.050000)
lt r1.x, r1.x, l(0.000000)
discard_nz r1.x
imm_atomic_alloc r1.x, u1
uge r1.y, cb2[0].x, r1.x
if_nz r1.y
  mul r1.yzw, r0.yyzw, cb1[0].xxyz
  mad r1.yzw, cb0[1].xxxx, r1.yyzw, cb1[2].xxyz
  mad_sat r2.xyz, r0.yzwy, cb1[0].xyzx, r1.yzwy
  min_sat r2.w, r0.x, l(0.500000)
  ftoi r0.xy, v6.xyxx
  mul r2.xyzw, r2.xyzw, l(255.000000, 255.000000, 255.000000, 255.000000)
  ftou r2.xyzw, r2.xyzw
  imad r0.z, r2.y, l(256), r2.x
  imad r0.z, r2.z, l(0x00010000), r0.z
  imad r2.z, r2.w, l(0x01000000), r0.z
  and r2.y, v5.w, l(-16)
  imm_atomic_exch r2.x, u0, r0.xyxx, r1.x
  store_structured u1.xyz, r1.x, l(0), r2.xyzx
endif 
ret 
// Approximately 22 instruction slots used
#endif

const BYTE g_AOITGeometryPS[] =
{
     68,  88,  66,  67,  29,  28, 
     85, 224,  62, 246, 207,  94, 
    138,  97, 222,  27,  75, 190, 
    233, 187,   1,   0,   0,   0, 
    144,  10,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    220,   5,   0,   0, 204,   6, 
      0,   0, 220,   6,   0,   0, 
    244,   9,   0,   0,  82,  68, 
     69,  70, 160,   5,   0,   0, 
      4,   0,   0,   0, 140,   1, 
      0,   0,   7,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
    255, 255,   0,   1,   0,   0, 
    120,   5,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
     28,   1,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  36,   1,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0,  47,   1, 
      0,   0,   4,   0,   0,   0, 
      4,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     80,   1,   0,   0,  11,   0, 
      0,   0,   6,   0,   0,   0, 
      1,   0,   0,   0,  12,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 102,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 117,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    126,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  83,  97, 109, 112, 
    108, 101, 114,   0,  68, 105, 
    102, 102, 117, 115, 101,  84, 
    101, 120,   0, 103,  70, 114, 
     97, 103, 109, 101, 110, 116, 
     76, 105, 115, 116,  70, 105, 
    114, 115, 116,  78, 111, 100, 
    101,  65, 100, 100, 114, 101, 
    115, 115,  85,  65,  86,   0, 
    103,  70, 114,  97, 103, 109, 
    101, 110, 116,  76, 105, 115, 
    116,  78, 111, 100, 101, 115, 
     85,  65,  86,   0,  76, 105, 
    103, 104, 116, 105, 110, 103, 
     66, 117, 102, 102, 101, 114, 
      0,  77,  97, 116, 101, 114, 
    105,  97, 108,   0,  70,  76, 
     95,  67, 111, 110, 115, 116, 
     97, 110, 116, 115,   0, 171, 
    126,   1,   0,   0,   1,   0, 
      0,   0, 236,   1,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    102,   1,   0,   0,   5,   0, 
      0,   0,  76,   2,   0,   0, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    117,   1,   0,   0,   4,   0, 
      0,   0, 160,   3,   0,   0, 
     48,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     80,   1,   0,   0,   1,   0, 
      0,   0, 144,   4,   0,   0, 
     12,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     20,   2,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      2,   0,   0,   0,  40,   2, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 109,  77, 
     97, 120,  76, 105, 115, 116, 
     78, 111, 100, 101, 115,   0, 
    100, 119, 111, 114, 100,   0, 
      0,   0,  19,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  34,   2,   0,   0, 
     20,   3,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,  40,   2, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  43,   3, 
      0,   0,   4,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,  40,   2,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  60,   3,   0,   0, 
      8,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
     40,   2,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     76,   3,   0,   0,  12,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0, 108,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 144,   3, 
      0,   0,  16,   0,   0,   0, 
      4,   0,   0,   0,   2,   0, 
      0,   0, 108,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 103,  95,  78, 117, 
    109,  68, 105, 114, 101,  99, 
    116, 105, 111, 110,  97, 108, 
     76, 105, 103, 104, 116, 115, 
      0, 103,  95,  78, 117, 109, 
     80, 111, 105, 110, 116,  76, 
    105, 103, 104, 116, 115,   0, 
    103,  95,  78, 117, 109,  83, 
    112, 111, 116,  76, 105, 103, 
    104, 116, 115,   0, 103,  95, 
     73, 110, 118,  68, 105, 115, 
    116,  97, 110,  99, 101,  80, 
    101, 114,  73, 110, 116, 101, 
    110, 115, 105, 116, 121,   0, 
    102, 108, 111,  97, 116,   0, 
      0,   0,   3,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 102,   3,   0,   0, 
    103,  95,  71, 108, 111,  98, 
     97, 108,  65, 109,  98, 105, 
    101, 110, 116,   0,  64,   4, 
      0,   0,   0,   0,   0,   0, 
     12,   0,   0,   0,   2,   0, 
      0,   0,  80,   4,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 116,   4,   0,   0, 
     16,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
     80,   4,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    125,   4,   0,   0,  28,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0, 108,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 135,   4, 
      0,   0,  32,   0,   0,   0, 
     12,   0,   0,   0,   2,   0, 
      0,   0,  80,   4,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  68, 105, 102, 102, 
    117, 115, 101,   0, 102, 108, 
    111,  97, 116,  51,   0, 171, 
      1,   0,   3,   0,   1,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  72,   4,   0,   0, 
     83, 112, 101,  99, 117, 108, 
     97, 114,   0,  83, 104, 105, 
    110, 105, 110, 101, 115, 115, 
      0,  69, 109, 105, 115, 115, 
    105, 118, 101,   0, 184,   4, 
      0,   0,   0,   0,   0,   0, 
     12,   0,   0,   0,   2,   0, 
      0,   0,  84,   5,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  36,  69, 108, 101, 
    109, 101, 110, 116,   0,  70, 
    114,  97, 103, 109, 101, 110, 
    116,  76, 105, 115, 116,  78, 
    111, 100, 101,   0, 110, 101, 
    120, 116,   0, 171,   0,   0, 
     19,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     34,   2,   0,   0, 100, 101, 
    112, 116, 104,   0, 171, 171, 
      0,   0,   3,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 102,   3,   0,   0, 
     99, 111, 108, 111, 114,   0, 
    171, 171, 210,   4,   0,   0, 
    216,   4,   0,   0,   0,   0, 
      0,   0, 252,   4,   0,   0, 
      4,   5,   0,   0,   4,   0, 
      0,   0,  40,   5,   0,   0, 
    216,   4,   0,   0,   8,   0, 
      0,   0,   5,   0,   0,   0, 
      1,   0,   3,   0,   0,   0, 
      3,   0,  48,   5,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 193,   4, 
      0,   0,  77, 105,  99, 114, 
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
     15,   8,   0,   0, 218,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   6,   0,   0,   0, 
     15,   3,   0,   0,  80,  79, 
     83,  73,  84,  73,  79,  78, 
      0,  78,  79,  82,  77,  65, 
     76,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  84, 
     65,  78,  71,  69,  78,  84, 
      0,  66,  73,  78,  79,  82, 
     77,  65,  76,   0,  83,  86, 
     95,  80,  79,  83,  73,  84, 
     73,  79,  78,   0, 171, 171, 
     79,  83,  71,  78,   8,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  83,  72, 
     69,  88,  16,   3,   0,   0, 
     80,   0,   0,   0, 196,   0, 
      0,   0, 106,   8,   0,   1, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   0,   0,   0,   0, 
     85,  85,   0,   0, 156,  24, 
      0,   4,   0, 224,  17,   0, 
      0,   0,   0,   0,  68,  68, 
      0,   0, 158,   0, 128,   4, 
      0, 224,  17,   0,   1,   0, 
      0,   0,  12,   0,   0,   0, 
     98,  16,   0,   3,  50,  16, 
     16,   0,   2,   0,   0,   0, 
     98,  16,   0,   3, 130,  16, 
     16,   0,   5,   0,   0,   0, 
    100,  32,   0,   4,  50,  16, 
     16,   0,   6,   0,   0,   0, 
      1,   0,   0,   0, 104,   0, 
      0,   2,   3,   0,   0,   0, 
     69,   0,   0, 139, 194,   0, 
      0, 128,  67,  85,  21,   0, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  16,  16,   0, 
      2,   0,   0,   0,  54, 121, 
     16,   0,   0,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0, 205, 204,  76, 189, 
     49,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  13,   0, 
      4,   3,  10,   0,  16,   0, 
      1,   0,   0,   0, 178,   0, 
      0,   5,  18,   0,  16,   0, 
      1,   0,   0,   0,   0, 224, 
     17,   0,   1,   0,   0,   0, 
     80,   0,   0,   8,  34,   0, 
     16,   0,   1,   0,   0,   0, 
     10, 128,  32,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  31,   0,   4,   3, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   8, 
    226,   0,  16,   0,   1,   0, 
      0,   0,  86,  14,  16,   0, 
      0,   0,   0,   0,   6, 137, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  11, 226,   0,  16,   0, 
      1,   0,   0,   0,   6, 128, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  86,  14, 
     16,   0,   1,   0,   0,   0, 
      6, 137,  32,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
     50,  32,   0,  10, 114,   0, 
     16,   0,   2,   0,   0,   0, 
    150,   7,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 150,   7,  16,   0, 
      1,   0,   0,   0,  51,  32, 
      0,   7, 130,   0,  16,   0, 
      2,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  63,  27,   0,   0,   5, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,  16,  16,   0, 
      6,   0,   0,   0,  56,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
    127,  67,   0,   0, 127,  67, 
      0,   0, 127,  67,   0,   0, 
    127,  67,  28,   0,   0,   5, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  35,   0, 
      0,   9,  66,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16,   0,   2,   0,   0,   0, 
      1,  64,   0,   0,   0,   1, 
      0,   0,  10,   0,  16,   0, 
      2,   0,   0,   0,  35,   0, 
      0,   9,  66,   0,  16,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   2,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      1,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  35,   0, 
      0,   9,  66,   0,  16,   0, 
      2,   0,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   1,  42,   0,  16,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   7,  34,   0,  16,   0, 
      2,   0,   0,   0,  58,  16, 
     16,   0,   5,   0,   0,   0, 
      1,  64,   0,   0, 240, 255, 
    255, 255, 184,   0,   0,   9, 
     18,   0,  16,   0,   2,   0, 
      0,   0,   0, 224,  17,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0, 168,   0,   0,   9, 
    114, 224,  17,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  21,   0,   0,   1, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 148,   0,   0,   0, 
     22,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   7,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0
};
