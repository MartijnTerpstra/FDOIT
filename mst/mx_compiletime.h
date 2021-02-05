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

_MST_CONSTEXPR size_t _Compiletime_strlen_iterator(const char* cString, size_t index)
{
	return (cString[index] == 0 ? index : _Compiletime_strlen_iterator(cString, index + 1));
}

_MST_CONSTEXPR size_t _Compiletime_strlen(const char* cString)
{
	return _Compiletime_strlen_iterator(cString, 0);
}

_MST_CONSTEXPR size_t _Compiletime_strpos_compare_iterator(const char* cString, const char* cSearch, size_t offset, size_t index, size_t strLenString, size_t strLenSearch)
{
	return (index == strLenSearch) ? offset : (cString[offset + index] != cSearch[index] ? -1 : _Compiletime_strpos_compare_iterator(cString, cSearch, offset, index + 1, strLenString, strLenSearch));
}

_MST_CONSTEXPR size_t _Compiletime_strpos_iterator(const char* cString, const char* cSearch, size_t index, size_t strLenString, size_t strLenSearch)
{
	return (index > strLenString - strLenSearch) ? -1 : (_Compiletime_strpos_compare_iterator(cString, cSearch, index, 0, strLenString, strLenSearch) != -1 ? _Compiletime_strpos_compare_iterator(cString, cSearch, index, 0, strLenString, strLenSearch) : _Compiletime_strpos_iterator(cString, cSearch, index + 1, strLenString, strLenSearch));
}

_MST_CONSTEXPR size_t _Compiletime_strpos_impl(const char* cString, const char* cSearch, size_t strLenString, size_t strLenSearch)
{
	return (strLenSearch > strLenString) ? -1 : _Compiletime_strpos_iterator(cString, cSearch, 0, strLenString, strLenSearch);
}

_MST_CONSTEXPR size_t _Compiletime_strpos(const char* cString, const char* cSearch)
{
	return _Compiletime_strpos_impl(cString, cSearch, _Compiletime_strlen(cString), _Compiletime_strlen(cSearch));
}

_MST_CONSTEXPR uint32 _Compiletime_hash32_interator(const char* cString, size_t strLen, size_t index, uint32 currentHash)
{
	return (strLen <= index) ? currentHash : _Compiletime_hash32_interator(cString, strLen, index + 1, (currentHash ^ ((uint32)cString[index])) * 16777619UL);
}

_MST_CONSTEXPR uint64 _Compiletime_hash64_interator(const char* cString, size_t strLen, size_t index, uint64 currentHash)
{
	return (strLen <= index) ? (currentHash ^ (currentHash >> 32)) : _Compiletime_hash64_interator(cString, strLen, index + 1, (currentHash ^ ((uint64)cString[index])) * 1099511628211ULL);
}


_MST_CONSTEXPR uint32 _Compiletime_hash32(const char* cString, size_t offset, size_t strLen)
{
	return _Compiletime_hash32_interator(cString, strLen, offset, 2166136261UL);
}

_MST_CONSTEXPR uint64 _Compiletime_hash64(const char* cString, size_t offset, size_t strLen)
{
	return _Compiletime_hash64_interator(cString, strLen, offset, 14695981039346656037ULL);
}

_MST_CONSTEXPR size_t _Compiletime_hash_of_forward_iterator2(const char* cString, size_t index, size_t notFoundIndex)
{
	return (index == _Compiletime_strlen(cString)) ? notFoundIndex : (cString[index] == ' ') ? index + 1 : _Compiletime_hash_of_forward_iterator2(cString, index + 1, notFoundIndex);
}

_MST_CONSTEXPR size_t _Compiletime_hash_of_forward_iterator(const char* cString, size_t index)
{
	return (cString[index] == '<') ? _Compiletime_hash_of_forward_iterator2(cString, index + 1, index + 1) : _Compiletime_hash_of_forward_iterator(cString, index + 1);
}

_MST_CONSTEXPR size_t _Compiletime_hash_of_backward_iterator(const char* cString, size_t index)
{
	return (cString[index] == '>') ? index : _Compiletime_hash_of_backward_iterator(cString, index - 1);
}

_MST_CONSTEXPR uint32 _Compiletime_hash_of32_impl(const char* cString)
{
	return _Compiletime_hash32(cString, _Compiletime_hash_of_forward_iterator(cString, 0), _Compiletime_hash_of_backward_iterator(cString, _Compiletime_strlen(cString) - 1));
}

_MST_CONSTEXPR uint64 _Compiletime_hash_of64_impl(const char* cString)
{
	return _Compiletime_hash64(cString, _Compiletime_hash_of_forward_iterator(cString, 0), _Compiletime_hash_of_backward_iterator(cString, _Compiletime_strlen(cString) - 1));
}

template<typename T>
_MST_CONSTEXPR uint32 _Compiletime_hash_of32()
{
	return ::mst::_Details::_Compiletime_hash_of32_impl(__FUNCSIG__);
}

template<typename T>
_MST_CONSTEXPR uint64 _Compiletime_hash_of64()
{
	return ::mst::_Details::_Compiletime_hash_of64_impl(__FUNCSIG__);
}

}; // namespace _Details
}; // namespace mst