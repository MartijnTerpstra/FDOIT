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

// old school breakpoints
#if _WIN32
#define _MST_BREAK __debugbreak()
#else
#error "implement breakpoint"
#endif

#if MST_DEBUGMODE || defined(MST_DEBUG_CHECKS) // for assertions

// ERRORS

#if _HAS_AMP

inline void _Mst_check_if_gpu(bool _Value)
{
	if(_Value)
	{
		::mst::logger::error("error found in GPU compatible code");
		_MST_BREAK;
	}
}

template<typename _Ty>
inline void _Mst_check_if_arg_gpu(bool _Value, const _Ty& _Arg)
{
	if(_Value)
	{
		::mst::logger::error("error found in GPU compatible code");
		_MST_BREAK;
	}
}

template<typename _Iter>
inline void _Mst_check_iter_range_gpu(_Iter _Value, _Iter _Begin, _Iter _End)
{
	if((_Value) < (_Begin) || (_Value) > (_End))
	{
		::mst::logger::error("error found in GPU compatible code");
		_MST_BREAK;
	}
}

inline void _Mst_check_arr_range_gpu(size_t _Value, size_t _Size)
{
	if((_Value) < 0 || (_Value) >= (_Size))
	{
		::mst::logger::error("error found in GPU compatible code");
		_MST_BREAK;
	}
}

template<typename _Ty>
inline void _Mst_check_value_range_gpu(_Ty _Value, _Ty _Begin, _Ty _End)
{
	if((_Value) < (_Begin) || (_Value) > (_End))
	{
		::mst::logger::error("error found in GPU compatible code");
		_MST_BREAK;
	}
}

inline void _Mst_check_if_gpu(bool _Value) __MST_GPU_ONLY
{
	/* do nothing on GPU */
}

template<typename _Ty>
inline void _Mst_check_if_arg_gpu(bool _Value, const _Ty& _Arg) __MST_GPU_ONLY
{
	/* do nothing on GPU */
}

template<typename _Iter>
inline void _Mst_check_iter_range_gpu(_Iter _Value, _Iter _Begin, _Iter _End) __MST_GPU_ONLY
{
	/* do nothing on GPU */
}

inline void _Mst_check_arr_range_gpu(size_t _Value, size_t _Size) __MST_GPU_ONLY
{
	/* do nothing on GPU */
}

template<typename _Ty>
inline void _Mst_check_value_range_gpu(_Ty _Value, _Ty _Begin, _Ty _End) __MST_GPU_ONLY
{
	/* do nothing on GPU */
}

// WARNINGS

inline void _Mst_warn_if_gpu(bool _Value)
{
	if(_Value)
	{
		::mst::logger::warning("warning found in GPU compatible code, turn on BREAK_ON_WARNING to get a break on the point");
		// warnings
#if BREAK_ON_WARNINGS
		_MST_BREAK;
#endif
	}
}

template<typename _Ty>
inline void _Mst_warn_if_arg_gpu(bool _Value, const _Ty& _Arg)
{
	if(_Value)
	{
		::mst::logger::warning("warning found in GPU compatible code, turn on BREAK_ON_WARNING to get a break on the point", _Arg);
#if BREAK_ON_WARNINGS
		_MST_BREAK;
#endif
	}
}

inline void _Mst_warn_if_gpu(bool _Value) __MST_GPU_ONLY
{
	/* do nothing on GPU */
}

template<typename _Ty>
inline void _Mst_warn_if_arg_gpu(bool _Value, const _Ty& _Arg) __MST_GPU_ONLY
{
	/* do nothing on GPU */
}

#endif

#endif /* MST_DEBUGMODE || defined(MST_DEBUG_CHECKS) */