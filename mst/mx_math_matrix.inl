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

template<typename _Value_type, size_t _Columns> template<typename _xValue_type>
inline matrix<_Value_type, _Columns, 1>::matrix(const matrix<_xValue_type, _Columns, 1>& _Other)
{
	_Data[0] = vector<_Value_type, _Columns>(_Other._Data[0]);
}

template<typename _Value_type, size_t _Columns>
inline matrix<_Value_type, _Columns, 1>::matrix(_Value_type initVal)
{
	_Data[0] = vector<_Value_type, _Columns>(initVal);
}

template<typename _Value_type, size_t _Columns>
inline matrix<_Value_type, _Columns, 1>::matrix(const vector<_Value_type, _Columns>& _Row0)
{
	_Data[0] = _Row0;
}

template<typename _Value_type, size_t _Columns> template<typename _xValue_type>
inline matrix<_Value_type, _Columns, 2>::matrix(const matrix<_xValue_type, _Columns, 2>& _Other)
{
	_Data[0] = vector<_Value_type, _Columns>(_Other._Data[0]);
	_Data[1] = vector<_Value_type, _Columns>(_Other._Data[1]);
}

template<typename _Value_type, size_t _Columns>
inline matrix<_Value_type, _Columns, 2>::matrix(_Value_type initVal)
{
	_Data[0] = vector<_Value_type, _Columns>(initVal);
	_Data[1] = vector<_Value_type, _Columns>(initVal);
}

template<typename _Value_type, size_t _Columns>
inline matrix<_Value_type, _Columns, 2>::matrix(const vector<_Value_type, _Columns>& _Row0,
												const vector<_Value_type, _Columns>& _Row1)
{
	_Data[0] = _Row0;
	_Data[1] = _Row1;
}

template<typename _Value_type, size_t _Columns> template<typename _xValue_type>
inline matrix<_Value_type, _Columns, 3>::matrix(const matrix<_xValue_type, _Columns, 3>& _Other)
{
	_Data[0] = vector<_Value_type, _Columns>(_Other._Data[0]);
	_Data[1] = vector<_Value_type, _Columns>(_Other._Data[1]);
	_Data[2] = vector<_Value_type, _Columns>(_Other._Data[2]);
}

template<typename _Value_type, size_t _Columns>
inline matrix<_Value_type, _Columns, 3>::matrix(_Value_type initVal)
{
	_Data[0] = vector<_Value_type, _Columns>(initVal);
	_Data[1] = vector<_Value_type, _Columns>(initVal);
	_Data[2] = vector<_Value_type, _Columns>(initVal);
}

template<typename _Value_type, size_t _Columns>
inline matrix<_Value_type, _Columns, 3>::matrix(const vector<_Value_type, _Columns>& _Row0,
												const vector<_Value_type, _Columns>& _Row1,
												const vector<_Value_type, _Columns>& _Row2)
{
	_Data[0] = _Row0;
	_Data[1] = _Row1;
	_Data[2] = _Row2;
}

template<typename _Value_type, size_t _Columns> template<typename _xValue_type>
inline matrix<_Value_type, _Columns, 4>::matrix(const matrix<_xValue_type, _Columns, 4>& _Other)
{
	_Data[0] = vector<_Value_type, _Columns>(_Other._Data[0]);
	_Data[1] = vector<_Value_type, _Columns>(_Other._Data[1]);
	_Data[2] = vector<_Value_type, _Columns>(_Other._Data[2]);
	_Data[3] = vector<_Value_type, _Columns>(_Other._Data[3]);
}

template<typename _Value_type, size_t _Columns>
inline matrix<_Value_type, _Columns, 4>::matrix(_Value_type initVal)
{
	_Data[0] = vector<_Value_type, _Columns>(initVal);
	_Data[1] = vector<_Value_type, _Columns>(initVal);
	_Data[2] = vector<_Value_type, _Columns>(initVal);
	_Data[3] = vector<_Value_type, _Columns>(initVal);
}

