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

#ifndef MSMART_PTR_H
#define MSMART_PTR_H

#include <mcore.h>
#include <mx_cast.h>
#include <mx_memalloc.h>
#include <mx_refblock.h>
#include <mx_smart_ptr.h>
#include <mx_back_ptr.h>

#pragma warning (disable : 4345)

namespace mst {

#define smart_this_ptr (_Smart_this_ptr(this))

/*
#if _MST_HAS_LAMBDAS && _MST_HAS_DECLTYPE

#define make_smart_ptr(_Constructor) ::mst::_Details::_Make_smart_ptr<decltype(_Constructor)>([&](void* _Memory) { new (_Memory) _Constructor; }, [&](decltype(_Constructor)* _Obj) { typedef decltype(_Constructor) T; _Obj->~T(); })
#define make_smart_ptr_del(_Constructor, _Custom_deleter) ::mst::smart_ptr<decltype(_Constructor)>(new _Constructor, _Custom_deleter)

#else

#define make_smart_ptr(_Constructor) ::mst::_Details::_Make_smart_ptr(new _Constructor)
#define make_smart_ptr_del(_Constructor, _Custom_deleter) ::mst::_Details::_Make_smart_ptr(new _Constructor, _Custom_deleter)

#endif
*/

class smart_ptr_access;

#if _MST_VARIADIC_TEMPLATE_HACK_SUPPORTED
#define MST_VARIADIC_INCLUDE <mx_make_smart.h>
#include <mvariadic_template.h>
#else
template<typename T>
smart_ptr<T> make_smart()
{
	return make_smart_ptr(T());
}
#endif

template<typename T>
class smart_ptr : public ::mst::_Details::_Smart_ptr_base<T>
{
public:
	typedef T value_type;

	smart_ptr(::std::nullptr_t)
	{
		this->_reset_ptr((T*) 0, ::mst::_Details::_Refblock_static::_Get_null_block());
	}

	template<typename T2>
	explicit smart_ptr(T2* ptr)
	{
		_reset_ptr(ptr, new ::mst::_Details::_Refblock_ptr<T2>(ptr));
	}

	template<typename T2, typename T3>
	explicit smart_ptr(const smart_ptr<T3>& coOwner, T2* ptr)
	{
		_reset_ptr(ptr, coOwner._MyBlock);
	}

	template<typename T2, typename Deleter>
	explicit smart_ptr(T2* ptr, Deleter customDeleter)
	{
		_reset_ptr(ptr, new ::mst::_Details::_Refblock_ptr_del<T2, Deleter>(ptr, customDeleter));
	}

	template<typename T2>
	smart_ptr(const ::mst::smart_ptr<T2>& _Other, ::mst::_Details::_Mst_cast_dynamic)
	{
		this->_reset_ptr(_Other, ::mst::_Details::_Mst_cast_dynamic());
	}

	template<typename T2>
	smart_ptr(const ::mst::smart_ptr<T2>& _Other, ::mst::_Details::_Mst_cast_static)
	{
		this->_reset_ptr(_Other, ::mst::_Details::_Mst_cast_static());
	}

	template<typename T2>
	smart_ptr(const ::mst::smart_ptr<T2>& _Other, ::mst::_Details::_Mst_cast_const)
	{
		this->_reset_ptr(_Other, ::mst::_Details::_Mst_cast_const());
	}

	template<typename T2>
	smart_ptr(const ::mst::smart_ptr<T2>& _Other, ::mst::_Details::_Mst_cast_reinterpret)
	{
		this->_reset_ptr(_Other, ::mst::_Details::_Mst_cast_reinterpret());
	}

	smart_ptr() _MST_NOEXCEPT
	{
		this->_reset_ptr(_MyPtr, ::mst::_Details::_Refblock_static::_Get_null_block());
	}

	smart_ptr(const smart_ptr& other) _MST_NOEXCEPT
	{
		this->_reset_ptr(other);
	}

