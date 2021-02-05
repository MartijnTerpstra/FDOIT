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

#include <mx_foreach.h>

namespace mst {

template<typename T>
class iterator_range;

namespace _Details {

template<typename Iterator>
typename Iterator _Foreach_begin(const iterator_range<Iterator>& c)
{
	return c.begin();
}

template<typename Iterator>
typename Iterator _Foreach_end(const iterator_range<Iterator>& c)
{
	return c.end();
}

template<typename Iterator>
struct _Foreach_iter_type<iterator_range<Iterator>>
{
	typedef typename Iterator type;
	typedef typename Iterator ctype;
	typedef typename std::iterator_traits<Iterator>::reference reference_type;
	typedef typename std::iterator_traits<Iterator>::reference creference_type;
};

}; // namespace _Details
}; // namespace mst