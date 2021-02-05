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

#include <yvals.h>

#if _MSC_VER

#define _MST_USING_VC_COMPILER 1

#define _IS_VC13_COMPILER	0
#define _IS_VC12_COMPILER	0
#define _IS_VC11_COMPILER	0
#define _IS_VC10_COMPILER	0
#define _IS_VC9_COMPILER	0

#if _HAS_CPP17 || _CPPLIB_VER >= 650

#undef _IS_VC13_COMPILER
#define _IS_VC13_COMPILER 1
#define _MST_COMPILER_VER 13

#elif _HAS_VARIADIC_TEMPLATES || _CPPLIB_VER >= 610

#undef _IS_VC12_COMPILER
#define _IS_VC12_COMPILER 1
#define _MST_COMPILER_VER 12

#elif _CPPLIB_VER >= 540

#undef _IS_VC11_COMPILER
#define _IS_VC11_COMPILER 1
#define _MST_COMPILER_VER 11

#elif (_HAS_CPP0X && _HAS_TR1) || _CPPLIB_VER >= 520

#undef _IS_VC10_COMPILER
#define _IS_VC10_COMPILER 1
#define _MST_COMPILER_VER 10

#else

#undef _IS_VC9_COMPILER
#define _IS_VC9_COMPILER 1
#define _MST_COMPILER_VER 9

#endif

#if _MST_COMPILER_VER >= 13
#define _MST_HAS_CONSTEXPR 1
#endif

#if _MST_COMPILER_VER >= 13
#define _MST_NOEXCEPT	noexcept
#define _MST_NOEXCEPT_OP(x)	noexcept(x)
#else
#define _MST_NOEXCEPT	throw ()
#define _MST_NOEXCEPT_OP(x)
#endif

#if _MST_COMPILER_VER >= 13
#define _MST_HAS_THREAD_LOCAL 1
#endif

#if _MST_COMPILER_VER >= 12
#define _MST_HAS_INITIALIZER_LISTS 1
#endif

#if _MST_COMPILER_VER >= 12
#define _MST_HAS_VARIADIC_TEMPLATES 1
#endif

#if _MST_COMPILER_VER >= 12
#define _MST_HAS_TEMPLATE_ALIASES 1
#endif

#if _MST_COMPILER_VER >= 12
#define _MST_HAS_DEFAULT_DELETE 1
#endif

#if _MST_COMPILER_VER >= 12
#define _MST_HAS_DEFAULT_TEMPLATE_ARGS_OUTSIDE_CLASS 1
#endif

#if _MST_COMPILER_VER >= 11
#define _MST_HAS_RANGE_BASED_FORS 1
#endif

#if _MST_COMPILER_VER >= 11
#define _MST_HAS_STL_THREADING_V1 1
#define _MST_HAS_STL_CHRONO 1
#endif

#if _MST_COMPILER_VER >= 10
#define _MST_HAS_LAMBDAS 1
#endif

#if _MST_COMPILER_VER >= 10
#define _MST_HAS_DECLTYPE 1
#endif

#if _MST_COMPILER_VER >= 10
#define _MST_HAS_AUTO 1
#endif

#if _MST_COMPILER_VER >= 10
#define _MST_HAS_TYPE_TRAITS 1
#endif

#if _MST_COMPILER_VER >= 10
#define _MST_HAS_RVALUE_REFS 1
#endif

#if _MST_COMPILER_VER >= 10
#define _MST_HAS_BUILTIN_STATIC_ASSERT 1
#endif

#if _MST_HAS_RVALUE_REFS
#define _MST_VARIADIC_TEMPLATE_HACK_SUPPORTED 1
#endif

#if _NATIVE_NULLPTR_SUPPORTED
#define _MST_HAS_NATIVE_NULLPTR 1
#endif

#define _MST_UNUSED(x) ((void)x)

// backwards compatibility
#if _MST_COMPILER_VER == 9
#define _UNSAFE_CHAR_TRAITS 1
#endif


#if _MST_COMPILER_VER < 11
#define final
#endif

#if _MST_COMPILER_VER < 11
#define override
#define _MST_OVERRIDE
#else
#define _MST_OVERRIDE override
#endif

#if _M_IX86
#define _MST_HAS_X86 1
#endif

#if _M_X64
#define _MST_HAS_X64 1
#define _MST_HAS_64BIT 1
#endif

#ifndef _MST_LIB_COMPILE

#if _MST_COMPILER_VER == 9
#define _MST_VC_VERSION "2008"
#elif _MST_COMPILER_VER == 10
#define _MST_VC_VERSION "2010"
#elif _MST_COMPILER_VER == 11
#define _MST_VC_VERSION "2012"
#elif _MST_COMPILER_VER == 12
#define _MST_VC_VERSION "2013"
#elif _MST_COMPILER_VER == 13
#define _MST_VC_VERSION "2015"
#else
#error "unsupported visual studio version"
#endif

#if _MST_HAS_X86
#define _MST_VC_PLATFORM "_Win32"
#elif _MST_HAS_X64
#define _MST_VC_PLATFORM "_x64"
#else
#error "unsupported platform architecture"
#endif

#if _DEBUG
#define _MST_VC_DEBUG "_d"
#else
#define _MST_VC_DEBUG
#endif

#pragma comment(lib, "mst" _MST_VC_VERSION _MST_VC_PLATFORM _MST_VC_DEBUG ".lib")

#endif // _MST_LIB_COMPILE

#else

#error "compiler not supported"

#endif // MSC_VER