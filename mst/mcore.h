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

#ifndef MCORE_H
#define MCORE_H

/* the current version of the MST */
#define MST_VER 3601

/* the current version of the MST in string format */
#define MST_VER_STR "3.6.01"

/**/
	/* when this version is changed, functionality is changed or deprecated */
	/* this will possibly break your code, so check every new big version for an upgrade */
/**/
#define MST_BIG_VER (MST_VER / 100)

/**/
	/* this version is increased when bus are fixed and other small things are done. */
	/* will never break your code unless you worked with a bug in the first place. */
/**/
#define MST_SMALL_VER (MST_VER - (MST_BIG_VER * 100))

// typedefs of unsigned types
#ifndef _UNSIGNED_INTEGERS_DEFINED
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char ubyte;
typedef unsigned char byte;
#define _UNSIGNED_INTEGERS_DEFINED 1
#endif

typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

#ifndef _VARIADIC_MAX
#define _VARIADIC_MAX 10
#endif

#ifndef _MST_EPSILON
#define _MST_EPSILON (1e-5L)
#endif

#ifndef NOMINMAX
#define NOMINMAX 1
#endif


/*
 C++ AMP handling
 
 if you want de math library(and some other features) for the GPU
 you need to include <amp.h> before any mst header
*/
#ifdef _AMP_H
#define _HAS_AMP 1
#endif

#if _HAS_AMP
#define __MST_GPU restrict(amp, cpu)
#define __MST_GPU_ONLY restrict(amp)
#else
#define __MST_GPU
#define __MST_GPU_ONLY
#endif

#include <mx_core.h>

#ifndef MST_DEBUGMODE
#if _DEBUG
#define MST_DEBUGMODE 1
#endif
#endif

#ifndef MST_DEFAULT_NARGS
#define MST_DEFAULT_NARGS 5
#endif

#define null nullptr

#endif // MCORE_H