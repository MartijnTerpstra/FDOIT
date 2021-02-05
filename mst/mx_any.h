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

class _Concept
{
public:
	virtual _Concept* MST_API _Clone() = 0;

	virtual void MST_API _Release() = 0;
};

template<typename T>
struct _Model final : public _Concept
{
public:
	inline _Model(const typename ::std::remove_reference<T>::type& _Value)
		: _Myvalue(_Value)
	{
	}

	inline _Model(typename ::std::remove_reference<T>::type& _Value)
		: _Myvalue(_Value)
	{
	}

	inline _Model(typename ::std::remove_reference<T>::type&& _Value)
		: _Myvalue(move(_Value))
	{
	}

	_Concept* MST_API _Clone() override
	{
		return new _Model(_Myvalue);
	}

	void MST_API _Release() override
	{
		delete this;
	}

	T _Myvalue;
};

}; // namespace _Details
}; // namespace mst