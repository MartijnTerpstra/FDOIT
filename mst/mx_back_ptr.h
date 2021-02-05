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

template<typename T>
class smart_ptr;

template<typename T>
class back_ptr
{
	template<typename T2>
	friend class smart_ptr;
public:

	back_ptr() _MST_NOEXCEPT
	{
		this->_reset_ptr();
	}

	back_ptr(::std::nullptr_t) _MST_NOEXCEPT
	{
		this->_reset_ptr(nullptr);
	}

	back_ptr(const ::mst::_Details::_Smart_ptr_base<T>& other) _MST_NOEXCEPT
	{
		this->_reset_ptr(other);
	}

	back_ptr(const back_ptr& other) _MST_NOEXCEPT
	{
		this->_reset_ptr(other);
	}

#if _MST_HAS_RVALUE_REFS
	back_ptr(back_ptr&& other) _MST_NOEXCEPT
	{
		this->_reset_ptr(::std::move(other));
	}
#endif

#if _MST_HAS_DEFAULT_TEMPLATE_ARGS_OUTSIDE_CLASS
	template<class T2,
		class = typename ::std::enable_if<::std::is_convertible<T2*, T*>::value,
		void>::type>
		back_ptr(const ::mst::_Details::_Smart_ptr_base<T2>& other) _MST_NOEXCEPT
	{
		this->_reset_ptr(other);
	}
#else
	template<class T2>
	back_ptr(const ::mst::_Details::_Smart_ptr_base<T2>& other,
			  typename ::std::enable_if<::std::is_convertible<T2*, T*>::value,
			  void>::type ** = 0) _MST_NOEXCEPT
	{
		this->_reset_ptr(other);
	}
#endif // _MST_HAS_DEFAULT_TEMPLATE_ARGS_OUTSIDE_CLASS

	~back_ptr()
	{
		this->_MyBlock->_Dec_back();
	}

	back_ptr& operator = (const ::mst::_Details::_Smart_ptr_base<T>& other) _MST_NOEXCEPT
	{
		_MyBlock->_Dec_back();

		this->_MyPtr = other._MyPtr;
		this->_MyBlock = other._MyBlock;
		this->_MyBlock->_Inc_back();

		return *this;
	}

	back_ptr& operator = (::std::nullptr_t) _MST_NOEXCEPT
	{
		_MyBlock->_Dec_back();

		this->_MyPtr = null;
		this->_MyBlock = ::mst::_Details::_Refblock_static::_Get_null_block();

		return *this;
	}

	inline back_ptr& operator = (const back_ptr& other) _MST_NOEXCEPT
	{
		_MyBlock->_Dec_back();

		this->_MyPtr = other._MyPtr;
		this->_MyBlock = other._MyBlock;
		this->_MyBlock->_Inc_back();

		return *this;
	}

#if _MST_HAS_RVALUE_REFS
	inline back_ptr& operator = (back_ptr&& other) _MST_NOEXCEPT
	{
		swap(other);

		return *this;
	}
#endif

	bool operator == (::std::nullptr_t) const _MST_NOEXCEPT
	{
		return _MyPtr == null;
	}

	bool operator == (const back_ptr& _Ptr) const _MST_NOEXCEPT
	{
		return _MyPtr == _Ptr->_MyPtr;
	}

	bool operator == (const smart_ptr<T>& other) const _MST_NOEXCEPT
	{
		return _MyPtr == other->_MyPtr;
	}

	friend bool operator == (::std::nullptr_t, const back_ptr& ptr) _MST_NOEXCEPT
	{
		return ptr->_MyPtr == null;
	}

	inline bool is_valid() const _MST_NOEXCEPT
	{
		return _MyBlock != null && _MyBlock->IsValid();
	}

	inline ::mst::smart_ptr<T> lock() const _MST_NOEXCEPT;

	inline refcount_t use_count() const _MST_NOEXCEPT
	{
		return (_MyBlock->_Is_valid() ? _MyBlock->_Use_count() : 0);
	}

	inline refcount_t back_count() const _MST_NOEXCEPT
	{
		return (_MyBlock->_Is_valid() ? _MyBlock->_Back_count() : 0);
	}

	inline bool expired() _MST_NOEXCEPT
	{
		return _MyBlock->_Is_valid() || _MyBlock->_Use_count() == 0;
	}

	inline void swap(back_ptr& other) _MST_NOEXCEPT
	{
		T* _Ptr = _MyPtr;
		::mst::_Details::_Refblock_base* _Block = _MyBlock;

		_MyPtr = other._MyPtr;
		_MyBlock = other._MyBlock;

		other._MyPtr = _Ptr;
		other._MyBlock = _Block;
	}

private:
	inline void _reset_ptr(::std::nullptr_t) _MST_NOEXCEPT
	{
		this->_MyPtr = null;
		this->_MyBlock = ::mst::_Details::_Refblock_static::_Get_null_block();
	}

	inline void _reset_ptr(const ::mst::_Details::_Smart_ptr_base<T>& other) _MST_NOEXCEPT
	{
		this->_MyPtr = other._MyPtr;
		this->_MyBlock = other._MyBlock;

		this->_MyBlock->_Inc_back();
	}

	template<typename T2>
	inline void _reset_ptr(const ::mst::_Details::_Smart_ptr_base<T2>& other) _MST_NOEXCEPT
	{
		this->_MyPtr = other._MyPtr;
		this->_MyBlock = other._MyBlock;

		this->_MyBlock->_Inc_back();
	}

	inline void _reset_ptr(const back_ptr& other) _MST_NOEXCEPT
	{
		this->_MyPtr = other._MyPtr;
		this->_MyBlock = other._MyBlock;

		this->_MyBlock->_Inc_back();
	}

#if _MST_HAS_RVALUE_REFS
	inline void _reset_ptr(back_ptr&& other) _MST_NOEXCEPT
	{
		this->_MyPtr = other._MyPtr;
		this->_MyBlock = other._MyBlock;

		other._MyBlock = ::mst::_Details::_Refblock_static::_Get_null_block();
	}
#endif

	inline void _reset_ptr() _MST_NOEXCEPT
	{
		this->_MyBlock = ::mst::_Details::_Refblock_static::_Get_null_block();
	}

private:
	T* _MyPtr;
	::mst::_Details::_Refblock_base* _MyBlock;

}; // class back_ptr

}; // namespace mst