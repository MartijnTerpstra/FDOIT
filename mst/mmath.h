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

#ifndef MMATH_H
#define MMATH_H

#ifdef MMATH2_H
#error "either include mmath.h or mmath2.h"
#endif

#define __INSIDE_MMATH_H__

#include <mcore.h>
#include <ostream>
#include <mdebug.h>
#include <cmath>
#include <emmintrin.h>
#include <algorithm>
#include <mcommon.h>
#include <mmath_algorithm.h>

#include <mx_math.h>

namespace mst { namespace math {

#ifndef PI
#define PI		(3.141592653589793238462f)
#endif

#ifndef EPSILON
#define EPSILON (1e-5f)
#endif
	
// forward declarations
struct float2;
struct float3;
struct float4;
struct quaternion;
struct matrix3x3;
struct matrix4x4;

// enumerations
struct euler_XYZ {};
struct euler_XZY {};
struct euler_YXZ {};
struct euler_YZX {};
struct euler_ZXY {};
struct euler_ZYX {};

// float2

/* construct float2 from x and y components */
inline float2 cfloat2(float x, float y) __MST_GPU;

/* construct float2 from x and y components */
inline float2 cfloat2(const float (&xy)[2]) __MST_GPU;

/* construct float2 from x and y components */
inline float2 cfloat2(const float* xy) __MST_GPU;

/* construct float2 from a swizzled float2 */
template<size_t X, size_t Y>
inline float2 cfloat2(const _Details::_Swizzle_proxy<X,Y>& vec);

struct float2
{
	typedef float elem_type;

	/* sets the x and y components */
	inline void set(float ax, float ay) __MST_GPU;

	/* sets the x and y components */
	inline void set(const float (&values)[2]) __MST_GPU;

	/* normalizes itself and returns a reference to itself */
	inline float2& normalize() __MST_GPU;

	/* returns the normalized version of itself */
	inline float2 normalized() const __MST_GPU;

	/* returns the length of the vector */
	inline float length() const __MST_GPU;

	/* returns the square length of the vector */
	inline float square_length() const __MST_GPU;

	/* returns the distance between it and vec */
	inline float distance(const float2& vec) const __MST_GPU;

	/* returns the square distance between it and vec */
	inline float square_distance(const float2& vec) const __MST_GPU;

	/* returns the dot product between it and vec */
	inline float dot(const float2& vec ) const __MST_GPU;

	/* returns the cross product between it and vec */
	inline float cross(const float2& vec ) const __MST_GPU;

	/* swaps the signs of all axis. x will be -x etc. */
	inline void swap_signs() __MST_GPU;

	/* returns the float array data */
	inline float* data();

	/* returns the float array data */
	inline const float* data() const;

	// operator overloads

	inline float2& operator += ( const float2& vec ) __MST_GPU;
	template<size_t X, size_t Y>
	inline float2& operator += ( const _Details::_Swizzle_proxy<X,Y>& vec );
	inline float2& operator -= ( const float2& vec ) __MST_GPU;
	template<size_t X, size_t Y>
	inline float2& operator -= ( const _Details::_Swizzle_proxy<X,Y>& vec );
	inline float2& operator *= ( const float& val ) __MST_GPU;
	inline float2& operator *= ( const float2& vec ) __MST_GPU;
	template<size_t X, size_t Y>
	inline float2& operator *= ( const _Details::_Swizzle_proxy<X,Y>& vec );
	inline float2& operator /= ( const float2& vec ) __MST_GPU;
	template<size_t X, size_t Y>
	inline float2& operator /= ( const _Details::_Swizzle_proxy<X,Y>& vec );
	inline float2& operator /= ( const float& val ) __MST_GPU;

	inline friend float2 operator + ( const float2& v1, const float2& v2 ) __MST_GPU;
	template<size_t X, size_t Y>
	inline friend float2 operator + ( const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2 );
	inline friend float2 operator - ( const float2& v1, const float2& v2 ) __MST_GPU;
	template<size_t X, size_t Y>
	inline friend float2 operator - ( const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2 );
	inline friend float2 operator * ( const float2& v, float val ) __MST_GPU;
	inline friend float2 operator * ( const float2& v1, const float2& v2 ) __MST_GPU;
	template<size_t X, size_t Y>
	inline friend float2 operator * ( const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2 );
	inline friend float2 operator * ( float val, const float2& v ) __MST_GPU;
	inline friend float2 operator / ( const float2& v, float val ) __MST_GPU;
	inline friend float2 operator / ( const float2& v1, const float2& v2 ) __MST_GPU;
	template<size_t X, size_t Y>
	inline friend float2 operator / ( const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2 );
	inline friend float2 operator / ( float val, const float2& v ) __MST_GPU;

	inline friend bool  operator == (const float2& v1, const float2& v2) __MST_GPU;
	inline friend bool  operator != (const float2& v1, const float2& v2) __MST_GPU;

