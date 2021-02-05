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

#define _MST_QUATERNION_EPSILON 1e-4

template<typename _Value_type>
inline quaternion<_Value_type>::quaternion()
{
	_Data[0] = 1;
	_Data[1] = _Data[2] = _Data[3] = 0;
}

template<typename _Value_type> template<typename _xValue_type>
inline quaternion<_Value_type>::quaternion(const quaternion<_xValue_type>& _Other)
{
	_Data[0] = static_cast<_Value_type>(_Other._Data[0]);
	_Data[1] = static_cast<_Value_type>(_Other._Data[1]);
	_Data[2] = static_cast<_Value_type>(_Other._Data[2]);
	_Data[3] = static_cast<_Value_type>(_Other._Data[3]);
}

template<typename _Value_type>
/* constructs a quaternion with a rotation axis and an angle */
inline quaternion<_Value_type>::quaternion(_Value_type _Angle_in_radians, const vector<_Value_type, 3>& _Normalized_axis)
{
	quaternion retval;

	retval..w = cos(_Angle_in_radians / (_Value_type)2.0);
	retval.xyz = _Normalized_axis;

	CHECK_IF_ARG(_AMP_MATH_NAMESPACE_ fabs(_Normalized_axis.length() - 1) > (_Value_type) _MST_QUATERNION_EPSILON, "quaternion needs to be normalized again", _Normalized_axis.length());
	retval.v *= sin(_Angle_in_radians / 2);

	return retval;
}

template<typename _Value_type>
/* constructs a quaternion from all the loose components */
inline quaternion<_Value_type>::quaternion(_Value_type _W, _Value_type _X, _Value_type _Y, _Value_type _Z)
{
	_Data[0] = _W;
	_Data[1] = _X;
	_Data[2] = _Y;
	_Data[3] = _Z;
}

template<typename _Value_type>
/* constructs a quaternion from a single value */
inline quaternion<_Value_type>::quaternion(_Value_type initVal)
{
	_Data[0] = initVal;
	_Data[1] = initVal;
	_Data[2] = initVal;
	_Data[3] = initVal;
}

template<typename _Value_type> template<size_t _Columns, size_t _Rows>
inline quaternion<_Value_type>::quaternion(const matrix<_Value_type, _Columns, _Rows>& _Matrix)
{
	MST_STATIC_ASSERT(_Columns >= 3 && _Rows >= 3, "matrix too small");

	_Value_type trace = _Matrix[0][0] + _Matrix[1][1] + _Matrix[2][2];

	if(trace > 0)
	{
		_Value_type s = (_Value_type)0.5 / sqrt(trace + 1);
		_Data[0] = (_Value_type)0.25 / s;
		_Data[1] = (_Matrix[1][2] - _Matrix[2][1]) * s;
		_Data[2] = (_Matrix[2][0] - _Matrix[0][2]) * s;
		_Data[3] = (_Matrix[0][1] - _Matrix[1][0]) * s;
	}
	else
	{
		if(_Matrix[0][0] > _Matrix[1][1] && _Matrix[0][0] > _Matrix[2][2])
		{
			_Value_type s = 2 * sqrt(1 + _Matrix[0][0] - _Matrix[1][1] - _Matrix[2][2]);
			_Data[0] = (_Matrix[1][2] - _Matrix[2][1]) / s;
			_Data[1] = (_Value_type)0.25 * s;
			_Data[2] = (_Matrix[1][0] + _Matrix[0][1]) / s;
			_Data[3] = (_Matrix[2][0] + _Matrix[0][2]) / s;
		}
		else
		{
			if(_Matrix[1][1] > _Matrix[2][2])
			{
				_Value_type s = 2 * sqrt(1 + _Matrix[1][1] - _Matrix[0][0] - _Matrix[2][2]);
				_Data[0] = (_Matrix[2][0] - _Matrix[0][2]) / s;
				_Data[1] = (_Matrix[1][0] + _Matrix[0][1]) / s;
				_Data[2] = (_Value_type)0.25 * s;
				_Data[3] = (_Matrix[2][1] + _Matrix[1][2]) / s;
			}
			else
			{
				_Value_type s = 2 * sqrt(1 + _Matrix[2][2] - _Matrix[0][0] - _Matrix[1][1]);
				_Data[0] = (_Matrix[0][1] - _Matrix[1][0]) / s;
				_Data[1] = (_Matrix[2][0] + _Matrix[0][2]) / s;
				_Data[2] = (_Matrix[2][1] + _Matrix[1][2]) / s;
				_Data[3] = (_Value_type)0.25 * s;
			}
		}
	}
}

