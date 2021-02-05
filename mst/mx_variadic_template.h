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


#if !_MST_VARIADIC_TEMPLATE_HACK_SUPPORTED
#error "variadic templates require C++11"
#endif // !_MST_VARIADIC_TEMPLATE_HACK_SUPPORTED

// note: no include guards

#undef MST_VARIADIC_TEMPLATE_DECL				
#undef MST_VARIADIC_TEMPLATE					
#undef MST_VARIADIC_TEMPLATE_TYPES				
#undef MST_VARIADIC_TEMPLATE_TYPES_COMMA		
#undef MST_VARIADIC_TEMPLATE_REFFS				
#undef MST_VARIADIC_TEMPLATE_REFFS_COMMA		
#undef MST_VARIADIC_TEMPLATE_COPIES			
#undef MST_VARIADIC_TEMPLATE_COPIES_COMMA		
#undef MST_VARIADIC_TEMPLATE_FORWARDS			
#undef MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	

#if MST_VARIADIC_TEMPLATE_COUNT == -1

#undef MST_VARIADIC_TEMPLATE_COUNT

#define MST_VARIADIC_TEMPLATE_COUNT 0
#define MST_VARIADIC_TEMPLATE_DECL				
#define MST_VARIADIC_TEMPLATE					
#define MST_VARIADIC_TEMPLATE_TYPES				
#define MST_VARIADIC_TEMPLATE_TYPES_COMMA		
#define MST_VARIADIC_TEMPLATE_REFFS				
#define MST_VARIADIC_TEMPLATE_REFFS_COMMA		
#define MST_VARIADIC_TEMPLATE_COPIES			
#define MST_VARIADIC_TEMPLATE_COPIES_COMMA		
#define MST_VARIADIC_TEMPLATE_FORWARDS			
#define MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	

#elif MST_VARIADIC_TEMPLATE_COUNT == 0
// not end iteration proceed to new 
#undef MST_VARIADIC_TEMPLATE_COUNT

#define MST_VARIADIC_TEMPLATE_COUNT 1
#define MST_VARIADIC_TEMPLATE_DECL				template<typename Arg0>
#define MST_VARIADIC_TEMPLATE					, typename Arg0
#define MST_VARIADIC_TEMPLATE_TYPES				Arg0
#define MST_VARIADIC_TEMPLATE_TYPES_COMMA		, Arg0
#define MST_VARIADIC_TEMPLATE_REFFS				Arg0&& arg0
#define MST_VARIADIC_TEMPLATE_REFFS_COMMA		, Arg0&& arg0
#define MST_VARIADIC_TEMPLATE_COPIES			Arg0 arg0
#define MST_VARIADIC_TEMPLATE_COPIES_COMMA		, Arg0 arg0
#define MST_VARIADIC_TEMPLATE_FORWARDS			::std::forward<Arg0>(arg0)
#define MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	, ::std::forward<Arg0>(arg0)

#elif MST_VARIADIC_TEMPLATE_COUNT == 1

#undef MST_VARIADIC_TEMPLATE_COUNT
#define MST_VARIADIC_TEMPLATE_COUNT 2
#define MST_VARIADIC_TEMPLATE_DECL				template<typename Arg0, typename Arg1>
#define MST_VARIADIC_TEMPLATE					, typename Arg0, typename Arg1
#define MST_VARIADIC_TEMPLATE_TYPES				Arg0, Arg1
#define MST_VARIADIC_TEMPLATE_TYPES_COMMA		, Arg0, Arg1
#define MST_VARIADIC_TEMPLATE_REFFS				Arg0&& arg0, Arg1&& arg1
#define MST_VARIADIC_TEMPLATE_REFFS_COMMA		, Arg0&& arg0, Arg1&& arg1
#define MST_VARIADIC_TEMPLATE_COPIES			Arg0 arg0, Arg1 arg1
#define MST_VARIADIC_TEMPLATE_COPIES_COMMA		, Arg0 arg0, Arg1 arg1
#define MST_VARIADIC_TEMPLATE_FORWARDS			::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1)
#define MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	, ::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1)

#elif MST_VARIADIC_TEMPLATE_COUNT == 2