	template<size_t X, size_t Y>
	inline friend bool  operator == (const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2);
	template<size_t X, size_t Y>
	inline friend bool  operator != (const float2& v1, const _Details::_Swizzle_proxy<X,Y>& v2);

	inline float2 operator- () const __MST_GPU;

	inline friend std::ostream& operator << (std::ostream& stream, const float2& value);

	inline float& operator[](size_t n);
	inline const float& operator[](size_t n) const;

#if _HAS_AMP
	inline float& operator[](size_t n) __MST_GPU_ONLY;
	inline const float& operator[](size_t n) const __MST_GPU_ONLY;
#endif

	union
	{
		struct { float x, y; };
		struct { float axis[2]; };
	};

	static const float2 zero;
	static const size_t dimensions = 2;
	typedef float value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};


// float3

/* construct float3 from the x, y and z components */
inline float3 cfloat3(float x, float y, float z) __MST_GPU;

/* construct float3 from a float2 and a z component */
inline float3 cfloat3(const float2& xy, float z) __MST_GPU;

/* construct float3 from the x, y and z components */
inline float3 cfloat3(const float (&xyz)[3]) __MST_GPU;

/* construct float3 from the x, y and z components */
inline float3 cfloat3(const float* xyz) __MST_GPU;

struct float3
{
	typedef float elem_type;

	/* sets the x, y and z components */
	inline void set(const float ax, const float ay, const float az) __MST_GPU;

	/* sets the x from ax, y from ay and z from az as new components */
	inline void set(const float3& ax, const float3& ay, const float3& az) __MST_GPU;

	/* sets the x, y and z components */
	inline void set(const float (&values)[3]) __MST_GPU;

	/* normalizes itself and returns a reference to itself */
	inline float3& normalize() __MST_GPU;

	/* returns the normalized version of itself */
	inline float3 normalized() const __MST_GPU;

	/* returns the length of the vector */
	inline float length() const __MST_GPU;

	/* returns the square length of the vector */
	inline float square_length() const __MST_GPU;

	/* returns the distance between it and vec */
	inline float distance(const float3& vec) const __MST_GPU;

	/* returns the square distance between it and vec */
	inline float square_distance(const float3& vec) const __MST_GPU;

	/* returns the dot product between it and vec */
	inline float dot(const float3& vec ) const __MST_GPU;

	/* returns the cross product between it and vec */
	inline float3 cross(const float3& vec ) const __MST_GPU;

	/* swaps the signs of all axis. x will be -x etc. */
	inline void swap_signs() __MST_GPU;

	/* returns the float array data */
	inline float* data();

	/* returns the float array data */
	inline const float* data() const;

	// operator overloads

	inline operator matrix4x4() const;

	inline float3& operator += ( const float3& vec ) __MST_GPU;
	inline float3& operator -= ( const float3& vec ) __MST_GPU;
	inline float3& operator *= ( const float& val ) __MST_GPU;
	inline float3& operator *= ( const float3& vec ) __MST_GPU;
	inline float3& operator /= ( const float3& vec ) __MST_GPU;
	inline float3& operator /= ( const float& val ) __MST_GPU;

	inline friend float3 operator + ( const float3& v1, const float3& v2 ) __MST_GPU;
	inline friend float3 operator - ( const float3& v1, const float3& v2 ) __MST_GPU;
	inline friend float3 operator * ( const float3& v, float val ) __MST_GPU;
	inline friend float3 operator * ( const float3& v1, const float3& v2 ) __MST_GPU;
	inline friend float3 operator * ( float val, const float3& v ) __MST_GPU;
	inline friend float3 operator / ( const float3& v, float val ) __MST_GPU;
	inline friend float3 operator / ( const float3& v1, const float3& v2 ) __MST_GPU;
	inline friend float3 operator / ( float val, const float3& v ) __MST_GPU;

	inline friend bool  operator == (const float3& v1, const float3& v2) __MST_GPU;
	inline friend bool  operator != (const float3& v1, const float3& v2) __MST_GPU;

	inline float3 operator- () const __MST_GPU;

	inline _Details::_Swizzle_proxy<0,1>& xy();
	inline _Details::_Swizzle_proxy<1,0>& yx();
	inline _Details::_Swizzle_proxy<0,2>& xz();
	inline _Details::_Swizzle_proxy<2,0>& zx();
	inline _Details::_Swizzle_proxy<1,2>& yz();
	inline _Details::_Swizzle_proxy<2,1>& zy();

	inline const _Details::_Swizzle_proxy<0,1>& xy() const;
	inline const _Details::_Swizzle_proxy<1,0>& yx() const;
	inline const _Details::_Swizzle_proxy<0,2>& xz() const;
	inline const _Details::_Swizzle_proxy<2,0>& zx() const;
	inline const _Details::_Swizzle_proxy<1,2>& yz() const;
	inline const _Details::_Swizzle_proxy<2,1>& zy() const;

