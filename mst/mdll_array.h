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
#include <mdll_malloc.h>

namespace mst {
namespace dll_safe {
	
template<typename T>
class array;

template<typename T>
class temp_array
{
	friend class mst::dll_safe::array<T>;
public:
	typedef T* pointer;
	typedef const T* cpointer;
	typedef pointer iterator;
	typedef cpointer const_iterator;
	typedef T& reference;
	typedef const T& const_reference;

public:
	inline temp_array()
	{
		_Mydata = null;
		_Mycount = 0;
	}

	inline explicit temp_array(size_t initCount)
	{
		_Init(initCount);
	}

#if _MST_HAS_RVALUE_REFS
	inline temp_array(temp_array&& other)
		: _Mydata(other._Mydata),
		_Mycount(other._Mycount)
	{
		other._Mydata = null;
	}
#endif

	inline ~temp_array()
	{
		if(_Mydata)
		{
			::mst::dll_safe::free_object(_Mydata);
		}
	}

#if _MST_HAS_RVALUE_REFS
	inline temp_array& operator = (temp_array&& other)
	{
		::std::swap(_Mydata, other._Mydata);
		::std::swap(_Mycount, other._Mycount);
	}
#endif

	T& operator [](size_t index)
	{
		return _Mydata[index];
	}

	const T& operator [](size_t index) const
	{
		return _Mydata[index];
	}

	inline void resize(size_t elemCount)
	{
		_Alloc(elemCount);
	}

	inline size_t size() const
	{
		return _Mycount;
	}

	inline iterator begin()
	{
		return _Mydata;
	}

	inline iterator end()
	{
		return _Mydata + _Mycount;
	}

	inline const_iterator begin() const
	{
		return _Mydata;
	}

	inline const_iterator end() const
	{
		return _Mydata + _Mycount;
	}

#if _MST_VARIADIC_TEMPLATE_HACK_SUPPORTED
#define MST_VARIADIC_INCLUDE <mx_dll_array_placement_new.inl>
#include <mvariadic_template.h>
#endif

private:

	void _Init(size_t elemCount)
	{
		_Mydata = null;
		_Mycount = 0;

		_Alloc(elemCount);

	}

	void _Init(size_t elemCount, const T* initList)
	{
		_Mydata = null;
		_Mycount = 0;

		_Alloc(elemCount);

		for(size_t i = 0; i < elemCount; ++i)
		{
			new (&_Mydata[i]) T(initList[i]);
		}
	}

	void _Alloc(size_t elemCount)
	{

		_Mydata = (T*)::mst::dll_safe::realloc(_Mydata, elemCount * sizeof(T));
		_Mycount = elemCount;
	}

private:
	T* _Mydata;
	size_t _Mycount;

}; // class temp_array<T>

template<typename T>
class array
{
public:
	typedef T* pointer;
	typedef const T* cpointer;
	typedef pointer iterator;
	typedef cpointer const_iterator;
	typedef T& reference;
	typedef const T& const_reference;
public:
	array()
	{
		_Mydata = null;
		_Mycount = 0;
	}

	explicit array(size_t initCount)
	{
		_Init(initCount);
	}

#if _MST_HAS_RVALUE_REFS
	inline array(array&& other)
		: _Mydata(other._Mydata),
		_Mycount(other._Mycount)
	{
		other._Mydata = null;
	}

	inline array(temp_array<T>&& other)
		: _Mydata(other._Mydata),
		_Mycount(other._Mycount)
	{
		other._Mydata = null;
	}
#endif

#if _MST_HAS_INITIALIZER_LISTS
	array(::std::initializer_list<T> initList)
	{
		_Init(initList.size(), initList.begin());
	}
#endif

	inline ~array()
	{
		if(_Mydata)
		{
			::mst::_Details::_Destroy_object_range(_Mydata, _Mydata + _Mycount);
			::mst::dll_safe::free(_Mydata);
		}
	}

	inline size_t size()
	{
		return _Mycount;
	}

	inline T* begin()
	{
		return _Mydata;
	}

	inline const T* begin() const
	{
		return _Mydata;
	}

	inline T* end()
	{
		return _Mydata + _Mycount;
	}

	inline const T* end() const
	{
		return _Mydata + _Mycount;
	}

	inline array& operator = (const array& other)
	{
		::std::swap(_Mydata, other._Mydata);
		::std::swap(_Mycount, other._Mycount);
	}

#if _HAS_RVALUE_REFERENCES
	inline array& operator = (array&& other)
	{
		::std::swap(_Mydata, other._Mydata);
		::std::swap(_Mycount, other._Mycount);
	}

	inline array& operator = (temp_array<T>&& other)
	{
		::std::swap(_Mydata, other._Mydata);
		::std::swap(_Mycount, other._Mycount);
	}
#endif

	inline T& operator [] (size_t index)
	{
		CHECK_ARR_RANGE(index, _Mycount, "index out of range");
		return _Mydata[index];
	}

	inline const T& operator [] (size_t index) const
	{
		CHECK_ARR_RANGE(index, _Mycount, "index out of range");
		return _Mydata[index];
	}

private:
	
	void _Init(size_t elemCount)
	{
		_Mydata = null;
		_Mycount = 0;

		_Alloc(elemCount);

		for(size_t i = 0; i < elemCount; ++i)
		{
			new (&_Mydata[i]) T();
		}
	}

	void _Init(size_t elemCount, const T* initList)
	{
		_Mydata = null;
		_Mycount = 0;

		_Alloc(elemCount);

		for(size_t i = 0; i < elemCount; ++i)
		{
			new (&_Mydata[i]) T(initList[i]);
		}
	}

	void _Alloc(size_t elemCount)
	{
		_Mydata = (T*)::mst::dll_safe::malloc(_Mydata, elemCount * sizeof(T));
		_Mycount = elemCount;
	}

private:
	T* _Mydata;
	size_t _Mycount;

}; // class array<T>

}; // namespace dll_safe
}; // namespace mst