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

#ifndef QUATERNION_EPSILON
#define QUATERNION_EPSILON 1e-4f
#endif

/* constructs a quaternion with a rotation axis and an angle */
inline quaternion (::mst::math::cquaternion)(float angle_in_radians, const float3& normalized_axis) __MST_GPU
{
	quaternion retval;

	retval.w = _AMP_MATH_NAMESPACE_ cos(angle_in_radians / 2.0f);
	retval.v = normalized_axis;

	CHECK_IF_ARG_GPU(_AMP_MATH_NAMESPACE_ fabs(normalized_axis.length() - 1.0f) > EPSILON, "vector needs to be normalized", normalized_axis.length());
	retval.v *= _AMP_MATH_NAMESPACE_ sin(angle_in_radians / 2.0f);

	return retval;
}

/* constructs a quaternion from all the loose components */
quaternion (::mst::math::cquaternion)(float w, float x, float y, float z) __MST_GPU
{
	quaternion retval = { w, x, y, z };
	return retval;
}

/* constructs a quaternion from a 4x4 matrix */
quaternion (::mst::math::cquaternion)(const matrix4x4& mat) __MST_GPU
{
	quaternion retval;
	retval.set(mat);
	return retval;
}

/* constructs a quaternion from a 3x3 matrix */
quaternion (::mst::math::cquaternion)(const matrix3x3& mat) __MST_GPU
{
	quaternion retval;
	retval.set(mat);
	return retval;
}

/* sets the quaternion's values with a rotation axis and an angle */
inline void quaternion::set(float angle_in_radians, const float3& normalized_axis) __MST_GPU
{
	w = _AMP_MATH_NAMESPACE_ cos(angle_in_radians / 2.0f);
	v = normalized_axis * _AMP_MATH_NAMESPACE_ sin(angle_in_radians / 2.0f);
}

/* sets the quaternion's values with all the loose components */
inline void quaternion::set(float aw, float ax, float ay, float az) __MST_GPU
{
	w = aw;
	v.set(ax, ay, az);
}

/* sets the quaternion's values from a 4x4 matrix */
inline void quaternion::set(const matrix4x4& mat) __MST_GPU
{
	float trace = mat[0][0] + mat[1][1] + mat[2][2];
	if( trace > 0 ) {
	float s = 0.5f / _AMP_MATH_NAMESPACE_ sqrt(trace+ 1.0f);
	w = 0.25f / s;
	x = ( mat[1][2] - mat[2][1] ) * s;
	y = ( mat[2][0] - mat[0][2] ) * s;
	z = ( mat[0][1] - mat[1][0] ) * s;
	} else {
	if ( mat[0][0] > mat[1][1] && mat[0][0] > mat[2][2] ) {
		float s = 2.0f * _AMP_MATH_NAMESPACE_ sqrt( 1.0f + mat[0][0] - mat[1][1] - mat[2][2]);
		w = (mat[1][2] - mat[2][1] ) / s;
		x = 0.25f * s;
		y = (mat[1][0] + mat[0][1] ) / s;
		z = (mat[2][0] + mat[0][2] ) / s;
	} else if (mat[1][1] > mat[2][2]) {
		float s = 2.0f * _AMP_MATH_NAMESPACE_ sqrt( 1.0f + mat[1][1] - mat[0][0] - mat[2][2]);
		w = (mat[2][0] - mat[0][2] ) / s;
		x = (mat[1][0] + mat[0][1] ) / s;
		y = 0.25f * s;
		z = (mat[2][1] + mat[1][2] ) / s;
	} else {
		float s = 2.0f * _AMP_MATH_NAMESPACE_ sqrt( 1.0f + mat[2][2] - mat[0][0] - mat[1][1] );
		w = (mat[0][1] - mat[1][0] ) / s;
		x = (mat[2][0] + mat[0][2] ) / s;
		y = (mat[2][1] + mat[1][2] ) / s;
		z = 0.25f * s;
	}
	}
}

/* sets the quaternion's values from a 3x3 matrix */
inline void quaternion::set(const matrix3x3& mat) __MST_GPU
{
	float trace = mat[0][0] + mat[1][1] + mat[2][2];
	if( trace > 0 ) {
	float s = 0.5f / _AMP_MATH_NAMESPACE_ sqrt(trace+ 1.0f);
	w = 0.25f / s;
	x = ( mat[1][2] - mat[2][1] ) * s;
	y = ( mat[2][0] - mat[0][2] ) * s;
	z = ( mat[0][1] - mat[1][0] ) * s;
	} else {
	if ( mat[0][0] > mat[1][1] && mat[0][0] > mat[2][2] ) {
		float s = 2.0f * _AMP_MATH_NAMESPACE_ sqrt( 1.0f + mat[0][0] - mat[1][1] - mat[2][2]);
		w = (mat[1][2] - mat[2][1] ) / s;
		x = 0.25f * s;
		y = (mat[1][0] + mat[0][1] ) / s;
		z = (mat[2][0] + mat[0][2] ) / s;
	} else if (mat[1][1] > mat[2][2]) {
		float s = 2.0f * _AMP_MATH_NAMESPACE_ sqrt( 1.0f + mat[1][1] - mat[0][0] - mat[2][2]);
		w = (mat[2][0] - mat[0][2] ) / s;
		x = (mat[1][0] + mat[0][1] ) / s;
		y = 0.25f * s;
		z = (mat[2][1] + mat[1][2] ) / s;
	} else {
		float s = 2.0f * _AMP_MATH_NAMESPACE_ sqrt( 1.0f + mat[2][2] - mat[0][0] - mat[1][1] );
		w = (mat[0][1] - mat[1][0] ) / s;
		x = (mat[2][0] + mat[0][2] ) / s;
		y = (mat[2][1] + mat[1][2] ) / s;
		z = 0.25f * s;
	}
	}
}

