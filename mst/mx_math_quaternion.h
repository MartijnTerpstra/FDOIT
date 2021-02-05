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


#define _mst_declare_value(_Name, _Idx) \
inline _Value_type _get_##_Name() const { return _Data[_Idx]; } \
inline void _set_##_Name(_Value_type _Val) { _Data[_Idx] = _Val; } \
_Value_type __declspec(property(put=_set_##_Name,get=_get_##_Name)) _Name

template<typename _Value_type>
class quaternion : private _Details::_Math_base<_Value_type>
{
public:
	MST_STATIC_ASSERT(std::is_floating_point<_Value_type>::value &&
		std::is_signed<_Value_type>::value, "vector<_Value_type,_Columns,_Rows>: _Value_type must be of a signed floating point type");

	static const size_t dimensions = 4;
	typedef _Value_type value_type;
	typedef typename ::std::is_unsigned<_Value_type> is_unsigned;

	inline quaternion();

	template<typename _Value_type2>
	inline explicit quaternion(const quaternion<_Value_type2>& _Other);

	/* constructs a quaternion with a rotation axis and an angle */
	inline quaternion(_Value_type _Angle_in_radians, const vector<_Value_type, 3>& _Normalized_axis);

	/* constructs a quaternion from all the loose components */
	inline quaternion(_Value_type _W, _Value_type _X, _Value_type _Y, _Value_type _Z);

	/* constructs a quaternion from a single value */
	inline explicit quaternion(_Value_type initValue);

	template<size_t _Columns, size_t _Rows>
	/* constructs a quaternion from a 4x4 matrix */
	explicit inline quaternion(const matrix<_Value_type, _Columns, _Rows>& _Matrix);

	/* constructs a quaternion's values from an array of values */
	inline quaternion(const _Value_type (&_Values)[4]);

	/* returns the conjugate */
	declare_inline_get_property(quaternion, conjugate);

	/* returns the inverse */
	declare_inline_get_property(quaternion, inverse);

	/* returns the left vector */
	declare_inline_get_property(vector3_type, left);

	/* returns the right vector */
	declare_inline_get_property(vector3_type, right);

	/* returns the up vector */
	declare_inline_get_property(vector3_type, up);

	/* returns the down vector */
	declare_inline_get_property(vector3_type, down);

	/* returns the forward vector */
	declare_inline_get_property(vector3_type, forward);

	/* returns the backward vector */
	declare_inline_get_property(vector3_type, backward);

	/* returns a vector with xyz as axis and w as angle */
	inline vector<_Value_type, 4> to_axis_angle() const;

	/* normalizes itself and returns a reference to itself */
	inline quaternion& normalize();

	/* returns the normalized version of itself */
	inline quaternion normalized() const;

	/* returns the length of the quaternion */
	inline _Value_type length() const;

	/* returns the square length of the quaternion */
	inline _Value_type squared_length() const;

	/* returns a copy of vec rotated by the orientation of the quaternion */
	inline vector<_Value_type, 3> rotate_point(const vector<_Value_type, 3>& _Vec) const;

	/* rotates the quaternion with quat's rotation */
	inline void rotate(const quaternion& _Quat);

	/* returns a copy of the quaternion rotated with quat's rotation */
	inline quaternion rotated(const quaternion& _Quat) const;

	/* makes the quaternion lookat the position */
	inline void look_at(const vector<_Value_type, 3>& _Position, const vector<_Value_type, 3>& _Up = vector<_Value_type, 3>(0,1,0));

	/* returns the dot product of this and quat */
	inline _Value_type dot(const quaternion& _Quat) const;

	/* returns a quaternion which is the spherical linear interpolation result between this and quat */
	inline quaternion slerp(const quaternion &_To, _Value_type _Interp) const;

	// operator overloads

	inline quaternion& operator *= (const quaternion& _Quat);
	inline quaternion& operator *= (_Value_type _Val);

	inline quaternion& operator /= (_Value_type _Val);

	inline quaternion operator - () const;

	inline _Value_type& operator[](size_t _Index);
	inline const _Value_type& operator[](size_t _Index) const;

	_mst_declare_value(w, 0);
	_mst_declare_value(x, 1);
	_mst_declare_value(y, 2);
	_mst_declare_value(z, 3);

	declare_inline_property(vector3_type, xyz);

	static const quaternion identity;

private:
	_Value_type _Data[4];

	template<typename _xValue_type>
	friend class quaternion;
};

#undef _mst_declare_value