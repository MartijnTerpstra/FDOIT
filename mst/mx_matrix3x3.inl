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

/* constructs the matrix from the values of the array */
matrix3x3 (::mst::math::cmatrix3x3)(const float (&values)[9]) __MST_GPU
{
	matrix3x3 retval;
	retval.set(values);
	return retval;
}

/* constructs the matrix from the values of the array */
matrix3x3 (::mst::math::cmatrix3x3)(const float (&values)[3][3]) __MST_GPU
{
	matrix3x3 retval;
	retval.set(values);
	return retval;
}

/* constructs the matrix from the values */
matrix3x3 (::mst::math::cmatrix3x3)(float val1x1, float val2x1, float val3x1,
			float val1x2, float val2x2, float val3x2,
			float val1x3, float val2x3, float val3x3) __MST_GPU
{
	matrix3x3 retval;
	retval.set(val1x1, val2x1, val3x1,
		val1x2, val2x2, val3x2,
		val1x3, val2x3, val3x3);
	return retval;
}

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 (::mst::math::cmatrix3x3)(float3 euler_rotations, euler_XYZ)
{
	return matrix3x3::identity_matrix.rotated_z(euler_rotations.z).rotated_y(euler_rotations.y).rotated_x(euler_rotations.x);
}

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 (::mst::math::cmatrix3x3)(float3 euler_rotations, euler_XZY)
{
	return matrix3x3::identity_matrix.rotated_y(euler_rotations.y).rotated_z(euler_rotations.z).rotated_x(euler_rotations.x);
}

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 (::mst::math::cmatrix3x3)(float3 euler_rotations, euler_YXZ)
{
	return matrix3x3::identity_matrix.rotated_z(euler_rotations.z).rotated_x(euler_rotations.x).rotated_y(euler_rotations.y);
}

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 (::mst::math::cmatrix3x3)(float3 euler_rotations, euler_YZX)
{
	return matrix3x3::identity_matrix.rotated_x(euler_rotations.x).rotated_y(euler_rotations.y).rotated_z(euler_rotations.z);
}

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 cmatrix3x3(float3 euler_rotations, euler_ZXY)
{
	return matrix3x3::identity_matrix.rotated_y(euler_rotations.y).rotated_x(euler_rotations.x).rotated_z(euler_rotations.z);
}

/* constructs matrix with euler angles in XYZ order */
inline matrix3x3 cmatrix3x3(float3 euler_rotations, euler_ZYX)
{
	return matrix3x3::identity_matrix.rotated_x(euler_rotations.x).rotated_y(euler_rotations.y).rotated_z(euler_rotations.z);
}

/* constructs the matrix from a quaternion*/
matrix3x3 (::mst::math::cmatrix3x3)(const quaternion& quat) __MST_GPU
{
	matrix3x3 retval;
	retval.set(quat);
	return retval;
}

/* construct the matrix for the orientation part of a 4x4 matrix */
inline matrix3x3 (::mst::math::cmatrix3x3)(const matrix4x4& matrix) __MST_GPU
{
	matrix3x3 retval;
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		retval[i][j] = matrix[i][j];
	}
	return retval;
}

/* turns the matrix into a identity matrix */
inline void matrix3x3::set_identity() __MST_GPU
{
	set(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

/* sets the values of the matrix */
inline void matrix3x3::set(float val1x1, float val2x1, float val3x1,
		float val1x2, float val2x2, float val3x2,
		float val1x3, float val2x3, float val3x3) __MST_GPU
{
	cell[0][0] = val1x1;
	cell[0][1] = val2x1;
	cell[0][2] = val3x1;
	cell[1][0] = val1x2;
	cell[1][1] = val2x2;
	cell[1][2] = val3x2;
	cell[2][0] = val1x3;
	cell[2][1] = val2x3;
	cell[2][2] = val3x3;
}

/* sets the values of the matrix */
inline void matrix3x3::set(const float (&values)[9]) __MST_GPU
{
	int k = 0;
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		cell[i][j] = values[k];
		k++;
	}
}

/* sets the values of the matrix */
inline void matrix3x3::set(const float (&values)[3][3]) __MST_GPU
{
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		cell[i][j] = values[i][j];
	}
}

/* sets the values of the matrix */
inline void matrix3x3::set(const quaternion& quat)
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

/* sets the values of the matrix */
inline void matrix3x3::set(const quaternion& quat, float scale)
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

/* returns the matrix's x axis */
inline const float3& matrix3x3::get_x_axis() __MST_GPU
{
	return *((const float3*)cell[0]);
}

/* returns the matrix's y axis */
inline const float3& matrix3x3::get_y_axis() __MST_GPU
{
	return *((const float3*)cell[1]);
}

/* returns the matrix's z axis */
inline const float3& matrix3x3::get_z_axis() __MST_GPU
{
	return *((const float3*)cell[2]);
}

/* sets the x axis of the matrix */
inline void matrix3x3::set_x_axis(const float3& vec) __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[0][i] = vec.axis[i];
	}
}

/* sets the y axis of the matrix */
inline void matrix3x3::set_y_axis(const float3& vec) __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[1][i] = vec.axis[i];
	}
}

/* sets the z axis of the matrix */
inline void matrix3x3::set_z_axis(const float3& vec) __MST_GPU
{
	for(int i = 0; i < 3; ++i)
	{
		cell[2][i] = vec.axis[i];
	}
}

