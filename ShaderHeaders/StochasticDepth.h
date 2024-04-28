#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer StochasticBuffer
// {
//
//   uint g_randMaskSizePowOf2MinusOne; // Offset:    0 Size:     4
//   uint g_randMaskAlphaValues;        // Offset:    4 Size:     4
//   uint g_randomOffset;               // Offset:    8 Size:     4
//   uint g_pad;                        // Offset:   12 Size:     4 [unused]
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
// tRandoms                          texture    uint          2d             t4      1 
// StochasticBuffer                  cbuffer      NA          NA            cb2      1 
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
// SV_POSITION              0   xyzw        6      POS   float   xy  
// SV_PrimitiveID           0   x           7   PRIMID    uint   x   
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Coverage              0    N/A    oMask COVERAGE    uint    YES
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB2[1], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (uint,uint,uint,uint) t4
dcl_input_ps linear v2.xy
dcl_input_ps_siv linear noperspective v6.xy, position
dcl_input_ps_sgv constant v7.x, primitive_id
dcl_output oMask
dcl_temps 2
sample_indexable(texture2d)(float,float,float,float) r0.x, v2.xyxx, t0.wxyz, s0
add r0.y, r0.x, l(-0.050000)
min r0.x, r0.x, l(0.500000)
lt r0.y, r0.y, l(0.000000)
discard_nz r0.y
utof r0.y, cb2[0].y
mul r0.x, r0.y, r0.x
ftou r0.y, r0.x
ftou r1.xy, v6.xyxx
ishl r1.xy, r1.xyxx, l(10, 20, 0, 0)
iadd r1.x, r1.y, r1.x
ishl r1.y, v7.x, l(5)
iadd r1.y, r1.y, cb2[0].z
iadd r1.x, r1.x, r1.y
iadd r1.y, r1.x, l(0x7ed55d16)
ishl r1.x, r1.x, l(12)
iadd r1.x, r1.x, r1.y
xor r1.y, r1.x, l(0xc761c23c)
ushr r1.x, r1.x, l(19)
xor r1.x, r1.x, r1.y
iadd r1.y, r1.x, l(0x165667b1)
ishl r1.x, r1.x, l(5)
iadd r1.x, r1.x, r1.y
iadd r1.y, r1.x, l(0xd3a2646c)
ishl r1.x, r1.x, l(9)
xor r1.x, r1.x, r1.y
iadd r1.y, r1.x, l(0xfd7046c5)
ishl r1.x, r1.x, l(3)
iadd r1.x, r1.x, r1.y
xor r1.y, r1.x, l(0xb55a4f09)
ushr r1.x, r1.x, l(16)
xor r1.x, r1.x, r1.y
and r0.x, r1.x, cb2[0].x
mov r0.zw, l(0,0,0,0)
ld_indexable(texture2d)(uint,uint,uint,uint) r0.x, r0.xyzw, t4.xyzw
mov oMask, r0.x
ret 
// Approximately 37 instruction slots used
#endif

