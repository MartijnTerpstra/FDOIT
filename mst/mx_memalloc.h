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

#include <set>
#include <mcore.h>
#include <mlogger.h>
#include <stdlib.h>

namespace mst {
namespace _Details {

template<size_t _Alignment>
class _MemAllocator
{
public:
	static void* allocate(size_t _Size)
	{
		void* p = _aligned_malloc(_Size, _Alignment);
		return p;
	}

	template<size_t _Size>
	static void* allocate_unmapped()
	{
		void* p = _aligned_malloc(_Mapped_size<_Alignment, _Size>::value, _Alignment);
		return p;
	}

	static void* reallocate(void* _Memory, size_t _Size)
	{
		_Memory = _aligned_realloc(_Memory, _Size, _Alignment);
		return _Memory;
	}

	static void free_memory(void* _Memory)
	{
		return _aligned_free(_Memory);
	}

}; // class _MemAllocator<size_t>

template<>
class _MemAllocator<1>
{
public:
	static void* allocate(size_t _Size)
	{
		void* p = malloc(_Size);
		return p;
	}

	static void* reallocate(void* _Memory, size_t _Size)
	{
		void* _Mem = realloc(_Memory, _Size);

		if(_Mem == null)
			throw std::bad_alloc();

		return _Mem;
	}

	static void free_memory(void* _Memory)
	{
		return free(_Memory);
	}

}; // class _MemAllocator<1>

}; // namespace _Details
}; // namespace mst