	explicit smart_ptr(const back_ptr<T>& other) _MST_NOEXCEPT
	{
		if(other._MyBlock->_Lock())
		{
			this->_MyPtr = other._MyPtr;
			this->_MyBlock = other._MyBlock;
		}
		else
		{
			this->_reset_ptr(_MyPtr, ::mst::_Details::_Refblock_static::_Get_null_block());
		}
	}

#if _MST_HAS_DEFAULT_TEMPLATE_ARGS_OUTSIDE_CLASS
	template<class T2,
	class = typename ::std::enable_if<::std::is_convertible<T2*, T*>::value,
		void>::type>
	smart_ptr(const ::mst::smart_ptr<T2>& other) _MST_NOEXCEPT
	{
		this->_reset_ptr(other);
	}
#else
	template<class T2>
	smart_ptr(const ::mst::smart_ptr<T2>& other,
			   typename ::std::enable_if<::std::is_convertible<T2*, T*>::value,
			   void>::type ** = 0) _MST_NOEXCEPT
	{
		this->_reset_ptr(other);
	}
#endif // _MST_HAS_DEFAULT_TEMPLATE_ARGS_OUTSIDE_CLASS

	inline bool is_valid() const
	{
		return _Is_valid();
	}

	inline void reset()
	{
		smart_ptr().swap(*this);
	}

	template<typename T2>
	inline void reset(T2* _Ptr)
	{
		smart_ptr(_Ptr).swap(*this);
	}

	template<typename T2, typename Deleter>
	inline void reset(T2* _Ptr, Deleter customDeleter)
	{
		smart_ptr(_Ptr, customDeleter).swap(*this);
	}

	inline smart_ptr& operator = ( const smart_ptr& _Right)
	{
		smart_ptr(_Right).swap(*this);
		return (*this);
	}

	template<class T2>
	inline smart_ptr& operator = ( const smart_ptr<T2>& _Right)
	{
		smart_ptr(_Right).swap(*this);
		return (*this);
	}

	inline bool operator == (const smart_ptr& _Other) const
	{
		return get() == _Other.get();
	}

	inline bool operator != (const smart_ptr& _Other) const
	{
		return !(*this == _Other);
	}

	inline bool operator == (::std::nullptr_t) const
	{
		return this->get() == null;
	}

	inline bool operator != (::std::nullptr_t) const
	{
		return !(*this == null);
	}

	inline friend bool operator == (::std::nullptr_t, const smart_ptr& _Right)
	{
		return _Right == null;
	}

	inline friend bool operator != (::std::nullptr_t, const smart_ptr& _Right)
	{
		return _Right != null;
	}

	inline bool operator > (const smart_ptr& _Other) const
	{
		return this->get() > _Other.get();
	}

	inline bool operator < (const smart_ptr& _Other) const
	{
		return this->get() < _Other.get();
	}

	inline bool operator >= (const smart_ptr& _Other) const
	{
		return !(*this < _Other);
	}

	inline bool operator <= (const smart_ptr& _Other)
	{
		return !(*this > _Other);
	}

	inline void swap(smart_ptr& _Right)
	{
		_Smart_ptr_base::swap(_Right);
	}

	inline smart_ptr& operator = (::std::nullptr_t)
	{
		_dec_ref();

		_reset_ptr((T*)0, ::mst::_Details::_Refblock_static::_Get_null_block());

		return (*this);
	}

#if _MST_HAS_RVALUE_REFS
	smart_ptr(smart_ptr&& _Other)
	{
		this->_reset_ptr(::std::move(_Other));
	}

	template<typename T2>
	smart_ptr(::mst::smart_ptr<T2>&& _Other, typename std::enable_if<std::is_convertible<T2, T>::value, void*>::type = (void*)0)
	{
		this->_reset_ptr(::std::move(_Other));
	}

	template<typename T2>
	smart_ptr(::mst::smart_ptr<T2>&& _Other, ::mst::_Details::_Mst_cast_dynamic)
	{
		this->_reset_ptr(::std::move(_Other), ::mst::_Details::_Mst_cast_dynamic());
	}

	template<typename T2>
	smart_ptr(::mst::smart_ptr<T2>&& _Other, ::mst::_Details::_Mst_cast_static)
	{
		this->_reset_ptr(::std::move(_Other), ::mst::_Details::_Mst_cast_static());
	}

	inline smart_ptr& operator = ( smart_ptr&& _Right)
	{
		smart_ptr(::std::move(_Right)).swap(*this);
		return (*this);
	}

	template<class T2>
	inline smart_ptr& operator = ( smart_ptr<T2>&& _Right)
	{
		smart_ptr(::std::move(_Right)).swap(*this);
		return (*this);
	}

	inline void swap(smart_ptr&& _Right)
	{
		_reset_ptr(::std::move(_Other));
	}

#endif /* _MST_HAS_RVALUE_REFS */

private:
	
	explicit smart_ptr(T* _Ptr, ::mst::_Details::_Refblock_base* _Block)
	{
		_reset_ptr(_Ptr, _Block);
	}