	inline friend std::ostream& operator << (std::ostream& stream, const float3& value);

	inline float& operator[](size_t n);
	inline const float& operator[](size_t n) const;

#if _HAS_AMP
	inline float& operator[](size_t n) __MST_GPU_ONLY;
	inline const float& operator[](size_t n) const __MST_GPU_ONLY;
#endif

	union
	{
		struct { float x, y, z; };
		struct { float axis[3]; };
	};

	static const float3 zero;
	static const size_t dimensions = 3;
	typedef float value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};


// float4

#if MST_SIMD_FLOAT4 && _HAS_AMP
#error "SIMD type of float4 is not available for GPU computations"
#endif /* MST_SIMD_FLOAT4 && _HAS_AMP */

/* construct float4 from the x, y, z and w components */
inline float4 cfloat4(float x, float y, float z, float w) __MST_GPU;

/* construct float4 from two float2s components */
inline float4 cfloat4(const float2& xy, const float2& zw) __MST_GPU;

/* construct float4 from a float2 and z and w components */
inline float4 cfloat4(const float2& xy, float z, float w) __MST_GPU;

/* construct float4 from a float3 and a w component */
inline float4 cfloat4(const float3& xyz, float w) __MST_GPU;

/* construct float4 from the x, y, z and w components */
inline float4 cfloat4(const float xyzw[4]) __MST_GPU;

#if MST_SIMD_FLOAT4
/* construct float4 from a simd block */
inline float4 cfloat4(const __m128& xyzw);
#endif /* MST_SIMD_FLOAT4 */

#if MST_SIMD_FLOAT4
_MST_ALIGN(16)
#endif /* MST_SIMD_FLOAT4 */
struct float4
{
	typedef float elem_type;

	/* sets the x, y, z and w components */
	inline void set(float ax, float ay, float az, float aw) __MST_GPU;

	/* sets the x, y, z and w components */
	inline void set(const float (&values)[4]) __MST_GPU;

#if MST_SIMD_FLOAT4
	/* sets the x, y, z and w components */
	inline void set(const __m128& values);
#endif /* MST_SIMD_FLOAT4 */

	/* normalizes itself and returns a reference to itself */
	inline float4& normalize() __MST_GPU;

	/* returns the normalized version of itself */
	inline float4 normalized() const __MST_GPU;

	/* returns the length of the vector */
	inline float length() const __MST_GPU;

	/* returns the square length of the vector */
	inline float square_length() const __MST_GPU;

	/* returns the distance between it and vec */
	inline float distance(const float4& vec) const __MST_GPU;
	
	/* returns the square distance between it and vec */
	inline float square_distance(const float4& vec) const __MST_GPU;

	/* returns the dot product between it and vec */
	inline float dot(const float4& vec ) const __MST_GPU;

	/* swaps the signs of all axis. x will be -x etc. */
	inline void swap_signs() __MST_GPU;

	/* returns the float array data */
	inline float* data();

	/* returns the float array data */
	inline const float* data() const;

	// operator overloads

	inline float4& operator += ( const float4& vec ) __MST_GPU;
	inline float4& operator -= ( const float4& vec ) __MST_GPU;
	inline float4& operator *= ( const float val ) __MST_GPU;
	inline float4& operator *= ( const float4& vec ) __MST_GPU;
	inline float4& operator /= ( const float4& vec ) __MST_GPU;
	inline float4& operator /= ( const float val ) __MST_GPU;

	inline float4 operator- () const __MST_GPU;

	inline friend float4 operator + ( const float4& v1, const float4& v2 ) __MST_GPU;
	inline friend float4 operator - ( const float4& v1, const float4& v2 ) __MST_GPU;
	inline friend float4 operator * ( const float4& v, const float val ) __MST_GPU;
	inline friend float4 operator * ( const float4& v1, const float4& v2 ) __MST_GPU;
	inline friend float4 operator * ( const float val, const float4& v ) __MST_GPU;
	inline friend float4 operator / ( const float4& v, const float val ) __MST_GPU;
	inline friend float4 operator / ( const float4& v1, const float4& v2 ) __MST_GPU;
	inline friend float4 operator / ( const float val, const float4& v ) __MST_GPU;

	inline friend bool  operator == (const float4& v1, const float4& v2) __MST_GPU;
	inline friend bool  operator != (const float4& v1, const float4& v2) __MST_GPU;

	inline friend std::ostream& operator << (std::ostream& stream, const float4& value);

	inline float& operator[](size_t n) __MST_GPU;

	inline const float& operator[](size_t n) const __MST_GPU;

	union
	{
		struct { float x, y, z, w; };
		struct { float axis[4]; };
		struct { float3 xyz; };
#if MST_SIMD_FLOAT4
		struct { __m128 xyzw4; };
#endif /* MST_SIMD_FLOAT4 */
	};

