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
#include <mx_common.h>
#include <mranges.h>

#if _MST_HAS_INITIALIZER_LISTS
#include <initializer_list>
#endif // _MST_HAS_INITIALIZER_LISTS

namespace mst {
/*
#define _MST_VALID_KEY(iter, key) (iter != _Myend && comp.equal<key_type>(key, iter->first))
#define _MST_INVALID_KEY(iter, key) (iter == _Myend || comp.not_equal<key_type>(key, iter->first))
*/
template<typename Key, typename Value, typename Compare = ::mst::compare>
class multiarraymap
{
public:
	typedef ::std::pair<const Key, Value> value_type;
	typedef Key key_type;
	typedef Value mapped_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	Compare comp;

	inline multiarraymap()
		: _Mybegin(null),
		_Myend(null),
		_Mylast(null)
	{
	}

	inline multiarraymap(const multiarraymap& other)
		: _Mybegin(null),
		_Myend(null),
		_Mylast(null)
	{
		_Adopt(other);
	}

#if _MST_HAS_INITIALIZER_LISTS

	inline multiarraymap(std::initializer_list<value_type> initList)
		: _Mybegin(null),
		_Myend(null),
		_Mylast(null)
	{
		_Set_capacity(initList.size());
		
		for(const value_type* it = initList.begin(); it != initList.end(); ++it)
		{
			insert(*it);
		}

		//insert(initList.begin(), initList.end());
	}

#endif // _MST_HAS_INITIALIZER_LISTS

	inline ~multiarraymap()
	{
		clear();
	}

	inline size_t capacity() const
	{
		return _Mylast - _Mybegin;
	}

	inline size_t size() const
	{
		return _Myend - _Mybegin;
	}

	inline bool empty() const
	{
		return _Mybegin == _Myend;
	}

	inline iterator begin()
	{
		return _Mybegin;
	}

	inline size_t count(const key_type& key)
	{
		// map is singular, so guaranteed 1
		return 1;
	}

	inline iterator begin() const
	{
		return _Mybegin;
	}

	inline const_iterator cbegin() const
	{
		return _Mybegin;
	}

	inline iterator end()
	{
		return _Myend;
	}

	inline iterator end() const
	{
		return _Myend;
	}

	inline const_iterator cend() const
	{
		return _Myend;
	}

	inline void clear()
	{
		_Tidy();
	}

	mapped_type& front()
	{
		CHECK_IF(empty(), "cannot call front() on empty container");

		return _Mybegin->second;
	}

	const mapped_type& front() const
	{
		CHECK_IF(empty(), "cannot call front() on empty container");

		return _Mybegin->second;
	}

	mapped_type& back()
	{
		CHECK_IF(empty(), "cannot call back() on empty container");

		return (_Myend - 1)->second;
	}

	const mapped_type& back() const
	{
		CHECK_IF(empty(), "cannot call back() on empty container");

		return (_Myend - 1)->second;
	}

	inline mapped_type& at(const key_type& key)
	{
		CHECK_IF(empty(), "cannot call at() on empty containers");

		iterator it = _Lower_bound(key);
		if(_MST_INVALID_KEY(it, key))
		{
			throw std::out_of_range("key not found");
		}

		return it->second;
	}

	inline const mapped_type& at(const key_type& key) const
	{
		CHECK_IF(empty(), "cannot call at() on empty containers");

		const_iterator it = _Lower_bound(key);
		if(_MST_INVALID_KEY(it, key))
		{
			throw std::out_of_range("key not found");
		}

		return it->second;
	}

	inline iterator find(const key_type& key)
	{
		iterator it = _Lower_bound(key);
		if(_MST_INVALID_KEY(it, key))
		{
			return end();
		}
		
		return it;
	}

	inline const_iterator find(const key_type& key) const
	{
		const_iterator it = _Lower_bound(key);
		if(_MST_INVALID_KEY(it, key))
		{
			return end();
		}

		return it;
	}

	inline mapped_type& operator[](const key_type& key)
	{
		if(empty())
		{
			_Grow(1);
			_Construct(0, value_type(key, mapped_type()));
			return front();
		}
		iterator it = _Lower_bound(key);
		if(_MST_VALID_KEY(it, key))
		{
			return it->second;
		}
		else
		{
			size_t offset = it - _Mybegin;
			_Grow(size() + 1);
			_Construct(offset, value_type(key, mapped_type()));
			return _Mybegin[offset].second;
		}
	}

	inline mapped_type& operator[](size_t index)
	{
		CHECK_ARR_RANGE(index, size(), "index out of range");

		return _Mybegin[index].second;
	}

