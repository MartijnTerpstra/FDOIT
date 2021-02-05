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
#include <malloc.h>

namespace mst {

template<typename T>
class aligned_allocator
{
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;

	aligned_allocator()
#if _MST_HAS_DEFAULT_DELETE
		= default;
#else
	{
		/* do nothing */
	}
#endif

	template<typename T2>
	aligned_allocator(const aligned_allocator<T2>& other)
	{
		/* do nothing */
	}

	void deallocate(pointer ptr, size_t count)
	{
		_free<::std::alignment_of<T>::value>(ptr);
	}

	pointer allocate(size_t count)
	{
		return _alloc<::std::alignment_of<T>::value>(count);
	}

#if _MST_VARIADIC_TEMPLATE_HACK_SUPPORTED
#define MST_VARIADIC_INCLUDE <mx_allocator_construct.h>
#include <mvariadic_template.h>
#endif

	void destroy(pointer ptr)
	{
		::mst::_Details::_Destroy_object(ptr);
	}

	template<typename T2>
	struct rebind
	{
		typedef aligned_allocator<T2> other;
	};

private:

	template<size_t aligment>
	inline void _free(void* memory)
	{
		_aligned_free(memory);
	}

	template<>
	inline void _free<1>(void* memory)
	{
		free(memory);
	}

	template<size_t aligment>
	inline pointer _alloc(size_t count)
	{
		return reinterpret_cast<pointer>(_aligned_malloc(sizeof(T) * count, aligment));
	}

	template<>
	inline pointer _alloc<1>(size_t count)
	{
		return reinterpret_cast<pointer>(malloc(sizeof(T) * count));
	}
};


template<>
class aligned_allocator<void>
{
public:
	typedef void value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef void* pointer;
	typedef const void* const_pointer;

	aligned_allocator()
#if _MST_HAS_DEFAULT_DELETE
		= default;
#else
	{
		/* do nothing */
	}
#endif

	template<typename T2>
	aligned_allocator(const aligned_allocator<T2>& other)
	{
		/* do nothing */
	}

	template<typename T2>
	struct rebind
	{
		typedef aligned_allocator<T2> other;
	};

};

}; // namespace mst