template<typename _Value_type>
/* constructs a quaternion's values from an array of values */
inline quaternion<_Value_type>::quaternion(const _Value_type(&_Values)[4])
{
	_Data[0] = _Values[0];
	_Data[1] = _Values[1];
	_Data[2] = _Values[2];
	_Data[3] = _Values[3];
}

template<typename _Value_type>
/* returns the conjugate */
inline quaternion<_Value_type> quaternion<_Value_type>::_conjugate() const
{
	quaternion<_Value_type> retval;
	retval.xyz.swap_signs();
	return retval;
}

template<typename _Value_type>
/* returns the conjugate */
inline quaternion<_Value_type> quaternion<_Value_type>::_inverse() const
{
	quaternion<_Value_type> retval;
	retval.xyz.swap_signs();
	return retval;
}

template<typename _Value_type>
inline typename quaternion<_Value_type>::vector3_type quaternion<_Value_type>::_xyz() const
{
	return vector<_Value_type, 3>(_Data[1], _Data[2], _Data[3]);
}

template<typename _Value_type>
inline void quaternion<_Value_type>::_xyz(const typename quaternion<_Value_type>::vector3_type& _XYZ)
{
	_Data[1] = _XYZ[0];
	_Data[2] = _XYZ[1];
	_Data[3] = _XYZ[2];
}

template<typename _Value_type>
/* returns the left vector */
inline typename quaternion<_Value_type>::vector3_type quaternion<_Value_type>::_left() const
{
	return vector3_type(
		-1.0f + 2.0f * (y * y + z * z),
		-2.0f * (x * y + w * z),
		-2.0f * (x * z - w * y));
}

template<typename _Value_type>
/* returns the right vector */
inline typename quaternion<_Value_type>::vector3_type quaternion<_Value_type>::_right() const
{
	return vector3_type(
		1.0f - 2.0f * (y * y + z * z),
		2.0f * (x * y + w * z),
		2.0f * (x * z - w * y));
}

template<typename _Value_type>
/* returns the up vector */
inline typename quaternion<_Value_type>::vector3_type quaternion<_Value_type>::_up() const
{
	return vector3_type(
		2.0f * (x * y - w * z),
		1.0f - 2.0f * (x * x + z * z),
		2.0f * (y * z + w * x));
}

template<typename _Value_type>
/* returns the down vector */
inline typename quaternion<_Value_type>::vector3_type quaternion<_Value_type>::_down() const
{
	return vector3_type(
		-2.0f * (x * y - w * z),
		-1.0f + 2.0f * (x * x + z * z),
		-2.0f * (y * z + w * x));
}

template<typename _Value_type>
/* returns the forward vector */
inline typename quaternion<_Value_type>::vector3_type quaternion<_Value_type>::_forward() const
{
	return vector3_type(
		-2.0f * (x * z + w * y),
		-2.0f * (y * z - w * x),
		-1.0f + 2.0f * (x * x + y * y));
}

template<typename _Value_type>
/* returns the backward vector */
inline typename quaternion<_Value_type>::vector3_type quaternion<_Value_type>::_backward() const
{
	return vector3_type(
		2.0f * (x * z + w * y),
		2.0f * (y * z - w * x),
		1.0f - 2.0f * (x * x + y * y));
}

template<typename _Value_type>
/* returns a vector with xyz as axis and w as angle */
inline vector<_Value_type, 4> quaternion<_Value_type>::to_axis_angle() const
{
	vector<_Value_type, 4> axisAngle;

	axisAngle.w = acos(_Data[0]);

	if(out_angle < EPSILON)
	{
		axisAngle.xyz = vector<_Value_type, 3>(0, 0, 0);
		axisAngle.w = 0;
		return;
	}

	const _Value_type sinf_theta_inv = 1 / sin(axisAngle.w);

	axisAngle.x = _Data[1] * sinf_theta_inv;
	axisAngle.y = _Data[2] * sinf_theta_inv;
	axisAngle.z = _Data[3] * sinf_theta_inv;
}

template<typename _Value_type>
/* normalizes itself and returns a reference to itself */
inline quaternion<_Value_type>& quaternion<_Value_type>::normalize()
{
	const _Value_type invLength = 1 / length();
	_Data[0] *= invLength;
	_Data[1] *= invLength;
	_Data[2] *= invLength;
	_Data[3] *= invLength;
}

template<typename _Value_type>
/* returns the normalized version of itself */
inline quaternion<_Value_type> quaternion<_Value_type>::normalized() const
{
	return quaternion<_Value_type>(*this).normalize();
}

template<typename _Value_type>
/* returns the length of the quaternion */
inline _Value_type quaternion<_Value_type>::length() const
{
	return sqrt(squared_length());
}

