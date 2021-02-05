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

#include <mdebug.h>
#include <mx_memalloc.h>

#if _MST_HAS_INITIALIZER_LISTS
#include <initializer_list>
#endif

namespace mst {

template<typename T>
class tidymap
{
public:
	// typedefs
	typedef T value_type;
	typedef T* pointer;
	typedef const T* cpointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* iterator;
	typedef const T* constiterator;

	typedef ::mst::_Details::_MemAllocator<::std::alignment_of<T>::value> _Allocator;

	tidymap() : _MyBegin(null), _MyEnd(null)
	{}

	tidymap(const tidymap& other) : _MyBegin(null), _MyEnd(null)
	{
#if MST_TIDYMAP_COPY_WARNING
		WARNING_MESG("copying std::tidymap<T>. this is slow, try moving it");
#endif

		const size_t othersize = other.size();
		_reallocate(othersize);
		for(size_t it = 0; it != othersize; ++it)
		{
			_copy_construct_object(&_MyBegin[it], other._MyBegin[it]);
		}
	}

#if _MST_HAS_RVALUE_REFS
	tidymap(tidymap&& other) : _MyBegin(other._MyBegin), _MyEnd(other._MyEnd)
	{
		other._MyBegin = null;
		other._MyEnd = null;
	}
#endif

#if _MST_HAS_INITIALIZER_LISTS
	tidymap(::std::initializer_list<T> initList)
	{
		const size_t othersize = initList.size();
		_reallocate(othersize);

		cpointer otherIt = initList.begin();
		for(size_t it = 0; it != othersize; ++it)
		{
			_copy_construct_object(&_MyBegin[it], *otherIt++);
		}
	}
#endif

	explicit tidymap(const size_t initSize) : _MyBegin(null), _MyEnd(null)
	{
		_reallocate(initSize);

		for(size_t it = 0; it != size(); ++it)
		{
			new (&_MyBegin[it]) T();
		}
	}

	~tidymap()
	{
		_tidy();
	}

	tidymap& operator = (const tidymap& other)
	{
#if MST_TIDYMAP_COPY_WARNING
		WARNING_MESG("copying std::tidymap<T>. this is slow, try moving the map");
#endif

		_destroy_range(begin(), end());
		size_t othersize = other.size();
		_reallocate(othersize);
		for(size_t it = 0; it != othersize; ++it)
		{
			_copy_construct_object(&_MyBegin[it], other._MyBegin[it]);
		}

		return *this;
	}

#if _MST_HAS_RVALUE_REFS
	tidymap& operator = (tidymap&& other)
	{
		_tidy();

		_MyBegin = other._MyBegin;
		_MyEnd = other._MyEnd;

		other._MyBegin = null;
		other._MyEnd = null;

		return *this;
	}
#endif

	inline void push_back(const T& value)
	{
		_push();

		_copy_construct_object<T>(_MyEnd - 1, value);
	}

#if _MST_HAS_RVALUE_REFS
	inline void push_back(T&& value)
	{
		_push();

		new (_MyEnd - 1) T(::std::move(value));
	}
#endif

#if _MST_VARIADIC_TEMPLATE_HACK_SUPPORTED
#define MST_VARIADIC_INCLUDE <mx_tidymap_emplace.h>
#include <mvariadic_template.h>
#endif

	inline void push_back() // push back default contructor
	{
		emplace_back();
	}

	inline void resize(size_t newSize)
	{
		size_t oldSize = size();
		if(newSize > oldSize)
		{
			// default construct new elements
			_reallocate(newSize);
			for(size_t i = oldSize; i < newSize; ++i)
			{
				new (_MyBegin + i) T;
			}
		}
		else
		{
			_destroy_range(begin() + newSize, begin() + oldSize);

			_reallocate(newSize);
		}
	}

	inline void pop_back()
	{
		CHECK_IF(empty(), "cannot pop back when tidymap is empty");
		::mst::_Details::_Destroy_object(_MyEnd - 1);
		_pop();
	}

	inline void erase(iterator iter)
	{
		CHECK_ITER_RANGE(iter, _MyBegin, _MyEnd, "iterator is not in the range");
		::mst::_Details::_Destroy_object(iter);

		memcpy(iter, iter + 1, (_MyEnd - (iter + 1)) * sizeof(T));

		_pop();
	}

	inline void erase(iterator iterFirst, iterator iterEnd)
	{
		CHECK_ITER_RANGE(iterFirst, _MyBegin, _MyEnd, "iterator is not in range");
		CHECK_ITER_RANGE(iterEnd, _MyBegin, _MyEnd, "iterator is not in range");
		
		_destroy_range(iterFirst, iterEnd);

		memcpy(iterFirst, iterEnd, (_MyEnd - iterEnd) * sizeof(T));

		_MyEnd -= (iterEnd - iterFirst);

		if(empty())
		{
			_tidy();
		}
		else
		{
			_reallocate(size());
		}
	}