template<typename _Value_type, size_t _Columns>
inline matrix<_Value_type, _Columns, 4>::matrix(const vector<_Value_type, _Columns>& _Row0,
												const vector<_Value_type, _Columns>& _Row1,
												const vector<_Value_type, _Columns>& _Row2,
												const vector<_Value_type, _Columns>& _Row3)
{
	_Data[0] = _Row0;
	_Data[1] = _Row1;
	_Data[2] = _Row2;
	_Data[3] = _Row3;
}

template<typename _Value_type> template<typename _xValue_type>
inline matrix<_Value_type, 4, 4>::matrix(const matrix<_xValue_type, 4, 4>& _Other)
{
	_Data[0] = vector<_Value_type, 4>(_Other._Data[0]);
	_Data[1] = vector<_Value_type, 4>(_Other._Data[1]);
	_Data[2] = vector<_Value_type, 4>(_Other._Data[2]);
	_Data[3] = vector<_Value_type, 4>(_Other._Data[3]);
}

template<typename _Value_type>
inline matrix<_Value_type, 4, 4>::matrix(const vector4_type& _Row0,
										 const vector4_type& _Row1,
										 const vector4_type& _Row2,
										 const vector4_type& _Row3)
{
	_Data[0] = _Row0;
	_Data[1] = _Row1;
	_Data[2] = _Row2;
	_Data[3] = _Row3;
}

template<typename _Value_type>
inline matrix<_Value_type, 4, 4>::matrix(const vector3_type& _Position)
{
	*this = identity;
	position = _Position;
}

template<typename _Value_type>
inline matrix<_Value_type, 4, 4>::matrix(const vector3_type& _Position, const quaternion<_Value_type>& _Orientation)
{
	_Data[3] = vector<_Value_type, 4>(0, 0, 0, 1);
	_position(_Position);
	set_orientation(_Orientation);
}

template<typename _Value_type>
inline void matrix<_Value_type, 4, 4>::set_orientation(const quaternion<_Value_type>& _Orientation)
{
	_Data[0][0] = 1 - 2 * (_Orientation.y * _Orientation.y + _Orientation.z * _Orientation.z);
	_Data[0][1] = 2 * (_Orientation.x * _Orientation.y - _Orientation.w * _Orientation.z);
	_Data[0][2] = 2 * (_Orientation.x * _Orientation.z + _Orientation.w * _Orientation.y);
	_Data[1][0] = 2 * (_Orientation.x * _Orientation.y + _Orientation.w * _Orientation.z);
	_Data[1][1] = 1 - 2 * (_Orientation.x * _Orientation.x + _Orientation.z * _Orientation.z);
	_Data[1][2] = 2 * (_Orientation.y * _Orientation.z - _Orientation.w * _Orientation.x);
	_Data[2][0] = 2 * (_Orientation.x * _Orientation.z - _Orientation.w * _Orientation.y);
	_Data[2][1] = 2 * (_Orientation.y * _Orientation.z + _Orientation.w * _Orientation.x);
	_Data[2][2] = 1 - 2 * (_Orientation.x * _Orientation.x + _Orientation.y * _Orientation.y);
}

template<typename _Value_type>
inline matrix<_Value_type, 4, 4> matrix<_Value_type, 4, 4>::create_projection(const clip_space<_Value_type>& _Clipspace, const radians<_Value_type>& _Fov, _Value_type width, _Value_type height, _Value_type _NearDepth, _Value_type _FarDepth)
{
	return create_projection(_Clipspace, _Fov, width / height, _NearDepth, _FarDepth);
}

template<typename _Value_type>
inline matrix<_Value_type, 4, 4> matrix<_Value_type, 4, 4>::create_projection(const clip_space<_Value_type>& _Clipspace, const radians<_Value_type>& _Fov, _Value_type _Aspect, _Value_type _NearDepth, _Value_type _FarDepth)
{
	long double sine, cotangent, deltaZ;
	long double radians = (_Fov / 2).count();
	long double aspect = _Aspect;

	deltaZ = _FarDepth - _NearDepth;
	sine = sin(radians);
	cotangent = cos(radians) / sine;

	matrix<_Value_type, 4, 4> retval = matrix<_Value_type, 4, 4>::zero;

	/* First row */
	retval[0].x = (_Value_type)(cotangent / aspect);

	/* Second row */
	retval[1].y = (_Value_type)cotangent;

	/* Third row */
	retval[2].z = (_Value_type)((_FarDepth) / deltaZ);
	retval[2].w = (_Value_type)(-_NearDepth * _FarDepth / deltaZ);

	/* Fourth row */
	retval[3].z = (_Value_type)1;

	return retval;
}