	static const float4 zero;
	static const size_t dimensions = 4;
	typedef float value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};


// matrix3x3

/* constructs the matrix from the values of the array */
inline matrix3x3 cmatrix3x3(const float (&values)[9]) __MST_GPU;

/* constructs the matrix from the values of the array */
inline matrix3x3 cmatrix3x3(const float (&values)[3][3]) __MST_GPU;

/* constructs the matrix from the values */
inline matrix3x3 cmatrix3x3(float val1x1, float val2x1, float val3x1,
			float val1x2, float val2x2, float val3x2,
			float val1x3, float val2x3, float val3x3) __MST_GPU;

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 cmatrix3x3(float3 euler_rotations, euler_XYZ) __MST_GPU;

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 cmatrix3x3(float3 euler_rotations, euler_XZY) __MST_GPU;

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 cmatrix3x3(float3 euler_rotations, euler_YXZ) __MST_GPU;

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 cmatrix3x3(float3 euler_rotations, euler_YZX) __MST_GPU;

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 cmatrix3x3(float3 euler_rotations, euler_ZXY) __MST_GPU;

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 cmatrix3x3(float3 euler_rotations, euler_ZYX) __MST_GPU;

/* constructs the matrix from a quaternion*/
inline matrix3x3 cmatrix3x3(const quaternion& quat) __MST_GPU;

/* construct the matrix for the orientation part of a 4x4 matrix */
inline matrix3x3 cmatrix3x3(const matrix4x4& matrix) __MST_GPU;

struct matrix3x3
{
	typedef float elem_type;

	/* turns the matrix into an identity matrix */
	inline void set_identity() __MST_GPU;

	/* sets the values of the matrix */
	inline void set(float val1x1, float val2x1, float val3x1,
			float val1x2, float val2x2, float val3x2,
			float val1x3, float val2x3, float val3x3) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const float (&values)[9]) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const float (&values)[3][3]) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const quaternion& quat) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const quaternion& quat, float scale) __MST_GPU;

	/* returns the matrix's x axis */
	inline const float3& get_x_axis() __MST_GPU;

	/* returns the matrix's y axis */
	inline const float3& get_y_axis() __MST_GPU;

	/* returns the matrix's z axis */
	inline const float3& get_z_axis() __MST_GPU;

	/* sets the x axis of the matrix */
	inline void set_x_axis(const float3& vec) __MST_GPU;

	/* sets the y axis of the matrix */
	inline void set_y_axis(const float3& vec) __MST_GPU;

	/* sets the z axis of the matrix */
	inline void set_z_axis(const float3& vec) __MST_GPU;

	/* rotates the matrix around the global x axis */
	inline void rotate_x( float angle_in_radians ) __MST_GPU;

	/* returns a copy of the matrix, that is rotated around the global x axis */
	inline matrix3x3 rotated_x( float angle_in_radians ) const __MST_GPU;

	/* rotates the matrix around the global y axis */
	inline void rotate_y( float angle_in_radians ) __MST_GPU;

	/* returns a copy of the matrix, that is rotated around the global y axis */
	inline matrix3x3 rotated_y( float angle_in_radians ) const __MST_GPU;

	/* rotates the matrix around the global z axis */
	inline void rotate_z( float angle_in_radians ) __MST_GPU;

	/* returns a copy of the matrix, that is rotated around the global z axis */
	inline matrix3x3 rotated_z( float angle_in_radians ) const __MST_GPU;

	/* transposes the matrix */
	inline void transpose() __MST_GPU;
	
	/* makes the matrix look at a target */
	inline void look_at(const float3& target, const float3& global_up = cfloat3(0,1,0)) __MST_GPU;

	/* returns the float array data */
	inline float* data();

	/* returns the float array data */
	inline const float* data() const;

	// operator overloads

	inline friend float3 operator * (const matrix3x3& mat, const float3& vec) __MST_GPU;
	inline friend matrix3x3 operator * (const matrix3x3& mat1, const matrix3x3& mat2) __MST_GPU;
	inline friend matrix3x3 operator * (const matrix3x3& mat, float value) __MST_GPU;

	inline matrix3x3& operator *= (const matrix3x3& mat) __MST_GPU;
	inline matrix3x3& operator *= (float value) __MST_GPU;

	/* rotates the matrix by mat */
	inline void rotate(const matrix3x3& mat) __MST_GPU;

	/* returns a copy of itself rotated by mat */
	inline matrix3x3 rotated(const matrix3x3& mat) const __MST_GPU;

	inline _Details::_float_array_3 operator [] (size_t n) __MST_GPU;
	inline _Details::_const_float_array_3 operator[](size_t n) const __MST_GPU;

	inline friend std::ostream& operator << (std::ostream& stream, const matrix3x3& value);

	float cell[3][3];

	static const matrix3x3 identity_matrix;
	static const size_t dimensions = 9;
	typedef float value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};


