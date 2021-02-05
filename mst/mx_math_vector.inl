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

template<typename _Value_type> template<typename _xValue_type>
inline vector<_Value_type, 1>::vector(const vector<_xValue_type, 1>& _Other)
{
	_Data[0] = static_cast<_Value_type>(_Other._Data[0]);
}

template<typename _Value_type>
inline vector<_Value_type, 1>::vector(_Value_type _X)
{
	_Data[0] = _X;
}

template<typename _Value_type> template<typename _xValue_type>
inline vector<_Value_type, 2>::vector(const vector<_xValue_type, 2>& _Other)
{
	_Data[0] = static_cast<_Value_type>(_Other._Data[0]);
	_Data[1] = static_cast<_Value_type>(_Other._Data[1]);
}

template<typename _Value_type>
inline vector<_Value_type, 2>::vector(_Value_type _X, _Value_type _Y)
{
	_Data[0] = _X;
	_Data[1] = _Y;
}

template<typename _Value_type>
inline vector<_Value_type, 2>::vector(_Value_type initVal)
{
	_Data[0] = initVal;
	_Data[1] = initVal;
}

template<typename _Value_type> template<typename _xValue_type>
inline vector<_Value_type, 3>::vector(const vector<_xValue_type, 3>& _Other)
{
	_Data[0] = static_cast<_Value_type>(_Other._Data[0]);
	_Data[1] = static_cast<_Value_type>(_Other._Data[1]);
	_Data[2] = static_cast<_Value_type>(_Other._Data[2]);
}

template<typename _Value_type>
inline vector<_Value_type, 3>::vector(_Value_type _X, _Value_type _Y, _Value_type _Z)
{
	_Data[0] = _X;
	_Data[1] = _Y;
	_Data[2] = _Z;
}

template<typename _Value_type>
inline vector<_Value_type, 3>::vector(const vector<_Value_type, 2>& _XY, _Value_type _Z)
{
	_Data[0] = _XY[0];
	_Data[1] = _XY[1];
	_Data[2] = _Z;
}

template<typename _Value_type>
inline vector<_Value_type, 3>::vector(_Value_type _X, const vector<_Value_type, 2>& _YZ)
{
	_Data[0] = _X;
	_Data[1] = _YZ[0];
	_Data[2] = _YZ[1];
}

template<typename _Value_type>
inline vector<_Value_type, 3>::vector(_Value_type initVal)
{
	_Data[0] = initVal;
	_Data[1] = initVal;
	_Data[2] = initVal;
}

template<typename _Value_type> template<typename _xValue_type>
inline vector<_Value_type, 4>::vector(const vector<_xValue_type, 4>& _Other)
{
	_Data[0] = static_cast<_Value_type>(_Other._Data[0]);
	_Data[1] = static_cast<_Value_type>(_Other._Data[1]);
	_Data[2] = static_cast<_Value_type>(_Other._Data[2]);
	_Data[3] = static_cast<_Value_type>(_Other._Data[3]);
}

template<typename _Value_type>
inline vector<_Value_type, 4>::vector(_Value_type _X, _Value_type _Y, _Value_type _Z, _Value_type _W)
{
	_Data[0] = _X;
	_Data[1] = _Y;
	_Data[2] = _Z;
	_Data[3] = _W;
}

template<typename _Value_type>
inline vector<_Value_type, 4>::vector(const vector<_Value_type, 2>& _XY, const vector<_Value_type, 2>& _ZW)
{
	_Data[0] = _XY[0];
	_Data[1] = _XY[1];
	_Data[2] = _ZW[0];
	_Data[3] = _ZW[1];
}

template<typename _Value_type>
inline vector<_Value_type, 4>::vector(const vector<_Value_type, 2>& _XY, _Value_type _Z, _Value_type _W)
{
	_Data[0] = _XY[0];
	_Data[1] = _XY[1];
	_Data[2] = _Z;
	_Data[3] = _W;
}

template<typename _Value_type>
inline vector<_Value_type, 4>::vector(_Value_type _X, const vector<_Value_type, 2>& _YZ, _Value_type _W)
{
	_Data[0] = _X;
	_Data[1] = _YZ[0];
	_Data[2] = _YZ[1];
	_Data[3] = _W;
}

template<typename _Value_type>
inline vector<_Value_type, 4>::vector(_Value_type _X, _Value_type _Y, const vector<_Value_type, 2>& _ZW)
{
	_Data[0] = _X;
	_Data[1] = _Y;
	_Data[2] = _ZW[0];
	_Data[3] = _ZW[1];
}

