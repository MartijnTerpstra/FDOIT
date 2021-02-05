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

#include <mcore.h>

#ifndef MST_MAPPED_PROPERTY_STRING_TYPE
#include <mdll_string.h>
#define MST_MAPPED_PROPERTY_STRING_TYPE ::mst::dll_safe::string<char>
#endif

#define MST_DEFAULT_GET_PREFIX _
#define MST_DEFAULT_SET_PREFIX _

#define MST_GET_PREFIX MST_DEFAULT_GET_PREFIX
#define MST_SET_PREFIX MST_DEFAULT_SET_PREFIX

#define _MST_PROPERTYNAME(x, y) _MST_PROPERTYNAME2(x,y)
#define _MST_PROPERTYNAME2(x, y) x##y

/* default declaration */

#define declare_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)
#define declare_get_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName; \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const
#define declare_set_property(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)

#define declare_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&)
#define declare_get_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const
#define declare_set_property_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&)

#define declare_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)
#define declare_get_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const
#define declare_set_property_mapped_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)


/* inline */

#define declare_inline_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	inline propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const; inline void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)
#define declare_inline_get_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName; \
	inline propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const
#define declare_inline_set_property(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	inline void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)

#define declare_inline_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	inline propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; inline void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&)
#define declare_inline_get_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	inline propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const
#define declare_inline_set_property_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	inline void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&)

#define declare_inline_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	inline propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; inline void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); \
	inline propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const; inline void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)
#define declare_inline_get_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	inline propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; inline propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const
#define declare_inline_set_property_mapped_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	inline void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); inline void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)


/* virtuals */

#define declare_virtual_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)
#define declare_virtual_get_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const
#define declare_virtual_set_property(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)

#define declare_virtual_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&)
#define declare_virtual_get_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const
#define declare_virtual_set_property_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&)

#define declare_virtual_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)
#define declare_virtual_get_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const
#define declare_virtual_set_property_mapped_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)


/* pure virtuals */

#define declare_pure_virtual_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const = 0; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&) = 0
#define declare_pure_virtual_get_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const = 0
#define declare_pure_virtual_set_property(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&) = 0

#define declare_pure_virtual_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const = 0; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, propertyType) = 0
#define declare_pure_virtual_get_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const = 0
#define declare_pure_virtual_set_property_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) = 0

#define declare_pure_virtual_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const = 0; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) = 0; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const = 0; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&) = 0
#define declare_pure_virtual_get_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const = 0; virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const = 0
#define declare_pure_virtual_set_property_mapped_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) = 0; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&) = 0

/* overrides */

#define declare_override_property(propertyType, propertyName) propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const override; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&) override
#define declare_override_get_property(propertyType, propertyName) propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const override
#define declare_override_set_property(propertyType, propertyName) void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&) override

#define declare_override_property_array(propertyType, propertyName) propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const override; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) override
#define declare_override_get_property_array(propertyType, propertyName) propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const override
#define declare_override_set_property_array(propertyType, propertyName) void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) override

#define declare_override_property_mapped_array(propertyType, propertyName) propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const override; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) override; propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const override; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&) override
#define declare_override_get_property_mapped_array(propertyType, propertyName) propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const override; propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const override
#define declare_override_set_property_mapped_array(propertyType, propertyName) void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) override; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&) override

/* dll export */

/* default declaration */

#define declare_dll_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	MST_DECLARE_DLL_FUNCTION propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const; MST_DECLARE_DLL_FUNCTION void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)
#define declare_dll_get_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName; \
	MST_DECLARE_DLL_FUNCTION propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const
#define declare_dll_set_property(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	MST_DECLARE_DLL_FUNCTION void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)

#define declare_dll_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	MST_DECLARE_DLL_FUNCTION propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; MST_DECLARE_DLL_FUNCTION void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, propertyType)
#define declare_dll_get_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	MST_DECLARE_DLL_FUNCTION propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const
#define declare_dll_set_property_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	MST_DECLARE_DLL_FUNCTION void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&)

#define declare_dll_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)
#define declare_dll_get_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const
#define declare_dll_set_property_mapped_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)


/* virtuals */

#define declare_dll_virtual_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	MST_DECLARE_DLL_FUNCTION virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const; MST_DECLARE_DLL_FUNCTION virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)
#define declare_dll_virtual_get_property(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName; \
	MST_DECLARE_DLL_FUNCTION virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const
#define declare_dll_virtual_set_property(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName; \
	MST_DECLARE_DLL_FUNCTION virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&)

#define declare_dll_virtual_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	MST_DECLARE_DLL_FUNCTION virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; MST_DECLARE_DLL_FUNCTION virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, propertyType)
#define declare_dll_virtual_get_property_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	MST_DECLARE_DLL_FUNCTION virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const
#define declare_dll_virtual_set_property_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	MST_DECLARE_DLL_FUNCTION virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&)

#define declare_dll_virtual_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName), put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)
#define declare_dll_virtual_get_property_mapped_array(propertyType, propertyName) __declspec(property(get = _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const; virtual propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const
#define declare_dll_virtual_set_property_mapped_array(propertyType, propertyName) __declspec(property(put = _MST_PROPERTYNAME(MST_SET_PREFIX,propertyName))) propertyType propertyName[]; \
	virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&); virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&)

/* overrides */

#define declare_dll_override_property(propertyType, propertyName) MST_DECLARE_DLL_FUNCTION propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const override; virtual void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&) override
#define declare_dll_override_get_property(propertyType, propertyName) MST_DECLARE_DLL_FUNCTION propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)() const override
#define declare_dll_override_set_property(propertyType, propertyName) MST_DECLARE_DLL_FUNCTION void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const propertyType&) override

#define declare_dll_override_property_array(propertyType, propertyName) MST_DECLARE_DLL_FUNCTION propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const override; MST_DECLARE_DLL_FUNCTION void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, propertyType) override
#define declare_dll_override_get_property_array(propertyType, propertyName) MST_DECLARE_DLL_FUNCTION propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const override
#define declare_dll_override_set_property_array(propertyType, propertyName) MST_DECLARE_DLL_FUNCTION void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) override

#define declare_dll_override_property_mapped_array(propertyType, propertyName) propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const override; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) override; propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const override; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&) override
#define declare_dll_override_get_property_mapped_array(propertyType, propertyName) propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(size_t) const override; propertyType MST_API _MST_PROPERTYNAME(MST_GET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&) const override
#define declare_dll_override_set_property_mapped_array(propertyType, propertyName) void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(size_t, const propertyType&) override; void _MST_PROPERTYNAME(MST_API MST_SET_PREFIX,propertyName)(const MST_MAPPED_PROPERTY_STRING_TYPE&, const propertyType&) override