// matrix4x4

/* constructs a matrix from the values of the array */
inline matrix4x4 cmatrix4x4(const float (&values)[16]) __MST_GPU;

/* constructs a matrix from the values of the array */
inline matrix4x4 cmatrix4x4(const float (&values)[4][4]) __MST_GPU;

/* constructs a matrix with a position and a quaternion for orientation */
inline matrix4x4 cmatrix4x4(const float3& position, const quaternion& quat) __MST_GPU;

/* constructs a matrix with a position and a quaternion for orientation and a scale */
inline matrix4x4 cmatrix4x4(const float3& position, const quaternion& quat, float scale) __MST_GPU;

/* constructs a matrix with a position and an orientation */
inline matrix4x4 cmatrix4x4(const float3& position, const matrix3x3& orientation = matrix3x3::identity_matrix) __MST_GPU;

/* constructs a matrix with a position and an orientation */
inline matrix4x4 cmatrix4x4(const float4& position, const matrix3x3& orientation = matrix3x3::identity_matrix) __MST_GPU;

/* constructs a matrix with a position and the 3 axis vectors */
inline matrix4x4 cmatrix4x4(const float3& position, const float3& x_axis, const float3& y_axis, const float3& z_axis) __MST_GPU;

/* constructs a matrix from the values */
inline matrix4x4 cmatrix4x4(float cell1, float cell2, float cell3, float cell4, 
	float cell5, float cell6, float cell7, float cell8, 
	float cell9, float cell10, float cell11, float cell12,
	float cell13, float cell14, float cell15, float cell16) __MST_GPU;

struct matrix4x4
{
	typedef float elem_type;

