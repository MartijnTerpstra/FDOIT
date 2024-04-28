#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// tResolvedColor                    texture  float4     2darray             t4      1 
// tTransmittance                    texture   float        2dMS             t5      1 
// tBackground                       texture  float3        2dMS             t6      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// TEXCOORD                 0   xy          0     NONE   float       
// SV_POSITION              0   xyzw        1      POS   float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_TARGET                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_resource_texture2darray (float,float,float,float) t4
dcl_resource_texture2dms(0) (float,float,float,float) t5
dcl_resource_texture2dms(0) (float,float,float,float) t6
dcl_input_ps_siv linear noperspective v1.xy, position
dcl_output o0.xyzw
dcl_temps 6
ftoi r0.xy, v1.xyxx
mov r0.zw, l(0,0,1,0)
ld_indexable(texture2darray)(float,float,float,float) r1.xyzw, r0.xyww, t4.xyzw
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r0.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r0.z, l(2)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r0.xyzw, t4.xyzw
mov r3.xyw, r0.xyxw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(3)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(4)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(5)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(6)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(7)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(8)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(9)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(10)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(11)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(12)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(13)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(14)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mov r3.z, l(15)
ld_indexable(texture2darray)(float,float,float,float) r2.xyzw, r3.xyzw, t4.xyzw
add r1.xyzw, r1.xyzw, r2.xyzw
mul r2.xyzw, r1.xyzw, l(0.062500, 0.062500, 0.062500, 0.062500)
lt r0.z, l(0.000000), r1.w
ldms_indexable(texture2dms)(float,float,float,float) r1.x, r0.xyww, t5.xyzw, l(0)
ldms_indexable(texture2dms)(float,float,float,float) r1.y, r0.xyww, t5.yxzw, l(1)
add r1.z, r1.y, r1.x
ldms_indexable(texture2dms)(float,float,float,float) r1.w, r0.xyww, t5.yzwx, l(2)
add r1.z, r1.w, r1.z
ldms_indexable(texture2dms)(float,float,float,float) r3.x, r0.xyww, t5.xyzw, l(3)
add r1.z, r1.z, r3.x
ldms_indexable(texture2dms)(float,float,float,float) r3.y, r0.xyww, t5.yxzw, l(4)
add r1.z, r1.z, r3.y
ldms_indexable(texture2dms)(float,float,float,float) r3.z, r0.xyww, t5.yzxw, l(5)
add r1.z, r1.z, r3.z
ldms_indexable(texture2dms)(float,float,float,float) r3.w, r0.xyww, t5.yzwx, l(6)
add r1.z, r1.z, r3.w
ldms_indexable(texture2dms)(float,float,float,float) r4.x, r0.xyww, t5.xyzw, l(7)
add r1.z, r1.z, r4.x
mad r1.z, -r1.z, l(0.125000), l(1.000000)
div r1.z, r1.z, r2.w
mul r4.yzw, r1.zzzz, r2.xxyz
movc r2.xyz, r0.zzzz, r4.yzwy, r2.xyzx
ldms_indexable(texture2dms)(float,float,float,float) r4.yzw, r0.xyww, t6.wxyz, l(1)
mul r4.yzw, r1.yyyy, r4.yyzw
ldms_indexable(texture2dms)(float,float,float,float) r5.xyz, r0.xyww, t6.xyzw, l(0)
mad r1.xyz, r1.xxxx, r5.xyzx, r4.yzwy
ldms_indexable(texture2dms)(float,float,float,float) r4.yzw, r0.xyww, t6.wxyz, l(2)
mad r1.xyz, r1.wwww, r4.yzwy, r1.xyzx
ldms_indexable(texture2dms)(float,float,float,float) r4.yzw, r0.xyww, t6.wxyz, l(3)
mad r1.xyz, r3.xxxx, r4.yzwy, r1.xyzx
ldms_indexable(texture2dms)(float,float,float,float) r4.yzw, r0.xyww, t6.wxyz, l(4)
mad r1.xyz, r3.yyyy, r4.yzwy, r1.xyzx
ldms_indexable(texture2dms)(float,float,float,float) r4.yzw, r0.xyww, t6.wxyz, l(5)
mad r1.xyz, r3.zzzz, r4.yzwy, r1.xyzx
ldms_indexable(texture2dms)(float,float,float,float) r3.xyz, r0.xyww, t6.xyzw, l(6)
ldms_indexable(texture2dms)(float,float,float,float) r0.xyz, r0.xyww, t6.xyzw, l(7)
mad r1.xyz, r3.wwww, r3.xyzx, r1.xyzx
mad r0.xyz, r4.xxxx, r0.xyzx, r1.xyzx
mad o0.xyz, r0.xyzx, l(0.125000, 0.125000, 0.125000, 0.000000), r2.xyzx
mov o0.w, l(1.000000)
ret 
// Approximately 88 instruction slots used
#endif

