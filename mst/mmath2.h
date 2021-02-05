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

#ifndef MMATH2_H
#define MMATH2_H

#ifdef MMATH_H
#error "either include mmath.h or mmath2.h"
#endif

#include <mcore.h>
#include <mdebug.h>
#include <cmath>
#include <mproperties.h>
#include <mx_math2.h>

#define NOMINMAX 1
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace mst { 
namespace math {

template<typename _Value_type, size_t _Elems>
class vector;

template<typename _Value_type, size_t _Columns, size_t _Rows>
class matrix;

template<typename _Value_type>
class quaternion;

template<typename _Value_type, size_t _Dimensions>
class aabb;

template<typename _Value_type, size_t _Dimensions>
class ray;

template<typename T>
struct get_value_type : ::mst::math::_Details::_Get_value_type<T>
{
};

#if _MST_HAS_TEMPLATE_ALIASES
template<class T>
using get_value_type_t = typename get_value_type<T>::type;
#endif

}; // namespace math
}; // namespace mst

#include <mmath_algorithm.h>

namespace mst { 
namespace math {

/* Depricated, use constexpr versions
#ifndef PI
#define PI		(3.141592653589793238462f)
#endif
*/

template<typename _Value_type>
inline _MST_CONSTEXPR _Value_type pi()
{
	return (_Value_type)3.141592653589793238462643383279502884197169399375105820974944592307816406286L;
}

inline _MST_CONSTEXPR float pi_f()
{
	return pi<float>();
}

inline _MST_CONSTEXPR double pi_d()
{
	return pi<double>();
}

inline _MST_CONSTEXPR long double pi_ld()
{
	return pi<long double>();
}

#if _MST_COMPILER_VER >= 12
#define _DEFAULT_MATH_CONSTRUCTOR = default;
#else
#define _DEFAULT_MATH_CONSTRUCTOR {}
#endif

template<typename T>
T epsilon()
{
	static_assert(::std::is_floating_point<T>::value, "T must be a floating point type");
	return (T) _MST_EPSILON;
}

#include <mx_math_angle.h>
#include <mx_math_space.h>
#include <mx_math_vector.h>
#include <mx_math_quaternion.h>
#include <mx_math_matrix.h>
#include <mx_math_aabb.h>
#include <mx_math_ray.h>

#include <mx_math_vector.inl>
#include <mx_math_quaternion.inl>
#include <mx_math_matrix.inl>

#undef vector1
#undef vector2
#undef vector3
#undef vector4

}; // namespace math
}; // namespace mst

#endif