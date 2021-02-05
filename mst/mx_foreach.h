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


class _Foreach_iter_wrapper
{
public:
	operator bool() const
	{
		return true;
	}
};

template<typename Iterator>
class _Foreach_iter_wrapper_impl : public _Foreach_iter_wrapper
{
public:
	_Foreach_iter_wrapper_impl(const Iterator& inIter)
		: iter(inIter)
	{}

	typedef Iterator iter_type;

	mutable Iterator iter;
};

template<typename Container>
struct _Foreach_iter_type
{
	typedef typename Container::iterator type;
	typedef typename Container::const_iterator ctype;
	typedef typename Container::reference reference_type;
	typedef typename Container::const_reference creference_type;
};

template<typename T, size_t N>
struct _Foreach_iter_type<T[N]>
{
	typedef typename T* type;
	typedef typename T* ctype;
	typedef typename T& reference_type;
	typedef typename const T& creference_type;
};

template<typename Container>
typename Container::iterator _Foreach_begin(Container& c)
{
	return c.begin();
}

template<typename Container>
typename Container::const_iterator _Foreach_begin(const Container& c)
{
	return c.begin();
}

template<typename T, size_t N>
typename T* _Foreach_begin(T(&array)[N])
{
	return array;
}

template<typename Container>
typename Container::iterator _Foreach_end(Container& c)
{
	return c.end();
}

template<typename Container>
typename Container::const_iterator _Foreach_end(const Container& c)
{
	return c.end();
}

template<typename T, size_t N>
typename T* _Foreach_end(T(&array)[N])
{
	return array + N;
}

template<typename Container>
_Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::type> _Foreach_get_begin(Container& container)
{
	return _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::type>(_Foreach_begin(container));
}

template<typename Container>
_Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::ctype> _Foreach_get_begin(const Container& container)
{
	return _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::ctype>(_Foreach_begin(container));
}

template<typename Container>
_Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::type> _Foreach_get_end(Container& container)
{
	return _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::type>(_Foreach_end(container));
}

template<typename Container>
_Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::ctype> _Foreach_get_end(const Container& container)
{
	return _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::ctype>(_Foreach_end(container));
}

template<typename Container>
typename _Foreach_iter_type<Container>::reference_type _Foreach_get_value(const _Foreach_iter_wrapper& wrap, Container&)
{
return *static_cast<const _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::type>&>(wrap).iter;
}

template<typename Container>
typename _Foreach_iter_type<Container>::creference_type _Foreach_get_value(const _Foreach_iter_wrapper& wrap, const Container&)
{
	return *static_cast<const _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::ctype>&>(wrap).iter;
}

template<typename Container>
void _Foreach_increment(const _Foreach_iter_wrapper& wrap, Container&)
{
	++static_cast<const _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::type>&>(wrap).iter;
}

template<typename Container>
void _Foreach_increment(const _Foreach_iter_wrapper& wrap, const Container&)
{
	++static_cast<const _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::ctype>&>(wrap).iter;
}

template<typename Container>
bool _Foreach_not_done(const _Foreach_iter_wrapper& begin, const _Foreach_iter_wrapper& end, Container&)
{
	return static_cast<const _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::type>&>(begin).iter !=
		static_cast<const _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::type>&>(end).iter;
}

template<typename Container>
bool _Foreach_not_done(const _Foreach_iter_wrapper& begin, const _Foreach_iter_wrapper& end, const Container&)
{
	return static_cast<const _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::ctype>&>(begin).iter !=
		static_cast<const _Foreach_iter_wrapper_impl<typename _Foreach_iter_type<Container>::ctype>&>(end).iter;
}

}; // namespace _Details
}; // namespace mst