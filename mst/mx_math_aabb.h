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

#define _mst_declare_value(_Name, _Idx) \
inline _Value_type _get_##_Name() const { return _Data[_Idx]; } \
inline void _set_##_Name(_Value_type _Val) { _Data[_Idx] = _Val; } \
_Value_type __declspec(property(put=_set_##_Name,get=_get_##_Name)) _Name

namespace _Details {

template<typename _Value_type, size_t _Dimensions>
class _Aabb
{
public:

	typedef ::mst::math::vector<_Value_type, _Dimensions> vector_type;
	static const size_t dimensions = _Dimensions;

public:

	inline _Aabb()
	{
		_Data[0] = vector_type((_Value_type)0);
		_Data[1] = vector_type((_Value_type)0);
	}

	inline _Aabb(const vector_type& min, const vector_type& max)
	{
		_Data[0] = min;
		_Data[1] = max;
	}

	inline bool contains(const vector_type& point)
	{
		for(size_t i = 0; i < _Dimensions; ++i)
		{
			if(point[i] < _Data[0][i] ||
			   point[i] > _Data[1][i])
			{
				return false;
			}
		}

		return true;
	}

	_mst_declare_value(min, 0);
	_mst_declare_value(max, 1);

	inline const _Value_type* data() const
	{
		return _Data[0].data();
	}

	inline _Value_type* data()
	{
		return _Data[0].data();
	}

protected:
	vector_type _Data[2];
};

}; // namespace _Details

template<typename _Value_type, size_t _Dimensions>
class aabb : public ::mst::math::_Details::_Aabb<_Value_type, _Dimensions>
{
};

template<typename _Value_type>
class aabb<_Value_type, 1> : public ::mst::math::_Details::_Aabb<_Value_type, 1>
{
public:

	inline aabb()
	{
	}

	inline aabb(const vector_type& min, const vector_type& max)
		: _Aabb<_Value_type, 1>(min, max)
	{
	}

	inline aabb(_Value_type left, _Value_type right)
		: _Aabb<_Value_type, 1>(left, right)
	{
	}

}; // class aabb<_Value_type, 1>

template<typename _Value_type>
class aabb<_Value_type, 2> : public ::mst::math::_Details::_Aabb<_Value_type, 2>
{
public:

	inline aabb()
	{
	}

	inline aabb(const vector_type& min, const vector_type& max)
		: _Aabb<_Value_type, 2>(min, max)
	{
	}

	inline aabb(_Value_type left, _Value_type right,
				_Value_type bottom, _Value_type top)
		: _Aabb<_Value_type, 2>(vector_type(left, bottom), vector_type(right, top))
	{
	}

}; // class aabb<_Value_type, 2>

template<typename _Value_type>
class aabb<_Value_type, 3> : public ::mst::math::_Details::_Aabb<_Value_type, 3>
{
public:

	inline aabb()
	{
	}

	inline aabb(const vector_type& min, const vector_type& max)
		: _Aabb<_Value_type, 3>(min, max)
	{
	}

	inline aabb(_Value_type left, _Value_type right,
				_Value_type bottom, _Value_type top,
				_Value_type front, _Value_type back)
		: _Aabb<_Value_type, 3>(vector_type(left, bottom, front), vector_type(right, top, back))
	{
	}

}; // class aabb<_Value_type, 3>

#undef _mst_declare_value