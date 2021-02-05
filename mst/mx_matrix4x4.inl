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

/* constructs a matrix from the values of the array */
matrix4x4 (::mst::math::cmatrix4x4)(const float (&values)[16]) __MST_GPU
{
	matrix4x4 retval;
	retval.set(values);
	return retval;
}

/* constructs a matrix from the values of the array */
matrix4x4 (::mst::math::cmatrix4x4)(const float (&values)[4][4]) __MST_GPU
{
	matrix4x4 retval;
	retval.set(values);
	return retval;
}

/* constructs a matrix with a position and a quaternion for orientation */
matrix4x4 (::mst::math::cmatrix4x4)(const float3& position, const quaternion& quat) __MST_GPU
{
	matrix4x4 retval;
	retval.set(position, quat);
	return retval;
}

/* constructs a matrix with a position and a quaternion for orientation and a scale */
matrix4x4 (::mst::math::cmatrix4x4)(const float3& position, const quaternion& quat, float scale) __MST_GPU
{
	matrix4x4 retval;
	retval.set(position, quat, scale);
	return retval;
}


/* constructs a matrix with a position and an orientation */
matrix4x4 (::mst::math::cmatrix4x4)(const float3& position, const matrix3x3& orientation) __MST_GPU
{
	matrix4x4 retval;
	retval.set(position, orientation);
	return retval;
}

/* constructs a matrix with a position and an orientation */
matrix4x4 (::mst::math::cmatrix4x4)(const float4& position, const matrix3x3& orientation) __MST_GPU
{
	matrix4x4 retval;
	retval.set(position, orientation);
	return retval;
}

matrix4x4 (::mst::math::cmatrix4x4)(const float3& position, const float3& x_axis, const float3& y_axis, const float3& z_axis) __MST_GPU
{
	matrix4x4 retval = matrix4x4::identity_matrix;
	retval.set_x_axis(x_axis);
	retval.set_y_axis(y_axis);
	retval.set_z_axis(z_axis);
	retval.set_position(position);
	return retval;
}

/* constructs a matrix from the values */
matrix4x4 (::mst::math::cmatrix4x4)(float cell1, float cell2, float cell3, float cell4, 
	float cell5, float cell6, float cell7, float cell8, 
	float cell9, float cell10, float cell11, float cell12,
	float cell13, float cell14, float cell15, float cell16) __MST_GPU
{
	matrix4x4 retval;

	retval.cell[0][0] = cell1, retval.cell[0][1] = cell2, retval.cell[0][2] = cell3, retval.cell[0][3] = cell4;
	retval.cell[1][0] = cell5, retval.cell[1][1] = cell6, retval.cell[1][2] = cell7, retval.cell[1][3] = cell8;
	retval.cell[2][0] = cell9,  retval.cell[2][1] = cell10, retval.cell[2][2] = cell11, retval.cell[2][3] = cell12;
	retval.cell[3][0] = cell13, retval.cell[3][1] = cell14, retval.cell[3][2] = cell15, retval.cell[3][3] = cell16;

	return retval;
}

/* sets the values of the matrix */
inline void matrix4x4::set(const float (&values)[16]) __MST_GPU
{
	int k = 0;
	for(int i = 0; i < 4; ++i) for(int j = 0; j < 4; ++j)
	{
		cell[i][j] = values[k];
		k++;
	}
}

/* sets the values of the matrix */
inline void matrix4x4::set(const float (&values)[4][4]) __MST_GPU
{
	for(int i = 0; i < 4; ++i) for(int j = 0; j < 4; ++j)
	{
		cell[i][j] = values[i][j];
	}
}

/* sets the values of the matrix */
inline void matrix4x4::set(float cell1, float cell2, float cell3, float cell4, 
	float cell5, float cell6, float cell7, float cell8, 
	float cell9, float cell10, float cell11, float cell12,
	float cell13, float cell14, float cell15, float cell16) __MST_GPU
{
	cell[0][0] = cell1, cell[1][0] = cell2, cell[2][0] = cell3, cell[3][0] = cell4;
	cell[0][1] = cell5, cell[1][1] = cell6, cell[2][1] = cell7, cell[3][1] = cell8;
	cell[0][2] = cell9, cell[1][2] = cell10, cell[2][2] = cell11, cell[3][2] = cell12;
	cell[0][3] = cell13, cell[1][3] = cell14, cell[2][3] = cell15, cell[3][3] = cell16;
}