	/* sets the values of the matrix */
	inline void set(const float (&values)[16]) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const float (&values)[4][4]) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(float cell1, float cell2, float cell3, float cell4, 
		float cell5, float cell6, float cell7, float cell8, 
		float cell9, float cell10, float cell11, float cell12,
		float cell13, float cell14, float cell15, float cell16) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const float3& position, const matrix3x3& orientation = matrix3x3::identity_matrix) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const float4& position, const matrix3x3& orientation = matrix3x3::identity_matrix) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const float3& position, const quaternion& quat) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const float4& position, const quaternion& quat) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const float3& position, const quaternion& quat, float scale) __MST_GPU;

	/* sets the values of the matrix */
	inline void set(const float4& position, const quaternion& quat, float scale) __MST_GPU;

	/* sets only the rotation part of the matrix from mat into the matrix */
	inline void set_orientation(const matrix4x4& mat) __MST_GPU;

	/* sets only the rotation part of the matrix from mat into the matrix */
	inline void set_orientation(const matrix3x3& mat) __MST_GPU;

	/* sets only the rotation part of the matrix from a quaternion */
	inline void set_orientation(const quaternion& quat) __MST_GPU;

	/* sets only the rotation part of the matrix from  a quaternion and a scale */
	inline void set_orientation(const quaternion& quat, float scale) __MST_GPU;

	/* sets only the rotation part of the matrix from values into the matrix */
	inline void set_orientation(const float (&values)[3][3]) __MST_GPU;

	/* sets only the rotation part of the matrix from xyz euler rotations into the matrix */
	inline void set_orientation_euler_xyz(const float3& euler_rotations) __MST_GPU;

	/* sets only the rotation part of the matrix from xzy euler rotations into the matrix */
	inline void set_orientation_euler_xzy(const float3& euler_rotations) __MST_GPU;

	/* sets only the rotation part of the matrix from yzx euler rotations into the matrix */
	inline void set_orientation_euler_yzx(const float3& euler_rotations) __MST_GPU;

	/* sets only the rotation part of the matrix from zxy euler rotations into the matrix */
	inline void set_orientation_euler_zxy(const float3& euler_rotations) __MST_GPU;

	/* sets only the rotation part of the matrix from zyx euler rotations into the matrix */
	inline void set_orientation_euler_zyx(const float3& euler_rotations) __MST_GPU;

	/* sets only the rotation part of the matrix from yxz euler rotations into the matrix */
	inline void set_orientation_euler_yxz(const float3& euler_rotations) __MST_GPU;

	/* turns the matrix into an identity matrix */
	inline void set_identity() __MST_GPU;

	/* resets the rotation part to identity values */
	inline void identity_rotation() __MST_GPU;

	/* returns the position part of the matrix */
	inline const float3& get_position() const __MST_GPU;

	/* sets the position part of the matrix */
	inline void set_position(const float3& position) __MST_GPU;

	/* sets the position part of the matrix */
	inline void set_position(const float4& position);

	/* translates the position of the matrix */
	inline void translate(const float3& translation) __MST_GPU;

	/* swaps the signs of the position part of the matrix */
	inline void swap_position() __MST_GPU;

	/* concatenates the matrix into the space of m2 */
	inline void concatenate( const matrix4x4& m2 ) __MST_GPU;

	/* returns the result of concatenating the matrix into the space of m2 */
	inline matrix4x4 concatenated( const matrix4x4& m2 ) const __MST_GPU;

	/* makes the matrix look at a target */
	inline void look_at(const float3& target, const float3& global_up = cfloat3(0,1,0)) __MST_GPU;

	/* rotates the matrix around the global x axis */
	inline void rotate_x( float angle_in_radians ) __MST_GPU;

	/* returns a copy of the matrix, that is rotated around the global x axis */
	inline matrix4x4 rotated_x( float angle_in_radians ) const __MST_GPU;

	/* rotates the matrix around the global y axis */
	inline void rotate_y( float angle_in_radians ) __MST_GPU;

	/* returns a copy of the matrix, that is rotated around the global y axis */
	inline matrix4x4 rotated_y( float angle_in_radians ) const __MST_GPU;

	/* rotates the matrix around the global z axis */
	inline void rotate_z( float rz ) __MST_GPU;

	/* returns a copy of the matrix, that is rotated around the global z axis */
	inline matrix4x4 rotated_z( float rz ) const __MST_GPU;

	/* rotates the vector by the orientation part of the matrix */
	inline void rotate_float3(float3& vec) const __MST_GPU;

	/* returns a copy of the vector, that is rotated by the orientation part of the matrix */
	inline float3 rotated_float3(const float3& vec) const __MST_GPU;

	/* rotates the vector by the orientation part of the matrix */
	inline void rotate_float4(float4& vec) const;

	/* returns a copy of the vector, that is rotated by the orientation part of the matrix */
	inline float4 rotated_float4(const float4& vec) const;

	/* sets the x axis of the matrix */
	inline void set_x_axis(const float3& vec) __MST_GPU;

	/* sets the y axis of the matrix */
	inline void set_y_axis(const float3& vec) __MST_GPU;

	/* sets the z axis of the matrix */
	inline void set_z_axis(const float3& vec) __MST_GPU;

	/* swaps the signs of the x axis */
	inline void swap_x_axis() __MST_GPU;

	/* swaps the signs of the y axis */
	inline void swap_y_axis() __MST_GPU;

	/* swaps the signs of the z axis */
	inline void swap_z_axis() __MST_GPU;

	/* returns the x axis of the matrix */
	inline const float3& get_x_axis() const __MST_GPU;

	/* returns the y axis of the matrix */
	inline const float3& get_y_axis() const __MST_GPU;

	/* returns the z axis of the matrix */
	inline const float3& get_z_axis() const __MST_GPU;

	/* transposes the matrix, and will return a reference to itself */
	inline matrix4x4& transpose() __MST_GPU;

	/* returns a transposed copy of itself */
	inline matrix4x4 transposed() const __MST_GPU;

	/* normalizes the x, y and z axis of the matrix, and will return a reference to itself */
	inline matrix4x4& normalize() __MST_GPU;

	/* returns a normalized copy of itself */
	inline matrix4x4 normalized() const __MST_GPU;

	/* returns a inversed copy of itself */
	inline matrix4x4 inversed() const __MST_GPU;

	/* inverts the matrix, and will return a reference to itself */
	inline matrix4x4& inverse() __MST_GPU;

	/* only rotates the matrix by mat */
	inline void rotate(const matrix4x4& mat) __MST_GPU;

	/* returns a copy of itself that is only rotated by mat */
	inline matrix4x4 rotated(const matrix4x4& mat) const __MST_GPU;

	/* only rotates the matrix by mat */
	inline void rotate(const matrix3x3& mat) __MST_GPU;

	/* returns a copy of itself that is only rotated by mat */
	inline matrix4x4 rotated(const matrix3x3& mat) const __MST_GPU;

	/* returns the float array data */
	inline float* data();

	/* returns the float array data */
	inline const float* data() const;

	// operator overloads

	inline matrix4x4& operator =(const matrix3x3& mat) __MST_GPU;

	inline matrix4x4& operator *= (const matrix4x4& mat) __MST_GPU;
	inline matrix4x4& operator *= (const matrix3x3& mat) __MST_GPU;
	inline matrix4x4& operator *= (float val) __MST_GPU;

	inline matrix4x4& operator += (const matrix4x4& mat) __MST_GPU;
	inline matrix4x4& operator -= (const matrix4x4& mat) __MST_GPU;

	inline friend matrix4x4 operator * (const matrix4x4& mat1, const matrix4x4& mat2) __MST_GPU;
	inline friend matrix4x4 operator * (const matrix4x4& mat, float val) __MST_GPU;
	inline friend float3 operator * (const matrix4x4& mat, const float3& vec) __MST_GPU;
	inline friend float4 operator * (const matrix4x4& mat, const float4& vec) __MST_GPU;

	inline friend matrix4x4 operator + (const matrix4x4& mat1, const matrix4x4& mat2) __MST_GPU;
	inline friend matrix4x4 operator - (const matrix4x4& mat1, const matrix4x4& mat2) __MST_GPU;

	inline _Details::_float_array_4 operator [] (size_t n) __MST_GPU;
	inline _Details::_const_float_array_4 operator [] (size_t n) const __MST_GPU;

	float cell[4][4];

	static const matrix4x4 identity_matrix;
	static const size_t dimensions = 16;
	typedef float value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};