	template<typename Deleter>
	explicit smart_ptr(::mst::_Details::_Refblock_object<T, Deleter>* _Block)
	{
		this->_reset_ptr(_Block->_Get_ptr(), _Block);
	}

	explicit smart_ptr(::mst::_Details::_Refblock_array<T>* _Block)
	{
		this->_reset_ptr(_Block->_Get_ptr(), _Block);
	}

private:

	friend class enable_smart_this_ptr;

	template<typename T2>
	friend class smart_ptr;

	template<typename T2>
	friend class ::mst::_Details::_Smart_ptr_accessor;

	friend class ::mst::_Details::_Smart_ptr_caster;

}; // class smart_ptr<T>

template<typename T>
inline ::mst::smart_ptr<T> (::mst::back_ptr<T>::lock)() const _MST_NOEXCEPT
{
	return smart_ptr<T>(*this);
}

class enable_smart_this_ptr
{
	friend class ::mst::_Details::_Refblock_base;
protected:
	enable_smart_this_ptr()
		: _Block(null)
	{}

	~enable_smart_this_ptr()
	{}

	template<typename T>
	smart_ptr<T> _Smart_this_ptr(T* _Ptr)
	{
#if _MST_HAS_TYPE_TRAITS
		static_assert(std::is_base_of<enable_smart_this_ptr, T>::value, "invalid use of enable_smart_this_ptr, use the smart_this_ptr macro");
#endif
		
		const void* _This = reinterpret_cast<const void*>(this);
		const void* _Begin = reinterpret_cast<const void*>(_Ptr);
		const void* _End = reinterpret_cast<const void*>(_Ptr + 1);

		CHECK_ITER_RANGE(_This, _Begin, _End, "invalid use of enable_smart_this_ptr, use the smart_this_ptr macro");
		CHECK_IF(_Block == null, "invalid call, this object was not created by a smart_ptr");
		return smart_ptr<T>(_Ptr, _Block);
	}

	template<typename T>
	smart_ptr<const T> _Smart_this_ptr(const T* _Ptr) const
	{
#if _MST_HAS_TYPE_TRAITS
		static_assert(std::is_base_of<enable_smart_this_ptr, T>::value, "invalid use of enable_smart_this_ptr, use the smart_this_ptr macro");
#endif

		const void* _This = reinterpret_cast<const void*>(this);
		const void* _Begin = reinterpret_cast<const void*>(_Ptr);
		const void* _End = reinterpret_cast<const void*>(_Ptr + 1);

		CHECK_ITER_RANGE(_This, _Begin, _End, "invalid use of enable_smart_this_ptr, use the smart_this_ptr macro");
		CHECK_IF(_Block == null, "invalid call, this object was not created by a smart_ptr");
		return smart_ptr<const T>(_Ptr, _Block);
	}

private:
	::mst::_Details::_Refblock_base* _Block;
};

	namespace _Details {

#if _MST_HAS_LAMBDAS

	template<typename T, typename _Fun, typename _Deleter>
	inline ::mst::smart_ptr<T> _Make_smart_ptr(_Fun _Func, _Deleter _Custom_deleter)
	{
		static_assert(::std::is_array<T>::value == false, "_Make_smart_ptr(): T may not be an array type");

		return ::mst::_Details::_Smart_ptr_accessor<T>::_Construct(new _Refblock_object<T, _Deleter>(::std::move(_Func),::std::move(_Custom_deleter)));
	}

#endif

	template<typename T>
	inline ::mst::smart_ptr<T> _Make_smart_ptr(T* _Object)
	{
		static_assert(::std::is_array<T>::value == false, "_Make_smart_ptr(): T may not be an array type");

		return ::mst::smart_ptr<T>(_Object);
	}

	template<typename T, typename Deleter>
	inline ::mst::smart_ptr<T> _Make_smart_ptr(T* _Object, Deleter _Custom_deleter)
	{
		static_assert(::std::is_array<T>::value == false, "_Make_smart_ptr(): T may not be an array type");

		return ::mst::smart_ptr<T>(_Object,
#if _MST_HAS_RVALUE_REFS
			::std::move(_Custom_deleter);
#else // !_MST_HAS_RVALUE_REFS
			_Custom_deleter
#endif // _MST_HAS_RVALUE_REFS
			);
	}


	}; // namespace _Details

}; // namespace mst

#endif /* MSMART_PTR_H */