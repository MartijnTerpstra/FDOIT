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
#include <mdebug.h>
#include <mx_array_view.h>

namespace mst {

template<typename T>
class array_view
{
public:

	typedef ::mst::_Details::_Array_view_iterator<T> iterator;

	array_view(const array_view& other)
		: _Mybase(other._Mybase)
	{
	}

	template<typename T2>
	array_view(const T2* ptr, size_t count)
	{
		::mst::_Details::_Array_view_ptr_size<T, T2>::_Init(_Mybase, ptr, count);
	}

	template<typename T2>
	array_view(const T2& value)
	{
		::mst::_Details::_Array_view_ptr_size<T, T2>::_Init(_Mybase, &value, 1);
	}

	template<typename T2, size_t ArraySize>
	array_view(const T2 (&arr)[ArraySize])
	{
		::mst::_Details::_Array_view_ptr_size<T, T2>::_Init(_Mybase, arr, ArraySize);
	}

	template<typename T2, size_t ArraySize>
	array_view(T(&arr)[ArraySize])
	{
		::mst::_Details::_Array_view_ptr_size<T, T2>::_Init(_Mybase, arr, ArraySize);
	}

	template<typename T2, typename Allocator>
	array_view(const ::std::vector<T2, Allocator>& container)
	{
		::mst::_Details::_Array_view_container<T, ::std::vector<T2, Allocator>>::_Init(_Mybase, container);
	}

	size_t size() const
	{
		return _Mybase._Mysize;
	}

	bool empty() const
	{
		return _Mybase._Mysize == 0;
	}

	const T& operator [](size_t index) const
	{
		CHECK_ARR_RANGE(index, _Mybase._Mysize, "index out of range");
		return _Mybase._Get_object_func(&_Mybase, index);
	}
	
	iterator begin() const
	{
		return iterator(&_Mybase, 0);
	}

	iterator end() const
	{
		return iterator(&_Mybase, _Mybase._Mysize);
	}

	iterator cbegin() const
	{
		return iterator(&_Mybase, 0);
	}

	iterator cend() const
	{
		return iterator(&_Mybase, _Mybase._Mysize);
	}
	
private:
	::mst::_Details::_Array_view_base<T> _Mybase;

}; // class array_view

}; // namespace mst
