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

/* construct float4 from the x, y, z and w components */
inline float4 (::mst::math::cfloat4)(float x, float y, float z, float w) __MST_GPU
{
	float4 retval = { x, y, z, w };
	return retval;
}

/* construct float4 from two float2s components */
inline float4 (::mst::math::cfloat4)(const float2& xy, const float2& zw) __MST_GPU
{
	float4 retval = { xy.x, xy.y, zw.x, zw.y };
	return retval;
}

/* construct float4 from a float2 and z and w components */
inline float4 (::mst::math::cfloat4)(const float2& xy, float z, float w) __MST_GPU
{
	float4 retval = { xy.x, xy.y, z, w };
	return retval;
}

/* construct float4 from a float3 and a w component */
inline float4 (::mst::math::cfloat4)(const float3& xyz, float w) __MST_GPU
{
	float4 retval = { xyz.x, xyz.y, xyz.z, w };
	return retval;
}

/* construct float4 from the x, y, z and w components */
inline float4 (::mst::math::cfloat4)(const float xyzw[4]) __MST_GPU
{
	float4 retval = { xyzw[0], xyzw[1], xyzw[2], xyzw[3] };
	return retval;
}

#if MST_SIMD_FLOAT4
/* construct float4 from a simd block */
inline float4 (::mst::math::cfloat4)(const __m128& xyzw)
{
	float4 retval;
	retval.xyzw4 = xyzw;
	return retval;
}
#endif

/* sets the x, y, z and w components */
inline void float4::set(float ax, float ay, float az, float aw) __MST_GPU
{
	x = ax;
	y = ay;
	z = az;
	w = aw;
}

/* sets the x, y, z and w components */
inline void float4::set(const float (&values)[4]) __MST_GPU
{
	x = values[0];
	y = values[1];
	z = values[2];
	w = values[3];
}

#if MST_SIMD_FLOAT4
/* sets the x, y, z and w components */
inline void float4::set(const __m128& values)
{
	xyzw4 = values;
}
#endif

/* normalizes itself and returns a reference to itself */
inline float4& float4::normalize() __MST_GPU
{
#if MST_SIMD_FLOAT4
	xyzw4 = _mm_div_ps(xyzw4, _mm_sqrt_ps( _mm_set_ps1(square_length())));
#else
	const float l = 1.0f / length();
	x *= l;
	y *= l;
	z *= l;
	w *= l;
#endif
	return *this;
}

/* returns the normalized version of itself */
inline float4 float4::normalized() const __MST_GPU
{
	return float4(*this).normalize();
}

/* returns the length of the vector */
inline float float4::length() const __MST_GPU
{
	return _AMP_MATH_NAMESPACE_ sqrt(square_length());
}

/* returns the square length of the vector */
inline float float4::square_length() const __MST_GPU
{
#if MST_SIMD_FLOAT4
	const __m128 xyzw_sqr = _mm_mul_ps(xyzw4, xyzw4);
	float sqr_len = xyzw_sqr.m128_f32[0] + xyzw_sqr.m128_f32[1] + xyzw_sqr.m128_f32[2] + xyzw_sqr.m128_f32[3];
	return sqr_len;
#else
	return (x * x + y * y + z * z + w * w);
#endif
}

/* returns the distance between it and vec */
inline float float4::distance(const float4& vec) const __MST_GPU
{
	return _AMP_MATH_NAMESPACE_ sqrt(square_distance(vec));
}
	
/* returns the square distance between it and vec */
inline float float4::square_distance(const float4& vec) const __MST_GPU
{
	float4 delta = vec - *this;
	delta *= delta;
	return delta.axis[0] + delta.axis[1] + delta.axis[2] + delta.axis[3];
}

/* returns the dot product between it and vec */
inline float float4::dot(const float4& vec ) const __MST_GPU
{
	const float4 mulled = *this * vec;

	return mulled.axis[0] + mulled.axis[1] + mulled.axis[2] + mulled.axis[3];
}

/* swaps the signs of all axis. x will be -x etc. */
inline void float4::swap_signs() __MST_GPU
{
#if MST_SIMD_FLOAT4
	xyzw4 = _mm_sub_ps(_mm_setzero_ps(), xyzw4);
#else
	x = -x;
	y = -y;
	z = -z;
	w = -w;
#endif
}

inline float4& float4::operator += ( const float4& vec ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	xyzw4 = _mm_add_ps(xyzw4, vec.xyzw4);
#else
	axis[0] += vec.axis[0];
	axis[1] += vec.axis[1];
	axis[2] += vec.axis[2];
	axis[3] += vec.axis[3];
#endif
	return *this;
}

