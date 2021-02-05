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

namespace mst {
namespace _Details {

template<typename T>
class _Array_view_base;

template<typename T>
class _Temp_wrapper;

template<typename T>
class _Array_view_iterator
{
public:
	inline _Array_view_iterator(const _Array_view_base<T>* viewer, size_t index);

	inline _Array_view_iterator& operator ++();

	inline _Array_view_iterator operator ++(int);

	inline _Temp_wrapper<T> operator * () const;

	inline bool operator == (const _Array_view_iterator& r);

	inline bool operator != (const _Array_view_iterator& r);

private:
	size_t _Myidx;
	const _Array_view_base<T>* _Mybase;
};

struct _Force_temp_tag { };

template<typename T>
class _Temp_wrapper
{
public:
	_Temp_wrapper(const T& other)
		: _Myptr(&other),
		_Istemp(false)
	{
	}

	template<typename T2>
	_Temp_wrapper(const T2& other)
		: _Temp_wrapper(other, typename ::std::is_convertible<T2*, T*>::type())
	{ }

	template<typename T2>
	_Temp_wrapper(const T2& other, _Force_temp_tag)
		: _Temp_wrapper(other, std::false_type())
	{ }

	_Temp_wrapper(const _Temp_wrapper& other)
		: _Istemp(other._Istemp),
		_Myptr(other._Istemp ? reinterpret_cast<const T*>(&_Myobject) : other._Myptr)
	{
		new (&_Myobject) T(*reinterpret_cast<const T*>(&other._Myobject));
	}

	_Temp_wrapper(_Temp_wrapper&& other)
		: _Istemp(other._Istemp),
		_Myptr(other._Istemp ? reinterpret_cast<const T*>(&_Myobject) : other._Myptr)
	{
		new (&_Myobject) T(move(*reinterpret_cast<T*>(&other._Myobject)));
	}

	~_Temp_wrapper()
	{
		if(_Istemp)
		{
			_Destroy_object(_Myptr);
		}
	}

	operator const T&() const
	{
		return *_Myptr;
	}

private:

	template<typename T2>
	_Temp_wrapper(const T2& other, ::std::true_type)
		: _Myptr(&other)
		_Istemp(false)
	{ }

	template<typename T2>
	_Temp_wrapper(const T2& other, ::std::false_type)
		: _Myptr(reinterpret_cast<T*>(&_Myobject)),
		_Istemp(true)
	{ 
		new (&_Myobject) T(other);
	}

private:
	const T* const _Myptr;
	typename ::std::aligned_storage<sizeof(T), ::std::alignment_of<T>::value>::type _Myobject;
	const bool _Istemp;
};

template<typename T>
class _Array_view_base
{
public:
	_Temp_wrapper<T> (*_Get_object_func)(const _Array_view_base<T>* viewBase, size_t idx);

	const void* _Mycontainer;
	size_t _Mysize;
};

template<typename T, typename ContainerType>
class _Array_view_container
{
public:
	inline static void _Init(_Array_view_base<T>& base, const ContainerType& container)
	{
		base._Get_object_func = &_Get_object;
		base._Mycontainer = &container;
		base._Mysize = container.size();
	}

	inline static _Temp_wrapper<T> _Get_object(const _Array_view_base<T>* viewBase, size_t idx)
	{
		const ContainerType& cont = *reinterpret_cast<const ContainerType*>(viewBase->_Mycontainer);

		return cont[idx];
	}
};

template<typename T, typename T2>
class _Array_view_initlist
{
public:
	inline static void _Init(_Array_view_base<T>& base, const std::initializer_list<T2>& container)
	{
		base._Get_object_func = &_Get_object;
		base._Mycontainer = &container;
		base._Mysize = container.size();
	}

	inline static _Temp_wrapper<T> _Get_object(const _Array_view_base<T>* viewBase, size_t idx)
	{
		const std::initializer_list<T2>& cont = *reinterpret_cast<const std::initializer_list<T2>*>(viewBase->_Mycontainer);

		return { cont.begin()[idx], ::mst::_Details::_Force_temp_tag() };
	}
};

template<typename T, typename T2, size_t ArraySize>
class _Array_view_array
{
	typedef T(&ArrayType)[ArraySize];
	typedef const T(&ConstArrayType)[ArraySize];
public:

	inline static void _Init(_Array_view_base<T>& base, ArrayType arr)
	{
		base._Get_object_func = &_Get_object;
		base._Mycontainer = static_cast<const T2*>(array);
		base._Mysize = ArraySize;
	}

	inline static void _Init(_Array_view_base<T>& base, ConstArrayType arr)
	{
		base._Get_object_func = &_Get_object;
		base._Mycontainer = static_cast<const T2*>(array);
		base._Mysize = ArraySize;
	}

private:

	inline static _Temp_wrapper<T> _Get_object(const _Array_view_base<T>* viewBase, size_t idx)
	{
		const T2* cont = reinterpret_cast<const T2*>(viewBase->_Mycontainer);

		CHECK_ARR_RANGE(idx, ArraySize, "index out of range");

		return arr[idx];
	}
};

template<typename T, typename T2>
class _Array_view_ptr_size
{
public:

	inline static void _Init(_Array_view_base<T>& base, const T2* ptr, size_t size)
	{
		base._Get_object_func = &_Get_object;
		base._Mycontainer = ptr;
		base._Mysize = size;
	}

private:

	inline static _Temp_wrapper<T> _Get_object(const _Array_view_base<T>* viewBase, size_t idx)
	{
		const T2* ptr = reinterpret_cast<const T2*>(viewBase->_Mycontainer);

		CHECK_ARR_RANGE(idx, viewBase->_Mysize, "index out of range");

		return ptr[idx];
	}

};

}; // namespace _Details
}; // namespace mst

template<typename T>
inline mst::_Details::_Array_view_iterator<T>::_Array_view_iterator(const mst::_Details::_Array_view_base<T>* viewer, size_t index)
	: _Mybase(viewer),
	_Myidx(index)
{
}

template<typename T>
inline mst::_Details::_Array_view_iterator<T>& mst::_Details::_Array_view_iterator<T>::operator++()
{
	++_Myidx;

	return *this;
}

template<typename T>
inline mst::_Details::_Array_view_iterator<T> mst::_Details::_Array_view_iterator<T>::operator++(int)
{
	return _Array_view_iterator(_Mybase, _Myidx++);
}

template<typename T>
inline mst::_Details::_Temp_wrapper<T> mst::_Details::_Array_view_iterator<T>::operator*() const
{
	return _Mybase->_Get_object_func(_Mybase, _Myidx);
}

template<typename T>
inline bool mst::_Details::_Array_view_iterator<T>::operator==(const mst::_Details::_Array_view_iterator<T>& r)
{
	return _Mybase == r._Mybase && _Myidx == r._Myidx;
}

template<typename T>
inline bool mst::_Details::_Array_view_iterator<T>::operator!=(const mst::_Details::_Array_view_iterator<T>& r)
{
	return _Mybase != r._Mybase || _Myidx != r._Myidx;
}