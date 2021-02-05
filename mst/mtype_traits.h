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

#include <limits.h>

#if _MST_HAS_TYPE_TRAITS

#include <type_traits>

#else

// fake typetraits

#define _MST_MANUAL_STD_TYPE_TRAITS 1

namespace std {

template<typename _Ty, _Ty _Val>
struct integral_constant
{
	typedef _Ty value_type;
	typedef integral_constant<_Ty, _Val> type;
	static const _Ty value = _Val;
}; // struct integral_constant

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


template <typename _Ty> struct is_pointer : public integral_constant<bool, false>
{
};

template <typename _Ty> struct is_pointer<_Ty*> : public integral_constant<bool, true>
{
};

template <typename _Ty> struct is_pointer<_Ty* const> : public integral_constant<bool, true>
{
};

template<typename _Ty>
struct is_const : public integral_constant<bool, false>
{};

template<typename _Ty>
struct is_const<const _Ty> : public integral_constant<bool, true>
{};

template<typename _Ty, size_t _Nx>
struct is_const<_Ty[_Nx]> : public integral_constant<bool, false>
{};

template<typename _Ty, size_t _Nx>
struct is_const<const _Ty[_Nx]> : public integral_constant<bool, true>
{};

// is_pod
template<typename _Ty>
struct is_pod : public integral_constant<bool, false>
{};

template<>
struct is_pod<signed int> : public integral_constant<bool, true>
{};

template<>
struct is_pod<signed long> : public integral_constant<bool, true>
{};

template<>
struct is_pod<signed long long> : public integral_constant<bool, true>
{};

template<>
struct is_pod<unsigned int> : public integral_constant<bool, true>
{};

template<>
struct is_pod<unsigned long> : public integral_constant<bool, true>
{};

template<>
struct is_pod<unsigned long long> : public integral_constant<bool, true>
{};

template<>
struct is_pod<float> : public integral_constant<bool, true>
{};

template<>
struct is_pod<double> : public integral_constant<bool, true>
{};

template<>
struct is_pod<long double> : public integral_constant<bool, true>
{};

template<>
struct is_pod<signed char> : public integral_constant<bool, true>
{};

template<>
struct is_pod<unsigned char> : public integral_constant<bool, true>
{};

template<>
struct is_pod<signed short> : public integral_constant<bool, true>
{};

template<>
struct is_pod<unsigned short> : public integral_constant<bool, true>
{};

// enable_if
template<bool _Value, typename _Ty = void>
struct enable_if {};

template<typename T>
struct remove_pointer
{
	typedef T type;
};

template<typename T>
struct remove_pointer<T*>
{
	typedef T type;
};

template<typename T>
struct remove_const
{
	typedef T type;
};

template<typename T>
struct remove_const < const T >
{
	typedef T type;
};

template<typename _Ty>
struct enable_if<true, _Ty>
{
	typedef _Ty type;
};

// is_array
template<typename _Ty>
struct is_array : public ::std::false_type
{};

template<typename _Ty>
struct is_array<_Ty[]> : public ::std::true_type
{};

template<typename _Ty, size_t _N>
struct is_array<_Ty[_N]> : public ::std::true_type
{};

// extent
template<typename _Ty>
struct extent : public ::std::integral_constant<size_t, 0>
{};

template<typename _Ty>
struct extent<_Ty[]> : public ::std::integral_constant<size_t, 0>
{};

template<typename _Ty, size_t _N>
struct extent<_Ty[_N]> : public ::std::integral_constant<size_t, _N>
{};

// is_same
template<typename _Ty1, typename _Ty2>
struct is_same : public ::std::false_type
{};

template<typename _Ty>
struct is_same<_Ty, _Ty> : public ::std::true_type
{};

// remove_reference
template<typename _Ty>
struct remove_reference
{
	typedef _Ty type;
};

template<typename _Ty>
struct remove_reference<_Ty&>
{
	typedef _Ty type;
};

// alignment of
template<typename _Ty>
struct _AlignmentTestStruct
{
	_Ty value1;
	char value2;
	_Ty value3;
};

#define _ALIGNMENT_OF(ty) (sizeof(_AlignmentTestStruct<ty>) - 2 * sizeof(ty))

template<typename _Ty>
struct alignment_of : public integral_constant<size_t, _ALIGNMENT_OF(_Ty)>
{};

template<typename _Ty>
struct alignment_of<_Ty&> : public integral_constant<size_t, _ALIGNMENT_OF(_Ty*)>
{};

#define _FITS(ty) _Align == _ALIGNMENT_OF(ty)
#define _NEXT_ALIGN(ty) \
	typedef typename _Aligned<_Len, _Align, ty, _FITS(ty)>::_Type _Type

template<class _Ty, size_t _Len> union _Align_type
	{	// union with size _Len bytes and alignment of _Ty
	_Ty _Val;
	char _Pad[_Len];
	};

template<size_t _Len, size_t _Align, class _Ty, bool _Ok>
	struct _Aligned;

template<size_t _Len, size_t _Align, class _Ty>
	struct _Aligned<_Len, _Align, _Ty, true>
	{	// define type with size _Len and alignment _Ty
	typedef _Align_type<_Ty, _Len> _Type;
	};

template<size_t _Len, size_t _Align>
	struct _Aligned<_Len, _Align, long, false>
	{	// define type with size _Len and alignment _Ty
	typedef _Align_type<double, _Len> _Type;
	};

template<size_t _Len, size_t _Align>
	struct _Aligned<_Len, _Align, int, false>
	{	// define type with size _Len and alignment _Ty
	_NEXT_ALIGN(long);
	};

template<size_t _Len, size_t _Align>
	struct _Aligned<_Len, _Align, short, false>
	{	// define type with size _Len and alignment _Ty
	_NEXT_ALIGN(int);
	};

template<size_t _Len, size_t _Align>
	struct _Aligned<_Len, _Align, char, false>
	{	// define type with size _Len and alignment _Ty
	_NEXT_ALIGN(short);
	};

template<size_t _Len, size_t _Align>
	struct aligned_storage
	{	// define type with size _Len and alignment _Ty
	typedef typename _Aligned<_Len, _Align, char, _FITS(char)>::_Type type;
	};

#undef _FITS
#undef _NEXT_ALIGN
#undef _ALIGNMENT_OF

// is_integral
template<typename _Ty>
struct is_integral : public integral_constant<bool, false>
{};

template<>
struct is_integral<int> : public integral_constant<bool, true>
{};

template<>
struct is_integral<unsigned int> : public integral_constant<bool, true>
{};

template<>
struct is_integral<short> : public integral_constant<bool, true>
{};

template<>
struct is_integral<unsigned short> : public integral_constant<bool, true>
{};

template<>
struct is_integral<char> : public integral_constant<bool, true>
{};

template<>
struct is_integral<signed char> : public integral_constant<bool, true>
{};

template<>
struct is_integral<unsigned char> : public integral_constant<bool, true>
{};

template<>
struct is_integral<long> : public integral_constant<bool, true>
{};

template<>
struct is_integral<unsigned long> : public integral_constant<bool, true>
{};

template<>
struct is_integral<long long> : public integral_constant<bool, true>
{};

template<>
struct is_integral<unsigned long long> : public integral_constant<bool, true>
{};

// is_floating_point
template<typename _Ty>
struct is_floating_point : public integral_constant<bool, false>
{};

template<>
struct is_floating_point<float> : public integral_constant<bool, true>
{};

template<>
struct is_floating_point<double> : public integral_constant<bool, true>
{};

template<>
struct is_floating_point<long double> : public integral_constant<bool, true>
{};

// is_arithmetic
template<typename _Ty>
struct is_arithmetic : public integral_constant<bool, is_floating_point<_Ty>::value || is_integral<_Ty>::value>
{};

template<typename _Ty>
struct is_unsigned : public ::std::false_type
{};

template<>
struct is_unsigned<unsigned int> : public ::std::true_type
{};

template<>
struct is_unsigned<unsigned char> : public ::std::true_type
{};

template<>
struct is_unsigned<unsigned short> : public ::std::true_type
{};

template<>
struct is_unsigned<unsigned long> : public ::std::true_type
{};

template<>
struct is_unsigned<unsigned long long> : public ::std::true_type
{};

template<typename _Ty>
struct is_signed : public ::std::false_type
{};

template<>
struct is_signed<int> : public ::std::true_type
{};

template<>
struct is_signed<char> : public ::std::true_type
{};

template<>
struct is_signed<short> : public ::std::true_type
{};

template<>
struct is_signed<long> : public ::std::true_type
{};

template<>
struct is_signed<long long> : public ::std::true_type
{};

template<>
struct is_signed<float> : public ::std::true_type
{};

template<>
struct is_signed<double> : public ::std::true_type
{};

template<>
struct is_signed<long double> : public ::std::true_type
{};

template<>
struct is_signed<signed char> : public ::std::true_type
{};

}; // namespace std