	inline void insert(iterator iter, const T& value)
	{
		CHECK_ITER_RANGE(iter, _MyBegin, _MyEnd, "iterator is not in range");

		const size_t offset = iter - _MyBegin;
		const size_t remain = _MyEnd - iter;

		_push();

		memmove(_MyBegin + offset + 1, _MyBegin + offset, remain * sizeof(T));

		new (_MyBegin + offset) T(value);
	}

#if _MST_HAS_RVALUE_REFS
	inline void insert(iterator iter, T&& value)
	{
		CHECK_ITER_RANGE(iter, _MyBegin, _MyEnd, "iterator is not in range");

		const size_t offset = iter - _MyBegin;
		const size_t remain = _MyEnd - iter;

		_push();

		memmove(_MyBegin + offset + 1, _MyBegin + offset, remain * sizeof(T));

		new (_MyBegin + offset) T(move(value));
	}
#endif

	inline void insert(iterator iter)
	{
		emplace(iter);
	}

	inline bool empty() const
	{
		return (_MyBegin == _MyEnd);
	}

	inline size_t size() const
	{
		return (_MyEnd - _MyBegin);
	}

	inline reference front()
	{
		return *_MyBegin;
	}

	inline const_reference front() const
	{
		return *_MyBegin;
	}

	inline reference back()
	{
		return *(_MyEnd - 1);
	}

	inline const_reference back() const
	{
		return *(_MyEnd - 1);
	}

	inline pointer data()
	{
		return _MyBegin;
	}

	inline cpointer data() const
	{
		return _MyBegin;
	}

	inline size_t data_size() const
	{
		return sizeof(T) * size();
	}

	inline tidymap& operator += (const tidymap& otherMap)
	{
		size_t oldSize = size();
		_reallocate(oldSize + otherMap.size());
		for(iterator it = begin() + oldSize, otherIter = otherMap._MyBegin; it != end(); ++it, ++otherIter)
		{
			new ((void*) it) T(*otherIter);
		}

		return *this;
	}

	inline const_reference operator[](size_t index) const
	{
		CHECK_ARR_RANGE(index, size(), "index out of range");
		return _MyBegin[index];
	}

	inline reference operator [](size_t index)
	{
		CHECK_ARR_RANGE(index, size(), "index out of range");
		return _MyBegin[index];
	}

	inline constiterator begin() const
	{
		return _MyBegin;
	}

	inline iterator begin()
	{
		return _MyBegin;
	}

	inline constiterator end() const
	{
		return _MyEnd;
	}

	inline iterator end()
	{
		return _MyEnd;
	}

	inline void clear()
	{
		_tidy();
	}

	inline size_t find(const T& value)
	{
		for(size_t it = 0; it < size(); ++it)
		{
			if(_MyBegin[it] == value)
				return it;
		}
		// not found -1 (0xFFFFFFFF) is returned
		return -1;
	}

	inline void _tidy()
	{
		if(_MyBegin)
		{
			for(iterator it = begin(); it != end(); ++it)
			{
				::mst::_Details::_Destroy_object(it);
			}
			_Allocator::free_memory(_MyBegin);
			_MyEnd = _MyBegin = null;
		}
	}

	inline void _destroy_range(iterator beginIter, iterator endIter)
	{
		::mst::_Details::_Destroy_object_range(beginIter, endIter);
	}

	inline void _push()
	{
		_reallocate(size() + 1);
	}

	inline void _pop()
	{
		_reallocate(size() - 1);
	}

	template<typename _Tx>
	inline void _copy_construct_object(_Tx* objectAddress, const _Tx& other)
	{
		typedef typename ::std::integral_constant<bool,std::extent<_Tx>::value != 0> _is_array;
		_copy_construct_object_impl<_Tx>(objectAddress, other, _is_array());
	}

	template<typename _Tx>
	inline void _copy_construct_object_impl(_Tx* objectAddress, const _Tx& other, ::std::true_type)
	{
		static const size_t _ArrSize = ::std::extent<_Tx>::value;
		typedef typename ::std::remove_extent<_Tx>::type _ArrType;

		for(uint i = 0; i < _ArrSize; ++i)
		{
			_copy_construct_object<_ArrType>(&(*objectAddress)[i], other[i]);
		}
	}

	template<typename _Tx>
	inline void _copy_construct_object_impl(_Tx* objectAddress, const _Tx& other, ::std::false_type)
	{
		new (objectAddress) _Tx(other);
	}

	inline void _reallocate(size_t _Newsize)
	{
		pointer newMem = (pointer)_Allocator::allocate(_Newsize * sizeof(T));

		size_t _Size = size();
		for(size_t i = 0; i < _Size; ++i)
		{
			_Copy_object(_Mybegin[0], newMem + i, ::std::is_nothrow_move_constructible<T>::type());
		}

		_destroy_range(_MyBegin, _MyEnd);

		_MyBegin = newMem;
		_MyEnd = _MyBegin + _Newsize;
	}

	inline void _Copy_object(T& from, T* to, std::true_type)
	{
		new (to) T(::std::move(from));
	}

	inline void _Copy_object(T& from, T* to, std::false_type)
	{
		new (to) T(from);
	}

private:
	pointer _MyBegin, _MyEnd;

}; // class tidymap<T>

}; // namespace mst