template<typename _Value_type>
inline vector<_Value_type, 4>::vector(const vector<_Value_type, 3>& _XYZ, _Value_type _W)
{
	_Data[0] = _XYZ[0];
	_Data[1] = _XYZ[1];
	_Data[2] = _XYZ[2];
	_Data[3] = _W;
}

template<typename _Value_type>
inline vector<_Value_type, 4>::vector(_Value_type _X, const vector<_Value_type, 3>& _YZW)
{
	_Data[0] = _X;
	_Data[1] = _YZW[0];
	_Data[2] = _YZW[1];
	_Data[3] = _YZW[2];
}

template<typename _Value_type>
inline vector<_Value_type, 4>::vector(_Value_type initVal)
{
	_Data[0] = initVal;
	_Data[1] = initVal;
	_Data[2] = initVal;
	_Data[3] = initVal;
}

template<typename _Value_type, size_t _Elems, bool _IsFP, bool _IsUnsigned>
inline const _Value_type* _Details::_Math_vector_base<_Value_type, _Elems, _IsFP, _IsUnsigned>::data() const
{
	return _Data;
}

template<typename _Value_type, size_t _Elems, bool _IsFP, bool _IsUnsigned>
inline _Value_type* _Details::_Math_vector_base<_Value_type, _Elems, _IsFP, _IsUnsigned>::data()
{
	return _Data;
}

template<typename _Value_type, size_t _Elems, bool _IsFP, bool _IsUnsigned>
inline _Value_type& _Details::_Math_vector_base<_Value_type, _Elems, _IsFP, _IsUnsigned>::operator[](size_t _Idx)
{
	CHECK_ARR_RANGE(_Idx, _Elems, "index out of range");
	return _Data[_Idx];
}

template<typename _Value_type, size_t _Elems, bool _IsFP, bool _IsUnsigned>
inline const _Value_type& _Details::_Math_vector_base<_Value_type, _Elems, _IsFP, _IsUnsigned>::operator[](size_t _Idx) const
{
	CHECK_ARR_RANGE(_Idx, _Elems, "index out of range");
	return _Data[_Idx];
}

/* returns the squared length */
template<typename _Value_type, size_t _Elems, bool _IsFP, bool _IsUnsigned>
inline _Value_type (_Details::_Math_vector_base<_Value_type, _Elems, _IsFP, _IsUnsigned>::squared_length)() const
{
	_Value_type retval = 0;
	for(size_t i = 0; i < _Elems; ++i)
	{
		retval += _Data[i] * _Data[i];
	}
	return retval;
}

/* returns the squared distance towards _Vec */
template<typename _Value_type, size_t _Elems, bool _IsFP, bool _IsUnsigned>
inline _Value_type _Details::_Math_vector_base<_Value_type, _Elems, _IsFP, _IsUnsigned>::squared_distance(const _Vector_t& _Vec) const
{
	_Value_type retval = 0;
	for(size_t i = 0; i < _Elems; ++i)
	{
		const _Value_type difference = _Vec._Data[i] - _Data[i];
		retval += difference * difference;
	}
	return retval;
}

/* returns the length */
template<typename _Value_type, size_t _Elems, bool _IsUnsigned>
inline _Value_type (_Details::_Math_vector_base<_Value_type, _Elems, true, _IsUnsigned>::length)() const
{
	return sqrt(squared_length());
}

/* returns the squared towards _Vec */
template<typename _Value_type, size_t _Elems, bool _IsUnsigned>
inline _Value_type _Details::_Math_vector_base<_Value_type, _Elems, true, _IsUnsigned>::distance(const _Vector_t& _Vec) const
{
	return sqrt(squared_distance(_Vec));
}

