#pragma once

#define _mst_declare_value(_Name, _Idx) \
inline _Value_type _get_##_Name() const { return _Data[_Idx]; } \
inline void _set_##_Name(_Value_type _Val) { _Data[_Idx] = _Val; } \
_Value_type __declspec(property(put=_set_##_Name,get=_get_##_Name)) _Name

namespace _Details {

template<typename _Value_type, size_t _Dimensions>
class _Ray
{
public:

	typedef ::mst::math::vector<_Value_type, _Dimensions> vector_type;

	_mst_declare_value(position, 0);
	_mst_declare_value(direction, 1);

protected:

	vector_type _Data[2];

}; // class _Ray<_Value_type, _Dimensions>

};

#undef _mst_declare_value

template<typename _Value_type, size_t _Dimensions>
class ray : public ::mst::math::_Details::_Ray<_Value_type, _Dimensions>
{
	ray() _DEFAULT_MATH_CONSTRUCTOR

	ray(const vector_type& position, const vector_type& direction)
	{
		CHECK_IF(fabs(direction.length() - (_Value_type)1) > MST_EPSILON, "direction required a length of 1");

		_Data[0] = position;
		_Data[1] = direction;
	}
};