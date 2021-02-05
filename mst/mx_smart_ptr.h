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
#include <mx_cast.h>

namespace mst {

template<typename _Ty>
class back_ptr;

class enable_smart_this_ptr;

class smart_ptr_access
{
public:
	template<typename T>
	inline static void destruct(T* pointer)
	{
		pointer->~T();
	}

	template<typename T>
	inline static void deallocate(T* pointer)
	{
		delete pointer;
	}

#if _MST_VARIADIC_TEMPLATE_HACK_SUPPORTED
#define MST_VARIADIC_INCLUDE <mx_smart_ptr_access_construct.h>
#include <mvariadic_template.h>
#else

	template<typename T>
	inline static void construct_placed(void* memory)
	{
		new (memory) T();
	}

	template<typename T>
	inline static T* construct()
	{
		return new T();
	}
#endif
};

namespace _Details {

template<typename _Ty, bool _Is_void = ::std::is_void<_Ty>::value>
class _Smart_ptr_base
{
	template<typename _Tx>
	friend class smart_ptr;

	template<typename _Tx>
	friend class back_ptr;

	_MST_TYPEDEF_BOOLEAN_TYPE(_Smart_ptr_base);

public:

	~_Smart_ptr_base()
	{
		this->_dec_ref();
	}

	inline _Ty* get() const
	{
		return this->_MyPtr;
	}

	inline _MST_OPERATOR_BOOL() const
	{
		return (this->_MyPtr != null ? _MST_CONVERTIBLE_TO_TRUE(_Smart_ptr_base) : 0);
	}

	inline refcount_t use_count() const
	{
		return (_MyBlock->_Is_valid() ? _MyBlock->_Use_count() : 0);
	}

	inline refcount_t back_count() const
	{
		return (_MyBlock->_Is_valid() ? _MyBlock->_Back_count() : 0);
	}

protected:
	// internal usage

	inline void _orphan()
	{
		this->_MyBlock = _Refblock_static::_Get_null_block();
	}

	inline void _reset_ptr(_Ty* _Ptr, ::mst::_Details::_Refblock_base* _Block)
	{ // _Refblockbase type, increment because it is not the first reference
		this->_MyPtr = _Ptr;
		this->_MyBlock = _Block;

		this->_MyBlock->_Inc();
	}

	template<typename _Tx>
	inline void _reset_ptr(const _Smart_ptr_base<_Tx>& _Other)
	{
		_MyPtr = _Other._MyPtr;
		_MyBlock = _Other._MyBlock;

		this->_MyBlock->_Inc();
	}

	template<typename _Tx>
	inline void _reset_ptr(const _Smart_ptr_base<_Tx>& _Other, ::mst::_Details::_Mst_cast_dynamic)
	{
		_MyPtr = dynamic_cast<_Ty*>(_Other._MyPtr);
		if(_MyPtr)
		{
			this->_MyBlock = _Other._MyBlock;
			this->_MyBlock->_Inc();
		}
		else
		{
			this->_MyBlock = _Refblock_static::_Get_null_block();
		}

	}

	template<typename _Tx>
	inline void _reset_ptr(const _Smart_ptr_base<_Tx>& _Other, ::mst::_Details::_Mst_cast_static)
	{
		_MyPtr = static_cast<_Ty*>(_Other._MyPtr);
		_MyBlock = _Other._MyBlock;

		this->_MyBlock->_Inc();
	}

	template<typename _Tx>
	inline void _reset_ptr(const _Smart_ptr_base<_Tx>& _Other, ::mst::_Details::_Mst_cast_const)
	{
		_MyPtr = const_cast<_Ty*>(_Other._MyPtr);
		_MyBlock = _Other._MyBlock;

		this->_MyBlock->_Inc();
	}

	template<typename _Tx>
	inline void _reset_ptr(const _Smart_ptr_base<_Tx>& _Other, ::mst::_Details::_Mst_cast_reinterpret)
	{
		_MyPtr = reinterpret_cast<_Ty*>(_Other._MyPtr);
		_MyBlock = _Other._MyBlock;

		this->_MyBlock->_Inc();
	}

#if _MST_HAS_RVALUE_REFS
	template<typename _Tx>
	inline void _reset_ptr(_Smart_ptr_base<_Tx>&& _Other)
	{
		_MyPtr = _Other._MyPtr;
		_MyBlock = _Other._MyBlock;

		_Other._orphan();
	}

