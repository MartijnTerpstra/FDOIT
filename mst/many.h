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
#include <mcompiletime.h>
#include <mx_any.h>

namespace mst {

class any
{
public:

	any()
		: _Myconcept(null),
		 _Myhash(0),
		_Mytypename("")
	{}

	template<typename T>
	any(const T& t)
		: _Myconcept(new ::mst::_Details::_Model<::std::remove_cv<T>::type>(t)),
		_Myhash(mst::compiletime::hash_of64<::std::remove_cv<T>::type>()),
		_Mytypename(mst::typename_of<::std::remove_cv<T>::type>())
	{}

	template<typename T>
	any(T&& t)
		: _Myconcept(new ::mst::_Details::_Model<std::remove_cv_t<T>>(move(t))),
		_Myhash(mst::compiletime::hash_of64<::std::remove_cv<T>::type>()),
		_Mytypename(mst::typename_of<::std::remove_cv<T>::type>())
	{}

	any(const any& other)
		: _Myconcept(other._Myconcept->_Clone()),
		_Myhash(other._Myhash),
		_Mytypename(other._Mytypename)
	{}

	any(any&& other)
		: _Myconcept(other._Myconcept),
		_Myhash(other._Myhash),
		_Mytypename(other._Mytypename)
	{
		other._Myconcept = null;
	}

	~any()
	{
		_Release();
	}

	any& operator = (const any& other)
	{
		_Release();

		_Myconcept = (other._Myconcept ? other._Myconcept->_Clone() : null);
		return *this;
	}

	any& operator = (any&& other)
	{
		swap(other);
		return *this;
	}

	void clear()
	{
		_Release();
	}

	bool empty() const
	{
		return _Myconcept != null;
	}

	const char* type_name() const
	{
		return _Mytypename;
	}

	uint64 type_hash() const
	{
		return _Myhash;
	}

	template<typename T>
	bool has_type()
	{
		return _Myhash == mst::compiletime::hash_of64<::std::remove_cv<T>::type>();
	}

	bool has_type(uint64 typeHash)
	{
		return _Myhash == typeHash;
	}

	bool has_type(const any& other)
	{
		return _Myhash == other._Myhash;
	}

	void swap(any& right)
	{
		auto tempConcept = _Myconcept;
		auto tempHash = _Myhash;

		_Myconcept = right._Myconcept;
		_Myhash = right._Myhash;

		right._Myconcept = tempConcept;
		right._Myhash = tempHash;
	}

	any(::mst::_Details::_Concept* _Concept, uint64 _Hash)
		: _Myconcept(_Concept),
		_Myhash(_Hash)
	{
	}

	void _Release()
	{
		if(_Myconcept)
		{
			_Myconcept->_Release();
			_Myconcept = null;
		}
	}

	uint64 _Myhash;
	::mst::_Details::_Concept* _Myconcept;
	const char* _Mytypename;
};

template<typename T>
inline T any_cast(::mst::any& any)
{
	if(any.has_type<T>())
	{
		return static_cast<::mst::_Details::_Model<::std::remove_cv<T>::type>*>(any._Myconcept)->_Myvalue;
	}

	throw ::std::bad_cast();
}

inline void swap(any& left, any& right)
{
	left.swap(right);
}

template<typename T>
inline ::mst::any make_any(const T& t)
{
	return ::mst::any(new ::mst::_Details::_Model<::std::remove_cv<T>::type>(t), mst::compiletime::hash_of64<::std::remove_cv<T>::type>());
}

template<typename T>
inline ::mst::any make_any(T&& t)
{
	return ::mst::any(new ::mst::_Details::_Model<::std::remove_cv<T>::type>(move(t)), mst::compiletime::hash_of64<::std::remove_cv<T>::type>());
}

}; // namespace mst