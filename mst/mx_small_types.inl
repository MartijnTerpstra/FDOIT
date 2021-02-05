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

inline int2 (::mst::math::cint2)(const int ax, const int ay) __MST_GPU
{
	int2 retval = { ax, ay };
	return retval;
}

inline void int2::set(const int ax, const int ay) __MST_GPU
{
	x = ax;
	y = ay;
}

inline int& int2::operator [] (size_t i) __MST_GPU
{
	CHECK_ARR_RANGE(i, 2, "index out of bounds");
	return axis[i];
}

bool (::mst::math::operator== )(const int2& left, const int2& right) __MST_GPU
{
	return (left.x == right.x && left.y == right.y);
}

inline ushort2 (::mst::math::cushort2)(const ushort ax, const ushort ay) __MST_GPU
{
	ushort2 retval = { ax, ay };
	return retval;
}

inline void ushort2::set(const ushort ax, const ushort ay) __MST_GPU
{
	x = ax;
	y = ay;
}

inline ushort2 (::mst::math::operator- )(const ushort2& vec1, const ushort2& vec2) __MST_GPU
{
	return cushort2(vec1.x - vec2.x, vec1.y - vec2.y);
}

inline ushort2 (::mst::math::operator* )(const ushort2& vec1, const ushort2& vec2) __MST_GPU
{
	return cushort2(vec1.x * vec2.x, vec1.y * vec2.y);
}
inline ushort2 (::mst::math::operator+ )(const ushort2& vec1, const ushort2& vec2) __MST_GPU
{
	return cushort2(vec1.x + vec2.x, vec1.y + vec2.y);
}

inline ushort2 (::mst::math::operator* )(const ushort2& vec1, const ushort val) __MST_GPU
{
	return cushort2(vec1.x * val, vec1.y * val);
}

inline ushort2 (::mst::math::operator/ )(const ushort2& vec1, const ushort val) __MST_GPU
{
	return cushort2(vec1.x / val, vec1.y / val);
}

inline ushort2 (::mst::math::operator/ )(const ushort val, const ushort2& vec1) __MST_GPU
{
	return cushort2(val / vec1.x, val / vec1.y);
}

inline bool (::mst::math::operator== )(const ushort2& vec1, const ushort2& vec2) __MST_GPU
{
	return (vec1.x == vec2.x && vec1.y == vec2.y);
}

inline bool (::mst::math::operator!= )(const ushort2& vec1, const ushort2& vec2) __MST_GPU
{
	return !(vec1 == vec2);
}
	
inline ushort2& ushort2::operator *= (const ushort val) __MST_GPU
{
	x *= val;
	y *= val;
	return *this;
}

inline ushort2& ushort2::operator /= (const ushort val) __MST_GPU
{
	x /= val; 
	y /= val; 
	return *this;
}

inline ushort2& ushort2::operator *= (const ushort2& vec) __MST_GPU 
{ 
	x *= vec.x; 
	y *= vec.y; 
	return *this; 
}

inline ushort2& ushort2::operator += (const ushort2& vec) __MST_GPU 
{ 
	x += vec.x; 
	y += vec.y; 
	return *this; 
}

inline ushort2& ushort2::operator -= (const ushort2& vec) __MST_GPU 
{ 
	x -= vec.x; 
	y -= vec.y; 
	return *this; 
}

inline ushort& ushort2::operator [] (size_t i) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(i, 2, "index out of bounds");
	return axis[i];
}

inline short2 (::mst::math::cshort2)(const short x, const short y)
{
	short2 retval = { x, y };
	return retval;
}

inline void short2::set(const short ax, const short ay) __MST_GPU 
{ 
	x = ax;
	y = ay; 
}

inline short& short2::operator [] (size_t i) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(i, 2, "index out of bounds");
	return axis[i];
}

inline bool (::mst::math::operator== )(const short2& left, const short2& right) __MST_GPU
{
	return (left.x == right.x && left.y == right.y);
}


inline uint2 (::mst::math::cuint2)(const uint x, const uint y)
{
	uint2 retval = { x, y };
	return retval;
}

inline uint& uint2::operator [] (size_t i) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(i, 2, "index out of bounds");
	return axis[i];
}

inline bool (::mst::math::operator== )(const uint2& left, const uint2& right) __MST_GPU
{
	return (left.x == right.x && left.y == right.y);
}
	
inline int3 (::mst::math::cint3)(const int x, const int y, const int z) __MST_GPU
{
	int3 retval = { x, y, z };
	return retval;
}

inline void int3::set(const int ax, int ay, int az) __MST_GPU
{
	x = ax; 
	y = ay; 
	z = az; 
}

inline int& int3::operator [] (size_t i) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(i, 3, "index out of bounds");
	return axis[i];
}

inline bool (::mst::math::operator== )(const int3& left, const int3& right) __MST_GPU
{
	return (left.x == right.x && left.y == right.y && left.z == right.z);
}