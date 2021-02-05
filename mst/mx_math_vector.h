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

#define _mst_declare_swizzle2(_Component1, _Component2) \
inline vector<_Value_type,2> _get_##_Component1##_Component2() const { return vector<_Value_type, 2>(_Component1, _Component2); } \
inline void _set_##_Component1##_Component2(const vector<_Value_type,2>& _Val) { _Component1 = _Val._Data[0]; _Component2 = _Val._Data[1]; } \
	vector<_Value_type,2> __declspec(property(put=_set_##_Component1##_Component2,get=_get_##_Component1##_Component2)) _Component1##_Component2

#define _mst_declare_get_swizzle2(_Component1, _Component2) \
inline vector<_Value_type,2> _get_##_Component1##_Component2() const { return vector<_Value_type, 2>(_Component1, _Component2); } \
vector<_Value_type,2> __declspec(property(get=_get_##_Component1##_Component2)) _Component1##_Component2

#define _mst_declare_swizzle3(_Component1, _Component2, _Component3) \
inline vector<_Value_type,3> _get_##_Component1##_Component2##_Component3() const { return vector<_Value_type, 3>(_Component1, _Component2, _Component3); } \
inline void _set_##_Component1##_Component2##_Component3(const vector<_Value_type,3>& _Val) { _Component1 = _Val._Data[0]; _Component2 = _Val._Data[1]; _Component3 = _Val._Data[2]; } \
	vector<_Value_type,3> __declspec(property(put=_set_##_Component1##_Component2##_Component3,get=_get_##_Component1##_Component2##_Component3)) _Component1##_Component2##_Component3

#define _mst_declare_get_swizzle3(_Component1, _Component2, _Component3) \
inline vector<_Value_type,3> _get_##_Component1##_Component2##_Component3() const { return vector<_Value_type, 3>(_Component1, _Component2, _Component3); } \
vector<_Value_type,3> __declspec(property(get=_get_##_Component1##_Component2##_Component3)) _Component1##_Component2##_Component3

#define _mst_declare_swizzle4(_Component1, _Component2, _Component3, _Component4) \
inline vector<_Value_type,4> _get_##_Component1##_Component2##_Component3##_Component4() const { return vector<_Value_type, 4>(_Component1, _Component2, _Component3, _Component4); } \
inline void _set_##_Component1##_Component2##_Component3##_Component4(const vector<_Value_type,4>& _Val) { _Component1 = _Val._Data[0]; _Component2 = _Val._Data[1]; _Component3 = _Val._Data[2]; _Component4 = _Val._Data[3]; } \
	vector<_Value_type,4> __declspec(property(put=_set_##_Component1##_Component2##_Component3##_Component4,get=_get_##_Component1##_Component2##_Component3##_Component4)) _Component1##_Component2##_Component3##_Component4

#define _mst_declare_get_swizzle4(_Component1, _Component2, _Component3, _Component4) \
inline vector<_Value_type,4> _get_##_Component1##_Component2##_Component3##_Component4() const { return vector<_Value_type, 4>(_Component1, _Component2, _Component3, _Component4); } \
	vector<_Value_type,4> __declspec(property(get=_get_##_Component1##_Component2##_Component3##_Component4)) _Component1##_Component2##_Component3##_Component4

namespace _Details {

template<typename _Value_type, size_t _Elems, bool _IsFP = std::is_floating_point<_Value_type>::value, bool _IsUnsigned = std::is_unsigned<_Value_type>::value>
class _Math_vector_base
{
protected:
	MST_STATIC_ASSERT(_Elems <= 4 && _Elems != 0, "_Elems value not supported");

	template<typename _xValue_type, size_t _xElems>
	friend class vector;

	_Value_type _Data[_Elems];

	typedef vector<_Value_type, _Elems> _Vector_t;

public:
	typedef _Value_type value_type;
	static const size_t dimensions = _Elems;
	typedef typename ::std::is_unsigned<_Value_type> is_unsigned;
	
	static const vector<_Value_type, _Elems> zero;

	inline const _Value_type* data() const;
	inline _Value_type* data();

	inline _Value_type& operator[](size_t _Idx);
	inline const _Value_type& operator[](size_t _Idx) const;

	/* returns the squared length */
	inline _Value_type squared_length() const;

	/* returns the squared distance towards _Vec */
	inline _Value_type squared_distance(const _Vector_t& _Vec) const;
};

template<typename _Value_type, size_t _Elems>
class _Math_vector_base<_Value_type, _Elems, false, false> : public _Math_vector_base<_Value_type, _Elems, false, true>
{
	// signed types only functions (should also exclude unsigned floating point)

public:

	/* returns negative version of itself */
	inline _Vector_t operator- () const;
};


template<typename _Value_type, size_t _Elems, bool _IsUnsigned>
class _Math_vector_base<_Value_type, _Elems, true, _IsUnsigned> : public _Math_vector_base<_Value_type, _Elems, false, _IsUnsigned>
{
	// floating point only functions

public:

	/* returns the length */
	inline _Value_type length() const;

	/* returns the squared distance towards _Vec */
	inline _Value_type distance(const _Vector_t& _Vec) const;

	/* normalizes and returns itself */
	inline vector<_Value_type, _Elems>& normalize();
};

}; // namespace _Details

template<typename _Value_type>
class vector<_Value_type, 1> : public _Details::_Math_vector_base<_Value_type, 1>
{
public:
	vector() _DEFAULT_MATH_CONSTRUCTOR
	template<typename _xValue_type>
	inline explicit vector(const vector<_xValue_type, 1>& _Other);
	inline explicit vector(_Value_type _X);

	operator _Value_type() const
	{
		return _Data[0];
	}

	_mst_declare_value(x,0);
};

template<typename _Value_type>
class vector<_Value_type, 2> : public _Details::_Math_vector_base<_Value_type, 2>
{
public:
	inline vector() _DEFAULT_MATH_CONSTRUCTOR
	template<typename _xValue_type>
	inline explicit vector(const vector<_xValue_type, 2>& _Other);
	inline vector(_Value_type _X, _Value_type _Y);
	inline explicit vector(_Value_type initVal);

	_mst_declare_value(x,0);
	_mst_declare_value(y,1);

	_mst_declare_swizzle2(x,y);
	_mst_declare_swizzle2(y,x);

	_mst_declare_get_swizzle2(x,x);
	_mst_declare_get_swizzle2(y,y);
};

template<typename _Value_type>
class vector<_Value_type, 3> : public _Details::_Math_vector_base<_Value_type, 3>
{
public:
	inline vector() _DEFAULT_MATH_CONSTRUCTOR
	template<typename _xValue_type>
	inline explicit vector(const vector<_xValue_type, 3>& _Other);
	inline vector(_Value_type _X, _Value_type _Y, _Value_type _Z);
	inline vector(const vector<_Value_type, 2>& _XY, _Value_type _Z);
	inline vector(_Value_type _X, const vector<_Value_type, 2>& _YZ);
	inline explicit vector(_Value_type initVal);

	/* returns the dot product with _Vec */
	inline _Value_type dot(const vector& _Vec ) const;

	/* returns the cross product with _Vec */
	inline vector cross(const vector& _Vec ) const;

	_mst_declare_value(x,0);
	_mst_declare_value(y,1);
	_mst_declare_value(z,2);

	_mst_declare_swizzle2(x,y);
	_mst_declare_swizzle2(y,x);
	_mst_declare_swizzle2(y,z);
	_mst_declare_swizzle2(z,y);
	_mst_declare_swizzle2(x,z);
	_mst_declare_swizzle2(z,x);

	_mst_declare_swizzle2(x,x);
	_mst_declare_swizzle2(y,y);
	_mst_declare_swizzle2(z,z);

	_mst_declare_swizzle3(x,y,z);
	_mst_declare_swizzle3(y,x,z);
	_mst_declare_swizzle3(y,z,x);
	_mst_declare_swizzle3(x,z,y);
	_mst_declare_swizzle3(z,x,y);
	_mst_declare_swizzle3(z,y,x);

	_mst_declare_get_swizzle3(x,x,x);
	_mst_declare_get_swizzle3(y,y,y);
	_mst_declare_get_swizzle3(z,z,z);

	_mst_declare_get_swizzle3(z,x,x);
	_mst_declare_get_swizzle3(x,z,x);
	_mst_declare_get_swizzle3(x,x,z);
	_mst_declare_get_swizzle3(y,x,x);
	_mst_declare_get_swizzle3(x,y,x);
	_mst_declare_get_swizzle3(x,x,y);

	_mst_declare_get_swizzle3(x,y,y);
	_mst_declare_get_swizzle3(y,x,y);
	_mst_declare_get_swizzle3(y,y,x);
	_mst_declare_get_swizzle3(z,y,y);
	_mst_declare_get_swizzle3(y,z,y);
	_mst_declare_get_swizzle3(y,y,z);

	_mst_declare_get_swizzle3(x,z,z);
	_mst_declare_get_swizzle3(z,x,z);
	_mst_declare_get_swizzle3(z,z,x);
	_mst_declare_get_swizzle3(y,z,z);
	_mst_declare_get_swizzle3(z,y,z);
	_mst_declare_get_swizzle3(z,z,y);
};

template<typename _Value_type>
class vector<_Value_type, 4> : public _Details::_Math_vector_base<_Value_type, 4>
{
public:
	inline vector() _DEFAULT_MATH_CONSTRUCTOR
	template<typename _xValue_type>
	inline explicit vector(const vector<_xValue_type, 4>& _Other);
	inline vector(_Value_type _X, _Value_type _Y, _Value_type _Z, _Value_type _W);
	inline vector(const vector<_Value_type, 2>& _XY, const vector<_Value_type, 2>& _ZW);
	inline vector(const vector<_Value_type, 2>& _XY, _Value_type _Z, _Value_type _W);
	inline vector(_Value_type _X, const vector<_Value_type, 2>& _YZ, _Value_type _W);
	inline vector(_Value_type _X, _Value_type _Y, const vector<_Value_type, 2>& _ZW);
	inline vector(const vector<_Value_type, 3>& _XYZ, _Value_type _W);
	inline vector(_Value_type _X, const vector<_Value_type, 3>& _YZW);
	inline explicit vector(_Value_type initVal);

	_mst_declare_value(x,0);
	_mst_declare_value(y,1);
	_mst_declare_value(z,2);
	_mst_declare_value(w,3);

	_mst_declare_swizzle2(x,y);
	_mst_declare_swizzle2(y,x);

	_mst_declare_swizzle2(y,z);
	_mst_declare_swizzle2(z,y);
	_mst_declare_swizzle2(x,z);
	_mst_declare_swizzle2(z,x);

	_mst_declare_swizzle2(x,w);
	_mst_declare_swizzle2(w,x);
	_mst_declare_swizzle2(y,w);
	_mst_declare_swizzle2(w,y);
	_mst_declare_swizzle2(z,w);
	_mst_declare_swizzle2(w,z);

	_mst_declare_swizzle2(x,x);
	_mst_declare_swizzle2(y,y);
	_mst_declare_swizzle2(z,z);
	_mst_declare_swizzle2(w,w);

	_mst_declare_swizzle3(x,y,z);
	_mst_declare_swizzle3(y,x,z);
	_mst_declare_swizzle3(y,z,x);
	_mst_declare_swizzle3(x,z,y);
	_mst_declare_swizzle3(z,x,y);
	_mst_declare_swizzle3(z,y,x);

	_mst_declare_swizzle3(w,y,z);
	_mst_declare_swizzle3(w,x,z);
	_mst_declare_swizzle3(w,z,x);
	_mst_declare_swizzle3(w,z,y);
	_mst_declare_swizzle3(w,x,y);
	_mst_declare_swizzle3(w,y,x);

	_mst_declare_swizzle3(x,w,z);
	_mst_declare_swizzle3(y,w,z);
	_mst_declare_swizzle3(y,w,x);
	_mst_declare_swizzle3(x,w,y);
	_mst_declare_swizzle3(z,w,y);
	_mst_declare_swizzle3(z,w,x);

	_mst_declare_swizzle3(x,y,w);
	_mst_declare_swizzle3(y,x,w);
	_mst_declare_swizzle3(y,z,w);
	_mst_declare_swizzle3(x,z,w);
	_mst_declare_swizzle3(z,x,w);
	_mst_declare_swizzle3(z,y,w);

	_mst_declare_get_swizzle3(x,x,x);
	_mst_declare_get_swizzle3(y,y,y);
	_mst_declare_get_swizzle3(z,z,z);
	_mst_declare_get_swizzle3(w,w,w);

	_mst_declare_get_swizzle3(y,x,x);
	_mst_declare_get_swizzle3(x,y,x);
	_mst_declare_get_swizzle3(x,x,y);
	_mst_declare_get_swizzle3(z,x,x);
	_mst_declare_get_swizzle3(x,z,x);
	_mst_declare_get_swizzle3(x,x,z);
	_mst_declare_get_swizzle3(w,x,x);
	_mst_declare_get_swizzle3(x,w,x);
	_mst_declare_get_swizzle3(x,x,w);

	_mst_declare_get_swizzle3(x,y,y);
	_mst_declare_get_swizzle3(y,x,y);
	_mst_declare_get_swizzle3(y,y,x);
	_mst_declare_get_swizzle3(z,y,y);
	_mst_declare_get_swizzle3(y,z,y);
	_mst_declare_get_swizzle3(y,y,z);
	_mst_declare_get_swizzle3(w,y,y);
	_mst_declare_get_swizzle3(y,w,y);
	_mst_declare_get_swizzle3(y,y,w);

	_mst_declare_get_swizzle3(x,z,z);
	_mst_declare_get_swizzle3(z,x,z);
	_mst_declare_get_swizzle3(z,z,x);
	_mst_declare_get_swizzle3(y,z,z);
	_mst_declare_get_swizzle3(z,y,z);
	_mst_declare_get_swizzle3(z,z,y);
	_mst_declare_get_swizzle3(w,z,z);
	_mst_declare_get_swizzle3(z,w,z);
	_mst_declare_get_swizzle3(z,z,w);

	_mst_declare_get_swizzle3(x,w,w);
	_mst_declare_get_swizzle3(w,x,w);
	_mst_declare_get_swizzle3(w,w,x);
	_mst_declare_get_swizzle3(y,w,w);
	_mst_declare_get_swizzle3(w,y,w);
	_mst_declare_get_swizzle3(w,w,y);
	_mst_declare_get_swizzle3(z,w,w);
	_mst_declare_get_swizzle3(w,z,w);
	_mst_declare_get_swizzle3(w,w,z);

	_mst_declare_get_swizzle4(x,x,x,x);
	_mst_declare_get_swizzle4(y,y,y,y);
	_mst_declare_get_swizzle4(z,z,z,z);
	_mst_declare_get_swizzle4(w,w,w,w);

	_mst_declare_swizzle4(x,y,z,w);
	_mst_declare_swizzle4(x,z,w,y);
	_mst_declare_swizzle4(x,z,y,w);
	_mst_declare_swizzle4(y,w,x,z);
	_mst_declare_swizzle4(y,w,z,x);
	_mst_declare_swizzle4(y,x,w,z);
	_mst_declare_swizzle4(y,x,z,w);
	_mst_declare_swizzle4(y,z,w,x);
	_mst_declare_swizzle4(y,z,x,w);
	_mst_declare_swizzle4(z,w,x,y);
	_mst_declare_swizzle4(z,w,y,x);
	_mst_declare_swizzle4(z,x,w,y);
	_mst_declare_swizzle4(z,x,y,w);
	_mst_declare_swizzle4(z,y,w,x);
	_mst_declare_swizzle4(z,y,x,w);

	_mst_declare_get_swizzle4(x,x,y,z);
	_mst_declare_get_swizzle4(x,x,z,y);
	_mst_declare_get_swizzle4(x,y,x,z);
	_mst_declare_get_swizzle4(x,y,z,x);
	_mst_declare_get_swizzle4(x,z,x,y);
	_mst_declare_get_swizzle4(x,z,y,x);
	_mst_declare_get_swizzle4(y,x,x,z);
	_mst_declare_get_swizzle4(y,x,z,x);
	_mst_declare_get_swizzle4(y,z,x,x);
	_mst_declare_get_swizzle4(z,x,x,y);
	_mst_declare_get_swizzle4(z,x,y,x);
	_mst_declare_get_swizzle4(z,y,x,x);

	_mst_declare_get_swizzle4(x,y,y,z);
	_mst_declare_get_swizzle4(x,y,z,y);
	_mst_declare_get_swizzle4(x,z,y,y);
	_mst_declare_get_swizzle4(y,x,y,z);
	_mst_declare_get_swizzle4(y,x,z,y);
	_mst_declare_get_swizzle4(y,y,x,z);
	_mst_declare_get_swizzle4(y,y,z,x);
	_mst_declare_get_swizzle4(y,z,x,y);
	_mst_declare_get_swizzle4(y,z,y,x);
	_mst_declare_get_swizzle4(z,x,y,y);
	_mst_declare_get_swizzle4(z,y,x,y);
	_mst_declare_get_swizzle4(z,y,y,x);

	_mst_declare_get_swizzle4(x,y,z,z);
	_mst_declare_get_swizzle4(x,z,y,z);
	_mst_declare_get_swizzle4(x,z,z,y);
	_mst_declare_get_swizzle4(y,x,z,z);
	_mst_declare_get_swizzle4(y,z,x,z);
	_mst_declare_get_swizzle4(y,z,z,x);
	_mst_declare_get_swizzle4(z,x,y,z);
	_mst_declare_get_swizzle4(z,x,z,y);
	_mst_declare_get_swizzle4(z,y,x,z);
	_mst_declare_get_swizzle4(z,y,z,x);
	_mst_declare_get_swizzle4(z,z,x,y);
	_mst_declare_get_swizzle4(z,z,y,x);

	_mst_declare_get_swizzle4(w,y,y,z);
	_mst_declare_get_swizzle4(w,y,z,y);
	_mst_declare_get_swizzle4(w,z,y,y);
	_mst_declare_get_swizzle4(y,w,y,z);
	_mst_declare_get_swizzle4(y,w,z,y);
	_mst_declare_get_swizzle4(y,y,w,z);
	_mst_declare_get_swizzle4(y,y,z,w);
	_mst_declare_get_swizzle4(y,z,w,y);
	_mst_declare_get_swizzle4(y,z,y,w);
	_mst_declare_get_swizzle4(z,w,y,y);
	_mst_declare_get_swizzle4(z,y,w,y);
	_mst_declare_get_swizzle4(z,y,y,w);

	_mst_declare_get_swizzle4(w,y,z,z);
	_mst_declare_get_swizzle4(w,z,y,z);
	_mst_declare_get_swizzle4(w,z,z,y);
	_mst_declare_get_swizzle4(y,w,z,z);
	_mst_declare_get_swizzle4(y,z,w,z);
	_mst_declare_get_swizzle4(y,z,z,w);
	_mst_declare_get_swizzle4(z,w,y,z);
	_mst_declare_get_swizzle4(z,w,z,y);
	_mst_declare_get_swizzle4(z,y,w,z);
	_mst_declare_get_swizzle4(z,y,z,w);
	_mst_declare_get_swizzle4(z,z,w,y);
	_mst_declare_get_swizzle4(z,z,y,w);

	_mst_declare_get_swizzle4(w,w,y,z);
	_mst_declare_get_swizzle4(w,w,z,y);
	_mst_declare_get_swizzle4(w,y,w,z);
	_mst_declare_get_swizzle4(w,y,z,w);
	_mst_declare_get_swizzle4(w,z,w,y);
	_mst_declare_get_swizzle4(w,z,y,w);
	_mst_declare_get_swizzle4(y,w,w,z);
	_mst_declare_get_swizzle4(y,w,z,w);
	_mst_declare_get_swizzle4(y,z,w,w);
	_mst_declare_get_swizzle4(z,w,w,y);
	_mst_declare_get_swizzle4(z,w,y,w);
	_mst_declare_get_swizzle4(z,y,w,w);

	_mst_declare_get_swizzle4(w,x,x,z);
	_mst_declare_get_swizzle4(w,x,z,x);
	_mst_declare_get_swizzle4(w,z,x,x);
	_mst_declare_get_swizzle4(x,w,x,z);
	_mst_declare_get_swizzle4(x,w,z,x);
	_mst_declare_get_swizzle4(x,x,w,z);
	_mst_declare_get_swizzle4(x,x,z,w);
	_mst_declare_get_swizzle4(x,z,w,x);
	_mst_declare_get_swizzle4(x,z,x,w);
	_mst_declare_get_swizzle4(z,w,x,x);
	_mst_declare_get_swizzle4(z,x,w,x);
	_mst_declare_get_swizzle4(z,x,x,w);

	_mst_declare_get_swizzle4(w,x,z,z);
	_mst_declare_get_swizzle4(w,z,x,z);
	_mst_declare_get_swizzle4(w,z,z,x);
	_mst_declare_get_swizzle4(x,w,z,z);
	_mst_declare_get_swizzle4(x,z,w,z);
	_mst_declare_get_swizzle4(x,z,z,w);
	_mst_declare_get_swizzle4(z,w,x,z);
	_mst_declare_get_swizzle4(z,w,z,x);
	_mst_declare_get_swizzle4(z,x,w,z);
	_mst_declare_get_swizzle4(z,x,z,w);
	_mst_declare_get_swizzle4(z,z,w,x);
	_mst_declare_get_swizzle4(z,z,x,w);

	_mst_declare_get_swizzle4(w,w,x,z);
	_mst_declare_get_swizzle4(w,w,z,x);
	_mst_declare_get_swizzle4(w,x,w,z);
	_mst_declare_get_swizzle4(w,x,z,w);
	_mst_declare_get_swizzle4(w,z,w,x);
	_mst_declare_get_swizzle4(w,z,x,w);
	_mst_declare_get_swizzle4(x,w,w,z);
	_mst_declare_get_swizzle4(x,w,z,w);
	_mst_declare_get_swizzle4(x,z,w,w);
	_mst_declare_get_swizzle4(z,w,w,x);
	_mst_declare_get_swizzle4(z,w,x,w);
	_mst_declare_get_swizzle4(z,x,w,w);

	_mst_declare_get_swizzle4(w,x,x,y);
	_mst_declare_get_swizzle4(w,x,y,x);
	_mst_declare_get_swizzle4(w,y,x,x);
	_mst_declare_get_swizzle4(x,w,x,y);
	_mst_declare_get_swizzle4(x,w,y,x);
	_mst_declare_get_swizzle4(x,x,w,y);
	_mst_declare_get_swizzle4(x,x,y,w);
	_mst_declare_get_swizzle4(x,y,w,x);
	_mst_declare_get_swizzle4(x,y,x,w);
	_mst_declare_get_swizzle4(y,w,x,x);
	_mst_declare_get_swizzle4(y,x,w,x);
	_mst_declare_get_swizzle4(y,x,x,w);

	_mst_declare_get_swizzle4(w,x,y,y);
	_mst_declare_get_swizzle4(w,y,x,y);
	_mst_declare_get_swizzle4(w,y,y,x);
	_mst_declare_get_swizzle4(x,w,y,y);
	_mst_declare_get_swizzle4(x,y,w,y);
	_mst_declare_get_swizzle4(x,y,y,w);
	_mst_declare_get_swizzle4(y,w,x,y);
	_mst_declare_get_swizzle4(y,w,y,x);
	_mst_declare_get_swizzle4(y,x,w,y);
	_mst_declare_get_swizzle4(y,x,y,w);
	_mst_declare_get_swizzle4(y,y,w,x);
	_mst_declare_get_swizzle4(y,y,x,w);

	_mst_declare_get_swizzle4(w,w,x,y);
	_mst_declare_get_swizzle4(w,w,y,x);
	_mst_declare_get_swizzle4(w,x,w,y);
	_mst_declare_get_swizzle4(w,x,y,w);
	_mst_declare_get_swizzle4(w,y,w,x);
	_mst_declare_get_swizzle4(w,y,x,w);
	_mst_declare_get_swizzle4(x,w,w,y);
	_mst_declare_get_swizzle4(x,w,y,w);
	_mst_declare_get_swizzle4(x,y,w,w);
	_mst_declare_get_swizzle4(y,w,w,x);
	_mst_declare_get_swizzle4(y,w,x,w);
	_mst_declare_get_swizzle4(y,x,w,w);

	_mst_declare_get_swizzle4(x,y,y,y);
	_mst_declare_get_swizzle4(y,x,y,y);
	_mst_declare_get_swizzle4(y,y,x,y);
	_mst_declare_get_swizzle4(y,y,y,x);

	_mst_declare_get_swizzle4(x,z,z,z);
	_mst_declare_get_swizzle4(z,x,z,z);
	_mst_declare_get_swizzle4(z,z,x,z);
	_mst_declare_get_swizzle4(z,z,z,x);

	_mst_declare_get_swizzle4(w,w,w,x);
	_mst_declare_get_swizzle4(w,w,x,w);
	_mst_declare_get_swizzle4(w,x,w,w);
	_mst_declare_get_swizzle4(x,w,w,w);

	_mst_declare_get_swizzle4(x,x,x,y);
	_mst_declare_get_swizzle4(x,x,y,x);
	_mst_declare_get_swizzle4(x,y,x,x);
	_mst_declare_get_swizzle4(y,x,x,x);

	_mst_declare_get_swizzle4(y,z,z,z);
	_mst_declare_get_swizzle4(z,y,z,z);
	_mst_declare_get_swizzle4(z,z,y,z);
	_mst_declare_get_swizzle4(z,z,z,y);

	_mst_declare_get_swizzle4(w,w,w,y);
	_mst_declare_get_swizzle4(w,w,y,w);
	_mst_declare_get_swizzle4(w,y,w,w);
	_mst_declare_get_swizzle4(y,w,w,w);

	_mst_declare_get_swizzle4(x,x,x,z);
	_mst_declare_get_swizzle4(x,x,z,x);
	_mst_declare_get_swizzle4(x,z,x,x);
	_mst_declare_get_swizzle4(z,x,x,x);

	_mst_declare_get_swizzle4(y,y,y,z);
	_mst_declare_get_swizzle4(y,y,z,y);
	_mst_declare_get_swizzle4(y,z,y,y);
	_mst_declare_get_swizzle4(z,y,y,y);

	_mst_declare_get_swizzle4(w,w,w,z);
	_mst_declare_get_swizzle4(w,w,z,w);
	_mst_declare_get_swizzle4(w,z,w,w);
	_mst_declare_get_swizzle4(z,w,w,w);

	_mst_declare_get_swizzle4(w,x,x,x);
	_mst_declare_get_swizzle4(x,w,x,x);
	_mst_declare_get_swizzle4(x,x,w,x);
	_mst_declare_get_swizzle4(x,x,x,w);

	_mst_declare_get_swizzle4(w,y,y,y);
	_mst_declare_get_swizzle4(y,w,y,y);
	_mst_declare_get_swizzle4(y,y,w,y);
	_mst_declare_get_swizzle4(y,y,y,w);

	_mst_declare_get_swizzle4(w,z,z,z);
	_mst_declare_get_swizzle4(z,w,z,z);
	_mst_declare_get_swizzle4(z,z,w,z);
	_mst_declare_get_swizzle4(z,z,z,w);

	_mst_declare_get_swizzle4(x,x,y,y);
	_mst_declare_get_swizzle4(x,y,x,y);
	_mst_declare_get_swizzle4(x,y,y,x);
	_mst_declare_get_swizzle4(y,x,x,y);
	_mst_declare_get_swizzle4(y,x,y,x);
	_mst_declare_get_swizzle4(y,y,x,x);

	_mst_declare_get_swizzle4(x,x,z,z);
	_mst_declare_get_swizzle4(x,z,x,z);
	_mst_declare_get_swizzle4(x,z,z,x);
	_mst_declare_get_swizzle4(z,x,x,z);
	_mst_declare_get_swizzle4(z,x,z,x);
	_mst_declare_get_swizzle4(z,z,x,x);

	_mst_declare_get_swizzle4(w,w,x,x);
	_mst_declare_get_swizzle4(w,x,w,x);
	_mst_declare_get_swizzle4(w,x,x,w);
	_mst_declare_get_swizzle4(x,w,w,x);
	_mst_declare_get_swizzle4(x,w,x,w);
	_mst_declare_get_swizzle4(x,x,w,w);

	_mst_declare_get_swizzle4(y,y,z,z);
	_mst_declare_get_swizzle4(y,z,y,z);
	_mst_declare_get_swizzle4(y,z,z,y);
	_mst_declare_get_swizzle4(z,y,y,z);
	_mst_declare_get_swizzle4(z,y,z,y);
	_mst_declare_get_swizzle4(z,z,y,y);

	_mst_declare_get_swizzle4(w,w,y,y);
	_mst_declare_get_swizzle4(w,y,w,y);
	_mst_declare_get_swizzle4(w,y,y,w);
	_mst_declare_get_swizzle4(y,w,w,y);
	_mst_declare_get_swizzle4(y,w,y,w);
	_mst_declare_get_swizzle4(y,y,w,w);

	_mst_declare_get_swizzle4(w,w,z,z);
	_mst_declare_get_swizzle4(w,z,w,z);
	_mst_declare_get_swizzle4(w,z,z,w);
	_mst_declare_get_swizzle4(z,w,w,z);
	_mst_declare_get_swizzle4(z,w,z,w);
	_mst_declare_get_swizzle4(z,z,w,w);
};


#undef _mst_declare_swizzle2
#undef _mst_declare_swizzle3
#undef _mst_declare_swizzle4

#undef _mst_declare_get_swizzle2
#undef _mst_declare_get_swizzle3
#undef _mst_declare_get_swizzle4

#undef _mst_declare_value