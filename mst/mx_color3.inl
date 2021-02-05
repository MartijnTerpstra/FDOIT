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

color3 (::mst::math::ccolor3)(float red, float green, float blue) __MST_GPU
{
	color3 retval = { red, green, blue };
	return retval;
}

inline void color3::set(float red, float green, float blue) __MST_GPU
{
	r = red;
	g = green;
	b = blue;
}

inline float& color3::operator[](size_t n) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 3, "index out of range");
	return rgb[n];
}

inline const float& color3::operator[](size_t n) const __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 3, "index out of range");
	return rgb[n];
}

inline color3& color3::operator *= (const color3& col) __MST_GPU
{
	r *= col.r; g *= col.g; b *= col.b;
	return *this;
}

inline color3& color3::operator *= (float val) __MST_GPU
{
	r *= val; g *= val; b *= val;
	return *this;
}

inline color3& color3::operator /= (const color3& col) __MST_GPU
{
	r /= col.r; g /= col.g; b /= col.b;
	return *this;
}

inline color3& color3::operator /= (float val) __MST_GPU
{
	CHECK_IF_GPU(val < EPSILON, "cannot devide by zero");
	const float inv_val = 1.0f / val;
	r *= inv_val; g *= inv_val; b *= inv_val;
	return *this;
}

inline color3& color3::operator += (const color3& col) __MST_GPU
{
	r += col.r; g += col.g; b += col.b;
	return *this;
}

inline color3& color3::operator -= (const color3& col) __MST_GPU
{
	r -= col.r; g -= col.g; b -= col.b;
	return *this;
}

inline color3 (::mst::math::operator + )(const color3& col1, const color3& col2) __MST_GPU
{
	return ccolor3(col1.r + col2.r, col1.g + col2.g, col1.b + col2.b);
}

inline color3 (::mst::math::operator - )(const color3& col1, const color3& col2) __MST_GPU
{
	return ccolor3(col1.r - col2.r, col1.g - col2.g, col1.b - col2.b);
}

inline color3 (::mst::math::operator * )(const color3& col1, const color3& col2) __MST_GPU
{
	return ccolor3(col1.r * col2.r, col1.g * col2.g, col1.b * col2.b);
}

inline color3 (::mst::math::operator * )(const color3& col, float val) __MST_GPU
{
	return ccolor3(col.r * val, col.g * val, col.b * val);
}

inline color3 (::mst::math::operator * )(float val, const color3& col) __MST_GPU
{
	return ccolor3(col.r * val, col.g * val, col.b * val);
}

inline color3 (::mst::math::operator / )(const color3& col1, const color3& col2) __MST_GPU
{
	return ccolor3(col1.r / col2.r, col1.g / col2.g, col1.b / col2.b);
}

inline color3 (::mst::math::operator / )(const color3& col, float val) __MST_GPU
{
	CHECK_IF_GPU(val < EPSILON, "cannot devide by zero");
	const float inv_val = 1.0f / val;
	return ccolor3(col.r * inv_val, col.g * inv_val, col.b * inv_val);
}

inline color3 (::mst::math::operator / )(float val, const color3& col) __MST_GPU
{
	return ccolor3(val / col.r, val / col.g, val / col.b);
}

inline bool (::mst::math::operator ==)(const color3& col1, const color3& col2) __MST_GPU
{
	return (col1.r == col2.r && col1.g == col2.g && col1.b == col2.b);
}

inline bool (::mst::math::operator !=)(const color3& col1, const color3& col2) __MST_GPU
{
	return (!(col1 == col2));
}

__declspec(selectany) const color3 color3::black = { 0, 0, 0 };
__declspec(selectany) const color3 color3::white = { 1, 1, 1 };