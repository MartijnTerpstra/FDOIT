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

#ifndef MCOMMON_H
#define MCOMMON_H

#include <mcore.h>
#include <mdebug.h>
#include <mmemory_view.h>
#include <mx_cast.h>
#include <mx_foreach.h>
#include <mx_common.h>

namespace mst {

class non_copyable
{
protected:
	non_copyable() {}
	~non_copyable() {}
private:
	non_copyable(const non_copyable&)
	{
		ERROR_MESG("cannot copy this class");
		_MST_BREAK;
	}
	non_copyable& operator = (const non_copyable&)
	{
		ERROR_MESG("cannot copy this class");
		_MST_BREAK;
	}
}; // class non_copyable

// returns the hash of the class
template<typename T>
inline uint32 _cdecl hash_of()
{
	return ::mst::_Details::_Hash_of32<T>();
}

template<typename T>
inline uint64 _cdecl hash_of64()
{
	return ::mst::_Details::_Hash_of64<T>();
}

inline uint32 hash32(const memory_view& memory)
{
	return ::mst::_Details::_Hash32(memory.data(), memory.size());
}

inline uint32 hash32(const char* cString)
{
	return ::mst::_Details::_Hash32(cString, strlen(cString));
}

inline uint32 hash32(const ::std::string& stdString)
{
	return ::mst::_Details::_Hash32(stdString.data(), stdString.length());
}

inline uint32 hash32(const ::std::wstring& stdString)
{
	return ::mst::_Details::_Hash32(stdString.data(), stdString.length());
}

#ifdef _MDLL_STRING_H
template<typename T>
inline uint32 hash32(const ::mst::dll_safe::string<T>& dllString)
{
	return ::mst::_Details::_Hash32(dllString.data(), dllString.length());
}
#endif

inline uint64 hash64(const memory_view& memory)
{
	return ::mst::_Details::_Hash64(memory.data(), memory.size());
}

inline uint64 hash64(const char* cString)
{
	return ::mst::_Details::_Hash64(cString, strlen(cString));
}

inline uint64 hash64(const ::std::string& stdString)
{
	return ::mst::_Details::_Hash64(stdString.data(), stdString.length());
}

inline uint64 hash64(const ::std::wstring& stdString)
{
	return ::mst::_Details::_Hash64(stdString.data(), stdString.length());
}

#ifdef _MDLL_STRING_H
template<typename T>
inline uint64 hash64(const ::mst::dll_safe::string<T>& dllString)
{
	return ::mst::_Details::_Hash64(dllString.data(), dllString.length());
}
#endif

template<typename T>
inline const char* typename_of()
{
	return ::mst::_Details::_Typename_of64<T>();
}

#if _MST_VARIADIC_TEMPLATE_HACK_SUPPORTED
#include <mx_printf_once.h>
#define MST_VARIADIC_INCLUDE <mx_printf.h>
#include <mvariadic_template.h>
#endif



#if _MST_HAS_RANGE_BASED_FORS

#define mst_foreach(iterator, container) for(iterator : container)

#elif(_MST_HAS_AUTO) //!_MST_HAS_RANGE_BASED_FOR_LOOP

#define mst_foreach(iterator, container) for(auto __iter = begin(container); __iter != end(container); ++__iter) if(bool __continue = true) for(iterator = *__iter; __continue; __continue = false)

#else // fallback

#define mst_foreach(iterator, container) \
if(const ::mst::_Details::_Foreach_iter_wrapper& _Begin = ::mst::_Details::_Foreach_get_begin(container)) \
if(const ::mst::_Details::_Foreach_iter_wrapper& _End = ::mst::_Details::_Foreach_get_end(container)) \
	for(; ::mst::_Details::_Foreach_not_done(_Begin, _End, container); ::mst::_Details::_Foreach_increment(_Begin, container)) \
		if(bool __continue = true) \
		for(iterator = ::mst::_Details::_Foreach_get_value(_Begin, container); __continue; __continue = false)

#endif


#if _MST_HAS_RVALUE_REFS

template<typename T, typename V>
T cast_static(V&& _Val)
{
	return ::mst::_Details::_Cast_static<T>(::std::forward<V>(_Val), 
		typename ::mst::_Details::_Mst_cast_traits<T, ::std:: remove_reference<V>::type>::tag());
}

template<typename T, typename V>
T cast_dynamic(V&& _Val)
{
	return ::mst::_Details::_Cast_dynamic<T>(::std::forward<V>(_Val), 
		typename ::mst::_Details::_Mst_cast_traits<T, ::std:: remove_reference<V>::type>::tag());
}

template<typename T, typename V>
T cast_reinterpret(V&& _Val)
{
	return ::mst::_Details::_Cast_reinterpret<T>(::std::forward<V>(_Val), 
		typename ::mst::_Details::_Mst_cast_traits<T, ::std:: remove_reference<V>::type>::tag());
}

template<typename T, typename V>
T cast_const(V&& _Val)
{
	return ::mst::_Details::_Cast_const<T>(::std::forward<V>(_Val),
		typename ::mst::_Details::_Mst_cast_traits<T, ::std:: remove_reference<V>::type>::tag());
}

#else // !_MST_HAS_RVALUE_REFS

template<typename T, typename V>
T cast_static(const V& _Val)
{
	return ::mst::_Details::_Cast_static<T>(_Val,
		typename ::mst::_Details::_Mst_cast_traits<T, ::std:: remove_reference<V>::type>::tag());
}

template<typename T, typename V>
T cast_dynamic(const V& _Val)
{
	return ::mst::_Details::_Cast_dynamic<T>(_Val,
		typename ::mst::_Details::_Mst_cast_traits<T, ::std:: remove_reference<V>::type>::tag());
}

template<typename T, typename V>
T cast_reinterpret(const V& _Val)
{
	return ::mst::_Details::_Cast_reinterpret<T>(_Val,
		typename ::mst::_Details::_Mst_cast_traits<T, ::std:: remove_reference<V>::type>::tag());
}

template<typename T, typename V>
T cast_const(const V& _Val)
{
	return ::mst::_Details::_Cast_const<T>(_Val,
		typename ::mst::_Details::_Mst_cast_traits<T, ::std:: remove_reference<V>::type>::tag());
}

#endif // _MST_HAS_RVALUE_REFS

}; // namespace mst

#endif /* MCOMMON_H */