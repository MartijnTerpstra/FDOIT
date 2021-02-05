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


// must be included after all the includes

#if !_MST_VARIADIC_TEMPLATE_HACK_SUPPORTED
#error "variadic templates require C++11"
#endif // !_MST_VARIADIC_TEMPLATE_HACK_SUPPORTED

// cleans up all defines

#ifndef __INSIDE_VAR_T__
#error "mvariadic_template_end.h: invalid use of header: always include mvariadic_template_begin.h before this header"
#endif // __INSIDE_VAR_T__

#undef __INSIDE_VAR_T__

#ifdef __MST_VAR_T_DONE__
#undef MST_NARGS
#undef MST_VAR_T_USE_PRE_COMMA_IN_ARGS

#undef MST_VERIADIC_TEMPLATE
#undef MST_VERIADIC_TEMPLATE_REFFS
#undef MST_VERIADIC_TEMPLATE_FORWARDS

#undef __MST_VAR_T_DONE__
#undef _MST_VAR_T_COMMA_IN_ARGS

#undef MST_VARIADIC_TEMPLATE_COUNT

#else // !__MST_VAR_T_DONE__

// not done, invalid variadic template!
#error "include count is not MST_NARGS"

#endif // __MST_VAR_T_DONE__