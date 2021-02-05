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

template<typename Ty>
inline Ty (::mst::math::lerp)(const Ty& u, const Ty& v, float s) __MST_GPU
{
	return (u * (1 - s)) + (v * s);
}

template<typename Ty>
inline Ty (::mst::math::lerp)(const Ty& u, const Ty& v, const Ty& w, const float2& st) __MST_GPU
{
	return lerp(lerp(u,v, st.x), w, st.y);
}

template<typename Ty>
inline Ty (::mst::math::cubic_interp)(const Ty& pre_u, const Ty& u, const Ty& v, const Ty& post_v, float s) __MST_GPU
{
	return u + 0.5 * s*(v - pre_u + s*(2.0*pre_u - 5.0*u + 4.0*v - post_v + s*(3.0*(u - v) + post_v - pre_u)));
}

	namespace _Details {

	template<typename Ty>
	inline Ty _Reflect( const Ty& i, const Ty& n, _Details::_Math_type)
	{
		return i - 2.0 * n * n.dot(i);
	}

	}; // namespace _Details

template<typename Ty>
inline Ty (::mst::math::reflect)( const Ty& i, const Ty& n )
{
	return _Details::_Reflect(i, n, 
		typename _Details::_Math_traits<Ty>::type());
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

	template<typename _Ty>
	inline _Ty _Saturate(const _Ty& _Val, _Details::_Math_type)
	{
		_Ty retval;
		for(size_t i = 0; i < _Ty::dimensions; ++i)
		{
			retval[i] = (_Val[i] > 0.0f ? (_Val[i] < 1.0f ? _Val[i] : 1.0f) : 0.0f);
		}

		return retval;
	}

	template<typename _Ty>
	inline _Ty _Saturate(const _Ty& _Val, _Details::_Value_type)
	{
		return (_Val > (_Ty)0.0 ? (_Val < (_Ty)1.0 ? _Val : (_Ty)1.0) : (_Ty)0.0);
	}

	}; // namespace _Details

/* returns clamps all the values to the range: [0,1] */
template<typename _Ty>
inline _Ty (::mst::math::saturate)(const _Ty& val)
{
	return _Details::_Saturate(val, 
		typename _Details::_Math_traits<_Ty>::type());
}

inline float ::mst::math::smoothstep(float minim, float maxim, float val)
{
	float t = ::mst::math::saturate((val - minim)/(maxim - minim));
	return t*t*(3.0f - (2.0f*t));
}

	namespace _Details {

	template<typename _Ty>
	inline _Ty _Frac(const _Ty& val, _Details::_Math_type)
	{
		_Ty retval;
		for(size_t i = 0; i < _Ty::dimensions; ++i)
		{
			retval = val - floor(val[i]);
		}
		return retval;
	}

	template<typename _Ty>
	inline _Ty _Frac(const _Ty& val, _Details::_Value_type)
	{
		return val - floor(val[i]);
	}

	}; // namespace _Details

template<typename _Ty>
inline _Ty (::mst::math::frac)(const _Ty& val)
{
	return _Details::_Frac(val,
		typename _Details::_Math_traits<_Ty>::type());
}

	namespace _Details {

	template<typename _Ty>
	inline _Ty _Clamp(const _Ty& val, float minim, float maxim, _Details::_Math_type)
	{
		_Ty retval;
		for(size_t i = 0; i < _Ty::dimensions; ++i)
		{
			retval[i] = (minim > val[i] ? minim : (maxim < val[i] ? maxim : val[i]));
		}

		return retval;
	}

	template<typename _Ty>
	inline _Ty _Clamp(const _Ty& val, const _Ty& minim, const _Ty& maxim, _Details::_Math_type)
	{
		_Ty retval;
		for(size_t i = 0; i < _Ty::dimensions; ++i)
		{
			retval[i] = (minim[i] > val[i] ? minim[i] : (maxim[i] < val[i] ? maxim[i] : val[i]));
		}

		return retval;
	}

	template<typename _Ty>
	inline _Ty _Clamp(const _Ty& val, const _Ty& minim, const _Ty& maxim, _Details::_Value_type)
	{
		return (minim > val ? minim : (maxim < val ? maxim : val));
	}

	}; // namespace _Details

template<typename _Ty>
inline _Ty (::mst::math::clamp)(const _Ty& val, float minim, float maxim)
{
	return _Details::_Clamp(val, minim, maxim, 
		typename _Details::_Math_traits<_Ty>::type());
}

template<typename _Ty>
inline _Ty (::mst::math::clamp)(const _Ty& val, const _Ty& minim, const _Ty& maxim)
{
	return _Clamp(val, minim, maxim, 
		typename _Details::_Math_traits<_Ty>::type());
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


#endif // __INSIDE_MMATH_H__