/* sets the values of the matrix */
inline void matrix4x4::set(const float3& position, const matrix3x3& orientation) __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[i][3] = 0.0f;
		cell[3][i] = position.axis[i];
	}
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		cell[i][j] = orientation[i][j];
	}

	cell[3][3] = 1.0f;
}

/* sets the values of the matrix */
inline void matrix4x4::set(const float4& position, const matrix3x3& orientation) __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[i][3] = 0.0f;
		cell[3][i] = position.axis[i];
	}
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		cell[i][j] = orientation[i][j];
	}

	cell[3][3] = position.w;
}

/* sets the values of the matrix */
inline void matrix4x4::set(const float3& position, const quaternion& quat) __MST_GPU
{
	set_orientation(quat);
	set_position(position);
	cell[3][3] = 1.0f;
	cell[0][3] = cell[1][3] = cell[2][3] = 0.0f;
}

/* sets the values of the matrix */
inline void matrix4x4::set(const float4& position, const quaternion& quat) __MST_GPU
{
	set_orientation(quat);
	set_position(position);
	cell[3][3] = 1.0f;
	cell[0][3] = cell[1][3] = cell[2][3] = 0.0f;
}

/* sets the values of the matrix */
inline void matrix4x4::set(const float3& position, const quaternion& quat, float scale) __MST_GPU
{
	set_orientation(quat, scale);
	set_position(position);
	cell[3][3] = 1.0f;
	cell[0][3] = cell[1][3] = cell[2][3] = 0.0f;
}

/* sets the values of the matrix */
inline void matrix4x4::set(const float4& position, const quaternion& quat, float scale) __MST_GPU
{
	set_orientation(quat, scale);
	set_position(position);
	cell[0][3] = cell[1][3] = cell[2][3] = 0.0f;
}

/* sets only the rotation part of the matrix from mat into the matrix */
inline void matrix4x4::set_orientation(const matrix4x4& mat) __MST_GPU
{
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		cell[i][j] = mat[i][j];
	}
}

/* sets only the rotation part of the matrix from mat into the matrix */
inline void matrix4x4::set_orientation(const matrix3x3& mat) __MST_GPU
{
	set_orientation(mat.cell);
}

/* sets only the rotation part of the matrix from a quaternion */
inline void matrix4x4::set_orientation(const quaternion& quat) __MST_GPU
{
	cell[0][0] = 1.0f - 2.0f * (quat.y * quat.y + quat.z * quat.z);
	cell[1][0] = 2.0f * (quat.x * quat.y - quat.w * quat.z);  
	cell[2][0] = 2.0f * (quat.x * quat.z + quat.w * quat.y);  
	cell[0][1] = 2.0f * (quat.x * quat.y + quat.w * quat.z);  
	cell[1][1] = 1.0f - 2.0f * (quat.x * quat.x + quat.z * quat.z);
	cell[2][1] = 2.0f * (quat.y * quat.z - quat.w * quat.x);  
	cell[0][2] = 2.0f * (quat.x * quat.z - quat.w * quat.y);  
	cell[1][2] = 2.0f * (quat.y * quat.z + quat.w * quat.x);  
	cell[2][2] = 1.0f - 2.0f * (quat.x * quat.x + quat.y * quat.y);
}

/* sets only the rotation part of the matrix from  a quaternion and a scale */
inline void matrix4x4::set_orientation(const quaternion& quat, float scale) __MST_GPU
{
	cell[0][0] = (1.0f - 2.0f * (quat.y * quat.y + quat.z * quat.z)) * scale;
	cell[1][0] = (2.0f * (quat.x * quat.y - quat.w * quat.z)) * scale;  
	cell[2][0] = (2.0f * (quat.x * quat.z + quat.w * quat.y)) * scale;  
	cell[0][1] = (2.0f * (quat.x * quat.y + quat.w * quat.z)) * scale;  
	cell[1][1] = (1.0f - 2.0f * (quat.x * quat.x + quat.z * quat.z)) * scale;
	cell[2][1] = (2.0f * (quat.y * quat.z - quat.w * quat.x)) * scale;  
	cell[0][2] = (2.0f * (quat.x * quat.z - quat.w * quat.y)) * scale;  
	cell[1][2] = (2.0f * (quat.y * quat.z + quat.w * quat.x)) * scale;  
	cell[2][2] = (1.0f - 2.0f * (quat.x * quat.x + quat.y * quat.y)) * scale;
}