template<typename _Value_type, size_t _Columns, size_t _Rows, bool _Is_square>
inline const _Value_type* _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, _Is_square>::data() const
{
	return _Data[0].data();
}

template<typename _Value_type, size_t _Columns, size_t _Rows, bool _Is_square>
inline _Value_type* _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, _Is_square>::data()
{
	return _Data[0].data();
}

template<typename _Value_type, size_t _Columns, size_t _Rows, bool _Is_square>
inline vector<_Value_type, _Columns>& _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, _Is_square>::operator[](size_t _Idx)
{
	CHECK_ARR_RANGE(_Idx, _Rows, "index out of range");
	return _Data[_Idx];
}

template<typename _Value_type, size_t _Columns, size_t _Rows, bool _Is_square>
inline const vector<_Value_type, _Columns>& _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, _Is_square>::operator[](size_t _Idx) const
{
	CHECK_ARR_RANGE(_Idx, _Rows, "index out of range");
	return _Data[_Idx];
}

template<typename _Value_type, size_t _Columns, size_t _Rows, bool _Is_square>
inline typename matrix<_Value_type, _Rows, _Columns> _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, _Is_square>::_transpose() const
{
	matrix<_Value_type, _Rows, _Columns> retval;
	for(size_t i = 0; i < _Rows; ++i) for(size_t j = 0; j < _Columns; ++j)
	{
		retval[j][i] = _Data[i][j];
	}
	return retval;
}

template<typename _Value_type, size_t _Columns, size_t _Rows, bool _Is_square>
inline vector<_Value_type, _Rows> _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, _Is_square>::_columns(size_t _Index) const
{
	column_type retval;

	for(size_t i = 0; i < _Rows; ++i)
	{
		retval[i] = _Data[i][_Index];
	}

	return retval;
}

template<typename _Value_type, size_t _Columns, size_t _Rows, bool _Is_square>
inline void _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, _Is_square>::_columns(size_t _Index, const vector<_Value_type, _Rows>& _Column)
{
	for(size_t i = 0; i < _Rows; ++i)
	{
		_Data[i][_Index] = _Column[i];
	}
}

template<typename _Value_type, size_t _Columns, size_t _Rows>
inline matrix<_Value_type, _Columns - 1, _Rows - 1> _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, true>::get_minor(size_t _Column, size_t _Row) const
{
	// indicate which col and row is being copied to dest
	size_t colCount=0,rowCount=0;

	size_t order = _Columns;

	matrix<_Value_type, _Columns - 1, _Rows - 1> retval;
 
	for(size_t i = 0; i < order; i++ )
	{
		if( i != _Row )
		{
			colCount = 0;
			for(size_t j = 0; j < order; j++ )
			{
				// when j is not the element
				if( j != _Column )
				{
					retval[rowCount][colCount] = _Data[i][j];
					colCount++;
				}
			}

			++rowCount;

		}
	}

	return retval;
}

template<typename _Value_type, size_t _Columns, size_t _Rows>
inline _Value_type _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, true>::_determinant() const
{
	// the determinant value
	_Value_type det = 0;

	size_t order = _Columns;
 
	// allocate the cofactor matrix
	matrix<_Value_type, _Columns - 1, _Columns - 1> minor;
 
	for(size_t i = 0; i < order; i++ )
	{
		// get minor of element (0,i)
		//GetMinor( mat, minor, 0, i );
		minor = get_minor(i,0);
		// the recusion is here!
 
		det += (i%2==1?-1:1) * _Data[0][i] * minor.determinant;
		//det += pow( -1.0, i ) * mat[0][i] * CalcDeterminant( minor,order-1 );
	}
 
	return det;
}