	inline const mapped_type& operator[](size_t index) const
	{
		CHECK_ARR_RANGE(index, size(), "index out of range");

		return _Mybegin[index].second;
	}

	inline bool contains(const key_type& key) const
	{
		const_iterator it = _Lower_bound(key);
		return _MST_VALID_KEY(it, key);
	}

	inline void insert(const value_type& keyValuePair)
	{
		_Insert(keyValuePair);
	}

	inline void shrink_to_fit()
	{
		if(_Myend != _Mylast)
		{
			_Set_capacity(size());
		}
	}

#if _MST_HAS_RVALUE_REFS

	template<typename PairType>
	inline void insert(PairType&& keyValuePair)
	{
		_Insert(::std::forward<PairType>(keyValuePair));
	}

#endif

	inline void erase(const key_type& key)
	{
		CHECK_IF(empty(), "cannot call erase on empty container");

		iterator it = _Lower_bound(key);

		CHECK_IF(_MST_INVALID_KEY(it, key), "key is not found");

		erase(it);
	}

	inline void erase(iterator key)
	{
		CHECK_IF(empty(), "cannot call erase on empty container");
		CHECK_ITER_RANGE(key, _Mybegin, _Myend, "iterator out of range");

		::mst::_Details::_Destroy_object(key);
		_Erase(key);
	}

	iterator lower_bound(const key_type& key)
	{
		return _Lower_bound(key);
	}

	const_iterator lower_bound(const key_type& key) const
	{
		return _Lower_bound(key);
	}

	iterator upper_bound(const key_type& key)
	{
		return _Upper_bound(key);
	}

	const_iterator upper_bound(const key_type& key) const
	{
		return _Upper_bound(key);
	}

	iterator_range<iterator> equal_range(const key_type& key)
	{
		return range<iterator>(lower_bound(key), upper_bound(key));
	}

	iterator_range<const_iterator> equal_range(const key_type& key) const
	{
	}

private:

	inline void _Erase(iterator eraseIterator)
	{
		size_t offset = eraseIterator - _Mybegin;
		::std::memcpy(_Mybegin + offset, _Mybegin + offset + 1, (size() - offset - 1) * sizeof(value_type));

		_Shrink(size() - 1);
	}

	inline void _Tidy()
	{
		if(!empty())
		{
			::mst::_Details::_Destroy_object_range(_Mybegin, _Myend);
			_Shrink(0);
		}
	}

	inline void _Insert(const value_type& keyValuePair)
	{
		if(empty())
		{
			_Grow(size() + 1);
			_Construct(0, keyValuePair);
		}
		else
		{
			iterator it = _Lower_bound(keyValuePair.first);
			if(_MST_INVALID_KEY(it, keyValuePair.first))
			{
				size_t offset = it - _Mybegin;
				_Grow(size() + 1);
				_Construct(offset, keyValuePair);
			}
		}
	}

	inline void _Construct(size_t offset, const value_type& keyValuePair)
	{
		::std::memmove(_Mybegin + offset + 1, _Mybegin + offset, (size() - offset - 1) * sizeof(value_type));

		new (_Mybegin + offset) value_type(keyValuePair);
	}

#if _MST_HAS_RVALUE_REFS

	template<typename PairType>
	inline void _Insert(PairType&& keyValuePair)
	{
		if(empty())
		{
			_Grow(size() + 1);
			_Construct(0, ::std::forward<PairType>(keyValuePair));
		}
		else
		{
			iterator it = _Lower_bound(keyValuePair.first);
			if(_MST_INVALID_KEY(it, keyValuePair.first))
			{
				size_t offset = it - _Mybegin;
				_Grow(size() + 1);
				_Construct(offset, ::std::forward<PairType>(keyValuePair));
			}
		}
	}

	template<typename PairType>
	inline void _Construct(size_t offset, PairType&& keyValuePair)
	{
		::std::memmove(_Mybegin + offset + 1, _Mybegin + offset, (size() - offset - 1) * sizeof(value_type));

		new (_Mybegin + offset) value_type(::std::forward<PairType>(keyValuePair));
	}

#endif // _MST_HAS_RVALUE_REFS

	inline void _Grow(size_t newSize)
	{
		CHECK_IF(newSize < size(), "should not happen");

		if(newSize > capacity())
		{
			size_t newCapacity = capacity() * 2;
			void* memory;

			if(_Mybegin)
			{
				memory = realloc(_Mybegin, newCapacity * sizeof(value_type));
			}
			else
			{
				memory = malloc(newSize * sizeof(value_type));
				newCapacity = newSize;
			}
			if(memory == null)
			{
				_Tidy();
				throw std::bad_alloc();
			}

			_Mybegin = reinterpret_cast<pointer>(memory);
			_Mylast = _Mybegin + newCapacity;
		}

		_Myend = _Mybegin + newSize;
	}