/* sets only the rotation part of the matrix from values into the matrix */
inline void matrix4x4::set_orientation(const float (&values)[3][3]) __MST_GPU
{
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		cell[i][j] = values[i][j];
	}
}

/* sets only the rotation part of the matrix from xyz euler rotations into the matrix */
inline void matrix4x4::set_orientation_euler_xyz(const float3& euler_rotations) __MST_GPU
{
	set_orientation(matrix3x3::identity_matrix.rotated_x(euler_rotations.x).rotated_y(euler_rotations.y).rotated_z(euler_rotations.z));
}

/* sets only the rotation part of the matrix from xzy euler rotations into the matrix */
inline void matrix4x4::set_orientation_euler_xzy(const float3& euler_rotations) __MST_GPU
{
	set_orientation(matrix3x3::identity_matrix.rotated_x(euler_rotations.x).rotated_z(euler_rotations.z).rotated_y(euler_rotations.y));
}

/* sets only the rotation part of the matrix from yzx euler rotations into the matrix */
inline void matrix4x4::set_orientation_euler_yzx(const float3& euler_rotations) __MST_GPU
{
	set_orientation(matrix3x3::identity_matrix.rotated_y(euler_rotations.y).rotated_z(euler_rotations.z).rotated_x(euler_rotations.x));
}

/* sets only the rotation part of the matrix from zxy euler rotations into the matrix */
inline void matrix4x4::set_orientation_euler_zxy(const float3& euler_rotations) __MST_GPU
{
	set_orientation(matrix3x3::identity_matrix.rotated_z(euler_rotations.z).rotated_x(euler_rotations.x).rotated_y(euler_rotations.y));
}

/* sets only the rotation part of the matrix from zyx euler rotations into the matrix */
inline void matrix4x4::set_orientation_euler_zyx(const float3& euler_rotations) __MST_GPU
{
	set_orientation(matrix3x3::identity_matrix.rotated_z(euler_rotations.z).rotated_y(euler_rotations.y).rotated_x(euler_rotations.x));
}

/* sets only the rotation part of the matrix from yxz euler rotations into the matrix */
inline void matrix4x4::set_orientation_euler_yxz(const float3& euler_rotations) __MST_GPU
{
	set_orientation(matrix3x3::identity_matrix.rotated_y(euler_rotations.y).rotated_x(euler_rotations.x).rotated_z(euler_rotations.z));
}

/* turns the matrix into an identity matrix */
inline void matrix4x4::set_identity() __MST_GPU
{
	set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

/* resets the rotation part to identity values */
inline void matrix4x4::identity_rotation() __MST_GPU
{
	cell[0][0] = cell[1][1] = cell[2][2] = 1.0f;

	cell[0][1] = cell[0][2] = cell[1][2] = 
	cell[1][0] = cell[2][0] = cell[2][1] = 0.0f;
}

/* returns the position part of the matrix */
inline const float3& matrix4x4::get_position() const __MST_GPU
{
	return *((const float3*)cell[3]);
}

/* sets the position part of the matrix */
inline void matrix4x4::set_position(const float3& position) __MST_GPU
{
	cell[3][0] = position.x;
	cell[3][1] = position.y;
	cell[3][2] = position.z;
}

/* sets the position part of the matrix */
inline void matrix4x4::set_position(const float4& position)
{
	cell[3][0] = position.x;
	cell[3][1] = position.y;
	cell[3][2] = position.z;
	cell[3][3] = position.w;
}

/* translates the position of the matrix */
inline void matrix4x4::translate(const float3& translation) __MST_GPU
{
	cell[3][0] += translation.x;
	cell[3][1] += translation.y;
	cell[3][2] += translation.z;
}

/* swaps the signs of the position part of the matrix */
inline void matrix4x4::swap_position() __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[3][i] = -cell[3][i];
	}
}

/* concatenates the matrix into the space of m2 */
inline void matrix4x4::concatenate( const matrix4x4& m ) __MST_GPU
{
	*this = concatenated(m);
}