#endif

namespace mst {

	template<typename T>
	struct numeric_traits
	{};

	template<>
	struct numeric_traits<char>
	{
		typedef char value_type;
		typedef char& reference_type;
		static const char zero = 0;
		static const char max = CHAR_MAX;
		static const char min = CHAR_MIN;
		static const size_t bits = 8;
	};

	template<>
	struct numeric_traits<signed char>
	{
		typedef signed char value_type;
		typedef signed char& reference_type;
		static const signed char zero = 0i8;
		static const signed char max = SCHAR_MAX;
		static const signed char min = SCHAR_MIN;
		static const size_t bits = 8;
	};

	template<>
	struct numeric_traits<unsigned char>
	{
		typedef unsigned char value_type;
		typedef unsigned char& reference_type;
		static const unsigned char zero = 0ui8;
		static const unsigned char max = UCHAR_MAX;
		static const unsigned char min = 0ui8;
		static const size_t bits = 8;
	};

	template<>
	struct numeric_traits<short>
	{
		typedef short value_type;
		typedef short& reference_type;
		static const short zero = 0i16;
		static const short max = SHRT_MAX;
		static const short min = SHRT_MIN;
		static const size_t bits = 16;
	};

	template<>
	struct numeric_traits<unsigned short>
	{
		typedef unsigned short value_type;
		typedef unsigned short& reference_type;
		static const unsigned short zero = 0ui16;
		static const unsigned short max = USHRT_MAX;
		static const unsigned short min = 0ui16;
		static const size_t bits = 16;
	};

