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

#include <mcore.h>
#include <mx_flag.h>
#include <mflag_traits.h>

#if _MST_HAS_INITIALIZER_LISTS
#include <initializer_list>
#endif

namespace mst {

template<typename T, typename FlagTraits = flag_traits<T>>
class flag
{
	MST_STATIC_ASSERT(::std::is_integral<typename FlagTraits::storage_type>::value, "FlagType must be integral");
	static const bool _Preshifted = FlagTraits::preshifted;
public:

	inline flag()
	: _Myflags(FlagTraits::init_value)
	{}

	inline flag(::std::nullptr_t)
		: _Myflags(FlagTraits::init_value)
	{}

	inline flag(T arg0)
		: _Myflags(FlagTraits::to_storage_type(arg0))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(1, arg0);
	}

	inline flag(T arg0, T arg1)
		: _Myflags(FlagTraits::to_storage_type(arg0 ) | FlagTraits::to_storage_type(arg1))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(2, arg0, arg1);
	}

	inline flag(T arg0, T arg1, T arg2)
		: _Myflags(FlagTraits::to_storage_type(arg0 ) | FlagTraits::to_storage_type(arg1 ) | FlagTraits::to_storage_type(arg2))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(3, arg0, arg1, arg2);
	}

	inline flag(T arg0, T arg1, T arg2, T arg3)
		: _Myflags(FlagTraits::to_storage_type(arg0 ) | FlagTraits::to_storage_type(arg1 ) | FlagTraits::to_storage_type(arg2 ) | FlagTraits::to_storage_type(arg3))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(4, arg0, arg1, arg2, arg3);
	}

	inline flag(T arg0, T arg1, T arg2, T arg3, T arg4)
		: _Myflags(FlagTraits::to_storage_type(arg0 ) | FlagTraits::to_storage_type(arg1 ) | FlagTraits::to_storage_type(arg2 ) | FlagTraits::to_storage_type(arg3 ) | FlagTraits::to_storage_type(arg4))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(5, arg0, arg1, arg2, arg3, arg4);
	}

	inline flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5)
		: _Myflags(FlagTraits::to_storage_type(arg0 ) | FlagTraits::to_storage_type(arg1 ) | FlagTraits::to_storage_type(arg2 ) | FlagTraits::to_storage_type(arg3 ) | FlagTraits::to_storage_type(arg4 ) | FlagTraits::to_storage_type(arg5))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(6, arg0, arg1, arg2, arg3, arg4, arg5);
	}

	inline flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6)
		: _Myflags(FlagTraits::to_storage_type(arg0 ) | FlagTraits::to_storage_type(arg1 ) | FlagTraits::to_storage_type(arg2 ) | FlagTraits::to_storage_type(arg3 ) | FlagTraits::to_storage_type(arg4 ) | FlagTraits::to_storage_type(arg5 ) | FlagTraits::to_storage_type(arg6))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(7, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	}

	inline flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6, T arg7)
		: _Myflags(FlagTraits::to_storage_type(arg0 ) | FlagTraits::to_storage_type(arg1 ) | FlagTraits::to_storage_type(arg2 ) | FlagTraits::to_storage_type(arg3 ) | FlagTraits::to_storage_type(arg4 ) | FlagTraits::to_storage_type(arg5 ) | FlagTraits::to_storage_type(arg6 ) | FlagTraits::to_storage_type(arg7))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(8, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}

	inline flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6, T arg7, T arg8)
		: _Myflags(FlagTraits::to_storage_type(arg0 ) | FlagTraits::to_storage_type(arg1 ) | FlagTraits::to_storage_type(arg2 ) | FlagTraits::to_storage_type(arg3 ) | FlagTraits::to_storage_type(arg4 ) | FlagTraits::to_storage_type(arg5 ) | FlagTraits::to_storage_type(arg6 ) | FlagTraits::to_storage_type(arg7 ) | FlagTraits::to_storage_type(arg8))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(9, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	}

	inline flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6, T arg7, T arg8, T arg9)
		: _Myflags(FlagTraits::to_storage_type(arg0) | FlagTraits::to_storage_type(arg1) | FlagTraits::to_storage_type(arg2) | FlagTraits::to_storage_type(arg3) | FlagTraits::to_storage_type(arg4) | FlagTraits::to_storage_type(arg5) | FlagTraits::to_storage_type(arg6) | FlagTraits::to_storage_type(arg7) | FlagTraits::to_storage_type(arg8) | FlagTraits::to_storage_type(arg9))
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(10, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	}

#if _MST_HAS_INITIALIZER_LISTS
	inline flag(std::initializer_list<T> initList)
		: _Myflags(0)
	{
		for(auto it : initList)
		{
			::mst::_Details::_Check_flags<FlagTraits>(it);
			_Myflags |= 1 << it;
		}
	}
#endif

	inline typename FlagTraits::storage_type get() const
	{
		return _Myflags;
	}

	inline bool is_enabled(T enumFlag) const
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(1, enumFlag);
		return (_Myflags & FlagTraits::to_storage_type(enumFlag)) == FlagTraits::to_storage_type(enumFlag);
	}

	inline void enable(T enumFlag)
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(1, enumFlag);
		_Myflags |= FlagTraits::to_storage_type(enumFlag);
	}

	inline void disable(T enumFlag)
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(1, enumFlag);
		_Myflags &= ~FlagTraits::to_storage_type(enumFlag);
	}

	inline void toggle(T enumFlag)
	{
		::mst::_Details::_Check_flags<FlagTraits, T>(1, enumFlag);
		_Myflags ^= FlagTraits::to_storage_type(enumFlag);
	}

private:
	typename FlagTraits::storage_type _Myflags;
}; // class flag

template<typename T>
inline flag<T> make_flag(T arg0)
{
	return flag<T>(arg0);
}

template<typename T>
inline flag<T> make_flag(T arg0, T arg1)
{
	return flag<T>(arg0, arg1);
}

template<typename T>
inline flag<T> make_flag(T arg0, T arg1, T arg2)
{
	return flag<T>(arg0, arg1, arg2);
}

template<typename T>
inline flag<T> make_flag(T arg0, T arg1, T arg2, T arg3)
{
	return flag<T>(arg0, arg1, arg2, arg3);
}

template<typename T>
inline flag<T> make_flag(T arg0, T arg1, T arg2, T arg3, T arg4)
{
	return flag<T>(arg0, arg1, arg2, arg3, arg4);
}

template<typename T>
inline flag<T> make_flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5)
{
	return flag<T>(arg0, arg1, arg2, arg3, arg4, arg5);
}

template<typename T>
inline flag<T> make_flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6)
{
	return flag<T>(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

template<typename T>
inline flag<T> make_flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6, T arg7)
{
	return flag<T>(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

template<typename T>
inline flag<T> make_flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6, T arg7, T arg8)
{
	return flag<T>(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

template<typename T>
inline flag<T> make_flag(T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6, T arg7, T arg8, T arg9)
{
	return 	flag<T>(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

}; // namespace mst