/* sets the quaternion's values from an array of values */
inline void quaternion::set(const float (&values)[4]) __MST_GPU
{
	for(int i = 0; i < 4; ++i)
	{
		element[i] = values[i];
	}
}

/* sets the quaternion's values from an array of values */
inline void quaternion::set(const double (&values)[4]) __MST_GPU
{
	for(int i = 0; i < 4; ++i)
	{
		element[i] = (float)values[i];
	}
}

/* conjugates the quaternion */
inline quaternion& quaternion::conjugate() __MST_GPU
{
	v.swap_signs();
	return *this;
}

/* returns a conjugated copy of the quaternion */
inline quaternion quaternion::conjugated() const __MST_GPU
{
	return quaternion(*this).conjugate();
}

/* conjugates the quaternion */
inline quaternion& quaternion::inverse() __MST_GPU
{
	conjugate();
	*this /= square_length();
	return *this;
}

/* returns a conjugated copy of the quaternion */
inline quaternion quaternion::inversed() const __MST_GPU
{
	return quaternion(*this).inverse();
}

inline void quaternion::to_axis_angle(float3& out_axis, float& out_angle) const __MST_GPU
{
	out_angle = _AMP_MATH_NAMESPACE_ acos(w);

	if(out_angle < EPSILON)
	{
		out_axis.set(0,0,0);
		out_angle = 0.0f;
		return;
	}

	// pre-compute to save time
	float sinf_theta_inv = 1.0f/ _AMP_MATH_NAMESPACE_ sin(out_angle);

	// now the vector
	out_axis.x = x*sinf_theta_inv;
	out_axis.y = y*sinf_theta_inv;
	out_axis.z = z*sinf_theta_inv;
}

/* normalizes itself and returns a reference to itself */
inline quaternion& quaternion::normalize() __MST_GPU
{
	const float inv_length = 1.0f / length();
	w *= inv_length;
	x *= inv_length;
	y *= inv_length;
	z *= inv_length;
	return *this;
}

/* returns the normalized version of itself */
inline quaternion quaternion::normalized() const __MST_GPU
{
	return quaternion(*this).normalize();
}

/* returns the length of the quaternion */
inline float quaternion::length() const __MST_GPU
{
	return _AMP_MATH_NAMESPACE_ sqrt( square_length() );
}

/* returns the square length of the quaternion */
inline float quaternion::square_length() const __MST_GPU
{
	return w * w + x * x + y * y + z * z;
}

/* returns vec rotated by the orientation of the quaternion */
inline float3 quaternion::rotate_point(const float3& vec) const __MST_GPU
{
	CHECK_IF_ARG_GPU(_AMP_MATH_NAMESPACE_ fabs(length() - 1.0f) > QUATERNION_EPSILON, "quaternion is not normalized, length", length());

	const float qw2 = w * w;
	const float qx2 = x * x;
	const float qy2 = y * y;
	const float qz2 = z * z;

	float3 dx = { 1 - 2*qy2 - 2*qz2, 2*x*y - 2*z*w, 2*x*z + 2*y*w },
		dy = { 2*x*y + 2*z*w, 1 - 2*qx2 - 2*qz2, 2*y*z - 2*x*w },
		dz = { 2*x*z - 2*y*w, 2*y*z + 2*x*w, 1 - 2*qx2 - 2*qy2 };

	return cfloat3(
		dx.x * vec.x + dx.y * vec.y + dx.z * vec.z,
		dy.x * vec.x + dy.y * vec.y + dy.z * vec.z,
		dz.x * vec.x + dz.y * vec.y + dz.z * vec.z
		);
}

/* rotates the quaternion with quats rotation */
inline void quaternion::rotate(const quaternion& quat)
{
	(*this) = quat * (*this);
}

/* returns a copy of the quaternion rotated with quats rotation */
inline quaternion quaternion::rotated(const quaternion& quat) const
{
	quaternion q(*this);
	q.rotate(quat);
	return q;
}

