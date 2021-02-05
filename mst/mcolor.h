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

#ifndef MCOLOR_H
#define MCOLOR_H

#include <mcore.h>
#include <mdebug.h>
#if MST_SIMD_COLOR4
#include <emmintrin.h>
#endif

#ifndef EPSILON
#define EPSILON (1e-5f)
#endif

namespace mst {
namespace math {

struct color3;
struct color4;

inline color3 ccolor3(float red, float green, float blue) __MST_GPU;

struct color3
{
	inline void set(float red, float green, float blue) __MST_GPU;

	inline float& operator[](size_t n) __MST_GPU;

	inline const float& operator[](size_t n) const __MST_GPU;

	inline color3& operator *= (const color3& col) __MST_GPU;
	inline color3& operator *= (float val) __MST_GPU;
	inline color3& operator /= (const color3& col) __MST_GPU;
	inline color3& operator /= (float val) __MST_GPU;
	inline color3& operator += (const color3& col) __MST_GPU;
	inline color3& operator -= (const color3& col) __MST_GPU;

	inline friend color3 operator * (const color3& col1, const color3& col2) __MST_GPU;
	inline friend color3 operator / (const color3& col1, const color3& col2) __MST_GPU;
	inline friend color3 operator + (const color3& col1, const color3& col2) __MST_GPU;
	inline friend color3 operator - (const color3& col1, const color3& col2) __MST_GPU;
	inline friend color3 operator * (const color3& col, float val) __MST_GPU;
	inline friend color3 operator * (float val, const color3& col) __MST_GPU;
	inline friend color3 operator / (const color3& col, float val) __MST_GPU;
	inline friend color3 operator / (float val, const color3& col) __MST_GPU;

	inline friend bool operator == (const color3& col1, const color3& col2) __MST_GPU;
	inline friend bool operator != (const color3& col1, const color3& col2) __MST_GPU;

	union
	{
		struct { float r, g, b; };
		struct { float rgb[3]; };
	};

	static const color3 white, black;
	static const size_t dimensions = 3;

}; // class color3

#if MST_SIMD_COLOR4 && _HAS_AMP
#error "SIMD type of color4 is not available for GPU computations"
#endif /* MST_SIMD_COLOR4 && _HAS_AMP */

inline color4 ccolor4(float red, float green, float blue, float alpha) __MST_GPU;
#if MST_SIMD_COLOR4
color4 make_color4(__m128 rgba);
#endif /* MST_SIMD_COLOR4 */

#if MST_SIMD_COLOR4
_CRT_ALIGN(16)
#endif /* MST_SIMD_COLOR4 */
struct color4
{
	inline void set(float red, float green, float blue, float alpha) __MST_GPU;

#if MST_SIMD_COLOR4
	inline void set(__m128 rgba);
#endif /* MST_SIMD_COLOR4 */

	inline float& operator[](size_t n) __MST_GPU;
	inline const float& operator[](size_t n) const __MST_GPU;

	inline color4& operator *= (const color4& col) __MST_GPU;
	inline color4& operator *= (float val) __MST_GPU;
	inline color4& operator /= (const color4& col) __MST_GPU;
	inline color4& operator /= (float val) __MST_GPU;
	inline color4& operator += (const color4& col) __MST_GPU;
	inline color4& operator -= (const color4& col) __MST_GPU;

	inline friend color4 operator * (const color4& col1, const color4& col2) __MST_GPU;
	inline friend color4 operator / (const color4& col1, const color4& col2) __MST_GPU;
	inline friend color4 operator + (const color4& col1, const color4& col2) __MST_GPU;
	inline friend color4 operator - (const color4& col1, const color4& col2) __MST_GPU;
	inline friend color4 operator * (const color4& col, float val) __MST_GPU;
	inline friend color4 operator * (float val, const color4& col) __MST_GPU;
	inline friend color4 operator / (const color4& col, float val) __MST_GPU;
	inline friend color4 operator / (float val, const color4& col) __MST_GPU;

	union
	{
		struct { float r, g, b, a; };
		struct { float rgba[4]; };
#if MST_SIMD_COLOR4
		struct { __m128 rgba4; };
#endif /* MST_SIMD_COLOR4 */
	};

	static const color4 white, black;
	static const size_t dimensions = 4;

}; // class color4;

#include <mx_color3.inl>
#include <mx_color4.inl>

}; // namespace math
}; // namespace mst

#endif // MCOLOR_H