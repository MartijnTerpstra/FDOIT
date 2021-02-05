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
#include <iterator>
#include <mx_ranges.h>

namespace mst {

template<typename T>
class iterator_range
{
public:
	inline iterator_range(T newBegin, T newEnd)
		: _Mybegin(newBegin),
		_Myend(newEnd)
	{

	}

	
	T begin() const
	{
		return _Mybegin;
	}

	T end() const
	{
		return _Myend;
	}
	

private:
	T _Mybegin, _Myend;
};

template<typename T>
T begin(const iterator_range<T>& rangePair)
{
	return rangePair.begin();
}

template<typename T>
T end(const iterator_range<T>& rangePair)
{
	return rangePair.begin();
}

#if _MST_HAS_DECLTYPE && _MST_HAS_AUTO
	
template<class Container>
inline auto range(Container& container) -> iterator_range<decltype(container.begin())>
{	// get beginning of sequence
	return iterator_range<decltype(container.begin())>(container.begin(), container.end());
}

template<class Container>
inline auto range(const Container& container) -> iterator_range<decltype(container.begin())>
{	// get beginning of sequence
	return iterator_range<decltype(container.begin())>(container.begin(), container.end());
}

template<class Container>
inline auto crange(Container& container) -> iterator_range<decltype(container.cbegin())>
{	// get beginning of sequence
	return iterator_range<decltype(container.cbegin())>(container.cbegin(), container.cend());
}

template<class Container>
inline auto crange(const Container& container) -> iterator_range<decltype(container.cbegin())>
{	// get beginning of sequence
	return iterator_range<decltype(container.cbegin())>(container.cbegin(), container.cend());
}

#else
	
template<class Container>
inline iterator_range<typename Container::iterator> range(Container& container)
{	// get beginning of sequence
	return iterator_range<typename Container::iterator>(container.begin(), container.end());
}

template<class Container>
inline iterator_range<typename Container::const_iterator> range(const Container& container)
{	// get beginning of sequence
	return iterator_range<typename Container::const_iterator>(container.begin(), container.end());
}

template<class Container>
inline iterator_range<typename Container::const_iterator> crange(Container& container)
{	// get beginning of sequence
	return iterator_range<typename Container::iterator>(container.cbegin(), container.cend());
}

template<class Container>
inline iterator_range<typename Container::const_iterator> crange(const Container& container)
{	// get beginning of sequence
	return iterator_range<typename Container::const_iterator>(container.cbegin(), container.cend());
}

#endif

template<class T>
inline iterator_range<T> range(const std::pair<T, T>& iterPair)
{	// get beginning of array
	return iterator_range<T>(iterPair.first, iterPair.second);
}

template<class T>
inline iterator_range<T> range(T newBegin, T newEnd)
{	// get beginning of array
	return iterator_range<T>(newBegin, newEnd);
}

template<class T, size_t Size>
inline iterator_range<T*> range(T(&arr)[Size])
{	// get beginning of array
	return iterator_range<T*>(arr, arr + Size);
}

template<class T, size_t Size>
inline iterator_range<T*> crange(const T(&arr)[Size])
{	// get beginning of array
	return iterator_range<T*>(arr, arr + Size);
}

template<class T, size_t Size>
inline iterator_range<const T*> crange(T(&arr)[Size])
{	// get beginning of array
	return iterator_range<const T*>(arr, arr + Size);
}

class stridemap;

template<typename T>
class stridemap_iterator;

template<typename T>
iterator_range<stridemap_iterator<T>> range(stridemap& strideMap)
{
	return iterator_range<stridemap_iterator<T>> (strideMap.begin<T>(), strideMap.end<T>());
}

template<typename T>
iterator_range<stridemap_iterator<const T>> range(const stridemap& strideMap)
{
	return iterator_range<stridemap_iterator<const T >> (strideMap.begin<T>(), strideMap.end<T>());
}

template<typename T>
iterator_range<stridemap_iterator<const T>> crange(stridemap& strideMap)
{
	return iterator_range<stridemap_iterator<const T>>(strideMap.cbegin<T>(), strideMap.cend<T>());
}

template<typename T>
iterator_range<stridemap_iterator<const T>> crange(const stridemap& strideMap)
{
	return iterator_range<stridemap_iterator<const T>>(strideMap.cbegin<T>(), strideMap.cend<T>());
}

}; // namespace mst