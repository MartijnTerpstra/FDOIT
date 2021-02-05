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

#ifndef _MST_MDET
#define _MST_MDET ::mst::math::_Details::
#endif

namespace mst {
namespace math {
namespace _Details {

struct _Math_type {};
struct _Scalar_type {};
struct _Array_type {};

template<typename T, typename IsScalar = typename ::std::is_arithmetic<T>::type>
struct _Math_traits_impl
{
	static const size_t dimensions = 1;
	typedef typename T value_type;
	typedef _Scalar_type math_type;
	typedef ::std::is_unsigned<T> is_unsigned;
};

template<typename T>
struct _Math_traits_impl<T, ::std::false_type>
{
	static const size_t dimensions = T::dimensions;
	typedef typename T::value_type value_type;
	typedef _Math_type math_type;
	typedef typename T::is_unsigned is_unsigned;
};

template<typename T>
struct _Math_traits : public _Math_traits_impl<T>
{
};

template<typename T, size_t N>
struct _Math_traits<T[N]>
{
	static const size_t dimensions = N;
	typedef typename ::std::remove_const<T>::type value_type;
	typedef _Array_type math_type;
	typedef typename _Math_traits_impl<T>::is_unsigned is_unsigned;
};

template<typename T>
struct _Cref_value
{
	typedef const typename _Math_traits<T>::value_type& type;
};

template<typename T>
struct _Cvalue
{
	inline static typename _Math_traits<T>::value_type _Create(const double initValue, _Math_type)
	{
		return typename _Math_traits<T>::value_type(initValue);
	}

	inline static typename _Math_traits<T>::value_type _Create(const double initValue, _Scalar_type)
	{
		return typename _Math_traits<T>::value_type(initValue);
	}

	inline static typename _Math_traits<T>::value_type _Create(const double initValue, _Array_type)
	{
		return typename _Math_traits<T>::value_type(_Cvalue<typename _Math_traits<T>::value_type>::create(initValue));
	}

	inline static typename _Math_traits<T>::value_type _Create(const size_t initValue, _Math_type)
	{
		return typename _Math_traits<T>::value_type(initValue);
	}

	inline static typename _Math_traits<T>::value_type _Create(const size_t initValue, _Scalar_type)
	{
		return typename _Math_traits<T>::value_type(initValue);
	}

	inline static typename _Math_traits<T>::value_type _Create(const size_t initValue, _Array_type)
	{
		return typename _Math_traits<T>::value_type(_Cvalue<typename _Math_traits<T>::value_type>::create(initValue));
	}

	inline static typename _Math_traits<T>::value_type create(const double initValue)
	{
		return _Create(initValue, typename _Math_traits<T>::math_type());
	}

	inline static typename _Math_traits<T>::value_type create(const size_t initValue)
	{
		return _Create(initValue, typename _Math_traits<T>::math_type());
	}
};

}; // namespace _Details
}; // namespace math
}; // namespace mst