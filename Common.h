//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//		Fixed Depth Order-Independent Transparency											//
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

/*
	commonly used code
*/

using std::string;
using std::move;
using std::unique_ptr;
using std::min;
using std::max;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::make_unique;

using mst::com_ptr;

template<typename T>
unique_ptr<T[]> make_unique_array(size_t count)
{
	return unique_ptr<T[]>(new T[count]);
}

#ifndef PI
#define PI 3.141592654f
#endif

#define ANTTWEAK_FRIEND_CALLBACK(callbackName) \
friend void __stdcall OnSet##callbackName(const void*,void*); \
friend void __stdcall OnGet##callbackName(void*,void*);

#define ANTTWEAK_BUTTON_CALLBACK(callbackName) \
void __stdcall OnClick##callbackName(void*);

typedef unsigned char uint8;

namespace Demo { namespace Common {

bool IsKeyDown(short key);

float DegreeToRadian(float degree);

float RadianToDegree(float radian);

int MakeMultipleOf(int value, int multiple);

float4 InitPixel(const uint8* data, DXGI_FORMAT format, float4);

uint GetPixelSize(DXGI_FORMAT format);

}; }; // namespace Demo::Common