/* normalized and returns itself */
template<typename _Value_type, size_t _Elems, bool _IsUnsigned>
inline vector<_Value_type, _Elems>& _Details::_Math_vector_base<_Value_type, _Elems, true, _IsUnsigned>::normalize()
{
	const _Value_type invLength = 1 / length();
	for(size_t i = 0; i < _Elems; ++i)
	{
		_Data[i] *= invLength;
	}
	return static_cast<vector<_Value_type, _Elems>&>(*this);
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems> _Details::_Math_vector_base<_Value_type, _Elems, false, false>::operator -() const
{
	vector<_Value_type, _Elems> retval;
	for(size_t i = 0; i < _Elems; ++i)
	{
		retval[i] = -_Data[i];
	}

	return retval;
}

/* returns the dot product of the  */
template<typename _Value_type>
inline _Value_type vector<_Value_type, 3>::dot(const vector<_Value_type, 3>& _Other) const
{
	return _Data[0] * _Other._Data[0] + _Data[1] * _Other._Data[1] + _Data[2] * _Other._Data[2];
}

template<typename _Value_type>
inline vector<_Value_type, 3> vector<_Value_type, 3>::cross(const vector<_Value_type, 3>& _Other) const
{
	return vector<_Value_type, 3>( _Data[1] * _Other._Data[2] - _Data[2] * _Other._Data[1], _Data[2] * _Other._Data[0] - _Data[0] * _Other._Data[2], _Data[0] * _Other._Data[1] - _Data[1] * _Other._Data[0] );
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems>& operator += (vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	for(size_t i = 0; i < _Elems; ++i)
	{
		_Left[i] += _Right[i];
	}
	return _Left;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems>& operator -= (vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	for(size_t i = 0; i < _Elems; ++i)
	{
		_Left[i] -= _Right[i];
	}
	return _Left;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems>& operator *= (vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	for(size_t i = 0; i < _Elems; ++i)
	{
		_Left[i] *= _Right[i];
	}
	return _Left;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems>& operator /= (vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	for(size_t i = 0; i < _Elems; ++i)
	{
		_Left[i] /= _Right[i];
	}
	return _Left;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems>& operator *= (vector<_Value_type, _Elems>& _Left, _Value_type _Right)
{
	for(size_t i = 0; i < _Elems; ++i)
	{
		_Left[i] *= _Right;
	}
	return _Left;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems>& operator /= (vector<_Value_type, _Elems>& _Left, _Value_type _Right)
{
	if(_Elems > 1)
	{
		const _Value_type invRight = 1 / _Right;
		for(size_t i = 0; i < _Elems; ++i)
		{
			_Left[i] *= invRight;
		}
	}
	else
	{
		for(size_t i = 0; i < _Elems; ++i)
		{
			_Left[i] /= _Right;
		}
	}
	return _Left;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems> operator + ( const vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	vector<_Value_type, _Elems> retval;
	for(size_t i = 0; i < _Elems; ++i)
	{
		retval[i] = _Left[i] + _Right[i];
	}
	return retval;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems> operator - ( const vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	vector<_Value_type, _Elems> retval;
	for(size_t i = 0; i < _Elems; ++i)
	{
		retval[i] = _Left[i] - _Right[i];
	}
	return retval;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems> operator * ( const vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	vector<_Value_type, _Elems> retval;
	for(size_t i = 0; i < _Elems; ++i)
	{
		retval[i] = _Left[i] * _Right[i];
	}
	return retval;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems> operator / ( const vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	vector<_Value_type, _Elems> retval;
	for(size_t i = 0; i < _Elems; ++i)
	{
		retval[i] = _Left[i] / _Right[i];
	}
	return retval;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems> operator * ( const vector<_Value_type, _Elems>& _Left, _Value_type _Right)
{
	vector<_Value_type, _Elems> retval;
	for(size_t i = 0; i < _Elems; ++i)
	{
		retval[i] = _Left[i] * _Right;
	}
	return retval;
}

template<typename _Value_type, size_t _Elems>
inline vector<_Value_type, _Elems> operator / ( const vector<_Value_type, _Elems>& _Left, _Value_type _Right)
{
	vector<_Value_type, _Elems> retval;
	for(size_t i = 0; i < _Elems; ++i)
	{
		retval[i] = _Left[i] / _Right;
	}
	return retval;
}

template<typename _Value_type, size_t _Elems>
inline bool  operator == (const vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	for(size_t i = 0; i < _Elems; ++i)
	{
		if(_Left[i] != _Right[i])
		{
			return false;
		}
	}

	return true;
}

template<typename _Value_type, size_t _Elems>
inline bool  operator != (const vector<_Value_type, _Elems>& _Left, const vector<_Value_type, _Elems>& _Right)
{
	return !(_Left == _Right);
}

namespace _Details {

template<typename _Value_type, size_t _Elems>
inline const vector<_Value_type, _Elems> _Make_zero_vector()
{
	vector<_Value_type, _Elems> m;
	for(size_t i = 0; i < _Elems; ++i)
	{
		m[i] = 0;
	}
	return m;
}

}; // namespace _Details

template<typename _Value_type, size_t _Elems, bool _IsFP, bool _IsUnsigned>
const vector<_Value_type, _Elems> _Details::_Math_vector_base<_Value_type, _Elems, _IsFP, _IsUnsigned>::zero = 
	_Details::_Make_zero_vector<_Value_type, _Elems>();