/* rotates the matrix around the global x axis */
inline void matrix3x3::rotate_x( float angle_in_radians ) __MST_GPU
{
	const float sx = _AMP_MATH_NAMESPACE_ sin(angle_in_radians);
	const float cx = _AMP_MATH_NAMESPACE_ cos(angle_in_radians);
	matrix3x3 rot_mat = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	rot_mat.cell[1][1] = cx, rot_mat.cell[1][2] = sx, rot_mat.cell[2][1] = -sx, rot_mat.cell[2][2] = cx;
	rotate(rot_mat);
}

/* returns a version of the matrix, rotated around the global x axis */
inline matrix3x3 matrix3x3::rotated_x( float angle_in_radians ) const __MST_GPU
{
	matrix3x3 retval(*this);
	retval.rotate_x(angle_in_radians);
	return retval;
}

/* rotates the matrix around the global y axis */
inline void matrix3x3::rotate_y( float angle_in_radians ) __MST_GPU
{
	const float sy = _AMP_MATH_NAMESPACE_ sin(angle_in_radians);
	const float cy = _AMP_MATH_NAMESPACE_ cos(angle_in_radians);
	matrix3x3 rot_mat = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	rot_mat.cell[0][0] = cy, rot_mat.cell[0][2] = -sy, rot_mat.cell[2][0] = sy, rot_mat.cell[2][2] = cy;
	rotate(rot_mat);
}

/* returns a version of the matrix, rotated around the global y axis */
inline matrix3x3 matrix3x3::rotated_y( float angle_in_radians ) const __MST_GPU
{
	matrix3x3 retval(*this);
	retval.rotate_y(angle_in_radians);
	return retval;
}

/* rotates the matrix around the global z axis */
inline void matrix3x3::rotate_z( float angle_in_radians ) __MST_GPU
{
	const float sz = _AMP_MATH_NAMESPACE_ sin(angle_in_radians);
	const float cz = _AMP_MATH_NAMESPACE_ cos(angle_in_radians);
	matrix3x3 rot_mat = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	rot_mat.cell[0][0] = cz, rot_mat.cell[0][1] = sz, rot_mat.cell[1][0] = -sz, rot_mat.cell[1][1] = cz;
	rotate(rot_mat);
}

/* returns a version of the matrix, rotated around the global z axis */
inline matrix3x3 matrix3x3::rotated_z( float angle_in_radians ) const __MST_GPU
{
	matrix3x3 retval(*this);
	retval.rotate_z(angle_in_radians);
	return retval;
}

/* transposes the matrix */
inline void matrix3x3::transpose() __MST_GPU
{
	std::swap(cell[0][1], cell[1][0]);
	std::swap(cell[0][2], cell[2][0]);
	std::swap(cell[2][1], cell[1][2]);
}

/* makes the matrix look at a target */
inline void matrix3x3::look_at(const float3& target, const float3& global_up) __MST_GPU
{
	const float3 direction = target.normalized();

	CHECK_IF_GPU(direction.distance(global_up.normalized()) < EPSILON, "bad up vector");

	const float3 right = direction.cross(global_up).normalize();
	const float3 local_up = right.cross(direction).normalize();

	set_x_axis(right);
	set_y_axis(local_up);
	set_z_axis(direction);
}

// operator overloads

inline float3 (::mst::math::operator * )(const matrix3x3& mat, const float3& vec) __MST_GPU
{
	float3 retval = { 0, 0, 0 };
	for(int y = 0; y < 3; ++y) for(int i = 0; i < 3; ++i)
	{
		retval.axis[y] += mat[i][y] * vec.axis[i];
	}
	return retval;
}

inline matrix3x3 (::mst::math::operator * )(const matrix3x3& mat1, const matrix3x3& mat2) __MST_GPU
{
	return mat1.rotated(mat2);
}

inline matrix3x3 (::mst::math::operator * )(const matrix3x3& mat, float value) __MST_GPU
{
	matrix3x3 retval;
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		retval[i][j] = mat[i][j] * value;
	}
	return retval;
}

inline matrix3x3& matrix3x3::operator *= (const matrix3x3& mat) __MST_GPU
{
	rotate(mat);
	return *this;
}

inline matrix3x3& matrix3x3::operator *= (float value) __MST_GPU
{
	for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
	{
		cell[i][j] *= value;
	}
	return *this;
}

/* rotates the matrix by mat */
inline void matrix3x3::rotate(const matrix3x3& mat) __MST_GPU
{
	*this = rotated(mat);
}

/* returns a copy of itself rotated by mat */
inline matrix3x3 matrix3x3::rotated(const matrix3x3& mat) const __MST_GPU
{
	matrix3x3 rot_mat = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		
	for(int x = 0; x < 3; ++x) for(int i = 0; i < 3; ++i) for(int y = 0; y < 3; ++y)
	{
		rot_mat[x][y] += cell[x][i] * mat[i][y];
	}

	return rot_mat;
}

inline _Details::_float_array_3 matrix3x3::operator [] (size_t n) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 3, "index out of bounds");
	return cell[n];
}
inline _Details::_const_float_array_3 matrix3x3::operator[](size_t n) const __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 3, "index out of bounds");
	return cell[n];
}

inline std::ostream& (::mst::math::operator << )(std::ostream& stream, const matrix3x3& value)
{
	stream << "< (" << value.cell[0][0] << ", " << value[1][0] << ", " << value[2][0] << ") , ";
	stream << "(" << value.cell[0][1] << ", " << value[1][1] << ", " << value[2][1] << ") , ";
	stream << "(" << value.cell[0][2] << ", " << value[1][2] << ", " << value[2][2] << ") >";
	return stream;
}

#endif // __INSIDE_MMATH_H__