/* returns the result of concatenating the matrix into the space of m2 */
inline matrix4x4 matrix4x4::concatenated( const matrix4x4& m ) const __MST_GPU
{
	return *this * m;
}

/* makes the matrix look at a target */
inline void matrix4x4::look_at(const float3& target, const float3& global_up) __MST_GPU
{
	const float3 direction = (target - get_position()).normalize();

	CHECK_IF_GPU(direction.distance(global_up.normalized()) < EPSILON, "bad up vector");

	const float3 right = direction.cross(global_up).normalize();
	const float3 local_up = right.cross(direction).normalize();

	set_x_axis(right);
	set_y_axis(local_up);
	set_z_axis(direction);
}

/* rotates the matrix around the global x axis */
inline void matrix4x4::rotate_x( float angle_in_radians ) __MST_GPU
{
	const float sx = _AMP_MATH_NAMESPACE_ sin( angle_in_radians );
	const float cx = _AMP_MATH_NAMESPACE_ cos( angle_in_radians );
	matrix4x4 rot_mat = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	rot_mat.cell[1][1] = cx, rot_mat.cell[1][2] = sx, rot_mat.cell[2][1] = -sx, rot_mat.cell[2][2] = cx;
	rotate(rot_mat);
}

/* returns a copy of the matrix, that is rotated around the global x axis */
inline matrix4x4 matrix4x4::rotated_x( float angle_in_radians ) const __MST_GPU
{
	const float sx = _AMP_MATH_NAMESPACE_ sin( angle_in_radians );
	const float cx = _AMP_MATH_NAMESPACE_ cos( angle_in_radians );
	matrix4x4 rot_mat = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	rot_mat.cell[1][1] = cx, rot_mat.cell[1][2] = sx, rot_mat.cell[2][1] = -sx, rot_mat.cell[2][2] = cx;
	return rotated(rot_mat);
}

/* rotates the matrix around the global y axis */
inline void matrix4x4::rotate_y( float angle_in_radians ) __MST_GPU
{
	const float sy = _AMP_MATH_NAMESPACE_ sin(angle_in_radians);
	const float cy = _AMP_MATH_NAMESPACE_ cos(angle_in_radians);
	matrix4x4 rot_mat = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	rot_mat.cell[0][0] = cy, rot_mat.cell[0][2] = -sy, rot_mat.cell[2][0] = sy, rot_mat.cell[2][2] = cy;
	rotate(rot_mat);
}

/* returns a copy of the matrix, that is rotated around the global y axis */
inline matrix4x4 matrix4x4::rotated_y( float angle_in_radians ) const __MST_GPU
{
	const float sy = _AMP_MATH_NAMESPACE_ sin(angle_in_radians);
	const float cy = _AMP_MATH_NAMESPACE_ cos(angle_in_radians);
	matrix4x4 rot_mat = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	rot_mat.cell[0][0] = cy, rot_mat.cell[0][2] = -sy, rot_mat.cell[2][0] = sy, rot_mat.cell[2][2] = cy;
	return rotated(rot_mat);
}

/* rotates the matrix around the global z axis */
inline void matrix4x4::rotate_z( float angle_in_radians ) __MST_GPU
{
	const float sz = _AMP_MATH_NAMESPACE_ sin(angle_in_radians);
	const float cz = _AMP_MATH_NAMESPACE_ cos(angle_in_radians);
	matrix4x4 rot_mat = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	rot_mat.cell[0][0] = cz, rot_mat.cell[0][1] = sz, rot_mat.cell[1][0] = -sz, rot_mat.cell[1][1] = cz;
	rotate(rot_mat);
}

/* returns a copy of the matrix, that is rotated around the global z axis */
inline matrix4x4 matrix4x4::rotated_z( float angle_in_radians ) const __MST_GPU
{
	const float sz = _AMP_MATH_NAMESPACE_ sin(angle_in_radians);
	const float cz = _AMP_MATH_NAMESPACE_ cos(angle_in_radians);
	matrix4x4 rot_mat = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	rot_mat.cell[0][0] = cz, rot_mat.cell[0][1] = sz, rot_mat.cell[1][0] = -sz, rot_mat.cell[1][1] = cz;
	return rotated(rot_mat);
}

