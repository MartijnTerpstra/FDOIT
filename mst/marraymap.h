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
#include <vector>
#include <mdebug.h>
#include <mx_common.h>
#include <mx_packed_pair.h>
#include <mx_multiarraymap.h>

#if _MST_HAS_INITIALIZER_LISTS
#include <initializer_list>
#endif // _MST_HAS_INITIALIZER_LISTS

namespace mst {

template<typename KeyType, typename ValueType, typename ComparisonType = ::std::less<KeyType>, typename AllocatorType = ::std::allocator<::std::pair<KeyType, ValueType>>>
class arraymap
{
public:
	typedef ::std::pair<const KeyType, ValueType> value_type;
	typedef KeyType key_type;
	typedef ValueType mapped_type;
	typedef value_type* pointer;
	typedef const value_type* cpointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef ::std::vector<::std::pair<KeyType, ValueType>, AllocatorType> container_type;
	typedef pointer iterator;
	typedef cpointer const_iterator;

	typedef typename container_type::iterator _Cont_iter;
	typedef typename container_type::const_iterator _Cont_const_iter;

	inline arraymap()
		: _Mypair()
	{
	}

	inline arraymap(const arraymap& other)
		: _Mypair(ComparisonType(), other._Mypair._Get_second())
	{
	}

#if _MST_HAS_INITIALIZER_LISTS

	inline arraymap(std::initializer_list<value_type> initList)
		: _Mybegin(null),
		_Myend(null),
		_MyPair(ComparisonType(), null)
	{
		_Set_capacity(initList.size());

		for(const value_type* it = initList.begin(); it != initList.end(); ++it)
		{
			insert(*it);
		}

		//insert(initList.begin(), initList.end());
	}

#endif // _MST_HAS_INITIALIZER_LISTS

	inline ~arraymap()
	{
	}

	inline size_t capacity() const
	{
		return _Get_cont();
	}

	inline size_t size() const
	{
		return _Get_cont().size();
	}

	inline bool empty() const
	{
		return _Get_cont().empty();
	}

	inline iterator begin()
	{
		return _To_extern(_Get_begin());
	}

	inline const_iterator begin() const
	{
		return _To_extern(_Get_begin());
	}

	inline const_iterator cbegin() const
	{
		return _To_extern(_Get_begin());
	}

	inline iterator end()
	{
		return _To_extern(_Get_end());
	}

	inline const_iterator end() const
	{
		return _To_extern(_Get_end());
	}

	inline const_iterator cend() const
	{
		return _To_extern(_Get_end());
	}

	inline size_t count(const key_type& key)
	{
		// map is singular, so guaranteed 1
		return contains(key) ? 1 : 0;
	}

	inline void clear()
	{
		_Tidy();
	}

	mapped_type& front()
	{
		CHECK_IF(empty(), "cannot call front() on empty container");

		return _Get_cont().front().second;
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

		_Cont_iter it = _Lower_bound(key);
		if(it == _Get_end() || _Get_comp()(key, it->first))
		{
			throw std::out_of_range("key not found");
		}

		return it->second;
	}

	inline const mapped_type& at(const key_type& key) const
	{
		CHECK_IF(empty(), "cannot call at() on empty containers");

		const_iterator it = _Lower_bound(key);
		if(it == _Get_end() || _Get_comp()(key, it->first)/*_MST_INVALID_KEY(it, key)*/)
		{
			throw std::out_of_range("key not found");
		}

		return it->second;
	}

	inline iterator find(const key_type& key)
	{
		_Cont_iter it = _Lower_bound(key);
		if(it == _Get_end() || _Get_comp()(key, it->first)/*_MST_INVALID_KEY(it, key)*/)
		{
			return end();
		}

		return _To_extern(it);
	}

	inline const_iterator find(const key_type& key) const
	{
		_Cont_const_iter it = _Lower_bound(key);
		if(it == _Get_end() || _Get_comp()(key, it->first)/*_MST_INVALID_KEY(it, key)*/)
		{
			return end();
		}

		return _To_extern(it);
	}

