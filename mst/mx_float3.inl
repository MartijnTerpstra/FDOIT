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

/* construct float3 from the x, y and z components */
inline float3 (::mst::math::cfloat3)(float x, float y, float z) __MST_GPU
{
	float3 retval = { x, y, z };
	return retval;
}

/* construct float3 from a float2 and a z component */
inline float3 (::mst::math::cfloat3)(const float2& xy, float z) __MST_GPU
{
	float3 retval = { xy.x, xy.y, z };
	return retval;
}

/* construct float3 from the x, y and z components */
inline float3 (::mst::math::cfloat3)(const float (&xyz)[3]) __MST_GPU
{
	float3 retval = { xyz[0], xyz[1], xyz[2] };
	return retval;
}

/* construct float3 from the x, y and z components */
inline float3 (::mst::math::cfloat3)(const float* xyz) __MST_GPU
{
	float3 retval = { xyz[0], xyz[1], xyz[2] };
	return retval;
}

/* sets the x, y and z components */
inline void float3::set(const float ax, const float ay, const float az ) __MST_GPU
{
	x = ax;
	y = ay;
	z = az;
}

/* sets the x from ax, y from ay and z from az as new components */
inline void float3::set(const float3& ax, const float3& ay, const float3& az) __MST_GPU
{
	x = ax.x;
	y = ay.y;
	z = az.z;
}

/* sets the x, y and z components */
inline void float3::set(const float (&values)[3]) __MST_GPU
{
	x = values[0];
	y = values[1];
	z = values[2];
}

/* normalizes itself and returns a reference to itself */
inline float3& float3::normalize() __MST_GPU
{
	const float l = 1.0f / length();
	x *= l;
	y *= l;
	z *= l;
	return *this;
}

/* returns the normalized version of itself */
inline float3 float3::normalized() const __MST_GPU
{
	return float3(*this).normalize();
}

/* returns the length of the vector */
inline float float3::length() const __MST_GPU
{
	return _AMP_MATH_NAMESPACE_ sqrt( square_length() );
}

/* returns the square length of the vector */
inline float float3::square_length() const __MST_GPU
{
	return (x * x + y * y + z * z);
}

/* returns the distance between it and vec */
inline float float3::distance(const float3& vec) const __MST_GPU
{
	return _AMP_MATH_NAMESPACE_ sqrt( square_distance(vec) );
}

/* returns the square distance between it and vec */
inline float float3::square_distance(const float3& vec) const __MST_GPU
{
	const float dx = vec.x - x;
	const float dy = vec.y - y;
	const float dz = vec.z - z;
	return (dx * dx + dy * dy + dz * dz);
}

/* returns the dot product between it and vec */
inline float float3::dot(const float3& vec ) const __MST_GPU
{
	return x * vec.x + y * vec.y + z * vec.z;
}

/* returns the cross product between it and vec */
inline float3 float3::cross(const float3& v ) const __MST_GPU
{
	return cfloat3( -(y * v.z - z * v.y), -(z * v.x - x * v.z), -(x * v.y - y * v.x) );
}

/* swaps the signs of all axis. x will be -x etc. */
inline void float3::swap_signs() __MST_GPU
{
	x = -x;
	y = -y;
	z = -z;
}

inline float3::operator matrix4x4() const
{
	return cmatrix4x4(*this);
}

inline float3& float3::operator += ( const float3& vec ) __MST_GPU
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

inline float3& float3::operator -= ( const float3& vec ) __MST_GPU
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

inline float3& float3::operator *= ( const float& val ) __MST_GPU
{
	x *= val;
	y *= val;
	z *= val;
	return *this;
}

inline float3& float3::operator *= ( const float3& vec ) __MST_GPU
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

inline float3& float3::operator /= ( const float3& vec ) __MST_GPU
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
}

inline float3& float3::operator /= ( const float& val ) __MST_GPU
{
	float inv_val = 1.0f / val;
	x *= inv_val;
	y *= inv_val;
	z *= inv_val;
return *this;}

inline float3 float3::operator- () const __MST_GPU
{
	return cfloat3( -x, -y, -z );
}

