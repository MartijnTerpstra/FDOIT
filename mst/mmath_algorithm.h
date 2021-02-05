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

#include <mcore.h>
#include <mx_math_algorithm.h>

namespace mst { 
namespace math {

// math functions
template<typename T>
inline T lerp(const T& u, const T& v, typename _MST_MDET _Cref_value<T>::type s) __MST_GPU;

template<typename T>
inline T lerp(const T& u, const T& v, const T& w, typename _MST_MDET _Cref_value<T>::type s, typename _MST_MDET _Cref_value<T>::type t) __MST_GPU;

template<typename T>
inline T cubic_interp(const T& pre_u, const T& u, const T& v, const T& post_v, typename _MST_MDET _Cref_value<T>::type s) __MST_GPU;

template<typename T>
inline T cubic_interp(const T (&uv)[4], typename _MST_MDET _Cref_value<T>::type s) __MST_GPU;

template<typename T>
inline T reflect(const T& i, const T& n);

inline float fast_sqrtf(const float val);
inline float fast_rsqrtf(const float val);

/* returns clamps all the values to the range: [0,1] */
template<typename T>
inline T saturate(const T& val);

template<typename T>
inline T smoothstep(const T& minim, const T& maxim, typename _MST_MDET _Cref_value<T>::type s);

template<typename T>
inline T frac(const T& val);

template<typename T>
inline T clamp(const T& val, typename _MST_MDET _Cref_value<T>::type minim, typename _MST_MDET _Cref_value<T>::type maxim);

template<typename T>
inline T clamp(const T& val, const T& minim, const T& maxim);

template<typename T>
inline typename ::mst::math::_Details::_Math_traits<T>::value_type average(const T& value);

template<typename T>
inline T greatest_common_devisor(const T& left, const T& right);

#include <mx_math_algorithm.inl>

}; // namespace math
}; // namespace mst