// quaternion

/* constructs a quaternion with a rotation axis and an angle */
inline quaternion cquaternion(float angle_in_radians, const float3& normalized_axis) __MST_GPU;

/* constructs a quaternion from all the loose components */
inline quaternion cquaternion(float aw, float ax, float ay, float az) __MST_GPU;

/* constructs a quaternion from a 4x4 matrix */
inline quaternion cquaternion(const matrix4x4& mat) __MST_GPU;

/* constructs a quaternion from a 3x3 matrix */
inline quaternion cquaternion(const matrix3x3& mat) __MST_GPU;

struct quaternion
{

	/* sets the quaternion's values with a rotation axis and an angle */
	inline void set(float angle_in_radians, const float3& normalized_axis) __MST_GPU;

	/* sets the quaternion's values with all the loose components */
	inline void set(float aw, float ax, float ay, float az) __MST_GPU;

	/* sets the quaternion's values from a 4x4 matrix */
	inline void set(const matrix4x4& mat) __MST_GPU;

	/* sets the quaternion's values from a 3x3 matrix */
	inline void set(const matrix3x3& mat) __MST_GPU;

	/* sets the quaternion's values from an array of values */
	inline void set(const float (&values)[4]) __MST_GPU;

	/* sets the quaternion's values from an array of values */
	inline void set(const double (&values)[4]) __MST_GPU;

	/* conjugates the quaternion */
	inline quaternion& conjugate() __MST_GPU;

	/* returns a conjugated copy of the quaternion */
	inline quaternion conjugated() const __MST_GPU;

	/* inverse the quaternion */
	inline quaternion& inverse() __MST_GPU;

	/* return a inversed copy of the quaternion */
	inline quaternion inversed() const __MST_GPU;

	/* sets out_axis to the orientation of rotation and out_angle to amount of rotation */
	inline void to_axis_angle(float3& out_axis, float& out_angle) const __MST_GPU;

	/* normalizes itself and returns a reference to itself */
	inline quaternion& normalize() __MST_GPU;

	/* returns the normalized version of itself */
	inline quaternion normalized() const __MST_GPU;

	/* returns the length of the quaternion */
	inline float length() const __MST_GPU;

	/* returns the square length of the quaternion */
	inline float square_length() const __MST_GPU;

	/* returns a copy of vec rotated by the orientation of the quaternion */
	inline float3 rotate_point(const float3& vec) const __MST_GPU;

	/* rotates the quaternion with quats rotation */
	inline void rotate(const quaternion& quat);

	/* returns a copy of the quaternion rotated with quats rotation */
	inline quaternion rotated(const quaternion& quat) const;

	/* makes the quaternion lookat the position */
	inline void look_at(const float3& position, const float3& up = cfloat3(0,1,0));

	/* returns the dot product of this and quat */
	inline float dot(const quaternion& quat) const __MST_GPU;

	/* returns the dot product of this and quat */
	inline float3 get_x_axis() const __MST_GPU;

	/* returns the dot product of this and quat */
	inline float3 get_y_axis() const __MST_GPU;

	/* returns the dot product of this and quat */
	inline float3 get_z_axis() const __MST_GPU;

	/* returns a quaternion which is the spherical linear interpolation result between this and quat */
	inline quaternion slerp(const quaternion &quat, float t) const __MST_GPU;

	/* returns the float array data */
	inline float* data();

	/* returns the float array data */
	inline const float* data() const;

	// operator overloads

	inline operator matrix3x3() const __MST_GPU;

	inline friend quaternion operator * (const quaternion& quat1, const quaternion& quat2) __MST_GPU;
	inline friend quaternion operator * (const quaternion& quat, float val) __MST_GPU;

	inline friend quaternion operator + (const quaternion& quat1, const quaternion& quat2) __MST_GPU;

	inline quaternion& operator *= (const quaternion& quat) __MST_GPU;
	inline quaternion& operator *= (float val) __MST_GPU;

	inline quaternion& operator /= (float val) __MST_GPU;

	inline quaternion operator - () const __MST_GPU;

	inline friend std::ostream& operator << (std::ostream& stream, const quaternion& value);

	inline float& operator[](size_t n) __MST_GPU;
	inline const float& operator[](size_t n) const __MST_GPU;