const BYTE g_StochasticDepth[] =
{
     68,  88,  66,  67, 156, 106, 
     72, 170,  62,  60,  32,  50, 
     42, 130, 179, 195,  48, 147, 
    255,  76,   1,   0,   0,   0, 
    228,   8,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    124,   2,   0,   0, 148,   3, 
      0,   0, 200,   3,   0,   0, 
     72,   8,   0,   0,  82,  68, 
     69,  70,  64,   2,   0,   0, 
      1,   0,   0,   0, 236,   0, 
      0,   0,   4,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
    255, 255,   0,   1,   0,   0, 
     23,   2,   0,   0,  82,  68, 
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
      0,   0,   2,   0,   0,   0, 
      4,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      4,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    216,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  83,  97, 109, 112, 
    108, 101, 114,   0,  68, 105, 
    102, 102, 117, 115, 101,  84, 
    101, 120,   0, 116,  82,  97, 
    110, 100, 111, 109, 115,   0, 
     83, 116, 111,  99, 104,  97, 
    115, 116, 105,  99,  66, 117, 
    102, 102, 101, 114,   0, 171, 
    171, 171, 216,   0,   0,   0, 
      4,   0,   0,   0,   4,   1, 
      0,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 164,   1,   0,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,   2,   0,   0,   0, 
    200,   1,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    236,   1,   0,   0,   4,   0, 
      0,   0,   4,   0,   0,   0, 
      2,   0,   0,   0, 200,   1, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   2,   2, 
      0,   0,   8,   0,   0,   0, 
      4,   0,   0,   0,   2,   0, 
      0,   0, 200,   1,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  17,   2,   0,   0, 
     12,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
    200,   1,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    103,  95, 114,  97, 110, 100, 
     77,  97, 115, 107,  83, 105, 
    122, 101,  80, 111, 119,  79, 
    102,  50,  77, 105, 110, 117, 
    115,  79, 110, 101,   0, 100, 
    119, 111, 114, 100,   0, 171, 
      0,   0,  19,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 193,   1,   0,   0, 
    103,  95, 114,  97, 110, 100, 
     77,  97, 115, 107,  65, 108, 
    112, 104,  97,  86,  97, 108, 
    117, 101, 115,   0, 103,  95, 
    114,  97, 110, 100, 111, 109, 
     79, 102, 102, 115, 101, 116, 
      0, 103,  95, 112,  97, 100, 
      0,  77, 105,  99, 114, 111, 
    115, 111, 102, 116,  32,  40, 
     82,  41,  32,  72,  76,  83, 
     76,  32,  83, 104,  97, 100, 
    101, 114,  32,  67, 111, 109, 
    112, 105, 108, 101, 114,  32, 
     49,  48,  46,  49,   0, 171, 
     73,  83,  71,  78,  16,   1, 
      0,   0,   8,   0,   0,   0, 
      8,   0,   0,   0, 200,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      7,   0,   0,   0, 209,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      7,   0,   0,   0, 216,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      3,   3,   0,   0, 225,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
      7,   0,   0,   0, 233,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   4,   0,   0,   0, 
      7,   0,   0,   0, 216,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   5,   0,   0,   0, 
     15,   0,   0,   0, 242,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   6,   0,   0,   0, 
     15,   3,   0,   0, 254,   0, 
      0,   0,   0,   0,   0,   0, 
      7,   0,   0,   0,   1,   0, 
      0,   0,   7,   0,   0,   0, 
      1,   1,   0,   0,  80,  79, 
     83,  73,  84,  73,  79,  78, 
      0,  78,  79,  82,  77,  65, 
     76,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  84, 
     65,  78,  71,  69,  78,  84, 
      0,  66,  73,  78,  79,  82, 
     77,  65,  76,   0,  83,  86, 
     95,  80,  79,  83,  73,  84, 
     73,  79,  78,   0,  83,  86, 
     95,  80, 114, 105, 109, 105, 
    116, 105, 118, 101,  73,  68, 
      0, 171, 171, 171,  79,  83, 
     71,  78,  44,   0,   0,   0, 
      1,   0,   0,   0,   8,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
    255, 255, 255, 255,   1,  14, 
      0,   0,  83,  86,  95,  67, 
    111, 118, 101, 114,  97, 103, 
    101,   0,  83,  72,  69,  88, 
    120,   4,   0,   0,  80,   0, 
      0,   0,  30,   1,   0,   0, 
    106,   8,   0,   1,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      2,   0,   0,   0,   1,   0, 
      0,   0,  90,   0,   0,   3, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   0,   0, 
      0,   0,  85,  85,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   4,   0,   0,   0, 
     68,  68,   0,   0,  98,  16, 
      0,   3,  50,  16,  16,   0, 
      2,   0,   0,   0, 100,  32, 
      0,   4,  50,  16,  16,   0, 
      6,   0,   0,   0,   1,   0, 
      0,   0,  99,   8,   0,   4, 
     18,  16,  16,   0,   7,   0, 
      0,   0,   7,   0,   0,   0, 
    101,   0,   0,   2,   0, 240, 
      0,   0, 104,   0,   0,   2, 
      2,   0,   0,   0,  69,   0, 
      0, 139, 194,   0,   0, 128, 
     67,  85,  21,   0,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  16,  16,   0,   2,   0, 
      0,   0,  54, 121,  16,   0, 
      0,   0,   0,   0,   0,  96, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   7,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
    205, 204,  76, 189,  51,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  63,  49,   0,   0,   7, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     13,   0,   4,   3,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     86,   0,   0,   6,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     26, 128,  32,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
     56,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  28,   0, 
      0,   5,  34,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     28,   0,   0,   5,  50,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  16,  16,   0,   6,   0, 
      0,   0,  41,   0,   0,  10, 
     50,   0,  16,   0,   1,   0, 
      0,   0,  70,   0,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,  10,   0,   0,   0, 
     20,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     30,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  41,   0, 
      0,   7,  34,   0,  16,   0, 
      1,   0,   0,   0,  10,  16, 
     16,   0,   7,   0,   0,   0, 
      1,  64,   0,   0,   5,   0, 
      0,   0,  30,   0,   0,   8, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,  42, 128, 
     32,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,  30,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  30,   0,   0,   7, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,  22,  93, 213, 126, 
     41,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
     12,   0,   0,   0,  30,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  87,   0,   0,   7, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,  60, 194,  97, 199, 
     85,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
     19,   0,   0,   0,  87,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  30,   0,   0,   7, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0, 177, 103,  86,  22, 
     41,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      5,   0,   0,   0,  30,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  30,   0,   0,   7, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0, 108, 100, 162, 211, 
     41,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      9,   0,   0,   0,  87,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  30,   0,   0,   7, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0, 197,  70, 112, 253, 
     41,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      3,   0,   0,   0,  30,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  87,   0,   0,   7, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   9,  79,  90, 181, 
     85,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
     16,   0,   0,   0,  87,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,   1,   0,   0,   8, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  10, 128, 
     32,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   8, 194,   0,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     45,   0,   0, 137, 194,   0, 
      0, 128,   3,  17,  17,   0, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 126, 
     16,   0,   4,   0,   0,   0, 
     54,   0,   0,   4,   1, 240, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    148,   0,   0,   0,  37,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,   4,   0,   0,   0, 
     16,   0,   0,   0,   8,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
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
      0,   0
};
