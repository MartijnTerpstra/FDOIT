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

template<typename _Ty>
class com_ptr;

template<typename _Ty>
class smart_ptr;
	
namespace _Details {

struct _Mst_cast_dynamic{};
struct _Mst_cast_static{};
struct _Mst_cast_reinterpret{};
struct _Mst_cast_const{};
struct _Mst_cast_this{};

struct _Unknown_tag {};
struct _Smart_ptr_tag {};

template<typename _Ty1, typename _Ty2>
struct _Mst_cast_traits
{
	typedef _Unknown_tag tag;
	typedef _Ty1 type1;
	typedef _Ty2 type2;
};

template<typename _Ty1, typename _Ty2>
struct _Mst_cast_traits<::mst::smart_ptr<_Ty1>, ::mst::smart_ptr<_Ty2>>
{
	typedef _Smart_ptr_tag tag;
	typedef smart_ptr<_Ty1> type1;
	typedef smart_ptr<_Ty2> type2;
};

template<typename _Ty1, typename _Ty2>
struct _Mst_cast_traits<::mst::com_ptr<_Ty1>, ::mst::com_ptr<_Ty2>>
{
	typedef _Smart_ptr_tag tag;
	typedef com_ptr<_Ty1> type1;
	typedef com_ptr<_Ty2> type2;
};

class _Smart_ptr_caster
{
public:
	template<typename T, typename V, typename Tag>
	static T _Cast(V&& _Val, Tag)
	{
		return T(::std::forward<V>(_Val), Tag());
	}
};

#if _MST_HAS_RVALUE_REFS

template<typename T, typename V>
inline T _Cast_static(V&& _Val, ::mst::_Details::_Unknown_tag)
{
	return static_cast<T>(::std::forward<V>(_Val));
}

template<typename T, typename V>
inline T _Cast_static(V&& _Val, ::mst::_Details::_Smart_ptr_tag)
{
	return _Smart_ptr_caster::_Cast<T>(::std::forward<V>(_Val), ::mst::_Details::_Mst_cast_static());
}

template<typename T, typename V>
inline T _Cast_dynamic(V&& _Val, ::mst::_Details::_Unknown_tag)
{
	return dynamic_cast<T>(::std::forward<V>(_Val));
}

template<typename T, typename V>
inline T _Cast_dynamic(V&& _Val, ::mst::_Details::_Smart_ptr_tag)
{
	return _Smart_ptr_caster::_Cast<T>(::std::forward<V>(_Val), ::mst::_Details::_Mst_cast_dynamic());
}

template<typename T, typename V>
inline T _Cast_const(V&& _Val, ::mst::_Details::_Unknown_tag)
{
	return const_cast<T>(::std::forward<V>(_Val));
}

template<typename T, typename V>
inline T _Cast_const(V&& _Val, ::mst::_Details::_Smart_ptr_tag)
{
	return _Smart_ptr_caster::_Cast<T>(::std::forward<V>(_Val), ::mst::_Details::_Mst_cast_const());
}

template<typename T, typename V>
inline T _Cast_reinterpret(V&& _Val, ::mst::_Details::_Unknown_tag)
{
	return reinterpret_cast<T>(::std::forward<V>(_Val));
}

template<typename T, typename V>
inline T _Cast_reinterpret(V&& _Val, ::mst::_Details::_Smart_ptr_tag)
{
	return _Smart_ptr_caster::_Cast<T>(::std::forward<V>(_Val), ::mst::_Details::_Mst_cast_reinterpret());
}

#else // !_MST_HAS_RVALUE_REFS

template<typename T, typename V>
inline T _Cast_static(const V& _Val, ::mst::_Details::_Unknown_tag)
{
	return static_cast<T>(_Val);
}

template<typename T, typename V>
inline T _Cast_static(const V& _Val, ::mst::_Details::_Smart_ptr_tag)
{
	return T(_Val, ::mst::_Details::_Mst_cast_static());
}

template<typename T, typename V>
inline T _Cast_dynamic(const V& _Val, ::mst::_Details::_Unknown_tag)
{
	return dynamic_cast<T>(_Val);
}

template<typename T, typename V>
inline T _Cast_dynamic(const V& _Val, ::mst::_Details::_Smart_ptr_tag)
{
	return T(_Val, ::mst::_Details::_Mst_cast_dynamic());
}

template<typename T, typename V>
inline T _Cast_const(const V& _Val, ::mst::_Details::_Unknown_tag)
{
	return const_cast<T>(_Val);
}

template<typename T, typename V>
inline T _Cast_const(const V& _Val, ::mst::_Details::_Smart_ptr_tag)
{
	return T(_Val, ::mst::_Details::_Mst_cast_const());
}

template<typename T, typename V>
inline T _Cast_reinterpret(const V& _Val, ::mst::_Details::_Unknown_tag)
{
	return reinterpret_cast<T>(_Val);
}

template<typename T, typename V>
inline T _Cast_reinterpret(const V& _Val, ::mst::_Details::_Smart_ptr_tag)
{
	return T(_Val, ::mst::_Details::_Mst_cast_reinterpret());
}

#endif // _MST_HAS_RVALUE_REFS

}; // namespace _Details
}; // namespace mst