	union
	{
		struct
		{
			float w;
			union
			{
				struct { float3 v; };
				struct { float x, y, z; };
			};
		};
		float element[4];
	};

	static const quaternion identity;
	static const size_t dimensions = 4;
	typedef float value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};


// forward declarations
struct int2;
struct int3;
struct uint2;

struct short2;
struct ushort2;

inline int2 cint2(const int ax, const int ay) __MST_GPU;

struct int2
{
	inline void set(const int ax, const int ay) __MST_GPU;

	/* returns the float array data */
	inline int* data();

	/* returns the float array data */
	inline const int* data() const;

	inline int& operator [] (size_t i);

	inline friend bool operator == (const int2& left, const int2& right) __MST_GPU;

	union
	{
		struct { int x, y; };
		struct { int axis[2]; };
	};

	static const int2 zero;
	static const size_t dimensions = 2;
	typedef int value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};

inline ushort2 cushort2(const ushort ax, const ushort ay) __MST_GPU;

struct ushort2
{
	inline void set(const ushort ax, const ushort ay) __MST_GPU;

	/* returns the float array data */
	inline ushort* data();

	/* returns the float array data */
	inline const ushort* data() const;

	inline friend ushort2 operator - (const ushort2& vec1, const ushort2& vec2) __MST_GPU;
	inline friend ushort2 operator * (const ushort2& vec1, const ushort2& vec2) __MST_GPU;
	inline friend ushort2 operator + (const ushort2& vec1, const ushort2& vec2) __MST_GPU;
	inline friend ushort2 operator * (const ushort2& vec1, const ushort val) __MST_GPU;
	inline friend ushort2 operator / (const ushort2& vec1, const ushort val) __MST_GPU;
	inline friend ushort2 operator / (const ushort val, const ushort2& vec1) __MST_GPU;

	inline friend bool operator == (const ushort2& vec1, const ushort2& vec2) __MST_GPU;
	inline friend bool operator != (const ushort2& vec1, const ushort2& vec2) __MST_GPU;
	
	inline ushort2& operator *= (const ushort val) __MST_GPU;
	inline ushort2& operator /= (const ushort val) __MST_GPU;
	inline ushort2& operator *= (const ushort2& vec) __MST_GPU;
	inline ushort2& operator += (const ushort2& vec) __MST_GPU;
	inline ushort2& operator -= (const ushort2& vec) __MST_GPU;

	inline ushort& operator [] (size_t i) __MST_GPU;

	union
	{
		struct { ushort x, y; };
		struct { ushort axis[2]; };
	};

	static const ushort2 zero;
	static const size_t dimensions = 2;
	typedef ushort value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};

inline short2 cshort2(const short x, const short y);

struct short2
{
	inline void set(const short ax, const short ay) __MST_GPU;

	/* returns the float array data */
	inline short* data();

	/* returns the float array data */
	inline const short* data() const;

	inline short& operator [] (size_t i) __MST_GPU;

	inline friend bool operator == (const short2& left, const short2& right) __MST_GPU;

	union
	{
		struct { short x, y; };
		struct { short axis[2]; };
	};

	static const short2 zero;
	static const size_t dimensions = 2;
	typedef int value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};

inline uint2 cuint2(const uint x, const uint y) __MST_GPU;

struct uint2
{
	inline uint& operator [] (size_t i) __MST_GPU;

	/* returns the float array data */
	inline uint* data();

	/* returns the float array data */
	inline const uint* data() const;

	inline friend bool operator == (const uint2& left, const uint2& right) __MST_GPU;
	
	union
	{
		struct { uint x, y; };
		struct { uint axis[2]; };
	};

	static const uint2 zero;
	static const size_t dimensions = 2;
	typedef uint value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};

inline int3 cint3(const int x, const int y, const int z) __MST_GPU;

struct int3
{

	inline void set(const int ax, int ay, int az) __MST_GPU;

	/* returns the float array data */
	inline int* data();

	/* returns the float array data */
	inline const int* data() const;

	inline int& operator [] (size_t i) __MST_GPU;

	inline friend bool operator == (const int3& left, const int3& right) __MST_GPU;

	union
	{
		struct { int x, y, z; };
		struct { int axis[3]; };
	};

	static const int3 zero;
	static const size_t dimensions = 3;
	typedef int value_type;
	typedef ::std::is_unsigned<value_type> is_unsigned;
};

//#include <mx_math.inl>
#include <mx_swizzling.h>
#include <mx_float2.inl>
#include <mx_float3.inl>
#include <mx_float4.inl>
#include <mx_matrix3x3.inl>
#include <mx_matrix4x4.inl>
#include <mx_quaternion.inl>
#include <mx_small_types.inl>
#include <mx_math_statics.inl>

#undef __INSIDE_MMATH_H__

}; }; // namespace mst::math

#endif