//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//		MST Utility Library							 										//
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

#pragma once

#ifndef __INSIDE_MMATH_H__

#error "include <mmath.h>"

#else

#if _MST_COMPILER_VER >= 11 && defined(_AMP_H)
#include <amp_math.h>
#define _AMP_MATH_NAMESPACE_ concurrency::fast_math::
#else
#define _AMP_MATH_NAMESPACE_
#endif

#ifndef _MST_MDET
#define _MST_MDET ::mst::math::_Details::
#endif

namespace mst { namespace math { 

struct float2;
struct float3;
struct float4;
struct quaternion;
struct matrix3x3;
struct matrix4x4;
struct color3;
struct color4;
	
namespace _Details {

typedef float (&_float_array_4)[4];
typedef float (&_float_array_3)[3];

typedef const float (&_const_float_array_4)[4];
typedef const float (&_const_float_array_3)[3];

template<size_t X, size_t Y>
struct _Swizzle_proxy;

}; // namespace _Details

}; }; // namespace mst::math::_Details

#endif // __INSIDE_MMATH_H__