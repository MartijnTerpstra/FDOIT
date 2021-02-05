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

template<typename _Value_type, size_t _Columns, size_t _Rows>
class matrix;

namespace _Details {

template<typename _Value_type, size_t _Columns, size_t _Rows, bool _Is_square = (_Columns == _Rows)>
class _Math_matrix_base : protected _Details::_Math_base<_Value_type>
{
public:
	typedef _Value_type value_type;
	typedef vector<_Value_type, _Columns> row_type;
	typedef vector<_Value_type, _Rows> column_type;
	typedef matrix<_Value_type, _Rows, _Columns> transpose_type;

	static const size_t rowCount = _Rows;
	static const size_t columnCount = _Columns;

protected:
	MST_STATIC_ASSERT(std::is_arithmetic<_Value_type>::value &&
		std::is_signed<_Value_type>::value, "vector<_Value_type,_Columns,_Rows>: _Value_type must be of a signed arithmetic type");

	template<typename _Value_type, size_t _Columns, size_t _Rows>
	friend class matrix;

	typedef matrix<_Value_type, _Columns, _Rows> _Matrix_t;

	row_type _Data[_Rows];

public:

	/* 0 initialized matrix */
	static const matrix<_Value_type, _Columns, _Rows> zero;

	typedef _Value_type value_type;
	static const size_t dimensions = _Columns * _Rows;
	typedef typename ::std::is_unsigned<_Value_type> is_unsigned;

	declare_inline_get_property(transpose_type, transpose);

	declare_inline_property_array(row_type, rows);

	declare_inline_property_array(column_type, columns);
	//__declspec(property(get = _columns, put = _columns)) culumn_type columns[];
	//inline culumn_type _columns(size_t) const;
	//inline void _columns(size_t, const culumn_type&);

	inline const _Value_type* data() const;
	inline _Value_type* data();

	inline vector<_Value_type, _Columns>& operator[](size_t _Idx);
	inline const vector<_Value_type, _Columns>& operator[](size_t _Idx) const;

	/* sets the values of the matrix */
	inline void set(const _Value_type (&_Values)[_Columns * _Rows]);

	/* sets the values of the matrix */
	inline void set(const _Value_type (&_Values)[_Columns][_Rows]) __MST_GPU;

	/* sets only a part of the matrix from _Matrix */
	template<size_t _xColumns, size_t _xRows>
	inline void set_part(const _Matrix_t& _Matrix, size_t _Column_count, size_t _Row_count, size_t _Column_offset = 0, size_t _Row_offset = 0) __MST_GPU;

	/* sets only a part of the matrix from _Matrix */
	template<size_t _xColumns, size_t _xRows>
	inline void set_part(const matrix<_Value_type, _xColumns, _xRows>& _Matrix, size_t _Column_offset = 0, size_t _Row_offset = 0) __MST_GPU;

	template<size_t _xColumns, size_t _xRows>
	/* sets only a part of the matrix from _Values */
	inline void set_part(const _Value_type (&_Values)[_xColumns][_xRows], size_t _Column_offset = 0, size_t _Row_offset = 0) __MST_GPU;
};

template<typename _Value_type, size_t _Columns, size_t _Rows>
class _Math_matrix_base<_Value_type, _Columns, _Rows, true> : public _Math_matrix_base<_Value_type, _Columns, _Rows, false>
{
public:

	/* identity matrix */
	static const matrix<_Value_type, _Columns, _Rows> identity;

	matrix<_Value_type, _Columns-1, _Rows-1> get_minor(size_t _Column, size_t _Row) const;

	declare_inline_get_property(_Matrix_t, inverse);

	declare_inline_get_property(_Value_type, determinant);
};

template<typename _Value_type>
class _Math_matrix_base<_Value_type, 1, 1, true> : public _Math_matrix_base<_Value_type, 1, 1, false>
{
private:

	typedef matrix<_Value_type, 1, 1> _Matrix_t;

public:

	/* identity matrix */
	static const matrix<_Value_type, 1,1> identity;

	declare_inline_get_property(_Matrix_t, inverse);

	declare_inline_get_property(_Value_type, determinant);
};

}; // namespace _Details

