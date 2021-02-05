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

#include <cstddef>
#include <mx_compiler.h>

#if _MST_USING_VC_COMPILER
#define MST_ALIGN(x) __declspec(align(x))
#else
#error "No alignment possible for this compiler"
#endif

#if _MST_USING_VC_COMPILER
#define MST_DECLARE_DLL_FUNCTION_GENERATE __declspec(dllexport)
#define MST_DECLARE_DLL_TYPE_GENERATE __declspec(dllexport)
#else
#error "No exporting to DLL possible for this compiler"
#endif

#ifndef MST_DECLARE_DLL_FUNCTION
#define MST_DECLARE_DLL_FUNCTION
#endif // !MST_DECLARE_DLL_FUNCTION

#ifndef MST_DECLARE_DLL_TYPE
#define MST_DECLARE_DLL_TYPE
#endif // !MST_DECLARE_DLL_TYPE

#if _MST_HAS_CONSTEXPR
#define _MST_CONSTEXPR constexpr
#else // !_MST_HAS_CONSTEXPR
#define _MST_CONSTEXPR
#endif // _MST_HAS_CONSTEXPR

#ifdef _WIN32
#define MST_DEPRECATED(newFunction) __declspec(deprecated("function is deprecated, use " \
	#newFunction " instead"))
#else
#error "MST_DEPRECATED not supported"
#endif

#ifndef MST_API
#define MST_API __fastcall
#endif // MST_API

#define _MST_ANONYMOUS_VAR_IMPL2(str1, str2) str1##str2
#define _MST_ANONYMOUS_VAR_IMPL(str1, str2) _MST_ANONYMOUS_VAR_IMPL2(str1,str2)

#ifdef __COUNTER__
#define _MST_ANONYMOUS_VAR(str) _MST_ANONYMOUS_VAR_IMPL(str, __COUNTER__)
#else
#define _MST_ANONYMOUS_VAR(str) _MST_ANONYMOUS_VAR_IMPL(str, __LINE__)
#endif

#if _MST_HAS_BUILTIN_STATIC_ASSERT

#define MST_STATIC_ASSERT static_assert

#else // !_MST_HAS_BUILTIN_STATIC_ASSERT

#define MST_STATIC_ASSERT(val, mesg) typedef char _MST_ANONYMOUS_VAR(__static_assert_t)[val]

#endif // _MST_HAS_BUILTIN_STATIC_ASSERT

#if !_MST_HAS_NATIVE_NULLPTR

// fake nullptr and std::nullptr_t
namespace std {

struct nullptr_t
{
	template<typename _Ty>
	inline operator _Ty*() const
	{
		return (_Ty*)0;
	}
};

};

static const ::std::nullptr_t nullptr = {};

#endif


#include <mtype_traits.h>

namespace mst { 
namespace _Details {

template<typename _Ty>
void _Destroy_object(_Ty*, ::std::true_type)
{
	/* do nothing, destructor is trivial */
}

template<typename _Ty>
void _Destroy_object(_Ty* _Ptr, ::std::false_type)
{
	_Ptr->~_Ty();
}

template<typename _Ty>
void _Destroy_object(_Ty* _Ptr)
{
#if _MST_HAS_TYPE_TRAITS
#if _MST_COMPILER_VER < 13
	_Destroy_object(_Ptr, typename ::std::has_trivial_destructor<_Ty>::type());
#else
	_Destroy_object(_Ptr, typename ::std::is_trivially_destructible<_Ty>::type());
#endif
#else
	_Destroy_object(_Ptr, typename ::std::is_arithmetic<_Ty>::type());
#endif
}


template<typename _Ty>
void _Destroy_object_range(_Ty* _Begin_ptr, _Ty* _Endptr, ::std::true_type)
{
	/* do nothing, destructor is trivial */
}

template<typename _Ty>
void _Destroy_object_range(_Ty* _Begin_ptr, _Ty* _Endptr, ::std::false_type)
{
	while(_Begin_ptr != _Endptr)
	{
		_Begin_ptr->~_Ty();
		++_Begin_ptr;
	}
}

template<typename _Ty>
void _Destroy_object_range(_Ty* _Begin_ptr, _Ty* _Endptr)
{
#if _MST_HAS_TYPE_TRAITS
#if _MST_COMPILER_VER < 13
	_Destroy_object_range(_Begin_ptr, _Endptr, typename ::std::has_trivial_destructor<_Ty>::type());
#else
	_Destroy_object_range(_Begin_ptr, _Endptr, typename ::std::is_trivially_destructible<_Ty>::type());
#endif
#else
	_Destroy_object_range(_Begin_ptr, _Endptr, typename ::std::is_arithmetic<_Ty>::type());
#endif
}

}; // namespace _Details
}; // namespace mst