/* rotates the vector by the orientation part of the matrix */
inline void matrix4x4::rotate_float3(float3& vec) const __MST_GPU
{
	vec = rotated_float3(vec);
}

/* returns a copy of the vector, that is rotated by the orientation part of the matrix */
inline float3 matrix4x4::rotated_float3(const float3& vec) const __MST_GPU
{
	float3 retval;
	for(int i = 0; i < 3; ++i)
	{
		retval.axis[i] = cell[0][i] * vec.x + cell[1][i] * vec.y + cell[2][i] * vec.z;
	}
	return retval;
}

/* rotates the vector by the orientation part of the matrix */
inline void matrix4x4::rotate_float4(float4& vec) const
{
	vec = rotated_float4(vec);
}

/* returns a copy of the vector, that is rotated by the orientation part of the matrix */
inline float4 matrix4x4::rotated_float4(const float4& vec) const
{
	float4 results;
	for(int i = 0; i < 3; ++i)
	{
		results[i] = cell[0][i] * vec.x + cell[1][i] * vec.y + cell[2][i] * vec.z;
	}
	results.w = vec.w;

	return results;
}

/* sets the x axis of the matrix */
inline void matrix4x4::set_x_axis(const float3& vec) __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[0][i] = vec.axis[i];
	}
}

/* sets the y axis of the matrix */
inline void matrix4x4::set_y_axis(const float3& vec) __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[1][i] = vec.axis[i];
	}
}

/* sets the z axis of the matrix */
inline void matrix4x4::set_z_axis(const float3& vec) __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[2][i] = vec.axis[i];
	}
}

/* swaps the signs of the x axis */
inline void matrix4x4::swap_x_axis() __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[0][i] = -cell[0][i];
	}
}

/* swaps the signs of the y axis */
inline void matrix4x4::swap_y_axis() __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[1][i] = -cell[1][i];
	}
}

/* swaps the signs of the z axis */
inline void matrix4x4::swap_z_axis() __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[2][i] = -cell[2][i];
	}
}

/* returns the x axis of the matrix */
inline const float3& matrix4x4::get_x_axis() const __MST_GPU
{
	return *((const float3*)cell[0]);
}

/* returns the y axis of the matrix */
inline const float3& matrix4x4::get_y_axis() const __MST_GPU
{
	return *((const float3*)cell[1]);
}

/* returns the z axis of the matrix */
inline const float3& matrix4x4::get_z_axis() const __MST_GPU
{
	return *((const float3*)cell[2]);
}

/* transposes the matrix, and will return a reference to itself */
inline matrix4x4& matrix4x4::transpose() __MST_GPU
{
	std::swap(cell[0][1], cell[1][0]);
	std::swap(cell[0][2], cell[2][0]);
	std::swap(cell[0][3], cell[3][0]);
	std::swap(cell[1][2], cell[2][1]);
	std::swap(cell[1][3], cell[3][1]);
	std::swap(cell[2][3], cell[3][2]);

	return *this;
}

/* returns a transposed copy of itself */
inline matrix4x4 matrix4x4::transposed() const __MST_GPU
{
	return matrix4x4(*this).transpose();
}

/* normalizes the x, y and z axis of the matrix, and will return a reference to itself */
inline matrix4x4& matrix4x4::normalize() __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		float3& axis = *((float3*)(float*)cell[i]);
		axis.normalize();
	}
	return *this;
}

/* returns a normalized copy of itself */
inline matrix4x4 matrix4x4::normalized() const __MST_GPU
{
	return matrix4x4(*this).normalize();
}

