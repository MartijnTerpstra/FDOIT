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

inline color4 (::mst::math::ccolor4)(float red, float green, float blue, float alpha) __MST_GPU
{
	color4 retval = { red, green, blue, alpha };
	return retval;
}

#if MST_SIMD_COLOR4
inline color4 (::mst::math::make_color4)(__m128 rgba)
{
	color4 retval;
	retval.rgba4 = rgba;
	return retval;
}
#endif /* MST_SIMD_FLOAT4 */

inline void color4::set(float red, float green, float blue, float alpha) __MST_GPU
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

#if MST_SIMD_FLOAT4
inline void color4::set(__m128 rgba)
{
	rgba4 = rgba;
}
#endif /* MST_SIMD_FLOAT4 */

inline float& color4::operator[](size_t n) __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 4, "index out of range");
	return rgba[n];
}

inline const float& color4::operator[](size_t n) const __MST_GPU
{
	CHECK_ARR_RANGE_GPU(n, 4, "index out of range");
	return rgba[n];
}

inline color4& color4::operator *= (const color4& col) __MST_GPU
{
#if MST_SIMD_FLOAT4
	rgba4 = _mm_mul_ps(rgba4, col.rgba4);
#else /* !MST_SIMD_FLOAT4 */
	r *= col.r;
	g *= col.g;
	b *= col.b;
	a *= col.a;
#endif /* MST_SIMD_FLOAT4 */
	return *this;
}

inline color4& color4::operator *= (float val) __MST_GPU
{
#if MST_SIMD_FLOAT4
	rgba4 = _mm_mul_ps(rgba4, _mm_set_ps1(val));
#else /* !MST_SIMD_FLOAT4 */
	r *= val;
	g *= val;
	b *= val;
	a *= val;
#endif /* MST_SIMD_FLOAT4 */
	return *this;
}

inline color4& color4::operator /= (const color4& col) __MST_GPU
{
#if MST_SIMD_FLOAT4
	rgba4 = _mm_div_ps(rgba4, col.rgba4);
#else /* !MST_SIMD_FLOAT4 */
	r /= col.r;
	g /= col.g;
	b /= col.b;
	a /= col.a;
#endif /* MST_SIMD_FLOAT4 */
	return *this;
}

inline color4& color4::operator /= (float val) __MST_GPU
{
	CHECK_IF_GPU(val < EPSILON, "cannot devide by zero");
#if MST_SIMD_FLOAT4
	rgba4 = _mm_div_ps(rgba4, _mm_set_ps1(val));
#else /* !MST_SIMD_FLOAT4 */
	r /= val;
	g /= val;
	b /= val;
	a /= val;
#endif /* MST_SIMD_FLOAT4 */
	return *this;
}

inline color4& color4::operator += (const color4& col) __MST_GPU
{
#if MST_SIMD_FLOAT4
	rgba4 = _mm_add_ps(rgba4, col.rgba4);
#else /* !MST_SIMD_FLOAT4 */
	r += col.r;
	g += col.g;
	b += col.b;
	a += col.a;
#endif /* MST_SIMD_FLOAT4 */
	return *this;
}

inline color4& color4::operator -= (const color4& col) __MST_GPU
{
#if MST_SIMD_FLOAT4
	rgba4 = _mm_sub_ps(rgba4, col.rgba4);
#else /* !MST_SIMD_FLOAT4 */
	r -= col.r;
	g -= col.g;
	b -= col.b;
	a -= col.a;
#endif /* MST_SIMD_FLOAT4 */
	return *this;
}

inline color4 (::mst::math::operator + )(const color4& col1, const color4& col2) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return make_color4(_mm_add_ps(col1.rgba4, col2.rgba4));
#else /* !MST_SIMD_FLOAT4 */
	return ccolor4(col1.r + col2.r, col1.g + col2.g, col1.b + col2.b, col1.a + col2.a);
#endif /* MST_SIMD_FLOAT4 */
}

inline color4 (::mst::math::operator - )(const color4& col1, const color4& col2) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return make_color4(_mm_sub_ps(col1.rgba4, col2.rgba4));
#else /* !MST_SIMD_FLOAT4 */
	return ccolor4(col1.r - col2.r, col1.g - col2.g, col1.b - col2.b, col1.a - col2.a);
#endif /* MST_SIMD_FLOAT4 */
}

inline color4 (::mst::math::operator * )(const color4& col1, const color4& col2) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return make_color4(_mm_mul_ps(col1.rgba4, col2.rgba4));
#else /* !MST_SIMD_FLOAT4 */
	return ccolor4(col1.r * col2.r, col1.g * col2.g, col1.b * col2.b, col1.a * col2.a);
#endif /* MST_SIMD_FLOAT4 */
}

inline color4 (::mst::math::operator * )(const color4& col, float val) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return make_color4(_mm_mul_ps(col.rgba4, _mm_set_ps1(val)));
#else /* !MST_SIMD_FLOAT4 */
	return ccolor4(col.r * val, col.g * val, col.b * val, col.a * val);
#endif /* MST_SIMD_FLOAT4 */
}

inline color4 (::mst::math::operator * )(float val, const color4& col) __MST_GPU
{
	return col * val;
}

inline color4 (::mst::math::operator / )(const color4& col1, const color4& col2) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return make_color4(_mm_div_ps(col1.rgba4, col2.rgba4));
#else /* !MST_SIMD_FLOAT4 */
	return ccolor4(col1.r / col2.r, col1.g / col2.g, col1.b / col2.b, col1.a / col2.a);
#endif /* MST_SIMD_FLOAT4 */
}

inline color4 (::mst::math::operator / )(const color4& col, float val) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return make_color4(_mm_div_ps(col.rgba4, _mm_set_ps1(val)));
#else
	return ccolor4(col.r / val, col.g / val, col.b / val, col.a / val);
#endif
}

inline color4 (::mst::math::operator / )(float val, const color4& col) __MST_GPU
{
#if MST_SIMD_FLOAT4
	return make_color4(_mm_div_ps(_mm_set_ps1(val), col.rgba4));
#else
	return ccolor4(val / col.r, val / col.g, val / col.b, val / col.a);
#endif
}

__declspec(selectany) const color4 color4::black = { 0, 0, 0, 1 };
__declspec(selectany) const color4 color4::white = { 1, 1, 1, 1 };