inline _Details::_Swizzle_proxy<0,1>& float3::xy()
{
	return *((_Details::_Swizzle_proxy<0,1>*)this);
}

inline _Details::_Swizzle_proxy<1,0>& float3::yx()
{
	return *((_Details::_Swizzle_proxy<1,0>*)this);
}

inline _Details::_Swizzle_proxy<0,2>& float3::xz()
{
	return *((_Details::_Swizzle_proxy<0,2>*)this);
}

inline _Details::_Swizzle_proxy<2,0>& float3::zx()
{
	return *((_Details::_Swizzle_proxy<2,0>*)this);
}

inline _Details::_Swizzle_proxy<1,2>& float3::yz()
{
	return *((_Details::_Swizzle_proxy<1,2>*)this);
}

inline _Details::_Swizzle_proxy<2,1>& float3::zy()
{
	return *((_Details::_Swizzle_proxy<2,1>*)this);
}

inline const _Details::_Swizzle_proxy<0,1>& float3::xy() const
{
	return *((const _Details::_Swizzle_proxy<0,1>*)this);
}

inline const _Details::_Swizzle_proxy<1,0>& float3::yx() const
{
	return *((const _Details::_Swizzle_proxy<1,0>*)this);
}

inline const _Details::_Swizzle_proxy<0,2>& float3::xz() const
{
	return *((const _Details::_Swizzle_proxy<0,2>*)this);
}

inline const _Details::_Swizzle_proxy<2,0>& float3::zx() const
{
	return *((const _Details::_Swizzle_proxy<2,0>*)this);
}

inline const _Details::_Swizzle_proxy<1,2>& float3::yz() const
{
	return *((const _Details::_Swizzle_proxy<1,2>*)this);
}

inline const _Details::_Swizzle_proxy<2,1>& float3::zy() const
{
	return *((const _Details::_Swizzle_proxy<2,1>*)this);
}


inline float3 (::mst::math::operator + )( const float3& v1, const float3& v2 ) __MST_GPU
{
	return cfloat3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
}

inline float3 (::mst::math::operator - )( const float3& v1, const float3& v2 ) __MST_GPU
{
	return cfloat3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
}

inline float3 (::mst::math::operator * )( const float3& v, float val ) __MST_GPU
{
	return cfloat3( v.x * val, v.y * val, v.z * val );
}

inline float3 (::mst::math::operator * )( const float3& v1, const float3& v2 ) __MST_GPU
{
	return cfloat3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z );
}

inline float3 (::mst::math::operator * )( float val, const float3& v ) __MST_GPU
{
	return cfloat3( v.x * val, v.y * val, v.z * val );
}

inline float3 (::mst::math::operator / )( const float3& v, float val ) __MST_GPU
{
	float inv_val = 1.0f / val;
	return cfloat3( v.x * inv_val, v.y * inv_val, v.z * inv_val );
}

inline float3 (::mst::math::operator / )( const float3& v1, const float3& v2 ) __MST_GPU
{
	return cfloat3( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z );
}

inline float3 (::mst::math::operator / )( float val, const float3& v ) __MST_GPU
{
	return cfloat3( val / v.x, val / v.y, val / v.z );
}

inline bool (::mst::math::operator == )(const float3& v1, const float3& v2) __MST_GPU
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

inline bool (::mst::math::operator != )(const float3& v1, const float3& v2) __MST_GPU
{
	return (v1.x != v2.x || v1.y != v2.y || v1.z != v2.z);
}

inline std::ostream& (::mst::math::operator << )(std::ostream& stream, const float3& value)
{
	stream << "<" << value.x << ", " << value.y << ", " << value.z << ">";
	return stream;
}

inline float& float3::operator[](size_t n)
{
	CHECK_ARR_RANGE(n, 3, "index out of bounds");
	return axis[n];
}

inline const float& float3::operator[](size_t n) const
{
	CHECK_ARR_RANGE(n, 3, "index out of bounds");
	return axis[n];
}

#if _HAS_AMP
inline float& float3::operator[](size_t n) __MST_GPU_ONLY
{
	return axis[n];
}

inline const float& float3::operator[](size_t n) const __MST_GPU_ONLY
{
	return axis[n];
}
#endif

#endif // __INSIDE_MMATH_H__