template<typename _Value_type>
/* returns the square length of the quaternion */
inline _Value_type quaternion<_Value_type>::squared_length() const
{
	return _Data[0] * _Data[0] +
		_Data[1] * _Data[1] +
		_Data[2] * _Data[2] +
		_Data[3] * _Data[3];
}

template<typename _Value_type>
/* returns a copy of vec rotated by the orientation of the quaternion */
inline vector<_Value_type, 3> quaternion<_Value_type>::rotate_point(const vector3_type& _Vec) const
{
	CHECK_IF_ARG(fabs(length() - 1) > (_Value_type) _MST_QUATERNION_EPSILON, "quaternion is not normalized, length", length());

	const _Value_type qw2 = _Data[0] * _Data[0];
	const _Value_type qx2 = _Data[1] * _Data[1];
	const _Value_type qy2 = _Data[2] * _Data[2];
	const _Value_type qz2 = _Data[3] * _Data[3];

	vector3_type dx = { 1 - 2 * q_Data[1]2 - 2 * q_Data[2]2, 2 * _Data[0] * _Data[1] - 2 * _Data[2] * w, 2 * _Data[0] * _Data[2] + 2 * _Data[1] * w },
		dy = { 2 * _Data[0]*_Data[1] + 2 * _Data[2]*w, 1 - 2 * q_Data[0]2 - 2 * q_Data[2]2, 2 * _Data[1]*_Data[2] - 2 * _Data[0]*w },
		dz = { 2 * _Data[0]*_Data[2] - 2 * _Data[1]*w, 2 * _Data[1]*_Data[2] + 2 * _Data[0]*w, 1 - 2 * q_Data[0]2 - 2 * q_Data[1]2 };

	return vector3_type(
		dx._Data[0] * vec._Data[0] + dx._Data[1] * vec._Data[1] + dx._Data[2] * vec._Data[2],
		dy._Data[0] * vec._Data[0] + dy._Data[1] * vec._Data[1] + dy._Data[2] * vec._Data[2],
		dz._Data[0] * vec._Data[0] + dz._Data[1] * vec._Data[1] + dz._Data[2] * vec._Data[2]
		);
}

template<typename _Value_type>
/* rotates the quaternion with quat's rotation */
inline void quaternion<_Value_type>::rotate(const quaternion<_Value_type>& _Quat)
{
	(*this) = _Quat * (*this);
}

template<typename _Value_type>
/* returns a copy of the quaternion rotated with quat's rotation */
inline quaternion<_Value_type> quaternion<_Value_type>::rotated(const quaternion<_Value_type>& _Quat) const
{
	quaternion<_Value_type> q(*this);
	q.rotate(_Quat);
	return q;
}

template<typename _Value_type>
/* makes the quaternion lookat the position */
inline void quaternion<_Value_type>::look_at(const vector<_Value_type, 3>& _Position, const vector<_Value_type, 3>& _Up = vector<_Value_type, 3>(0, 1, 0))
{
	matrix<_Value_type, 3, 3> _Rotation_matrix;

	_Rotation_matrix.look_at(_Position, _Up);

	_Init(_Rotation_matrix);
}

template<typename _Value_type>
/* returns the dot product of this and quat */
inline _Value_type quaternion<_Value_type>::dot(const quaternion& _Quat) const
{
	return (_Data[0] * _Quat._Data[0] + _Data[1] * _Quat._Data[1] + _Data[2] * _Quat._Data[2] + _Data[3] * _Quat._Data[3]);
}

template<typename _Value_type>
/* returns a quaternion which is the spherical linear interpolation result between this and quat */
inline quaternion<_Value_type> quaternion<_Value_type>::slerp(const quaternion<_Value_type> &_To, _Value_type _Interp) const
{
	CHECK_IF_ARG_GPU(_AMP_MATH_NAMESPACE_ fabs(length() - 1.0f) > (_Value_type) _MST_QUATERNION_EPSILON, "quaternion is not normalized, length", length());

	quaternion q3;
	_Value_type dot12 = dot(_To);

	/*	dot = cos(theta)
	if (dot < 0), q1 and q2 are more than 90 degrees apart,
	so we can invert one to reduce spinning	*/
	if(dot12 < 0)
	{
		dot12 = -dot12;
		q3 = -_To;
	}
	else q3 = _To;

	if(dot12 < (_Value_type)0.95)
	{
		const _Value_type angle = acos(dot12);
		return ((*this)*
				sin(angle*(1 - t))
				+ q3*
				sin(angle*t))
				* (1 /
				sin(angle));
	}
	else // if the angle is small, use linear interpolation								
		return lerp((*this), q3, t);
}