inline float4& float4::operator -= ( const float4& vec ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	xyzw4 = _mm_sub_ps(xyzw4, vec.xyzw4);
#else
	axis[0] -= vec.axis[0];
	axis[1] -= vec.axis[1];
	axis[2] -= vec.axis[2];
	axis[3] -= vec.axis[3];
#endif
	return *this;
}

inline float4& float4::operator *= ( const float val ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	xyzw4 = _mm_mul_ps(xyzw4, _mm_set_ps1(val));
#else
	axis[0] *= val;
	axis[1] *= val;
	axis[2] *= val;
	axis[3] *= val;
#endif
	return *this;
}

inline float4& float4::operator *= ( const float4& vec ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	xyzw4 = _mm_mul_ps(xyzw4, vec.xyzw4);
#else
	axis[0] *= vec.axis[0];
	axis[1] *= vec.axis[1];
	axis[2] *= vec.axis[2];
	axis[3] *= vec.axis[3];
#endif
	return *this;
}

inline float4& float4::operator /= ( const float4& vec ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	xyzw4 = _mm_div_ps(xyzw4, vec.xyzw4);
#else
	axis[0] /= vec.axis[0];
	axis[1] /= vec.axis[1];
	axis[2] /= vec.axis[2];
	axis[3] /= vec.axis[3];
#endif
	return *this;
}

inline float4& float4::operator /= ( const float val ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	xyzw4 = _mm_div_ps(xyzw4, _mm_set_ps1(val));
#else
	float inv_val = 1.0f / val;
	axis[0] *= inv_val;
	axis[1] *= inv_val;
	axis[2] *= inv_val;
	axis[3] *= inv_val;
#endif
	return *this;
}

inline float4 float4::operator- () const __MST_GPU
{
#if MST_SIMD_FLOAT4
	return cfloat4( _mm_sub_ps(_mm_setzero_ps(), xyzw4) );
#else
	return cfloat4(-x, -y, -z, -w);
#endif
}

inline float4 (::mst::math::operator + )( const float4& v1, const float4& v2 ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return cfloat4(_mm_add_ps(v1.xyzw4, v2.xyzw4));
#else
	return cfloat4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
#endif
}

inline float4 (::mst::math::operator - )( const float4& v1, const float4& v2 ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return cfloat4(_mm_sub_ps(v1.xyzw4, v2.xyzw4));
#else
	return cfloat4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
#endif
}

inline float4 (::mst::math::operator * )( const float4& v, const float val ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return cfloat4(_mm_mul_ps(v.xyzw4, _mm_set_ps1(val)));
#else
	return cfloat4(v.x * val, v.y * val, v.z * val, v.w * val);
#endif
}

inline float4 (::mst::math::operator * )( const float4& v1, const float4& v2 ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return cfloat4(_mm_mul_ps(v1.xyzw4, v2.xyzw4));
#else
	return cfloat4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
#endif
}

inline float4 (::mst::math::operator * )( const float val, const float4& v ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return cfloat4(_mm_mul_ps(v.xyzw4, _mm_set_ps1(val)));
#else
	return cfloat4(v.x * val, v.y * val, v.z * val, v.w * val);
#endif
}

inline float4 (::mst::math::operator / )( const float4& v, const float val ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return cfloat4(_mm_div_ps(v.xyzw4, _mm_set_ps1(val)));
#else
	return cfloat4(v.x / val, v.y / val, v.z / val, v.w / val);
#endif
}

inline float4 (::mst::math::operator / )( const float4& v1, const float4& v2 ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return cfloat4(_mm_div_ps(v1.xyzw4, v2.xyzw4));
#else
	return cfloat4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
#endif
}

inline float4 (::mst::math::operator / )( const float val, const float4& v ) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return cfloat4(_mm_div_ps(_mm_set_ps1(val), v.xyzw4));
#else
	return cfloat4(val / v.x, val / v.y,val / v.z, val / v.w);
#endif
}

inline bool (::mst::math::operator == )(const float4& v1, const float4& v2) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return (_mm_movemask_ps(_mm_cmpneq_ps(v1.xyzw4, v2.xyzw4)) == 0);
#else
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w);
#endif
}

inline bool (::mst::math::operator != )(const float4& v1, const float4& v2) __MST_GPU
{
	return !(v1 == v2);
}

inline std::ostream& (::mst::math::operator << )(std::ostream& stream, const float4& value)
{
	stream << "<" << value.x << ", " << value.y << ", " << value.z << ", " << value.w << ">";
	return stream;
}

inline float& float4::operator[](size_t n) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 4, "index out of bounds");
	return axis[n];
}

inline const float& float4::operator[](size_t n) const __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 4, "index out of bounds");
	return axis[n];
}

#endif // __INSIDE_MMATH_H__