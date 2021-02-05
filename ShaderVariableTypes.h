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

#pragma once

namespace Demo { namespace Graphics {

enum VariableType
{
	FLOAT_TYPE,
	FLOAT2_TYPE,
	FLOAT3_TYPE,
	FLOAT4_TYPE,
	MATRIX_TYPE, // 4x4 only
	UINT_TYPE,
	STRUCT_TYPE,
	UNKNOWN_TYPE
};

struct ShaderVariable
{
	VariableType type;
	uint offset;
	uint buffer;
	size_t size;
	size_t array_size;
	string name;
};

struct ShaderTexture
{
	uint slot;
	string name;
};

struct ShaderBuffer
{
	com_ptr<ID3D11Buffer> buffer;
	void* data;
	size_t data_size;
	uint slot;
	bool dirty;
};

template<VariableType type>
struct EnumBase
{
	static const VariableType value = type;
};

template<typename T>
struct ToEnum : public EnumBase<std::is_class<T>::value ? STRUCT_TYPE : UNKNOWN_TYPE>
{
};

template<>
struct ToEnum<float> : public EnumBase<FLOAT_TYPE>
{
};

template<>
struct ToEnum<uint> : public EnumBase<UINT_TYPE>
{
};

template<>
struct ToEnum<float2> : public EnumBase<FLOAT2_TYPE>
{
};

template<>
struct ToEnum<float3> : public EnumBase<FLOAT3_TYPE>
{
};

template<>
struct ToEnum<float4> : public EnumBase<FLOAT4_TYPE>
{
};

template<>
struct ToEnum<matrix> : public EnumBase<MATRIX_TYPE>
{
};

inline VariableType CreateEnum(D3D_SHADER_VARIABLE_TYPE type, D3D_SHADER_VARIABLE_CLASS clss, uint rows, uint columns)
{
	switch(type)
	{
	case D3D_SVT_FLOAT:
		switch(columns)
		{
		case 1:
			if(rows == 1)
			{
				return FLOAT_TYPE;
			}
			break;
		case 2:
			if(rows == 1)
			{
				return FLOAT2_TYPE;
			}
			break;
		case 3:
			if(rows == 1)
			{
				return FLOAT3_TYPE;
			}
			break;
		case 4:
			if(rows == 1)
			{
				return FLOAT4_TYPE;
			}
			if(rows == 4)
			{
				return MATRIX_TYPE;
			}
			break;
		}
		break;

	case D3D_SVT_UINT:
		if(rows == 1 && columns == 1)
		{
			return UINT_TYPE;
		}
		break;

	default:
		if(clss == D3D10_SVC_STRUCT)
		{
			return STRUCT_TYPE;
		}
	}

	return UNKNOWN_TYPE;
}

}; }; // namespace Demo::Graphics
