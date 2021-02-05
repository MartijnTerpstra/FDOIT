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
#include <mx_aligned_unique_ptr.h>

namespace mst {

template<typename T>
class aligned_unique_ptr
{
#if _MST_HAS_DEFAULT_DELETE
	aligned_unique_ptr(const aligned_unique_ptr&) = delete;
	aligned_unique_ptr& operator = (const aligned_unique_ptr&) = delete;
#else
	aligned_unique_ptr(const aligned_unique_ptr&);
	aligned_unique_ptr& operator = (const aligned_unique_ptr&);
#endif

public:

	aligned_unique_ptr()
		: _Ptr((T*)0)
	{}

	aligned_unique_ptr(aligned_unique_ptr&& other)
		: _Ptr(other._Ptr)
	{ 
		other._Ptr = null;
	}

	explicit aligned_unique_ptr(::mst::_Details::_Aligned_unique_block<T>* _Block)
		: _Myblock(_Block)
	{ }

	~aligned_unique_ptr()
	{
		_Release();
	}

	aligned_unique_ptr& operator = (aligned_unique_ptr&& other)
	{
		::std::swap(_Myblock, other._Myblock);
		return *this;
	}

	T* get() const
	{
		return _Myblock != null ? (T*)_Myblock->_Get_storage() : null;
	}

	T* operator -> () const
	{
		return get();
	}

	T* release()
	{
		T* retval = get();
		_Myblock = null;
	}

private:

	void _Release()
	{
		if(_Myblock)
		{
			::std::_Destroy((T*)_Myblock->_Get_storage());
			delete _Myblock;
			_Myblock = null;
		}
	}

private:
	::mst::_Details::_Aligned_unique_block<T>* _Myblock;
};

#if _MST_VARIADIC_TEMPLATE_HACK_SUPPORTED
#define MST_VARIADIC_INCLUDE <mx_make_aligned_unique.h>
#include <mvariadic_template.h>
#else
template<typename T>
smart_ptr<T> make_smart()
{
	return make_smart_ptr(T());
}
#endif

}; // namespace mst