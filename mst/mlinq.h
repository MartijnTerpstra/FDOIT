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

#include <mcommon.h>

namespace mst {

class linq
{
public:

	template<typename T, typename Fun>
	inline static bool any(const T& container, Fun fun)
	{
		mst_foreach(const auto& it, container)
		{
			if(fun(it))
				return true;
		}

		return false;
	}

	template<typename T>
	inline static bool any(const T& container)
	{
		mst_foreach(const auto& it, container)
		{
			return true;
		}

		return false;
	}

	template<typename T>
	inline static decltype(auto) single(const T& container)
	{
		if(!any(container))
			throw ::std::invalid_argument("container does not contain any elements");

		const auto* retval = &::std::begin(container);

		bool isSingle = false;

		mst_foreach(const auto& it, container)
		{
			if(isSingle)
				throw ::std::invalid_argument("container contains more than 1 result");

			isSingle = true;
			retval = &it;
		}

		if(!isSingle)
			throw ::std::invalid_argument("container does not contain any results");

		return *retval;
	}

	template<typename T>
	inline static decltype(auto) single(T& container)
	{
		if(!any(container))
			throw ::std::invalid_argument("container does not contain any elements");

		auto* retval = &::std::begin(container);

		bool isSingle = false;

		mst_foreach(auto& it, container)
		{
			if(isSingle)
				throw ::std::invalid_argument("container contains more than 1 result");

			isSingle = true;
			retval = &it;
		}

		if(!isSingle)
			throw ::std::invalid_argument("container does not contain any results");

		return *retval;
	}

	template<typename T, typename Telem, typename Fun>
	inline static const Telem& single(const T& container, Fun fun)
	{
		if(!any(container))
			throw ::std::invalid_argument("container does not contain any elements");

		const auto* retval = &::std::begin(container);

		bool isSingle = false;

		mst_foreach(const auto& it, container)
		{
			if(fun(it))
			{
				if(isSingle)
					throw ::std::invalid_argument("container contains more than 1 result");

				isSingle = true;
				retval = &it;
			}
		}

		if(!isSingle)
			throw ::std::invalid_argument("container does not contain any results");

		return *retval;
	}

	template<typename T, typename Telem, typename Fun>
	inline static Telem& single(T& container, Fun fun)
	{
		if(!any(container))
			throw ::std::invalid_argument("container does not contain any elements");

		auto* retval = &::std::begin(container);

		bool isSingle = false;

		mst_foreach(auto& it, container)
		{
			if(fun(it))
			{
				if(isSingle)
					throw ::std::invalid_argument("container contains more than 1 result");

				isSingle = true;
				retval = &it;
			}
		}

		if(!isSingle)
			throw ::std::invalid_argument("container does not contain any results");

		return *retval;
	}

}; // class linq

}; // namespace mst