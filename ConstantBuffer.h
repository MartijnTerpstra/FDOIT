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

enum BufferTarget
{
	PIXEL_SHADER,
	VERTEX_SHADER,
};

template<typename T, D3D11_USAGE usage = D3D11_USAGE_DEFAULT>
class ConstantBuffer
{
	typedef std::integral_constant<bool, usage == D3D11_USAGE_DEFAULT> is_default_usage;
public:

	union
	{
		struct { T data; };
		struct { __m128 __aligned[(sizeof(T) + 15) / 16]; };
	};

	ConstantBuffer()
	{
		memset(&data, 0, sizeof(__aligned));
	}

	uint GetSize() const
	{
		if(m_Buffer)
		{
			D3D11_BUFFER_DESC desc;
			m_Buffer->GetDesc(&desc);

			return desc.ByteWidth / sizeof(__aligned);
		}
		return 0;
	}

	void Update(const com_ptr<ID3D11DeviceContext>& context)
	{
		if(m_Buffer == nullptr)
		{
			com_ptr<ID3D11Device> device;
			context->GetDevice(mst::initialize(device));
			D3D11_BUFFER_DESC desc = {};
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.ByteWidth = sizeof(__aligned);
			desc.CPUAccessFlags = (usage == D3D11_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0);
			desc.Usage = usage;
			device->CreateBuffer(&desc, nullptr, mst::initialize(m_Buffer));
		}
		Update(context, is_default_usage());
	}

	void Update(const com_ptr<ID3D11DeviceContext>& context, std::true_type)
	{ // D3D11_USAGE_DEFAULT
		context->UpdateSubresource(m_Buffer.get(), 0, nullptr, &data, 0, 0);
	}

	void Reset()
	{
		m_Buffer = nullptr;
	}

	void Update(const com_ptr<ID3D11DeviceContext>& context, std::false_type)
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		context->Map(m_Buffer.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &data, sizeof(__aligned));
		context->Unmap(m_Buffer.get(), 0);
	}

	void PSSetConstantBuffer(const com_ptr<ID3D11DeviceContext>& context, uint slot)
	{
		if(m_Buffer == nullptr)
		{
			com_ptr<ID3D11Device> device;
			context->GetDevice(mst::initialize(device));
			D3D11_BUFFER_DESC desc = {};
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.ByteWidth = sizeof(__aligned);
			desc.CPUAccessFlags = (usage == D3D11_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0);
			desc.Usage = usage;
			device->CreateBuffer(&desc, nullptr, mst::initialize(m_Buffer));
		}
		context->PSSetConstantBuffers(slot, 1, &m_Buffer);
	}

	void VSSetConstantBuffer(const com_ptr<ID3D11DeviceContext>& context, uint slot)
	{
		if(m_Buffer == nullptr)
		{
			com_ptr<ID3D11Device> device;
			context->GetDevice(mst::initialize(device));
			D3D11_BUFFER_DESC desc = {};
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.ByteWidth = sizeof(__aligned);
			desc.CPUAccessFlags = (usage == D3D11_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0);
			desc.Usage = usage;
			device->CreateBuffer(&desc, nullptr, mst::initialize(m_Buffer));
		}
		context->VSSetConstantBuffers(slot, 1, &m_Buffer);
	}

private:
	com_ptr<ID3D11Buffer> m_Buffer;

}; // class ConstantBuffer<T, slot, usage>


}; }; // namespace Demo::Graphics
