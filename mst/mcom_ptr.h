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

#ifndef MCOM_PTR_H
#define MCOM_PTR_H

#include <mcore.h>
#include <mdebug.h>
#include <mx_cast.h>
#include <Unknwn.h>
#include <mx_com_ptr.h>

namespace mst {

template<typename T>
class com_ptr
{

	_MST_TYPEDEF_BOOLEAN_TYPE(com_ptr);

public:

	typedef T element_type;

public:
	explicit com_ptr() _MST_NOEXCEPT
		: _MyPtr((T*)0)
	{
	}

	explicit com_ptr(T* _Ptr) _MST_NOEXCEPT
	{
		this->_MyPtr = _Ptr;
		// do not add reference
	}

	com_ptr(const com_ptr& _Other) _MST_NOEXCEPT
	{
		this->_MyPtr = _Other._MyPtr;
		_Add_ref();
	}

	com_ptr(::std::nullptr_t) _MST_NOEXCEPT
		: _MyPtr((T*)0)
	{
	}

	template<typename T2>
	com_ptr(const com_ptr<T2>& _Other, T* _Dummy = typename ::mst::pointer<T2>::type()) _MST_NOEXCEPT
	{
		_MST_UNUSED(_Dummy);
		this->_MyPtr = _Other._MyPtr;
		_Add_ref();
	}

	template<typename T2>
	com_ptr(const com_ptr<T2>& _Other, ::mst::_Details::_Mst_cast_dynamic) _MST_NOEXCEPT
	{
		_MyPtr = (T*)0;

		if(_Other._MyPtr)
		{
			_Other._MyPtr->QueryInterface<T>(&_MyPtr);
		}
	}

	template<typename T2>
	com_ptr(const com_ptr<T2>& _Other, ::mst::_Details::_Mst_cast_static) _MST_NOEXCEPT
	{
		_MyPtr = (T*)0;

		if(_Other._MyPtr)
		{
			_Other._MyPtr->QueryInterface<T>(&_MyPtr);
		}
	}

	template<typename T2>
	com_ptr(const com_ptr<T2>& _Other, ::mst::_Details::_Mst_cast_const) _MST_NOEXCEPT
	{
		_MyPtr = (T*)0;

		if(_Other._MyPtr)
		{
			_Other._MyPtr->QueryInterface<T>(&_MyPtr);
		}
	}

	// no reinterpret cast, not supported for com ptrs

	inline com_ptr& operator = (const com_ptr& _Right) _MST_NOEXCEPT
	{
		com_ptr(_Right).swap(*this);
		return (*this);
	}

	template<class T2>
	inline com_ptr& operator = (const com_ptr<T2>& _Right) _MST_NOEXCEPT
	{
		com_ptr(_Right).swap(*this);
		return (*this);
	}

	inline com_ptr& operator = (::std::nullptr_t) _MST_NOEXCEPT
	{
		_Release();
		_MyPtr = (T*)0;
		return (*this);
	}

	inline bool operator == (const com_ptr& _Other) const _MST_NOEXCEPT
	{
		return get() == _Other.get();
	}

	inline bool operator != (const com_ptr& _Other) const _MST_NOEXCEPT
	{
		return !(*this == _Other);
	}

	inline bool operator == (::std::nullptr_t) const _MST_NOEXCEPT
	{
		return this->get() == (void*)0;
	}

	inline bool operator != (::std::nullptr_t) const _MST_NOEXCEPT
	{
		return this->get() != (void*)0;
	}

	inline _MST_OPERATOR_BOOL() const _MST_NOEXCEPT
	{
		return ((_MyPtr != 0) ? _MST_CONVERTIBLE_TO_TRUE(com_ptr) : 0);
	}

	inline ULONG reset() const _MST_NOEXCEPT
	{
		if(this->_MyPtr)
		{
			return _MyPtr->Release();
		}
		return -1;
	}

	inline T* release() _MST_NOEXCEPT
	{
		T* retval = this->_MyPtr;
		this->_MyPtr = (T*)0;
		return retval;
	}

