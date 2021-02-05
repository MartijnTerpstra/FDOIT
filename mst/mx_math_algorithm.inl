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
#include <emmintrin.h>

template<typename T>
inline T(::mst::math::lerp)(const T& u, const T& v, typename _MST_MDET _Cref_value<T>::type s)
{
	return (u * (1 - s)) + (v * s);
}

template<typename T>
inline T(::mst::math::lerp)(const T& u, const T& v, const T& w, typename _MST_MDET _Cref_value<T>::type s, typename _MST_MDET _Cref_value<T>::type t)
{
	return lerp(lerp(u, v, s), w, t);
}

template<typename T>
inline T(::mst::math::cubic_interp)(const T& pre_u, const T& u, const T& v, const T& post_v, typename _MST_MDET _Cref_value<T>::type s)
{
	return u + _MST_MDET _Cvalue<T>::create(0.5) * s*(v - pre_u + s*(_MST_MDET _Cvalue<T>::create(2.0)*pre_u - _MST_MDET _Cvalue<T>::create(5.0)*u + _MST_MDET _Cvalue<T>::create(4.0)*v - post_v + s*(_MST_MDET _Cvalue<T>::create(3.0)*(u - v) + post_v - pre_u)));
}

template<typename T>
inline T(::mst::math::cubic_interp)(const T (&uv)[4], typename _MST_MDET _Cref_value<T>::type s)
{
	return uv[1] + _MST_MDET _Cvalue<T>::create(0.5) * s*(uv[2] - uv[0] + s*(_MST_MDET _Cvalue<T>::create(2.0)*uv[0] - _MST_MDET _Cvalue<T>::create(5.0)*uv[1] + _MST_MDET _Cvalue<T>::create(4.0)*uv[2] - uv[3] + s*(_MST_MDET _Cvalue<T>::create(3.0)*(uv[1] - uv[2]) + uv[3] - uv[0])));
}

namespace _Details {

	template<typename Ty>
	inline Ty _Reflect(const Ty& i, const Ty& n, _Details::_Math_type)
	{
		return i - 2.0 * n * n.dot(i);
	}

}; // namespace _Details

template<typename Ty>
inline Ty(::mst::math::reflect)(const Ty& i, const Ty& n)
{
	return _Details::_Reflect(i, n,
							  typename _Details::_Math_traits<Ty>::math_type());
}

inline float ::mst::math::fast_sqrtf(const float val)
{
	CHECK_IF(val < 0.0f, "value is negative");
	__m128 val4 = _mm_set_ps1(val);
	return _mm_mul_ps(_mm_rsqrt_ps(val4),val4).m128_f32[0];
}

inline float ::mst::math::fast_rsqrtf(const float val)
{
	CHECK_IF(val < 0.0f, "value is negative");
	return _mm_rsqrt_ps(_mm_set_ps1(val)).m128_f32[0];
}

namespace _Details {

	template<typename T>
	inline T _Saturate(const T& val, _MST_MDET _Scalar_type)
	{
		return (val > (T)0.0 ? (val < (T)1.0 ? val : (T)1.0) : (T)0.0);
	}

	template<typename T>
	inline T _Saturate(const T& val, _MST_MDET _Math_type)
	{
		T retval;
		for(size_t i = 0; i < _Ty::dimensions; ++i)
		{
			retval.data()[i] = _Saturate(val.data()[i], _MST_MDET _Scalar_type);
		}

		return retval;
	}

}; // namespace _Details

/* returns clamps all the values to the range: [0,1] */
template<typename _Ty>
inline _Ty(::mst::math::saturate)(const _Ty& val)
{
	return _Details::_Saturate(val,
							   typename _Details::_Math_traits<_Ty>::math_type());
}

namespace _Details {

template<typename T>
inline T _Smoothstep(const T& minim, const T& maxim, typename _MST_MDET _Cref_value<T>::type val, typename _MST_MDET _Math_type)
{
	T t = ::mst::math::saturate((T(val) - minim) / (maxim - minim));
	return t*t*(_MST_MDET _Cvalue<T>::create(3.0) - (_MST_MDET _Cvalue<T>::create(2.0)*t));
}

template<typename T>
inline T _Smoothstep(const T& minim, const T& maxim, typename _MST_MDET _Cref_value<T>::type val, typename _MST_MDET _Scalar_type)
{
	T t = ::mst::math::saturate((val - minim) / (maxim - minim));
	return t*t*(T(3.0) - (T(2.0)*t));
}

template<typename T>
inline T _Smoothstep(const T& minim, const T& maxim, typename _MST_MDET _Cref_value<T>::type val, typename _MST_MDET _Array_type)
{
	static_assert(0, "::mst::math::smoothstep() does not support arrays");
}

}; // namespace _Details