template<typename _Value_type>
inline _Value_type _Details::_Math_matrix_base<_Value_type, 1, 1, true>::_determinant() const
{
	return _Data[0][0];
}

template<typename _Value_type, size_t _Columns, size_t _Rows>
inline matrix<_Value_type, _Columns, _Rows> _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, true>::_inverse() const
{
	// get the determinant
	const _Value_type det = 1/determinant;

	const size_t order = _Columns;

	matrix<_Value_type, _Columns, _Rows> retval;
 
	matrix<_Value_type, _Columns - 1, _Rows - 1> minor;
 
	for(size_t j=0;j<order;j++)
	{
		for(size_t i=0;i<order;i++)
		{
			// get the co-factor (matrix) of A(j,i)
			minor = get_minor(i,j);
			retval[i][j] = det*minor.determinant;
			if( (i+j)%2 == 1)
				retval[i][j] = -retval[i][j];
		}
	}
 
	// release memory
	//delete [] minor[0];

	return retval;
}

template<typename _Value_type>
inline matrix<_Value_type, 1, 1> _Details::_Math_matrix_base<_Value_type, 1, 1, true>::_inverse() const
{
	return matrix<_Value_type, 1, 1>(1/_Data[0][0]);
}

template<typename _Value_type, size_t _RowsColumns, size_t _Rows>
inline vector<_Value_type, _Rows> operator * (
	const matrix<_Value_type, _RowsColumns, _Rows>& _Left,
	const vector<_Value_type, _RowsColumns>& _Right)
{
	vector<_Value_type, _Rows> retval = vector<_Value_type, _Rows>::zero;
	
	for(int x = 0; x < _Rows; ++x) for(int i = 0; i < _RowsColumns; ++i)
	{
		retval[x] += _Left[x][i] *
			_Right[i];
	}

	return retval;
}

template<typename _Value_type, size_t _Columns, size_t _RowsColumns, size_t _Rows>
inline matrix<_Value_type, _Columns, _Rows> operator * (
	const matrix<_Value_type, _Columns, _RowsColumns>& _Left,
	const matrix<_Value_type, _RowsColumns, _Rows>& _Right)
{
	matrix<_Value_type, _Columns, _Rows> retval = matrix<_Value_type, _Columns, _Rows>::zero;
	
	for(int x = 0; x < _Rows; ++x) for(int y = 0; y < _Columns; ++y) for(int i = 0; i < _RowsColumns; ++i)
	{
		retval[x][y] += _Left[i][y] * 
			_Right[x][i];
	}

	return retval;
}

template<typename _Value_type, size_t _Size>
inline matrix<_Value_type, _Size, _Size> operator * (
	const matrix<_Value_type, _Size, _Size>& _Left,
	const matrix<_Value_type, _Size, _Size>& _Right)
{
	//_Math_matrix_base<_Value_type, _Size, _Size> mat = matrix<_Value_type, _Size, _Size>::zero;
	matrix<_Value_type, _Size, _Size> retval = matrix<_Value_type, _Size, _Size>::zero;

	for(int x = 0; x < _Size; ++x) for(int i = 0; i < _Size; ++i) for(int y = 0; y < _Size; ++y)
	{
		retval[x][y] += _Left[i][y] * 
			_Right[x][i];
	}

	return retval;
}

namespace _Details {

template<typename _Value_type, size_t _Columns, size_t _Rows>
inline const matrix<_Value_type, _Columns, _Rows> _Make_zero_matrix()
{
	matrix<_Value_type, _Columns, _Rows> m;
	for(size_t i = 0; i < _Rows; ++i) for(size_t j = 0; j < _Columns; ++j)
	{
		m[i][j] = 0;
	}
	return m;
}

template<typename _Value_type, size_t _Columns, size_t _Rows>
inline const matrix<_Value_type, _Columns, _Rows> _Make_identity_matrix()
{
	matrix<_Value_type, _Columns, _Rows> m;
	for(size_t i = 0; i < _Rows; ++i) for(size_t j = 0; j < _Columns; ++j)
	{
		m[i][j] = 0;
	}
	for(size_t i = 0; i < _Rows; ++i)
	{
		m[i][i] = 1;
	}
	return m;
}

}; // namespace _Details

