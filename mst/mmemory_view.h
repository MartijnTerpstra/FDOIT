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

namespace mst {

class memory_view
{
public:

	inline explicit memory_view(const void* dataPtr, size_t dataSize)
		: _Mydata(dataPtr), _Mysize(dataSize)
	{

	}

	template<typename T, size_t ArraySize>
	explicit memory_view(T (&arr)[ArraySize])
		: _Mydata(arr), _Mysize(ArraySize * sizeof(T))
	{
#if _MST_HAS_TYPE_TRAITS
		MST_STATIC_ASSERT(::std::is_trivial<T>::value, "ContainerType::value_type is not trivial");
#endif
	}

	template<typename T, size_t ArraySize>
	explicit memory_view(const T(&arr)[ArraySize])
		: _Mydata(arr), _Mysize(ArraySize * sizeof(T))
	{
#if _MST_HAS_TYPE_TRAITS
		MST_STATIC_ASSERT(::std::is_trivial<T>::value, "ContainerType::value_type is not trivial");
#endif
	}

	template<typename ContainerType>
	inline explicit memory_view(const ContainerType& container)
		: _Mydata(container.data()),
		_Mysize(container.size() * sizeof(typename ContainerType::value_type))
	{
#if _MST_HAS_TYPE_TRAITS
		MST_STATIC_ASSERT(::std::is_trivial<typename ContainerType::value_type>::value, "ContainerType::value_type is not trivial");
#endif
	}

	inline size_t size() const
	{
		return _Mysize;
	}

	inline bool empty() const
	{
		return _Mysize == 0;
	}

	inline const void* data() const
	{
		return _Mydata;
	}

	inline const byte* begin() const
	{
		return reinterpret_cast<const byte*>(_Mydata);
	}

	inline const byte* end() const
	{
		return reinterpret_cast<const byte*>(_Mydata) + _Mysize;
	}

	inline const byte* cbegin() const
	{
		return reinterpret_cast<const byte*>(_Mydata);
	}

	inline const byte* cend() const
	{
		return reinterpret_cast<const byte*>(_Mydata) + _Mysize;
	}

private:
	const void* const _Mydata;
	const size_t _Mysize;
};

}; // namespace mst