	inline void _Shrink(size_t newSize)
	{
		if(newSize != 0)
		{
			if(newSize < capacity() >> 2)
			{
				size_t newCapacity = capacity() >> 2;
				void* memory = realloc(_Mybegin, newCapacity * sizeof(value_type));
				if(memory == null)
				{ // should never happen? could possibly be asserted
					_Tidy();
					throw std::bad_alloc();
				}
				_Mybegin = reinterpret_cast<pointer>(memory);
				_Mylast = _Mybegin + newCapacity;
			}
			_Myend = _Mybegin + newSize;
		}
		else
		{
			if(_Mybegin)
			{
				free(_Mybegin);
			}
			_Mybegin = _Myend = _Mylast = null;
		}
	}

	inline void _Set_capacity(size_t newCapacity)
	{
		CHECK_IF(newCapacity < size(), "invalid capacity");


		if(newCapacity != 0)
		{
			size_t newSize = size();
			void* memory;

			if(_Mybegin)
			{
				memory = realloc(_Mybegin, newCapacity * sizeof(value_type));
			}
			else
			{
				memory = malloc(newCapacity * sizeof(value_type));
			}
			if(memory == null)
			{
				_Tidy();
				throw std::bad_alloc();
			}

			_Mybegin = reinterpret_cast<pointer>(memory);
			_Myend = _Mybegin + newSize;
			_Mylast = _Mybegin + newCapacity;
		}
		else
		{
			if(_Mybegin)
			{
				free(_Mybegin);
			}
			_Mybegin = _Myend = _Mylast = null;
		}
	}

	inline iterator _Find(const key_type& key)
	{
		size_t range = size();

		iterator beginIter = _Mybegin;

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			iterator middleIter = beginIter + halfRange;

			if(comp.less(middleIter->first, key))
			{
				CHECK_IF(comp.less(key, middleIter->first), "invalid comparison operations");
				beginIter = ++middleIter;
				range -= halfRange + 1;
			}
			else
			{
				range = halfRange;
			}
		}

		return beginIter;
	}

	inline iterator _Lower_bound(const key_type& key)
	{
		size_t range = size();

		iterator beginIter = _Mybegin;

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			iterator middleIter = beginIter + halfRange;

			if(comp.less(middleIter->first, key))
			{
				CHECK_IF(comp.less(key, middleIter->first), "invalid comparison operations");
				beginIter = ++middleIter;
				range -= halfRange + 1;
			}
			else
			{
				range = halfRange;
			}
		}

		return beginIter;
	}

	inline iterator _Upper_bound(const key_type& key)
	{
		size_t range = size();

		iterator beginIter = _Mybegin;

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			iterator middleIter = beginIter + halfRange;

			if(comp.greater(middleIter->first, key))
			{
				CHECK_IF(comp.greater(key, middleIter->first), "invalid comparison operations");
				range = halfRange;
			}
			else
			{
				beginIter = ++middleIter;
				range -= halfRange + 1;
			}
		}

		return beginIter;
	}

	inline const_iterator _Lower_bound(const key_type& key) const
	{
		size_t range = size();

		const_iterator beginIter = _Mybegin;

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			const_iterator middleIter = beginIter + halfRange;

			if(comp.less(middleIter->first, key))
			{
				CHECK_IF(comp.less(key, middleIter->first), "invalid comparison operations");
				beginIter = ++middleIter;
				range -= halfRange + 1;
			}
			else
			{
				range = halfRange;
			}
		}

		return beginIter;
	}

	inline const_iterator _Upper_bound(const key_type& key) const
	{
		size_t range = size();

		const_iterator beginIter = _Mybegin;

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			const_iterator middleIter = beginIter + halfRange;

			if(comp.greater(middleIter->first, key))
			{
				CHECK_IF(comp.greater(key, middleIter->first), "invalid comparison operations");
				range = halfRange;
			}
			else
			{
				beginIter = ++middleIter;
				range -= halfRange + 1;
			}
		}

		return beginIter;
	}

	void _Adopt(const multiarraymap& other)
	{
		::mst::_Details::_Destroy_object_range(_Mybegin, _Myend);
		size_t size = other.size();
		_Set_capacity(size);

		for(size_t i = 0; i < size; ++i)
		{
			new (_Mybegin + i) value_type(other._Mybegin[i]);
		}
		_Myend = _Mybegin + size;
	}

private:
	pointer _Mybegin, _Myend, _Mylast;

}; // struct tidymap


}; // namespace mst