#undef MST_VARIADIC_TEMPLATE_COUNT
#define MST_VARIADIC_TEMPLATE_COUNT 3
#define MST_VARIADIC_TEMPLATE_DECL				template<typename Arg0, typename Arg1, typename Arg2>
#define MST_VARIADIC_TEMPLATE					, typename Arg0, typename Arg1, typename Arg2
#define MST_VARIADIC_TEMPLATE_TYPES				Arg0, Arg1, Arg2
#define MST_VARIADIC_TEMPLATE_TYPES_COMMA		, Arg0, Arg1, Arg2
#define MST_VARIADIC_TEMPLATE_REFFS				Arg0&& arg0, Arg1&& arg1, Arg2&& arg2
#define MST_VARIADIC_TEMPLATE_REFFS_COMMA		, Arg0&& arg0, Arg1&& arg1, Arg2&& arg2
#define MST_VARIADIC_TEMPLATE_COPIES			Arg0 arg0, Arg1 arg1, Arg2 arg2
#define MST_VARIADIC_TEMPLATE_COPIES_COMMA		, Arg0 arg0, Arg1 arg1, Arg2 arg2
#define MST_VARIADIC_TEMPLATE_FORWARDS			::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2)
#define MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	, ::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2)

#elif MST_VARIADIC_TEMPLATE_COUNT == 3

#undef MST_VARIADIC_TEMPLATE_COUNT
#define MST_VARIADIC_TEMPLATE_COUNT 4
#define MST_VARIADIC_TEMPLATE_DECL				template<typename Arg0, typename Arg1, typename Arg2, typename Arg3>
#define MST_VARIADIC_TEMPLATE					, typename Arg0, typename Arg1, typename Arg2, typename Arg3
#define MST_VARIADIC_TEMPLATE_TYPES				Arg0, Arg1, Arg2, Arg3
#define MST_VARIADIC_TEMPLATE_TYPES_COMMA		, Arg0, Arg1, Arg2, Arg3
#define MST_VARIADIC_TEMPLATE_REFFS				Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3
#define MST_VARIADIC_TEMPLATE_REFFS_COMMA		, Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3
#define MST_VARIADIC_TEMPLATE_COPIES			Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3
#define MST_VARIADIC_TEMPLATE_COPIES_COMMA		, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3
#define MST_VARIADIC_TEMPLATE_FORWARDS			::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3)
#define MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	, ::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3)

#elif MST_VARIADIC_TEMPLATE_COUNT == 4

#undef MST_VARIADIC_TEMPLATE_COUNT
#define MST_VARIADIC_TEMPLATE_COUNT 5
#define MST_VARIADIC_TEMPLATE_DECL				template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
#define MST_VARIADIC_TEMPLATE					, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4
#define MST_VARIADIC_TEMPLATE_TYPES				Arg0, Arg1, Arg2, Arg3, Arg4
#define MST_VARIADIC_TEMPLATE_TYPES_COMMA		, Arg0, Arg1, Arg2, Arg3, Arg4
#define MST_VARIADIC_TEMPLATE_REFFS				Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4
#define MST_VARIADIC_TEMPLATE_REFFS_COMMA		, Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4
#define MST_VARIADIC_TEMPLATE_COPIES			Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4
#define MST_VARIADIC_TEMPLATE_COPIES_COMMA		, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4
#define MST_VARIADIC_TEMPLATE_FORWARDS			::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4)
#define MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	, ::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4)

#elif MST_VARIADIC_TEMPLATE_COUNT == 5

#undef MST_VARIADIC_TEMPLATE_COUNT
#define MST_VARIADIC_TEMPLATE_COUNT 6
#define MST_VARIADIC_TEMPLATE_DECL				template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
#define MST_VARIADIC_TEMPLATE					, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5
#define MST_VARIADIC_TEMPLATE_TYPES				Arg0, Arg1, Arg2, Arg3, Arg4, Arg5
#define MST_VARIADIC_TEMPLATE_TYPES_COMMA		, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5
#define MST_VARIADIC_TEMPLATE_REFFS				Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5
#define MST_VARIADIC_TEMPLATE_REFFS_COMMA		, Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5
#define MST_VARIADIC_TEMPLATE_COPIES			Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5
#define MST_VARIADIC_TEMPLATE_COPIES_COMMA		, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5
#define MST_VARIADIC_TEMPLATE_FORWARDS			::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4), ::std::forward<Arg5>(arg5)
#define MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	, ::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4), ::std::forward<Arg5>(arg5)

#elif MST_VARIADIC_TEMPLATE_COUNT == 6

