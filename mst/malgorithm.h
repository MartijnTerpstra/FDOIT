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

#include <mcore.h>
#include <emmintrin.h>
#include <algorithm>
#include <mdebug.h>
#pragma once

namespace mst {

template<class _Container, typename _Function>
inline void iterate_remove(_Container& _Cont, _Function _Func)
{
	_Cont.erase(::std::remove_if(_Cont.begin(), _Cont.end(), _Func), _Cont.end());
}

template<typename _Container, typename _Function>
inline void iterate(const _Container& _Cont, _Function _Func)
{
	::std::for_each(_Cont.begin(), _Cont.end(), _Func);
}

template<typename _Iterator, typename _Function>
inline void iterate(_Iterator _Begin, _Iterator _End, _Function _Func)
{
	::std::for_each(_Begin, _End, _Func);
}

/*
inline float radix_sort(const float* input, const float* output, size_t elemCount);
inline float radix_sort(const int* input, const int* output, size_t elemCount);
inline float radix_sort(const uint* input, const uint* output, size_t elemCount);

template<typename InputIterator, typename OutputIterator>
inline float radix_sort(InputIterator beginIter, InputIterator endIter, OutputIterator beginOutIter);

template<typename InputContainer, typename OutputContainer>
inline float radix_sort(const InputContainer& input, OutputContainer& output);

inline float radix_sort_indexed(const float* input, const float* output, const uint* inputIndices, const uint* outputIndices, size_t indexCount);
inline float radix_sort_indexed(const int* input, const int* output, const uint* inputIndices, const uint* outputIndices, size_t indexCount);
inline float radix_sort_indexed(const uint* input, const uint* output, const uint* inputIndices, const uint* outputIndices, size_t indexCount);

template<typename InputIterator, typename OutputIterator>
inline float radix_sort_indexed(InputIterator beginIter, InputIterator endIter, OutputIterator beginOutIter);

template<typename InputContainer, typename OutputContainer>
inline float radix_sort_indexed(const InputContainer& beginIter, OutputIterator beginOutIter);
*/

}; // namespace mst