template<typename _Value_type, size_t _Columns, size_t _Rows>
class matrix : public _Details::_Math_matrix_base<_Value_type, _Columns, _Rows>
{
};

template<typename _Value_type, size_t _Columns>
class matrix<_Value_type, _Columns, 1> : public _Details::_Math_matrix_base<_Value_type, _Columns, 1>
{
public:
	matrix() _DEFAULT_MATH_CONSTRUCTOR
	template<typename _xValue_type>
	inline explicit matrix(const matrix<_xValue_type, _Columns, 1>& _Other);
	inline explicit matrix(_Value_type initVal);

	inline matrix(const vector<_Value_type, _Columns>& _Row0);
};

template<typename _Value_type, size_t _Columns>
class matrix<_Value_type, _Columns, 2>: public _Details::_Math_matrix_base<_Value_type, _Columns, 2>
{
public:
	matrix() _DEFAULT_MATH_CONSTRUCTOR

	template<typename _xValue_type>
	inline explicit matrix(const matrix<_xValue_type, _Columns, 2>& _Other);
	inline explicit matrix(_Value_type initVal);

	inline matrix(const vector<_Value_type, _Columns>& _Row0,
				  const vector<_Value_type, _Columns>& _Row1);
};

template<typename _Value_type, size_t _Columns>
class matrix<_Value_type, _Columns, 3> : public _Details::_Math_matrix_base<_Value_type, _Columns, 3>
{
public:
	matrix() _DEFAULT_MATH_CONSTRUCTOR

	template<typename _xValue_type>
	inline explicit matrix(const matrix<_xValue_type, _Columns, 3>& _Other);
	inline explicit matrix(_Value_type initVal);

	inline matrix(const vector<_Value_type, _Columns>& _Row0,
				  const vector<_Value_type, _Columns>& _Row1,
				  const vector<_Value_type, _Columns>& _Row2);
};

template<typename _Value_type, size_t _Columns>
class matrix<_Value_type, _Columns, 4> : public _Details::_Math_matrix_base<_Value_type, _Columns, 4>
{
public:
	matrix() _DEFAULT_MATH_CONSTRUCTOR

	template<typename _xValue_type>
	inline explicit matrix(const matrix<_xValue_type, _Columns, 4>& _Other);
	inline explicit matrix(_Value_type initVal);

	inline matrix(const vector<_Value_type, _Columns>& _Row0,
				  const vector<_Value_type, _Columns>& _Row1,
				  const vector<_Value_type, _Columns>& _Row2,
				  const vector<_Value_type, _Columns>& _Row3);
};

template<typename _Value_type>
class matrix<_Value_type, 4, 4> : public _Details::_Math_matrix_base<_Value_type, 4, 4>
{
public:
	matrix() _DEFAULT_MATH_CONSTRUCTOR

	template<typename _xValue_type>
	inline explicit matrix(const matrix<_xValue_type, 4, 4>& _Other);
	inline explicit matrix(_Value_type initVal);

	inline matrix(const vector4_type& _Row0,
				  const vector4_type& _Row1,
				  const vector4_type& _Row2,
				  const vector4_type& _Row3);

	inline matrix(const vector3_type& _Position);

	inline matrix(const vector3_type& _Position, const quaternion<_Value_type>& _Orientation);

	inline void set_orientation(const quaternion<_Value_type>& _Orientation);

	inline static matrix create_projection(const clip_space<_Value_type>& _Clipspace, const radians<_Value_type>& _Fov, _Value_type width, _Value_type height, _Value_type _NearDepth, _Value_type _FarDepth);

	inline static matrix create_projection(const clip_space<_Value_type>& _Clipspace, const radians<_Value_type>& _Fov, _Value_type _Aspect, _Value_type _NearDepth, _Value_type _FarDepth);

	/* the position of the matrix */
	declare_inline_property(vector3_type, position);

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
	
	inline matrix rotated_x(_Value_type _Angle_in_radians) const;
	inline matrix rotated_y(_Value_type _Angle_in_radians) const;
	inline matrix rotated_z(_Value_type _Angle_in_radians) const;

	inline void scale(_Value_type _Scale);

	inline void scale(const vector3_type& _Scale);
};