/* returns a inversed copy of itself */
inline matrix4x4 matrix4x4::inversed() const __MST_GPU
{
	const float* values = (const float*)cell[0];

	const float a0 = values[ 0]*values[ 5] - values[ 1]*values[ 4];
	const float a1 = values[ 0]*values[ 6] - values[ 2]*values[ 4];
	const float a2 = values[ 0]*values[ 7] - values[ 3]*values[ 4];
	const float a3 = values[ 1]*values[ 6] - values[ 2]*values[ 5];
	const float a4 = values[ 1]*values[ 7] - values[ 3]*values[ 5];
	const float a5 = values[ 2]*values[ 7] - values[ 3]*values[ 6];
	const float b0 = values[ 8]*values[13] - values[ 9]*values[12];
	const float b1 = values[ 8]*values[14] - values[10]*values[12];
	const float b2 = values[ 8]*values[15] - values[11]*values[12];
	const float b3 = values[ 9]*values[14] - values[10]*values[13];
	const float b4 = values[ 9]*values[15] - values[11]*values[13];
	const float b5 = values[10]*values[15] - values[11]*values[14];

	const float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
	if(_AMP_MATH_NAMESPACE_ fabs(det) > EPSILON)
	{
		matrix4x4 retval;
		float* retvalues = (float*)retval.cell[0];
		retvalues[ 0] = + values[ 5]*b5 - values[ 6]*b4 + values[ 7]*b3;
		retvalues[ 4] = - values[ 4]*b5 + values[ 6]*b2 - values[ 7]*b1;
		retvalues[ 8] = + values[ 4]*b4 - values[ 5]*b2 + values[ 7]*b0;
		retvalues[12] = - values[ 4]*b3 + values[ 5]*b1 - values[ 6]*b0;
		retvalues[ 1] = - values[ 1]*b5 + values[ 2]*b4 - values[ 3]*b3;
		retvalues[ 5] = + values[ 0]*b5 - values[ 2]*b2 + values[ 3]*b1;
		retvalues[ 9] = - values[ 0]*b4 + values[ 1]*b2 - values[ 3]*b0;
		retvalues[13] = + values[ 0]*b3 - values[ 1]*b1 + values[ 2]*b0;
		retvalues[ 2] = + values[13]*a5 - values[14]*a4 + values[15]*a3;
		retvalues[ 6] = - values[12]*a5 + values[14]*a2 - values[15]*a1;
		retvalues[10] = + values[12]*a4 - values[13]*a2 + values[15]*a0;
		retvalues[14] = - values[12]*a3 + values[13]*a1 - values[14]*a0;
		retvalues[ 3] = - values[ 9]*a5 + values[10]*a4 - values[11]*a3;
		retvalues[ 7] = + values[ 8]*a5 - values[10]*a2 + values[11]*a1;
		retvalues[11] = - values[ 8]*a4 + values[ 9]*a2 - values[11]*a0;
		retvalues[15] = + values[ 8]*a3 - values[ 9]*a1 + values[10]*a0;

		const float invDet = 1.0f/det;
		for(int i = 0; i < 16; ++i)
		{
			retvalues[i] *= invDet;
		}
		return retval;
	}

	return cmatrix4x4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
}

/* inverts the matrix, and will return a reference to itself */
inline matrix4x4& matrix4x4::inverse() __MST_GPU
{
	*this = inversed();
	return *this;
}

/* only rotates the matrix by mat */
inline void matrix4x4::rotate(const matrix4x4& mat) __MST_GPU
{
	float newcells[3][3] = {};
	for(int x = 0; x < 3; ++x) for(int i = 0; i < 3; ++i) for(int y = 0; y < 3; ++y)
	{
		newcells[x][y] += mat[x][i] * cell[i][y];
	}
	set_orientation(newcells);
}

/* returns a copy of itself that is only rotated by mat */
inline matrix4x4 matrix4x4::rotated(const matrix4x4& mat) const __MST_GPU
{
	matrix4x4 rot_mat(*this);
	rot_mat.rotate(mat);
	return rot_mat;
}

/* only rotates the matrix by mat */
inline void matrix4x4::rotate(const matrix3x3& mat) __MST_GPU
{
	float newcells[3][3] = {};
	for(int x = 0; x < 3; ++x) for(int i = 0; i < 3; ++i) for(int y = 0; y < 3; ++y)
	{
		newcells[x][y] += mat[x][i] * cell[i][y];
	}
	set_orientation(newcells);
}

/* returns a copy of itself that is only rotated by mat */
inline matrix4x4 matrix4x4::rotated(const matrix3x3& mat) const __MST_GPU
{
	matrix4x4 rot_mat(*this);
	rot_mat.rotate(mat);
	return rot_mat;
}

// operator overloads

inline matrix4x4& matrix4x4::operator =(const matrix3x3& mat) __MST_GPU
{
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		cell[i][j] = mat[i][j];
	}
	return *this;
}