#undef MST_VARIADIC_TEMPLATE_COUNT
#define MST_VARIADIC_TEMPLATE_COUNT 7
#define MST_VARIADIC_TEMPLATE_DECL				template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
#define MST_VARIADIC_TEMPLATE					, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6
#define MST_VARIADIC_TEMPLATE_TYPES				Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6
#define MST_VARIADIC_TEMPLATE_TYPES_COMMA		, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6
#define MST_VARIADIC_TEMPLATE_REFFS				Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5, Arg6&& arg6
#define MST_VARIADIC_TEMPLATE_REFFS_COMMA		, Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5, Arg6&& arg6
#define MST_VARIADIC_TEMPLATE_COPIES			Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6
#define MST_VARIADIC_TEMPLATE_COPIES_COMMA		, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6
#define MST_VARIADIC_TEMPLATE_FORWARDS			::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4), ::std::forward<Arg5>(arg5), ::std::forward<Arg6>(arg6)
#define MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	, ::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4), ::std::forward<Arg5>(arg5), ::std::forward<Arg6>(arg6)

#elif MST_VARIADIC_TEMPLATE_COUNT == 7

#undef MST_VARIADIC_TEMPLATE_COUNT
#define MST_VARIADIC_TEMPLATE_COUNT 8
#define MST_VARIADIC_TEMPLATE_DECL				template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
#define MST_VARIADIC_TEMPLATE					, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7
#define MST_VARIADIC_TEMPLATE_TYPES				Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7
#define MST_VARIADIC_TEMPLATE_TYPES_COMMA		, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7
#define MST_VARIADIC_TEMPLATE_REFFS				Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5, Arg6&& arg6, Arg7&& arg7
#define MST_VARIADIC_TEMPLATE_REFFS_COMMA		, Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5, Arg6&& arg6, Arg7&& arg7
#define MST_VARIADIC_TEMPLATE_COPIES			Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7
#define MST_VARIADIC_TEMPLATE_COPIES_COMMA		, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7
#define MST_VARIADIC_TEMPLATE_FORWARDS			::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4), ::std::forward<Arg5>(arg5), ::std::forward<Arg6>(arg6), ::std::forward<Arg7>(arg7)
#define MST_VARIADIC_TEMPLATE_FORWARDS_COMMA	, ::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4), ::std::forward<Arg5>(arg5), ::std::forward<Arg6>(arg6), ::std::forward<Arg7>(arg7)

#elif MST_VARIADIC_TEMPLATE_COUNT == 8

#undef MST_VARIADIC_TEMPLATE_COUNT
#define MST_VARIADIC_TEMPLATE_COUNT 9
#define MST_VARIADIC_TEMPLATE typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8
#define MST_VARIADIC_TEMPLATE_TYPES Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8
#define MST_VARIADIC_TEMPLATE_REFFS Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5, Arg6&& arg6, Arg7&& arg7, Arg8&& arg8
#define MST_VARIADIC_TEMPLATE_COPIES Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8
#define MST_VARIADIC_TEMPLATE_FORWARDS ::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4), ::std::forward<Arg5>(arg5), ::std::forward<Arg6>(arg6), ::std::forward<Arg7>(arg7), ::std::forward<Arg8>(arg8)

#elif MST_VARIADIC_TEMPLATE_COUNT == 9

#undef MST_VARIADIC_TEMPLATE_COUNT
#define MST_VARIADIC_TEMPLATE_COUNT 10
#define MST_VARIADIC_TEMPLATE typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9
#define MST_VARIADIC_TEMPLATE_TYPES Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9
#define MST_VARIADIC_TEMPLATE_REFFS Arg0&& arg0, Arg1&& arg1, Arg2&& arg2, Arg3&& arg3, Arg4&& arg4, Arg5&& arg5, Arg6&& arg6, Arg7&& arg7, Arg8&& arg8, Arg9&& arg9
#define MST_VARIADIC_TEMPLATE_COPIES Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9
#define MST_VARIADIC_TEMPLATE_FORWARDS ::std::forward<Arg0>(arg0), ::std::forward<Arg1>(arg1), ::std::forward<Arg2>(arg2), ::std::forward<Arg3>(arg3), ::std::forward<Arg4>(arg4), ::std::forward<Arg5>(arg5), ::std::forward<Arg6>(arg6), ::std::forward<Arg7>(arg7), ::std::forward<Arg8>(arg8), ::std::forward<Arg9>(arg9)

#endif // MST_VARIADIC_TEMPLATE_COUNT == 0

#if MST_VARIADIC_TEMPLATE_COUNT == MST_NARGS

#define __MST_VAR_T_DONE__

#endif // MST_VARIADIC_TEMPLATE_COUNT != MST_NARGS