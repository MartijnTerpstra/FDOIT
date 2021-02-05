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

/* construct float2 from x and y components */
inline float2 (::mst::math::cfloat2)(float x, float y) __MST_GPU
{
	float2 retval = { x, y };
	return retval;
}

/* construct float2 from x and y components */
inline float2 (::mst::math::cfloat2)(const float (&xy)[2]) __MST_GPU
{
	float2 retval = { xy[0], xy[1] };
	return retval;
}

/* construct float2 from x and y components */
inline float2 (::mst::math::cfloat2)(const float* xy) __MST_GPU
{
	float2 retval = { xy[0], xy[1] };
	return retval;
}

/* construct float2 from a _Swizzle_proxy */
template<size_t X, size_t Y>
inline float2 (::mst::math::cfloat2)(const _Details::_Swizzle_proxy<X,Y>& vec)
{
	float2 retval = { vec.x, vec.y };
	return retval;
}

/* sets the x, y and z components */
inline void float2::set(const float ax, const float ay) __MST_GPU
{
	x = ax;
	y = ay;
}

/* sets the x, y and z components */
inline void float2::set(const float (&values)[2]) __MST_GPU
{
	x = values[0];
	y = values[1];
}

/* normalizes itself and returns a reference to itself */
inline float2& float2::normalize() __MST_GPU
{
	const float l = 1.0f / length();
	x *= l;
	y *= l;
	return *this;
}

/* returns the normalized version of itself */
inline float2 float2::normalized() const __MST_GPU
{
	return float2(*this).normalize();
}

/* returns the length of the vector */
inline float float2::length() const __MST_GPU
{
	return _AMP_MATH_NAMESPACE_ sqrt( square_length() );
}

/* returns the square length of the vector */
inline float float2::square_length() const __MST_GPU
{
	return (x * x + y * y);
}

/* returns the distance between it and vec */
inline float float2::distance(const float2& vec) const __MST_GPU
{
	return _AMP_MATH_NAMESPACE_ sqrt( square_distance(vec) );
}

/* returns the square distance between it and vec */
inline float float2::square_distance(const float2& vec) const __MST_GPU
{
	const float dx = vec.x - x;
	const float dy = vec.y - y;
	return (dx * dx + dy * dy);
}

/* returns the dot product between it and vec */
inline float float2::dot(const float2& vec ) const __MST_GPU
{
	return x * vec.x + y * vec.y;
}

inline float float2::cross(const float2& vec) const __MST_GPU
{
	return -(x * vec.y - y * vec.x);
}

/* swaps the signs of all axis. x will be -x etc. */
inline void float2::swap_signs() __MST_GPU
{
	x = -x;
	y = -y;
}

inline float2& float2::operator += ( const float2& vec ) __MST_GPU
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template<size_t X, size_t Y>
inline float2& float2::operator += ( const _Details::_Swizzle_proxy<X,Y>& vec )
{
	x += vec.x;
	y += vec.y;
	return *this;
}

inline float2& float2::operator -= ( const float2& vec ) __MST_GPU
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<size_t X, size_t Y>
inline float2& float2::operator -= ( const _Details::_Swizzle_proxy<X,Y>& vec )
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

inline float2& float2::operator *= ( const float& val ) __MST_GPU
{
	x *= val;
	y *= val;
	return *this;
}

inline float2& float2::operator *= ( const float2& vec ) __MST_GPU
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

template<size_t X, size_t Y>
inline float2& float2::operator *= ( const _Details::_Swizzle_proxy<X,Y>& vec )
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

inline float2& float2::operator /= ( const float2& vec ) __MST_GPU
{
	x /= vec.x;
	y /= vec.y;
	return *this;
}

template<size_t X, size_t Y>
inline float2& float2::operator /= ( const _Details::_Swizzle_proxy<X,Y>& vec )
{
	x /= vec.x;
	y /= vec.y;
	return *this;
}

inline float2& float2::operator /= ( const float& val ) __MST_GPU
{
	float inv_val = 1.0f / val;
	x *= inv_val;
	y *= inv_val;
	return *this;
}

inline float2 float2::operator- () const __MST_GPU
{
	return cfloat2( -x, -y );
}

inline float2 (::mst::math::operator + )( const float2& v1, const float2& v2 ) __MST_GPU
{
	return cfloat2( v1.x + v2.x, v1.y + v2.y );
}

template<size_t X, size_t Y>
inline float2 (::mst::math::operator + )( const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2 )
{
	return cfloat2( v1.x + v2.x, v1.y + v2.y );
}

inline float2 (::mst::math::operator - )( const float2& v1, const float2& v2 ) __MST_GPU
{
	return cfloat2( v1.x - v2.x, v1.y - v2.y );
}

template<size_t X, size_t Y>
inline float2 (::mst::math::operator - )( const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2 )
{
	return cfloat2( v1.x - v2.x, v1.y - v2.y );
}

inline float2 (::mst::math::operator * )( const float2& v, float val ) __MST_GPU
{
	return cfloat2( v.x * val, v.y * val );
}

inline float2 (::mst::math::operator * )( const float2& v1, const float2& v2 ) __MST_GPU
{
	return cfloat2( v1.x * v2.x, v1.y * v2.y );
}

template<size_t X, size_t Y>
inline float2 (::mst::math::operator * )( const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2 )
{
	return cfloat2( v1.x * v2.x, v1.y * v2.y );
}

inline float2 (::mst::math::operator * )( float val, const float2& v ) __MST_GPU
{
	return cfloat2( v.x * val, v.y * val );
}

inline float2 (::mst::math::operator / )( const float2& v, float val ) __MST_GPU
{
	float inv_val = 1.0f / val;
	return cfloat2( v.x * inv_val, v.y * inv_val );
}

inline float2 (::mst::math::operator / )( const float2& v1, const float2& v2 ) __MST_GPU
{
	return cfloat2( v1.x / v2.x, v1.y / v2.y );
}

template<size_t X, size_t Y>
inline float2 (::mst::math::operator / )( const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2 )
{
	return cfloat2( v1.x / v2.x, v1.y / v2.y );
}

inline float2 (::mst::math::operator / )( float val, const float2& v ) __MST_GPU
{
	return cfloat2( val / v.x, val / v.y );
}

inline bool (::mst::math::operator == )(const float2& v1, const float2& v2) __MST_GPU
{
	return (v1.x == v2.x && v1.y == v2.y);
}

template<size_t X, size_t Y>
inline bool (::mst::math::operator == )(const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

inline bool (::mst::math::operator != )(const float2& v1, const float2& v2) __MST_GPU
{
	return !(v1 == v2);
}

template<size_t X, size_t Y>
inline bool (::mst::math::operator != )(const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2)
{
	return !(v1 == v2);
}

inline std::ostream& (::mst::math::operator << )(std::ostream& stream, const float2& value)
{
	stream << "<" << value.x << ", " << value.y << ">";
	return stream;
}

inline float& float2::operator[](size_t n) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 2, "index out of bounds");
	return axis[n];
}

inline const float& float2::operator[](size_t n) const __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 2, "index out of bounds");
	return axis[n];
}

#endif // __INSIDE_MMATH_H__