template<typename T>
inline T (::mst::math::smoothstep)(const T& minim, const T& maxim, typename _MST_MDET _Cref_value<T>::type val)
{
	return _MST_MDET _Smoothstep(minim, maxim, val);
}

namespace _Details {

	template<typename T>
	inline T _Frac(const T& val, _MST_MDET _Math_type)
	{
		static_assert(::std::is_floating_point<typename _MST_MDET _Math_traits<T>::value_type>::value, "frac() cannot be used with integer types");

		T retval;
		for(size_t i = 0; i < _Ty::dimensions; ++i)
		{
			retval = val - floor(val.data()[i]);
		}
		return retval;
	}

	template<typename T>
	inline T _Frac(const T& val, _MST_MDET _Scalar_type)
	{
		static_assert(::std::is_floating_point<T>::value, "::mst::math::frac() cannot be used with integer types");
		return val - floor(val[i]);
	}

	template<typename T>
	inline T _Frac(const T& val, _MST_MDET _Array_type)
	{
		static_assert(0, "::mst::math::frac() does not support arrays");
	}

}; // namespace _Details

template<typename _Ty>
inline _Ty(::mst::math::frac)(const _Ty& val)
{
	return _Details::_Frac(val, typename _Details::_Math_traits<_Ty>::math_type());
}

namespace _Details {

	template<typename T>
	inline T _Clamp(const T& val, const T& minim, const T& maxim, _MST_MDET _Scalar_type)
	{
		return (minim > val ? minim : (maxim < val ? maxim : val));
	}

	template<typename T>
	inline T _Clamp(const T& val, typename _MST_MDET _Cref_value<T>::type minim,
					typename _MST_MDET _Cref_value<T>::type maxim, _MST_MDET _Math_type)
	{
		T retval;
		for(size_t i = 0; i < T::dimensions; ++i)
		{
			retval.data()[i] = _Clamp(val.data()[i], minim, maxim, _MST_MDET _Scalar_type());

			//retval.data()[i] = (minim > val.data()[i] ? minim : (maxim < val.data()[i] ? maxim : val[i]));
		}

		return retval;
	}

	template<typename T>
	inline T _Clamp(const T& val, const T& minim, const T& maxim, _MST_MDET _Math_type)
	{
		T retval;
		for(size_t i = 0; i < T::dimensions; ++i)
		{
			//retval.data()[i] = (minim.data()[i] > val.data()[i] ? minim.data()[i] : (maxim.data()[i] < val.data()[i] ? maxim.data()[i] : val.data()[i]));
			retval.data()[i] = _Clamp(val.data()[i], minim.data()[i], maxim.data()[i], _MST_MDET _Scalar_type());
		}

		return retval;
	}

}; // namespace _Details

template<typename T>
inline T(::mst::math::clamp)(const T& val, typename _MST_MDET _Cref_value<T>::type minim, typename _MST_MDET _Cref_value<T>::type maxim)
{
	return _MST_MDET _Clamp(val, minim, maxim, typename _MST_MDET _Math_traits<T>::math_type());
}

template<typename T>
inline T(::mst::math::clamp)(const T& val, const T& minim, const T& maxim)
{
	return _MST_MDET _Clamp(val, minim, maxim, typename _MST_MDET _Math_traits<T>::math_type());
}

namespace _Details {

template<typename T>
inline typename _MST_MDET _Math_traits<T>::value_type _Average(const T& val, _MST_MDET _Array_type)
{
	typename _MST_MDET _Math_traits<T>::value_type retval = typename _MST_MDET _Cvalue<T>::create(0.0);
	for(size_t i = 0; i < _MST_MDET _Math_traits<T>::dimensions; ++i)
	{
		retval += val[i];
	}

	return retval / _Cvalue<T>::create(_Math_traits<T>::dimensions);
}

template<typename T>
inline typename _MST_MDET _Math_traits<T>::value_type _Average(const T& val, _MST_MDET _Math_type)
{
	typename _MST_MDET _Math_traits<T>::value_type retval = typename _MST_MDET _Math_traits<T>::value_type(0.0);
	for(size_t i = 0; i < _MST_MDET _Math_traits<T>::dimensions; ++i)
	{
		retval += val[i];
	}

	return retval / _Math_traits<T>::dimensions;
}

template<typename T>
inline typename _MST_MDET _Math_traits<T>::value_type _Average(const T& val, _MST_MDET _Scalar_type)
{
	// it's a single value
	return val;
}

}; // namespace _Details

template<typename T>
inline typename _MST_MDET _Math_traits<T>::value_type (::mst::math::average)(const T& val)
{
	return _MST_MDET _Average(val, typename _MST_MDET _Math_traits<T>::math_type());
}

template<typename T>
inline T(::mst::math::greatest_common_devisor)(const T& left, const T& right)
{
	T remaining;
	while(right != 0)
	{
		remaining = left % right;
		left = right;
		right = remaining;
	}
	return left;
}