/* makes the quaternion lookat the position */
inline void quaternion::look_at(const float3& position, const float3& up)
{
	matrix3x3 mat(matrix3x3::identity_matrix);

	mat.look_at(position, up);

	set(mat);
}

/* returns the dot product of this and quat */
inline float quaternion::dot(const quaternion& quat) const __MST_GPU
{
	return (w * quat.w + x * quat.x + y * quat.y + z * quat.z);
}

/* returns the dot product of this and quat */
inline float3 quaternion::get_x_axis() const __MST_GPU
{
	float3 retval =
	{
		1.0f - 2.0f * (y * y + z * z),
		2.0f * (x * y + w * z),
		2.0f * (x * z - w * y)
	};

	return retval;
}

/* returns the dot product of this and quat */
inline float3 quaternion::get_y_axis() const __MST_GPU
{
	float3 retval =
	{
		2.0f * (x * y - w * z),
		1.0f - 2.0f * (x * x + z * z),
		2.0f * (y * z + w * x)
	};

	return retval;
}

/* returns the dot product of this and quat */
inline float3 quaternion::get_z_axis() const __MST_GPU
{
	float3 retval =
	{
		2.0f * (x * z + w * y),
		2.0f * (y * z - w * x),
		1.0f - 2.0f * (x * x + y * y)
	};

	return retval;
}

/* returns a quaternion which is the spherical linear interpolation result between this and quat */
inline quaternion quaternion::slerp(const quaternion &q2, float t) const __MST_GPU
{
	CHECK_IF_ARG_GPU(_AMP_MATH_NAMESPACE_ fabs(length() - 1.0f) > QUATERNION_EPSILON, "quaternion is not normalized, length", length());

	quaternion q3;
	float dot12 = dot(q2);

	/*	dot = cos(theta)
		if (dot < 0), q1 and q2 are more than 90 degrees apart,
		so we can invert one to reduce spinning	*/
	if (dot12 < 0)
	{
		dot12 = -dot12;
		q3 = -q2;
	} else q3 = q2;
		
	if (dot12 < 0.95f)
	{
		float angle = _AMP_MATH_NAMESPACE_ acos(dot12);
		return ((*this)*
			_AMP_MATH_NAMESPACE_ sin(angle*(1-t))
			+ q3* 
			_AMP_MATH_NAMESPACE_ sin(angle*t))
			* (1.0f/ 
			_AMP_MATH_NAMESPACE_ sin(angle));
	} else // if the angle is small, use linear interpolation								
		return lerp((*this),q3,t);
}

inline quaternion::operator matrix3x3() const __MST_GPU
{
	matrix3x3 retval;
	retval.set(*this);
	return retval;
}

inline quaternion (::mst::math::operator * )(const quaternion& quat1, const quaternion& quat2) __MST_GPU
{
	return cquaternion(quat1.w*quat2.w - quat1.v.dot(quat2.v),
				quat1.y*quat2.z - quat1.z*quat2.y + quat1.w*quat2.x + quat1.x*quat2.w,
				quat1.z*quat2.x - quat1.x*quat2.z + quat1.w*quat2.y + quat1.y*quat2.w,
				quat1.x*quat2.y - quat1.y*quat2.x + quat1.w*quat2.z + quat1.z*quat2.w);
}

inline quaternion (::mst::math::operator * )(const quaternion& quat, float val) __MST_GPU
{
	return cquaternion(quat.w * val, quat.x * val, quat.y * val, quat.z * val);
}

inline quaternion (::mst::math::operator + )(const quaternion& quat1, const quaternion& quat2) __MST_GPU
{
	return cquaternion(quat1.w + quat2.w, quat1.x + quat2.x, quat1.y + quat2.y, quat1.z + quat2.z);
}

inline quaternion& quaternion::operator *= (const quaternion& quat) __MST_GPU
{
	const float rw = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
	const float rx = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
	const float ry = w * quat.y - x * quat.z + y * quat.w + z * quat.x;
	const float rz = w * quat.z + x * quat.y - y * quat.x + z * quat.w;

	w = rw;
	x = rx;
	y = ry;
	z = rz;

	return *this;
}

inline quaternion& quaternion::operator *= (float val) __MST_GPU
{
	for(int i = 0; i < 4; ++i)
	{
		element[i] *= val;
	}

	return *this;
}

inline quaternion& quaternion::operator /= (float val) __MST_GPU
{
	return (*this *= 1.0f / val);
}

inline quaternion quaternion::operator - () const __MST_GPU
{
	return cquaternion(-w, -x, -y, -z);
}

inline std::ostream& (::mst::math::operator << )(std::ostream& stream, const quaternion& value)
{
	stream << "<" << value.w << ", " << value.x << ", " << value.y << ", " << value.z << ">";
	return stream;
}

inline const float& quaternion::operator[](size_t n) const __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 4, "array index out of range");
	return element[n];
}

inline float& quaternion::operator[](size_t n) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 4, "array index out of range");
	return element[n];
}

#endif // __INSIDE_MMATH_H__