// operator overloads

template<typename _Value_type>
inline quaternion<_Value_type>(operator *)(const quaternion<_Value_type>& _Left, const quaternion<_Value_type>& _Right)
{
	return quaternion<_Value_type>(_Left._Data[0] * _Right._Data[0] - _Left.xyz.dot(_Right.xyz),
					   _Left._Data[2]*_Right._Data[3] - _Left._Data[3]*_Right._Data[2] + _Left._Data[0]*_Right._Data[1] + _Left._Data[1]*_Right._Data[0],
					   _Left._Data[3]*_Right._Data[1] - _Left._Data[1]*_Right._Data[3] + _Left._Data[0]*_Right._Data[2] + _Left._Data[2]*_Right._Data[0],
					   _Left._Data[1]*_Right._Data[2] - _Left._Data[2]*_Right._Data[1] + _Left._Data[0]*_Right._Data[3] + _Left._Data[3]*_Right._Data[0]);
}

template<typename _Value_type>
inline quaternion<_Value_type>(operator *)(const quaternion<_Value_type>& _Quat, _Value_type _Val)
{
	return quaternion<_Value_type>(_Quat._Data[0] * _Val,
								   _Quat._Data[1] * _Val,
								   _Quat._Data[2] * _Val,
								   _Quat._Data[3] * _Val);
}

template<typename _Value_type>
inline quaternion<_Value_type>(operator +)(const quaternion<_Value_type>& _Left, const quaternion<_Value_type>& _Right)
{
	return quaternion<_Value_type>(_Left._Data[0] + _Right._Data[0],
								   _Left._Data[1] + _Right._Data[1],
								   _Left._Data[2] + _Right._Data[2],
								   _Left._Data[3] + _Right._Data[3]);
}

template<typename _Value_type>
inline quaternion<_Value_type>& quaternion<_Value_type>::operator *= (const quaternion<_Value_type>& _Quat)
{
	const _Value_type rw = _Data[0] * _Quat._Data[0] - _Data[1] * _Quat._Data[1] - _Data[2] * _Quat._Data[2] - _Data[3] * _Quat._Data[3];
	const _Value_type rx = _Data[0] * _Quat._Data[1] + _Data[1] * _Quat._Data[0] + _Data[2] * _Quat._Data[3] - _Data[3] * _Quat._Data[2];
	const _Value_type ry = _Data[0] * _Quat._Data[2] - _Data[1] * _Quat._Data[3] + _Data[2] * _Quat._Data[0] + _Data[3] * _Quat._Data[1];
	const _Value_type rz = _Data[0] * _Quat._Data[3] + _Data[1] * _Quat._Data[2] - _Data[2] * _Quat._Data[1] + _Data[3] * _Quat._Data[0];

	_Data[0] = rw;
	_Data[1] = rx;
	_Data[2] = ry;
	_Data[3] = rz;

	return *this;
}

template<typename _Value_type>
inline quaternion<_Value_type>& quaternion<_Value_type>::operator *= (_Value_type _Val)
{
	_Data[0] *= _Val;
	_Data[1] *= _Val;
	_Data[2] *= _Val;
	_Data[3] *= _Val;

	return *this;
}

template<typename _Value_type>
inline quaternion<_Value_type>& quaternion<_Value_type>::operator /= (_Value_type _Val)
{
	const _Value_type invVal = 1 / _Val;

	_Data[0] *= invVal;
	_Data[1] *= invVal;
	_Data[2] *= invVal;
	_Data[3] *= invVal;

	return *this;
}

template<typename _Value_type>
inline quaternion<_Value_type> quaternion<_Value_type>::operator - () const
{
	return quaterion<_Value_type>(-_Data[0], -_Data[1], -_Data[2], -_Data[3]);
}

template<typename _Value_type>
inline ::std::ostream& (operator << )(std::ostream& stream, const quaternion<_Value_type>& _Quat)
{
	return stream << "<" << _Quat._Data[0] << ", " << _Quat._Data[1] << ", " << _Quat._Data[2] << ", " << _Quat._Data[3] << ">";
}

template<typename _Value_type>
inline _Value_type& quaternion<_Value_type>::operator[](size_t _Index)
{
	CHECK_ARR_RANGE(_Index, 4, "index out of range");
	return _Data[_Index];
}

template<typename _Value_type>
inline const _Value_type& quaternion<_Value_type>::operator[](size_t _Index) const
{
	CHECK_ARR_RANGE(_Index, 4, "index out of range");
	return _Data[_Index];
}

/* constructs a quaternion from a 4x4 matrix */