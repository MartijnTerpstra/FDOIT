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

#include "Precomp.h"

using namespace Demo::Common;

bool ::IsKeyDown(short key)
{
	return (GetKeyState(key) & 0x80) != 0;
}

float ::DegreeToRadian(float degree)
{
	return degree * PI / 180.0f;
}

float ::RadianToDegree(float radian)
{
	return radian * 180.0f / PI;
}

int (::MakeMultipleOf)(int value, int multiple)
{
	int modulo = value % multiple;
	return (modulo != 0 ? value + (multiple - modulo) : value);
}

float4 (::InitPixel)(const uint8* data, DXGI_FORMAT format, float4)
{
	switch(format)
	{
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		return float4(data[3] / 255.0f, data[2] / 255.0f, data[1] / 255.0f, data[0] / 255.0f);

	default:
		_MST_BREAK;
		// invalid format
		return float4(0,0,0,0);
	}
}

uint (::GetPixelSize)(DXGI_FORMAT format)
{
	switch(format)
	{
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		return 4;

	default:
		_MST_BREAK;
		// invalid format
		return 16;
	}
}