	template<typename _Tx>
	inline void _reset_ptr(_Smart_ptr_base<_Tx>&& _Other, ::mst::_Details::_Mst_cast_dynamic)
	{
		_MyPtr = dynamic_cast<_Ty*>(_Other._MyPtr);

		if(_MyPtr)
		{
			_MyBlock = _Other._MyBlock;
			_Other._orphan();
		}
		else
		{
			_MyBlock = _Refblock_static::_Get_null_block();
		}
	}

	template<typename _Tx>
	inline void _reset_ptr(_Smart_ptr_base<_Tx>&& _Other, ::mst::_Details::_Mst_cast_static)
	{
		_MyPtr = static_cast<_Ty*>(_Other._MyPtr);
		_MyBlock = _Other._MyBlock;

		_Other._orphan();
	}

	template<typename _Tx>
	inline void _reset_ptr(_Smart_ptr_base<_Tx>&& _Other, ::mst::_Details::_Mst_cast_const)
	{
		_MyPtr = const_cast<_Ty*>(_Other._MyPtr);
		_MyBlock = _Other._MyBlock;

		_Other._orphan();
	}

	template<typename _Tx>
	inline void _reset_ptr(_Smart_ptr_base<_Tx>&& _Other, ::mst::_Details::_Mst_cast_reinterpret)
	{
		_MyPtr = reinterpret_cast<_Ty*>(_Other._MyPtr);
		_MyBlock = _Other._MyBlock;

		_Other._orphan();
	}

#endif // _MST_HAS_RVALUE_REFS

	template<typename _Tb>
	inline void _reset_ptr(_Ty* _Ptr, _Tb* _Block)
	{ // non _Refblockbase type, must not increment reference because it's the first reference
		MST_STATIC_ASSERT((::std::is_same<_Refblock_base, _Tb>::value == false), "_Tb must derive of _Refblockbase");

		this->_MyPtr = _Ptr;
		this->_MyBlock = _Block;
	}

	inline void _dec_ref()
	{
		this->_MyBlock->_Dec();
	}

	inline void _inc_ref()
	{
		this->_MyBlock->_Inc();
	}

	inline void swap(_Smart_ptr_base& _Right)
	{
		::std::swap(this->_MyPtr, _Right._MyPtr);
		::std::swap(this->_MyBlock, _Right._MyBlock);
	}

	bool _Is_valid() const
	{
		return _MyBlock != null && _MyBlock->_Is_valid();
	}

	_Ty* _MyPtr;
	::mst::_Details::_Refblock_base* _MyBlock;

	template<typename _Ty, bool _Is_void>
	friend class _Smart_ptr_base;

	// for no initializing at default constructing
	struct _No_init_ptr {};

}; // class _Smart_ptr_base

template<typename _Ty>
class _Smart_ptr_base<_Ty, false> : public _Smart_ptr_base<_Ty, true>
{
public:

	inline _Ty* operator -> () const
	{
		CHECK_IFNOT(_Is_valid(), "cannot dereference a pointer to invalid memory");
		return this->_MyPtr;
	}

	inline _Ty& operator * () const
	{
		CHECK_IFNOT(_Is_valid(), "cannot dereference a pointer to invalid memory");
		return *this->_MyPtr;
	}

	inline _Ty& operator [] (size_t _Idx) const
	{
		CHECK_IFNOT(_Is_valid(), "cannot dereference a pointer to invalid memory");
		return this->_MyPtr[_Idx];
	}
};

template<typename T>
class _Smart_ptr_accessor
{
public:

	template<typename Deleter>
	static smart_ptr<T> _Construct(::mst::_Details::_Refblock_object<T, Deleter>* _Block)
	{
		return smart_ptr<T>(_Block);
	}
};

}; }; // namespace mst::_Details