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

namespace mst {

#if _MST_HAS_RVALUE_REFS
using ::std::move;
using ::std::forward;
#endif // _MST_HAS_RVALUE_REFS

	namespace _Details {

	template<typename T>
	struct _Mst_extentof
	{
		MST_STATIC_ASSERT(::std::extent<T>::value, "T must be a array object");

		static const size_t value = ::std::extent<T>::value;
	};

	inline uint32 _Hash32(const void* _First, size_t _Count)
	{
		auto _Memory = reinterpret_cast<const byte*>(_First);

		const uint32 _FNV_offset_basis = 2166136261UL;
		const uint32 _FNV_prime = 16777619UL;

		uint32 _Hash = _FNV_offset_basis;
		for(size_t _Next = 0; _Next < _Count; ++_Next)
		{	// fold in another byte
			_Hash ^= (uint32)_Memory[_Next];
			_Hash *= _FNV_prime;
		}

		return _Hash;
	}

	inline uint64 _Hash64(const void* _First, size_t _Count)
	{
		auto _Memory = reinterpret_cast<const byte*>(_First);

		const uint64 _FNV_offset_basis = 14695981039346656037ULL;
		const uint64 _FNV_prime = 1099511628211ULL;

		uint64 _Hash = _FNV_offset_basis;
		for(uint64 _Next = 0; _Next < _Count; ++_Next)
		{	// fold in another byte
			_Hash ^= (uint64)_Memory[_Next];
			_Hash *= _FNV_prime;
		}

		_Hash ^= _Hash >> 32;

		return _Hash;
	}

	inline uint32 _Hash_of32_impl(const char* _First)
	{

		size_t _N = strlen(_First);

		size_t _Begin = 0;
		while(_First[_Begin++] != '<')
		{
		}

		size_t _Begin2 = _Begin;
		while(_First[_Begin2++] != ' ')
		{
			if(_First[_Begin2] == '>')
			{
				_Begin2 = _Begin;
				break;
			}
		}

		size_t _End = _N;
		while(_First[--_End] != '>')
		{
		}

		return _Hash32(_First + _Begin2, _End - _Begin2);
	}

	inline uint64 _Hash_of64_impl(const char* _First)
	{

		size_t _N = strlen(_First);

		size_t _Begin = 0;
		while(_First[_Begin++] != '<')
		{
		}

		size_t _Begin2 = _Begin;
		while(_First[_Begin2++] != ' ')
		{
			if(_First[_Begin2] == '>')
			{
				_Begin2 = _Begin;
				break;
			}
		}

		size_t _End = _N;
		while(_First[--_End] != '>')
		{
		}

		return _Hash64(_First + _Begin2, _End - _Begin2);
	}

	template<typename T>
	inline uint32 _cdecl _Hash_of32()
	{
		static uint32 retval = ::mst::_Details::_Hash_of32_impl(__FUNCSIG__);

		return retval;
	}

	template<typename T>
	inline uint64 _cdecl _Hash_of64()
	{
		static uint64 retval = ::mst::_Details::_Hash_of64_impl(__FUNCSIG__);

		return retval;
	}

	inline ::std::string _Typename_of_impl(const char* _First)
	{

		size_t _N = strlen(_First);

		size_t _Begin = 0;
		while(_First[_Begin++] != '<')
		{
		}

		size_t _End = _N;
		while(_First[--_End] != '>')
		{
		}

		return ::std::string(_First + _Begin, _End - _Begin);
	}

	template<typename T>
	inline const char* _cdecl _Typename_of64()
	{
		static ::std::string retval = ::mst::_Details::_Typename_of_impl(__FUNCSIG__);

		return retval.c_str();
	}

	}; // namespace _Details

using std::swap;


#if _HAS_AMP
template<typename _Ty>
inline void swap(_Ty& left, _Ty& right) __MST_GPU_ONLY
{
	_Ty temp = left;
	left = right;
	right = temp;
}
#endif /* _HAS_AMP */


// zeroes objects and arrays
template<typename T>
inline void zeromem(T& val)
{
	MST_STATIC_ASSERT(!std::is_pointer<T>::value, "T = pointer");
#if _MST_HAS_TYPE_TRAITS
	MST_STATIC_ASSERT(std::is_pod<T>::value, "T = not pod");
#endif
	::std::memset(&val, 0, sizeof(T));
}

// copies objects and arrays
template<typename T>
inline void copymem(T& dst, const T& src)
{
	MST_STATIC_ASSERT(!std::is_pointer<T>::value, "T = pointer");
#if _MST_HAS_TYPE_TRAITS
	MST_STATIC_ASSERT(std::is_pod<T>::value, "T = not pod");
#endif
	::std::memcpy(&dst, &src, sizeof(T));
}

#ifndef extentof
#if _MST_HAS_TYPE_TRAITS
#define extentof(_Object) ::mst::_Details::_Mst_extentof<typename ::std:: remove_reference<decltype(_Object)>::type>::value
#else
#define extentof(_Object) (sizeof(_Object) / sizeof(_Object[0]))
#endif
#endif /* extentof */

struct compare
{
	template<typename T>
	bool less(const T& leftValue,
			  const T& rightValue) const
	{
		return leftValue < rightValue;
	}

	template<typename T>
	bool greater(const T& leftValue,
				 const T& rightValue) const
	{
		return leftValue > rightValue;
	}

	template<typename T>
	bool less_equal(const T& leftValue,
					const T& rightValue) const
	{
		return leftValue <= rightValue;
	}

	template<typename T>
	bool greater_equal(const T& leftValue,
					   const T& rightValue) const
	{
		return leftValue >= rightValue;
	}

	template<typename T>
	bool equal(const T& leftValue,
			   const T& rightValue) const
	{
		return leftValue == rightValue;
	}

	template<typename T>
	bool not_equal(const T& leftValue,
				   const T& rightValue) const
	{
		return leftValue != rightValue;
	}
};

}; // namespace mst