template<typename _Value_type, size_t _Columns, size_t _Rows, bool _Is_square>
const matrix<_Value_type, _Columns, _Rows> _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, _Is_square>::zero = 
	_Details::_Make_zero_matrix<_Value_type, _Columns, _Rows>();

template<typename _Value_type, size_t _Columns, size_t _Rows>
const matrix<_Value_type, _Columns, _Rows> _Details::_Math_matrix_base<_Value_type, _Columns, _Rows, true>::identity = 
	_Details::_Make_identity_matrix<_Value_type, _Columns, _Rows>();

template<typename _Value_type>
const matrix<_Value_type, 1, 1> _Details::_Math_matrix_base<_Value_type, 1, 1, true>::identity = 
	_Details::_Make_identity_matrix<_Value_type, 1, 1>();



template<typename _Value_type>
/* returns a copy of the matrix, that is rotated around the global x axis */
inline matrix<_Value_type,4,4> matrix<_Value_type,4,4>::rotated_x( _Value_type _Angle_in_radians ) const
{
	const float sx = sin( _Angle_in_radians );
	const float cx = cos( _Angle_in_radians );
	matrix<_Value_type,4,4> rot_mat = matrix<_Value_type,4,4>::identity;
	rot_mat[1].y = cx, rot_mat[2].y = sx, rot_mat[1].z = -sx, rot_mat[2].z = cx;
	return *this * rot_mat;
}

template<typename _Value_type>
/* returns a copy of the matrix, that is rotated around the global y axis */
inline matrix<_Value_type,4,4> matrix<_Value_type,4,4>::rotated_y( _Value_type _Angle_in_radians ) const
{
	const float sy = sin(_Angle_in_radians);
	const float cy = cos(_Angle_in_radians);
	matrix<_Value_type,4,4> rot_mat = matrix<_Value_type,4,4>::identity;
	rot_mat[0].x = cy, rot_mat[2].x = -sy, rot_mat[0].z = sy, rot_mat[2].z = cy;
	return *this * rot_mat;
}

template<typename _Value_type>
/* returns a copy of the matrix, that is rotated around the global z axis */
inline matrix<_Value_type,4,4> matrix<_Value_type,4,4>::rotated_z( _Value_type _Angle_in_radians ) const
{
	const float sz = sin(_Angle_in_radians);
	const float cz = cos(_Angle_in_radians);
	matrix<_Value_type,4,4> rot_mat = matrix<_Value_type,4,4>::identity;
	rot_mat[0].x = cz, rot_mat[1].x = sz, rot_mat[0].y = -sz, rot_mat[1].y = cz;
	return *this * rot_mat;
}

template<typename _Value_type>
inline typename ::mst::math::_Details::_Math_base<_Value_type>::vector3_type matrix<_Value_type, 4, 4>::_position() const
{
	return vector<_Value_type, 3>(_Data[0][3], _Data[1][3], _Data[2][3]);
}

template<typename _Value_type>
inline void matrix<_Value_type, 4, 4>::_position(const vector3_type& _Position)
{
	_Data[0][3] = _Position[0];
	_Data[1][3] = _Position[1];
	_Data[2][3] = _Position[2];
}

template<typename _Value_type>
inline void matrix<_Value_type, 4, 4>::scale(_Value_type _Scale)
{
	scale(vector3_type(_Scale, _Scale, _Scale));
}

template<typename _Value_type>
inline void matrix<_Value_type, 4, 4>::scale(const vector3_type& _Scale)
{
	matrix<_Value_type, 4, 4>(vector4_type(_Scale.x, 0, 0, 0),
							  vector4_type(0, _Scale.y, 0, 0),
							  vector4_type(0, 0, _Scale.z, 0),
							  vector4_type(0, 0, 0, 1)) * *this;
}