	template<>
	struct numeric_traits<int>
	{
		typedef int value_type;
		typedef int& reference_type;
		static const int zero = 0i32;
		static const int max = INT_MAX;
		static const int min = INT_MIN;
		static const size_t bits = 32;
	};

	template<>
	struct numeric_traits<unsigned int>
	{
		typedef unsigned int value_type;
		typedef unsigned int& reference_type;
		static const unsigned int zero = 0ui32;
		static const unsigned int max = UINT_MAX;
		static const unsigned int min = 0ui32;
		static const size_t bits = 32;
	};

	template<>
	struct numeric_traits<long>
	{
		typedef long value_type;
		typedef long& reference_type;
		static const long zero = 0L;
		static const long max = LONG_MAX;
		static const long min = LONG_MIN;
		static const size_t bits = 32;
	};

	template<>
	struct numeric_traits<unsigned long>
	{
		typedef unsigned long value_type;
		typedef unsigned long& reference_type;
		static const unsigned long zero = 0UL;
		static const unsigned long max = ULONG_MAX;
		static const unsigned long min = 0UL;
		static const size_t bits = 32;
	};

	template<>
	struct numeric_traits<long long>
	{
		typedef long long value_type;
		typedef long long& reference_type;
		static const long long zero = 0i64;
		static const long long max = LLONG_MAX;
		static const long long min = LLONG_MIN;
		static const size_t bits = 64;
	};

	template<>
	struct numeric_traits<unsigned long long>
	{
		typedef unsigned long long value_type;
		typedef unsigned long long& reference_type;
		static const unsigned long long zero = 0ui64;
		static const unsigned long long max = ULLONG_MAX;
		static const unsigned long long min = 0ui64;
		static const size_t bits = 64;
	};

};

#if _MST_COMPILER_VER >= 12

#define _MST_OPERATOR_BOOL explicit operator bool
#define _MST_CONVERTIBLE_TO_TRUE(_Type) true
#define _MST_TYPEDEF_BOOLEAN_TYPE(_Type)

#else

namespace mst { namespace _Details {

#define _MST_OPERATOR_BOOL operator _Mst_boolean_type

template<typename _Type>
struct _Mst_boolean_struct
{
	int _Unused;
};

#define _MST_CONVERTIBLE_TO_TRUE(_Type)  & ::mst::_Details::_Mst_boolean_struct<_Type>::_Unused

#define _MST_TYPEDEF_BOOLEAN_TYPE(_Type) \
	typedef int ::mst::_Details::_Mst_boolean_struct<_Type>::* _Mst_boolean_type

}; }; // namespace mst::_Details

#endif

#include <mx_is_pointer_to_const.h>
#include <mx_type_traits.h>
#include <mx_pointer.h>
#include <mx_func_type_traits.h>