const BYTE g_StochasticResolve16C[] =
{
     68,  88,  66,  67, 137,  85, 
    202, 248,  23, 173,  31,  92, 
    173, 123,  85, 245,  68, 197, 
    155,  48,   1,   0,   0,   0, 
    172,  13,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
     44,   1,   0,   0, 132,   1, 
      0,   0, 184,   1,   0,   0, 
     16,  13,   0,   0,  82,  68, 
     69,  70, 240,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
    255, 255,   0,   1,   0,   0, 
    198,   0,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
    156,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      5,   0,   0,   0, 255, 255, 
    255, 255,   4,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 171,   0,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   6,   0,   0,   0, 
      0,   0,   0,   0,   5,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 186,   0, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   6,   0, 
      0,   0,   0,   0,   0,   0, 
      6,   0,   0,   0,   1,   0, 
      0,   0,   9,   0,   0,   0, 
    116,  82, 101, 115, 111, 108, 
    118, 101, 100,  67, 111, 108, 
    111, 114,   0, 116,  84, 114, 
     97, 110, 115, 109, 105, 116, 
    116,  97, 110,  99, 101,   0, 
    116,  66,  97,  99, 107, 103, 
    114, 111, 117, 110, 100,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  49, 
     48,  46,  49,   0, 171, 171, 
     73,  83,  71,  78,  80,   0, 
      0,   0,   2,   0,   0,   0, 
      8,   0,   0,   0,  56,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  65,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
     15,   3,   0,   0,  84,  69, 
     88,  67,  79,  79,  82,  68, 
      0,  83,  86,  95,  80,  79, 
     83,  73,  84,  73,  79,  78, 
      0, 171, 171, 171,  79,  83, 
     71,  78,  44,   0,   0,   0, 
      1,   0,   0,   0,   8,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  83,  86,  95,  84, 
     65,  82,  71,  69,  84,   0, 
    171, 171,  83,  72,  69,  88, 
     80,  11,   0,   0,  80,   0, 
      0,   0, 212,   2,   0,   0, 
    106,   8,   0,   1,  88,  64, 
      0,   4,   0, 112,  16,   0, 
      4,   0,   0,   0,  85,  85, 
      0,   0,  88,  32,   0,   4, 
      0, 112,  16,   0,   5,   0, 
      0,   0,  85,  85,   0,   0, 
     88,  32,   0,   4,   0, 112, 
     16,   0,   6,   0,   0,   0, 
     85,  85,   0,   0, 100,  32, 
      0,   4,  50,  16,  16,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   0,   0, 
      0,   0, 104,   0,   0,   2, 
      6,   0,   0,   0,  27,   0, 
      0,   5,  50,   0,  16,   0, 
      0,   0,   0,   0,  70,  16, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   8, 194,   0, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  45,   0,   0, 137, 
      2,   2,   0, 128,  67,  85, 
     21,   0, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  15, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   4,   0, 
      0,   0,  45,   0,   0, 137, 
      2,   2,   0, 128,  67,  85, 
     21,   0, 242,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   4,   0, 
      0,   0,   0,   0,   0,   7, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     54,   0,   0,   5,  66,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   2,   0, 
      0,   0,  45,   0,   0, 137, 
      2,   2,   0, 128,  67,  85, 
     21,   0, 242,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   4,   0, 
      0,   0,  54,   0,   0,   5, 
    178,   0,  16,   0,   3,   0, 
      0,   0,  70,  12,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      3,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      4,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      5,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      6,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      7,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      8,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      9,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
     10,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
     11,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
     12,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
     13,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
     14,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
     15,   0,   0,   0,  45,   0, 
      0, 137,   2,   2,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  56,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128,  61, 
      0,   0, 128,  61,   0,   0, 
    128,  61,   0,   0, 128,  61, 
     49,   0,   0,   7,  66,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  46,   0, 
      0, 139,   2,   1,   0, 128, 
     67,  85,  21,   0,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  15,  16,   0,   0,   0, 
      0,   0,  70, 126,  16,   0, 
      5,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0,  22, 126, 
     16,   0,   5,   0,   0,   0, 
      1,  64,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   7, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0, 150, 115, 
     16,   0,   5,   0,   0,   0, 
      1,  64,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   7, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  42,   0, 
     16,   0,   1,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
     18,   0,  16,   0,   3,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0,  70, 126, 
     16,   0,   5,   0,   0,   0, 
      1,  64,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   7, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   3,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
     34,   0,  16,   0,   3,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0,  22, 126, 
     16,   0,   5,   0,   0,   0, 
      1,  64,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   7, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  26,   0, 
     16,   0,   3,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
     66,   0,  16,   0,   3,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0, 150, 124, 
     16,   0,   5,   0,   0,   0, 
      1,  64,   0,   0,   5,   0, 
      0,   0,   0,   0,   0,   7, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  42,   0, 
     16,   0,   3,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0, 150, 115, 
     16,   0,   5,   0,   0,   0, 
      1,  64,   0,   0,   6,   0, 
      0,   0,   0,   0,   0,   7, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
     18,   0,  16,   0,   4,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0,  70, 126, 
     16,   0,   5,   0,   0,   0, 
      1,  64,   0,   0,   7,   0, 
      0,   0,   0,   0,   0,   7, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   4,   0,   0,   0, 
     50,   0,   0,  10,  66,   0, 
     16,   0,   1,   0,   0,   0, 
     42,   0,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  62,   1,  64,   0,   0, 
      0,   0, 128,  63,  14,   0, 
      0,   7,  66,   0,  16,   0, 
      1,   0,   0,   0,  42,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  56,   0,   0,   7, 
    226,   0,  16,   0,   4,   0, 
      0,   0, 166,  10,  16,   0, 
      1,   0,   0,   0,   6,   9, 
     16,   0,   2,   0,   0,   0, 
     55,   0,   0,   9, 114,   0, 
     16,   0,   2,   0,   0,   0, 
    166,  10,  16,   0,   0,   0, 
      0,   0, 150,   7,  16,   0, 
      4,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
    226,   0,  16,   0,   4,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0,  54, 121, 
     16,   0,   6,   0,   0,   0, 
      1,  64,   0,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
    226,   0,  16,   0,   4,   0, 
      0,   0,  86,   5,  16,   0, 
      1,   0,   0,   0,  86,  14, 
     16,   0,   4,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
    114,   0,  16,   0,   5,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0,  70, 126, 
     16,   0,   6,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0,   6,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   5,   0,   0,   0, 
    150,   7,  16,   0,   4,   0, 
      0,   0,  46,   0,   0, 139, 
      2,   1,   0, 128,  67,  85, 
     21,   0, 226,   0,  16,   0, 
      4,   0,   0,   0,  70,  15, 
     16,   0,   0,   0,   0,   0, 
     54, 121,  16,   0,   6,   0, 
      0,   0,   1,  64,   0,   0, 
      2,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      1,   0,   0,   0, 246,  15, 
     16,   0,   1,   0,   0,   0, 
    150,   7,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  46,   0, 
      0, 139,   2,   1,   0, 128, 
     67,  85,  21,   0, 226,   0, 
     16,   0,   4,   0,   0,   0, 
     70,  15,  16,   0,   0,   0, 
      0,   0,  54, 121,  16,   0, 
      6,   0,   0,   0,   1,  64, 
      0,   0,   3,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   3,   0, 
      0,   0, 150,   7,  16,   0, 
      4,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
    226,   0,  16,   0,   4,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0,  54, 121, 
     16,   0,   6,   0,   0,   0, 
      1,  64,   0,   0,   4,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      3,   0,   0,   0, 150,   7, 
     16,   0,   4,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  46,   0,   0, 139, 
      2,   1,   0, 128,  67,  85, 
     21,   0, 226,   0,  16,   0, 
      4,   0,   0,   0,  70,  15, 
     16,   0,   0,   0,   0,   0, 
     54, 121,  16,   0,   6,   0, 
      0,   0,   1,  64,   0,   0, 
      5,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      1,   0,   0,   0, 166,  10, 
     16,   0,   3,   0,   0,   0, 
    150,   7,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  46,   0, 
      0, 139,   2,   1,   0, 128, 
     67,  85,  21,   0, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  15,  16,   0,   0,   0, 
      0,   0,  70, 126,  16,   0, 
      6,   0,   0,   0,   1,  64, 
      0,   0,   6,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
    114,   0,  16,   0,   0,   0, 
      0,   0,  70,  15,  16,   0, 
      0,   0,   0,   0,  70, 126, 
     16,   0,   6,   0,   0,   0, 
      1,  64,   0,   0,   7,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 246,  15,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   0,   0, 
      0,   0,   6,   0,  16,   0, 
      4,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  12, 
    114,  32,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,  62, 
      0,   0,   0,  62,   0,   0, 
      0,  62,   0,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
    130,  32,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    148,   0,   0,   0,  88,   0, 
      0,   0,   6,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,  36,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  17,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
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
