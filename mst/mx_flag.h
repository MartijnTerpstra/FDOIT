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

#if _MST_HAS_VARIADIC_TEMPLATES

#if MST_DEBUGMODE

template<typename FlagTraits, typename T>
inline void _Check_flags(size_t argCount, T arg)
{
	CHECK_IF((unsigned long long)arg > FlagTraits::max_value, "invalid flag size");
};

template<typename FlagTraits, typename First, typename... T>
inline void _Check_flags(size_t argCount, First first, T... args)
{
	CHECK_IF((unsigned long long)first > FlagTraits::max_value, "invalid flag size");
	_Check_flags<FlagTraits>(argCount, args...);
};

#else // !MST_DEBUGMODE

template<typename FlagTraits, typename T>
inline void _Check_flags(size_t argCount, T arg)
{
	// do nothing
	(void)argCount;
	(void)arg;
};

template<typename FlagTraits, typename First, typename... T>
inline void _Check_flags(size_t argCount, First first, T... args)
{
	// do nothing
	(void)argCount;
	(void)first;
	_Check_flags<FlagTraits>(argCount, args...);
};

#endif // MST_DEBUGMODE

#else /* !_MST_HAS_VARIADIC_TEMPLATES */

#if MST_DEBUGMODE

template<typename FlagTraits, typename First>
void _Check_flags(size_t argCount, ...)
{
	va_list argList;
	va_start(argList, argCount);
	for(size_t i = 0; i < argCount; i++)
	{
		First arg = va_arg(argList, First);

		CHECK_IF(arg > FlagTraits::max_value, "invalid flag size");
	}
	va_end(argList);
};

#else /* !MST_DEBUGMODE */

template<typename FlagTraits, typename First>
void _Check_flags(size_t argCount, ...)
{
	/* do nothing */
};

#endif /* _MST_HAS_VARIADIC_TEMPLATES */

#endif /* !MST_DEBUGMODE */

}; // namespace _Details
}; // namespace mst