inline matrix4x4& matrix4x4::operator *= (const matrix4x4& mat) __MST_GPU
{
	float newcells[4][4] = {};

	for(int x = 0; x < 4; ++x) for(int i = 0; i < 4; ++i) for(int y = 0; y < 4; ++y) 
	{
		newcells[x][y] += mat[x][i] * cell[i][y];
	}

	set(newcells);
	return *this;
}

inline matrix4x4& matrix4x4::operator *= (const matrix3x3& mat) __MST_GPU
{
	float newcells[3][3] = {};

	for(int x = 0; x < 3; ++x) for(int i = 0; i < 3; ++i) for(int y = 0; y < 3; ++y) 
	{
		newcells[x][y] += mat[x][i] * cell[i][y];
	}

	set_orientation(newcells);

	return *this;
}

inline matrix4x4& matrix4x4::operator *= (float val) __MST_GPU
{
	for(int x = 0; x < 4; ++x) for(int y = 0; y < 4; ++y)
	{
		cell[x][y] *= val;
	}

	return *this;
}

inline matrix4x4& matrix4x4::operator += (const matrix4x4& mat) __MST_GPU
{
	for(int x = 0; x < 4; ++x) for(int y = 0; y < 4; ++y)
	{
		cell[x][y] += mat.cell[x][y];
	}

	return *this;
}

inline matrix4x4& matrix4x4::operator -= (const matrix4x4& mat) __MST_GPU
{
	for(int x = 0; x < 4; ++x) for(int y = 0; y < 4; ++y)
	{
		cell[x][y] -= mat.cell[x][y];
	}

	return *this;
}

inline matrix4x4 (::mst::math::operator * )(const matrix4x4& mat1, const matrix4x4& mat2) __MST_GPU
{
	matrix4x4 newmat = {};

	for(int x = 0; x < 4; ++x) for(int i = 0; i < 4; ++i) for(int y = 0; y < 4; ++y)
	{
		newmat[x][y] += mat1[i][y] * mat2[x][i];
	}

	return newmat;
}

inline matrix4x4 (::mst::math::operator * )(const matrix4x4& mat, float val) __MST_GPU
{
	matrix4x4 newmat;
	for(int x = 0; x < 4; ++x) for(int y = 0; y < 4; ++y)
	{
		newmat[x][y] = mat[x][y] * val;
	}

	return newmat;
}
	
inline float3 (::mst::math::operator * )(const matrix4x4& mat, const float3& vec) __MST_GPU
{
	float3 ret_vec = { 0,0,0 };
	for(int i = 0; i < 3; ++i) for(int y = 0; y < 3; ++y)
	{
		ret_vec.axis[y] += mat[i][y] * vec.axis[i];
	}
	for(int i = 0; i < 3; ++i)
	{
		ret_vec.axis[i] += mat[3][i];
	}
	return ret_vec;
}

inline float4 (::mst::math::operator * )(const matrix4x4& mat, const float4& vec) __MST_GPU
{
	float4 ret_vec = { 0, 0, 0, 0 };
	for(int i = 0; i < 4; ++i) for(int y = 0; y < 4; ++y)
	{
		ret_vec.axis[y] += mat[i][y] * vec.axis[i];
	}
	return ret_vec;
}

inline matrix4x4 (::mst::math::operator +)(const matrix4x4& mat1, const matrix4x4& mat2) __MST_GPU
{
	matrix4x4 retval;

	for(int x = 0; x < 4; ++x) for(int y = 0; y < 4; ++y)
	{
		retval[x][y] = mat1[x][y] + mat2[x][y];
	}
}

inline matrix4x4 (::mst::math::operator -)(const matrix4x4& mat1, const matrix4x4& mat2) __MST_GPU
{
	matrix4x4 retval;

	for(int x = 0; x < 4; ++x) for(int y = 0; y < 4; ++y)
	{
		retval[x][y] = mat1[x][y] - mat2[x][y];
	}
}

inline _Details::_float_array_4 matrix4x4::operator [] (size_t n) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 4, "index out of bounds");
	return cell[n];
}
inline _Details::_const_float_array_4 matrix4x4::operator [] (size_t n) const __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 4, "index out of bounds");
	return cell[n];
}

#endif // __INSIDE_MMATH_H__