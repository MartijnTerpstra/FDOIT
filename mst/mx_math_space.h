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

template<typename _Value_type>
class clip_space
{
	template<typename _xValue_type>
	friend class clip_space;
public:

	inline clip_space() _DEFAULT_MATH_CONSTRUCTOR
	inline clip_space(const _Value_type& _Left, const _Value_type& _Right,
						const _Value_type& _Top, const _Value_type& _Bottom,
						const _Value_type& _Near, const _Value_type& _Far)
		: _Myleft(_Left), _Myright(_Right),
		_Mytop(_Top), _Mybottom(_Bottom),
		_Mynear(_Near), _Myfar(_Far)
	{ }
	inline clip_space(const clip_space& _Other)
		: _Myleft(_Other._Myleft), _Myright(_Other._Myright),
		_Mytop(_Other._Mytop), _Mybottom(_Other._Mybottom),
		_Mynear(_Other._Mynear), _Myfar(_Other._Myfar)
	{ }

	template<typename _xValue_type>
	inline explicit clip_space(const clip_space<_xValue_type>& _Other)
		: _Myleft((_xValue_type)_Other._Myleft), _Myright((_xValue_type)_Other._Myright),
		_Mytop((_xValue_type)_Other._Mytop), _Mybottom((_xValue_type)_Other._Mybottom),
		_Mynear((_xValue_type)_Other._Mynear), _Myfar((_xValue_type)_Other._Myfar)
	{ }

	inline _Value_type left() const
	{
		return _Myleft;
	}

	inline _Value_type right() const
	{
		return _Myright;
	}

	inline _Value_type top() const
	{
		return _Mytop;
	}

	inline _Value_type bottom() const
	{
		return _Mybottom;
	}

	inline _Value_type near() const
	{
		return _Mynear;
	}

	inline _Value_type far() const
	{
		return _Myfar;
	}

	inline static clip_space directx()
	{
		return clip_space((_Value_type)-1, (_Value_type)1, (_Value_type)1, (_Value_type)-1, (_Value_type)0, (_Value_type)1);
	}

	inline static clip_space opengl()
	{
		return clip_space((_Value_type)-1, (_Value_type)1, (_Value_type)-1, (_Value_type)1, (_Value_type)-1, (_Value_type)1);
	}

	inline static clip_space vulkan()
	{
		return clip_space((_Value_type)-1, (_Value_type)1, (_Value_type)-1, (_Value_type)1, (_Value_type)0, (_Value_type)1);
	}

private:
	
	_Value_type _Myleft, _Myright, _Mytop, _Mybottom, _Mynear, _Myfar;

}; // class clip_space<_Value_type>

template<typename _Value_type>
class texture_space
{
	template<typename _xValue_type>
	friend class texture_space;
public:

	inline texture_space() _DEFAULT_MATH_CONSTRUCTOR
	inline texture_space(const _Value_type& _Left, const _Value_type& _Right,
							const _Value_type& _Top, const _Value_type& _Bottom)
		: _Myleft(_Left), _Myright(_Right),
		_Mytop(_Top), _Mybottom(_Bottom)
	{ }
	inline texture_space(const texture_space& _Other)
		: _Myleft(_Other._Myleft), _Myright(_Other._Myright),
		_Mytop(_Other._Mytop), _Mybottom(_Other._Mybottom)
	{ }

	template<typename _xValue_type>
	inline explicit texture_space(const texture_space<_xValue_type>& _Other)
		: _Myleft((_xValue_type)_Other._Myleft), _Myright((_xValue_type)_Other._Myright),
		_Mytop((_xValue_type)_Other._Mytop), _Mybottom((_xValue_type)_Other._Mybottom)
	{ }

	inline _Value_type left() const
	{
		return _Myleft;
	}

	inline _Value_type right() const
	{
		return _Myright;
	}

	inline _Value_type top() const
	{
		return _Mytop;
	}

	inline _Value_type bottom() const
	{
		return _Mybottom;
	}

	inline static texture_space directx()
	{
		return texture_space((_Value_type)0, (_Value_type)1, (_Value_type)0, (_Value_type)1);
	}

	inline static texture_space opengl()
	{
		return texture_space((_Value_type)0, (_Value_type)1, (_Value_type)1, (_Value_type)0);
	}
	/*
	inline static texture_space vulkan() const
	{
		return texture_space((_Value_type)0, (_Value_type)1, (_Value_type)1, (_Value_type)0);
	}
	*/
private:

	_Value_type _Myleft, _Myright, _Mytop, _Mybottom;

}; // class texture_space<_Value_type>