	void swap(com_ptr& _Right) _MST_NOEXCEPT
	{
		::std::swap(this->_MyPtr, _Right._MyPtr);
	}

	template<typename T2>
	com_ptr<T2> as() const
	{
		if(_MyPtr == null) { ERROR_MESG("com_ptr<T>::as(): invalid call: pointer does not point to a valid object"); }

		static_assert(::std::is_base_of<IUnknown, T2>::value, "T2 must inherit from IUnknown");
#if _MST_HAS_TYPE_TRAITS
		return _As<T2>(::std::is_convertible<T, T2>::type());
#else
		return _As<T2>(::std::false_type())
#endif
	}

	template<typename T2>
	bool is() const
	{
		if(_MyPtr == null) { ERROR_MESG("com_ptr<T>::is(): invalid call: pointer does not point to a valid object"); }

		com_ptr<T2> _Right;
		return
#if _MST_HAS_TYPE_TRAITS
			::std::is_base_of<T2, T>::value || ::std::is_same<T2, T>::value ||

#endif
			SUCCEEDED(_MyPtr->QueryInterface<T2>(::mst::initialize(_Right)));
	}

	~com_ptr() _MST_NOEXCEPT
	{
		_Release();
	}

	inline T* const * operator&() const _MST_NOEXCEPT
	{
		return &this->_MyPtr;
	}

	inline T* get() const _MST_NOEXCEPT
	{
		return this->_MyPtr;
	}

	inline T& operator * () const _MST_NOEXCEPT
	{
		return *this->get();
	}

	inline T* operator -> () const _MST_NOEXCEPT
	{
		CHECK_IF(this->get() == null, "cannot dereference a null-pointer");
		return this->get();
	}

#if _MST_HAS_RVALUE_REFS

	com_ptr(com_ptr&& _Other) _MST_NOEXCEPT
	{
		this->_MyPtr = _Other._MyPtr;
		_Other._MyPtr = (T*)0;
	}

	template<typename T2>
	com_ptr(com_ptr<T2>&& _Other, T* _Dummy = typename ::mst::pointer<T2>::type()) _MST_NOEXCEPT
	{
		_MST_UNUSED(_Dummy);
		this->_MyPtr = _Other._MyPtr;
		_Other._MyPtr = (T2*)0;
	}

#endif /* _MST_HAS_RVALUE_REFS */

private:

	template<typename T2>
	com_ptr<T2> _As(::std::true_type) const _MST_NOEXCEPT
	{
		return *this;
	}

	template<typename T2>
	com_ptr<T2> _As(::std::false_type) const
	{

		com_ptr<T2> _Right;
		if(FAILED(_MyPtr->QueryInterface<T2>(::mst::initialize(_Right))))
		{
			return null;
		}
		return _Right;
	}

	inline void _Add_ref()
	{
		if(this->_MyPtr)
		{
			_MyPtr->AddRef();
		}
	}

	inline void _Release()
	{
		if(this->_MyPtr)
		{
			_MyPtr->Release();
		}
	}


	T* _MyPtr;

	template<typename T2>
	friend class com_ptr;

	friend class ::mst::_Details::_Smart_ptr_caster;

}; // class com_ptr

template<typename T>
com_ptr<T> make_com_ptr(T* _Ptr) _MST_NOEXCEPT
{
	return com_ptr<T>(_Ptr);
}

template<typename T>
::mst::_Details::_Com_ptr_combiner<T> MST_DEPRECATED(mst::initialize(com_ptr<T>)) com_ptr_constructor(::mst::com_ptr<T>& comObject)
{
	return ::mst::_Details::_Com_ptr_combiner<T>(comObject);
}

template<typename T>
::mst::_Details::_Com_ptr_combiner<T> initialize(::mst::com_ptr<T>& comObject)
{
	return ::mst::_Details::_Com_ptr_combiner<T>(comObject);
}

#define MST_IID_PPV_ARGS(comPtr) __uuidof(::std::remove_reference<decltype(comPtr)>::type::element_type), ::mst::_Details::_Initialize_ppv_args(comPtr)

}; // namespace mst

#endif /* MCOM_PTR_H */