	inline mapped_type& operator[](const key_type& key)
	{
		if(empty())
		{
			//			std::pair<key_type, mapped_type>(key, mapped_type());
			_Construct(0, std::pair<key_type, mapped_type>(key, mapped_type()));
			return front();
		}
		_Cont_iter it = _Lower_bound(key);
		if(it != _Get_end() && _Get_comp()(key, it->first))
		{
			return it->second;
		}
		else
		{
			size_t offset = it - _Get_begin();
			_Construct(offset, value_type(key, mapped_type()));
			return _Get_cont()[offset].second;
		}
	}

	inline mapped_type& operator[](size_t index)
	{
		CHECK_ARR_RANGE(index, size(), "index out of range");

		return _Get_cont()[index].second;
	}

	inline const mapped_type& operator[](size_t index) const
	{
		CHECK_ARR_RANGE(index, size(), "index out of range");

		return _Get_cont()[index].second;
	}

	inline bool contains(const key_type& key) const
	{
		_Cont_const_iter it = _Lower_bound(key);
		return it != _Get_end() && !_Get_comp()(key, it->first);// _MST_VALID_KEY(it, key);
	}

	inline const key_type& get_key(size_t index) const
	{
		return _Get_cont()[index].first;
	}

	inline void insert(const value_type& keyValueTypePair)
	{
		_Insert(keyValueTypePair);
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
	inline void insert(PairType&& keyValueTypePair)
	{
		_Insert(::std::forward<PairType>(keyValueTypePair));
	}

#endif

	inline void erase(const key_type& key)
	{
		CHECK_IF(empty(), "cannot call erase on empty container");

		iterator it = _Lower_bound(key);

		CHECK_IF(_MST_INVALID_KEY(it, key), "key is not found");

		erase(it);
	}

	inline iterator erase(iterator iter)
	{
		CHECK_IF(empty(), "cannot call erase on empty container");
		CHECK_ITER_RANGE(_From_extern(iter), _Get_begin(), _Get_end(), "iterator out of range");

		return _Erase(iter);
	}

	iterator lower_bound(const key_type& key)
	{
		return _To_extern(_Lower_bound(key));
	}

	const_iterator lower_bound(const key_type& key) const
	{
		return _To_extern(_Lower_bound(key));
	}

	iterator upper_bound(const key_type& key)
	{
		return _To_extern(_Upper_bound(key));
	}

	const_iterator upper_bound(const key_type& key) const
	{
		return _To_extern(_Upper_bound(key));
	}

private:

	inline const ComparisonType& _Get_comp() const
	{
		return _Mypair._Get_first();
	}

	inline void _Tidy()
	{
		_Get_cont().clear();
	}

	inline iterator _Insert(const value_type& keyValueTypePair)
	{
		if(empty())
		{
			return _Construct(0, keyValueTypePair);
		}
		else
		{
			_Cont_iter it = _Lower_bound(keyValueTypePair.first);
			if(it == _Get_end() || _Get_comp()(keyValueTypePair.first, it->first)/*_MST_INVALID_KEY(it, keyValueTypePair.first)*/)
			{
				size_t offset = it - _Mybegin;
				return _Construct(offset, keyValueTypePair);
			}

			return _To_extern(it);
		}
	}

	inline iterator _Erase(iterator eraseIterator)
	{
		/*
		size_t offset = eraseIterator - _Mybegin;
		::std::memcpy(_Mybegin + offset, _Mybegin + offset + 1, (size() - offset - 1) * sizeof(value_type));

		_Shrink(size() - 1);
		*/

		return _To_extern(_Get_cont().erase(_From_extern(eraseIterator)));
	}

	inline iterator _Construct(size_t offset, const value_type& keyValueTypePair)
	{
		return _To_extern(_Get_cont().insert(_Get_begin() + offset, keyValueTypePair));

		/*
		size_t oldSize = size();
		::std::memmove(_Mybegin + offset + 1, _Mybegin + offset, (size() - offset - 1) * sizeof(value_type));

		new (_Mybegin + offset) value_type(keyValueTypePair);
		*/
	}

#if _MST_HAS_RVALUE_REFS

	template<typename PairType>
	inline iterator _Insert(PairType&& keyValueTypePair)
	{
		if(empty())
		{
			return _Construct(0, ::std::forward<PairType>(keyValueTypePair));
		}
		else
		{
			_Cont_iter it = _Lower_bound(keyValueTypePair.first);
			if(it == _Get_end() || _Get_comp()(keyValueTypePair.first, it->first)/*_MST_INVALID_KEY(it, keyValueTypePair.first)*/)
			{
				size_t offset = it - _Get_begin();
				return _Construct(offset, ::std::forward<PairType>(keyValueTypePair));
			}
			return _To_extern(it);
		}
	}

	template<typename PairType>
	inline iterator _Construct(size_t offset, PairType&& keyValueTypePair)
	{
		//::std::memmove(_Mybegin + offset + 1, _Mybegin + offset, (size() - offset - 1) * sizeof(value_type));

		return _To_extern(_Get_cont().insert(_Get_begin() + offset, ::std::forward<PairType>(keyValueTypePair)));

		//new (_Mybegin + offset) value_type(::std::forward<PairType>(keyValueTypePair));
	}

#endif // _MST_HAS_RVALUE_REFS

	inline iterator _Find(const key_type& key)
	{
		size_t range = size();

		iterator beginIter = _Get_begin();

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			iterator middleIter = beginIter + halfRange;

			if(_Get_comp()(middleIter->first, key))
			{
				CHECK_IF(_Get_comp()(key, middleIter->first), "invalid comparison operations");
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

	inline _Cont_iter _Lower_bound(const key_type& key)
	{
		size_t range = size();

		_Cont_iter beginIter = _Get_begin();

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			_Cont_iter middleIter = beginIter + halfRange;

			if(_Get_comp()(middleIter->first, key))
			{
				CHECK_IF(_Get_comp()(key, middleIter->first), "invalid comparison operations");
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

		iterator beginIter = _Get_begin();

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			iterator middleIter = beginIter + halfRange;

			if(_Get_comp()(key, middleIter->first))
			{
				CHECK_IF(_Get_comp()(middleIter->first, key), "invalid comparison operations");
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

	inline _Cont_const_iter _Lower_bound(const key_type& key) const
	{
		size_t range = size();

		_Cont_const_iter beginIter = _Get_begin();

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			_Cont_const_iter middleIter = beginIter + halfRange;

			if(_Get_comp()(middleIter->first, key))
			{
				CHECK_IF(_Get_comp()(key, middleIter->first), "invalid comparison operations");
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

	inline _Cont_const_iter _Upper_bound(const key_type& key) const
	{
		size_t range = size();

		_Cont_const_iter beginIter = _Get_begin();

		while(range != 0)
		{
			size_t halfRange = range >> 1;

			_Cont_const_iter middleIter = beginIter + halfRange;

			if(_Get_comp()(key, middleIter->first))
			{
				CHECK_IF(_Get_comp()(middleIter->first, key), "invalid comparison operations");
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

	inline _Cont_const_iter _Get_end() const
	{
		return _Mypair._Get_second().end();
	}

	inline _Cont_iter  _Get_end()
	{
		return _Mypair._Get_second().end();
	}

	inline _Cont_const_iter _Get_begin() const
	{
		return _Mypair._Get_second().begin();
	}

	inline _Cont_iter _Get_begin()
	{
		return _Mypair._Get_second().begin();
	}

	inline const container_type& _Get_cont() const
	{
		return _Mypair._Get_second();
	}

	inline container_type& _Get_cont()
	{
		return _Mypair._Get_second();
	}

	inline iterator _To_extern(_Cont_iter iter)
	{
		return reinterpret_cast<iterator>(_Get_cont().data() + (iter - _Get_begin()));
	}

	inline const_iterator _To_extern(_Cont_const_iter iter) const
	{
		return reinterpret_cast<const_iterator>(_Get_cont().data() + (iter - _Get_begin()));
	}

	inline _Cont_iter _From_extern(iterator iter)
	{
		return _Get_begin() + (iter - begin());
	}

	inline _Cont_const_iter _From_extern(const_iterator iter) const
	{
		return _Get_begin() + (iter - begin());
	}

private:
	::mst::_Details::_Packed_pair<ComparisonType, container_type> _Mypair;

}; // class arraymap<KeyType, ValueType, ComparisonType, AllocatorType>


}; // namespace mst