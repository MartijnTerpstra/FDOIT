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
class degrees;

template<typename _Value_type>
class radians;

template<typename _Value_type>
class radians
{
	template<typename _xValue_type>
	friend class degrees;

	template<typename _xValue_type>
	friend class radians;
public:

	typedef _Value_type value_type;
	
	radians() _DEFAULT_MATH_CONSTRUCTOR
	radians(const _Value_type& _V)
		: _Angle(_V < max_angle() && _V >= 0 ? _V : fmod(_V, max_angle()))
	{ }

	radians(const radians& _Other)
		: _Angle(_Other._Angle)
	{ }

	template<typename _xValue_type>
	explicit radians(const radians<_xValue_type>& _Other)
		: _Angle((_Value_type)_Other._Angle)
	{ }

	radians(const degrees<_Value_type>& _Other)
		: _Angle(_Other._Angle * (max_angle() / _Other.max_angle()))
	{ }

	template<typename _xValue_type>
	explicit radians(const degrees<_xValue_type>& _Other)
		: _Angle((_Value_type)(_Other._Angle * (max_angle() / _Other.max_angle())))
	{ }

	inline radians& operator -= (const radians& _Other)
	{
		_Angle -= _Other._Angle;
		if(_Angle < 0)
			_Angle += max_angle();
		return *this;
	}

	inline radians& operator -= (const degrees<_Value_type>& _Other)
	{
		_Angle -= _Other._Angle * (max_angle() / _Other.max_angle());
		if(_Angle < 0)
			_Angle += max_angle();
		return *this;
	}

	inline radians& operator += (const radians& _Other)
	{
		_Angle += _Other._Angle;
		if(_Angle >= max_angle())
			_Angle -= max_angle();
		return *this;
	}

	inline radians& operator += (const degrees<_Value_type>& _Other)
	{
		_Angle += _Other._Angle * max_angle() / _Other.max_angle();
		if(_Angle >= max_angle())
			_Angle -= max_angle();
		return *this;
	}

	inline radians& operator *= (const _Value_type& _V)
	{
		_Angle = fmod(_Angle * _V, max_angle());
		
		return *this;
	}

	inline radians& operator /= (const _Value_type& _V)
	{
		_Angle = fmod(_Angle / _V, max_angle());

		return *this;
	}

	inline friend radians operator - (const radians& _L, const radians& _R)
	{
		_Value_type tmp = _L._Angle - _R._Angle;
		if(tmp < 0)
			tmp += _L.max_angle();
		return radians(tmp);
	}

	inline friend radians operator + (const radians& _L, const radians& _R)
	{
		_Value_type tmp = _L._Angle + _R._Angle;
		if(tmp >= _L.max_angle())
			tmp -= _L.max_angle();
		return radians(tmp);
	}

	inline friend radians operator * (const radians& _L, const _Value_type& _R)
	{
		return radians(fmod(_L._Angle * _R, _L.max_angle()));
	}

	inline friend radians operator / (const radians& _L, const _Value_type& _R)
	{
		return radians(fmod(_L._Angle / _R, _L.max_angle()));
	}

	inline _Value_type count() const
	{
		return _Angle;
	}

	_MST_CONSTEXPR inline _Value_type max_angle() const
	{
		return pi<_Value_type>() * 2;
	}

private:
	_Value_type _Angle;

}; // class radians

template<typename _Value_type>
class degrees
{
	template<typename _xValue_type>
	friend class degrees;

	template<typename _xValue_type>
	friend class radians;
public:

	typedef _Value_type value_type;

	degrees() _DEFAULT_MATH_CONSTRUCTOR
		degrees(const _Value_type& _V)
		: _Angle(_V < max_angle() && _V >= 0 ? _V : fmod(_V, max_angle()))
	{ }

	degrees(const degrees& _Other)
		: _Angle(_Other._Angle)
	{ }

	template<typename _xValue_type>
	explicit degrees(const degrees<_xValue_type>& _Other)
		: _Angle((_Value_type)_Other._Angle)
	{ }

	degrees(const radians<_Value_type>& _Other)
		: _Angle(_Other._Angle * (max_angle() / _Other.max_angle()))
	{ }

	template<typename _xValue_type>
	explicit degrees(const radians<_xValue_type>& _Other)
		: _Angle((_Value_type)(_Other._Angle * (max_angle() / _Other.max_angle())))
	{ }

	inline degrees& operator -= (const degrees& _Other)
	{
		_Angle -= _Other._Angle;
		if(_Angle < 0)
			_Angle += max_angle();
		return *this;
	}

	inline degrees& operator -= (const radians<_Value_type>& _Other)
	{
		_Angle -= _Other._Angle * (max_angle() / _Other.max_angle());
		if(_Angle < 0)
			_Angle += max_angle();
		return *this;
	}

	inline degrees& operator += (const degrees& _Other)
	{
		_Angle += _Other._Angle;
		if(_Angle >= max_angle())
			_Angle -= max_angle();
		return *this;
	}

	inline degrees& operator += (const radians<_Value_type>& _Other)
	{
		_Angle += _Other._Angle * max_angle() / _Other.max_angle();
		if(_Angle >= max_angle())
			_Angle -= max_angle();
		return *this;
	}

	inline degrees& operator *= (const _Value_type& _V)
	{
		_Angle = fmod(_Angle * _V, max_angle());

		return *this;
	}

	inline degrees& operator /= (const _Value_type& _V)
	{
		_Angle = fmod(_Angle / _V, max_angle());

		return *this;
	}

	inline friend degrees operator - (const degrees& _L, const degrees& _R)
	{
		_Value_type tmp = _L._Angle - _R._Angle;
		if(tmp < 0)
			tmp += _L.max_angle();
		return degrees(tmp);
	}

	inline friend degrees operator + (const degrees& _L, const degrees& _R)
	{
		_Value_type tmp = _L._Angle + _R._Angle;
		if(tmp >= _L.max_angle())
			tmp -= _L.max_angle();
		return degrees(tmp);
	}

	inline friend degrees operator * (const degrees& _L, const _Value_type& _R)
	{
		return degrees(fmod(_L._Angle * _R, _L.max_angle()));
	}

	inline friend degrees operator / (const degrees& _L, const _Value_type& _R)
	{
		return degrees(fmod(_L._Angle / _R, _L.max_angle()));
	}

	inline _Value_type count() const
	{
		return _Angle;
	}

	_MST_CONSTEXPR inline _Value_type max_angle() const
	{
		return (_Value_type)360;
	}

private:
	_Value_type _Angle;

}; // class degrees

#undef _mst_declare_value