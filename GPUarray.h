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

namespace Demo {

enum GPUarrayFlags
{
	GPUARR_USE_COUNTER,
	GPUARR_USE_CPU,
};

template<typename T>
class GPUarray
{
public:
	GPUarray()
		: m_elemCount(0),
		m_data(nullptr),
		m_isDirty(false),
		m_capacity(0),
		m_successfulRead(true)
	{
	}

	~GPUarray()
	{
	}

	void Init(const com_ptr<ID3D11Device>& device, mst::flag<D3D11_BIND_FLAG> bindFlags, mst::flag<GPUarrayFlags> flags = nullptr)
	{
		// resize array
		m_device = device;
		m_bindFlags = bindFlags;
		m_miscFlags = flags;
		m_device->GetImmediateContext(mst::initialize(m_context));
	}

	void PSSetShaderResource(uint bufferSlot)
	{
		MST_ASSERT(m_SRV, "not set as SRV");
		
		Update();

		m_context->PSSetShaderResources(bufferSlot, 1, &m_SRV);
	}

	void CSSetShaderResource(uint bufferSlot)
	{
		MST_ASSERT(m_SRV, "not set as SRV");
		
		Update();

		m_context->CSSetShaderResources(bufferSlot, 1, &m_SRV);
	}

	void CSSetUnorderedAccessViews(uint bufferSlot)
	{
		MST_ASSERT(m_UAV, "not set as UAV");

		Update();

		UINT initCount = 0;
		m_context->CSSetUnorderedAccessViews(bufferSlot, 1, &m_UAV, &initCount);
	}

	const com_ptr<ID3D11UnorderedAccessView>& GetUAV()
	{
		MST_ASSERT(m_UAV, "bad call: no UAV available");
		return m_UAV;
	}

	void Memset(UINT value)
	{
		MST_ASSERT(m_UAV, "cannot fill this object");
		UINT values[4] = { value, value, value, value };
		m_context->ClearUnorderedAccessViewUint(m_UAV.get(), values);
	}

	void Memset(INT value)
	{
		MST_ASSERT(m_UAV, "cannot fill this object");
		UINT values[4] = { value, value, value, value };
		m_context->ClearUnorderedAccessViewUint(m_UAV.get(), values);
	}

	void Memset(FLOAT value)
	{
		MST_ASSERT(m_UAV, "cannot fill this object");
		FLOAT values[4] = { value, value, value, value };
		m_context->ClearUnorderedAccessViewFloat(m_UAV.get(), values);
	}

	uint GetElemCount() const
	{
		return m_elemCount;
	}

	uint GetCapacity() const
	{
		return m_capacity;
	}

	void Clear()
	{
		m_elemCount = 0;
	}

	T Get(size_t index) const
	{
		return m_data[index];
	}

	void Set(size_t index, const T& data) const
	{
		m_isDirty = true;
		m_data[index] = data;
	}

	bool LoadFromGPU(bool waitForBuffer = false)
	{
		MST_ASSERT(m_data, "no memory to load from gpu, unset GPUARR_NO_CPU");

		if(!m_readBuffer)
		{
			D3D11_BUFFER_DESC desc = {};
			desc.ByteWidth = sizeof(T) * m_capacity;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			desc.Usage = D3D11_USAGE_STAGING;

			m_device->CreateBuffer(&desc, nullptr, mst::initialize(m_readBuffer));
		}

		if(m_successfulRead || waitForBuffer)
		{
			m_context->CopyResource(m_readBuffer.get(), m_buffer.get());
		}

		UINT mapFlags = 0;
		if(waitForBuffer == false)
		{
			mapFlags = D3D11_MAP_FLAG_DO_NOT_WAIT;
		}

		D3D11_MAPPED_SUBRESOURCE resource;

		HRESULT hr = m_context->Map(m_readBuffer.get(), 0, D3D11_MAP_READ, mapFlags, &resource);


		if(FAILED(hr))
		{
			m_successfulRead = false;
			return false;
		}

		m_successfulRead = true;
		auto memsize = sizeof(T) * m_capacity;
		memcpy(m_data.get(), resource.pData, sizeof(T) * m_capacity);

		std::vector<uint> test(m_capacity);
		memcpy(test.data(), resource.pData, sizeof(T) * m_capacity);

		m_context->Unmap(m_readBuffer.get(), 0);
		
		return true;
	}

	void Fill(UINT value)
	{
		MST_ASSERT(m_UAV, "cannot fill this object");
		UINT values[4] = { value, value, value, value };
		m_context->ClearUnorderedAccessViewUint(m_UAV.get(), values);
	}

	void PushBack(const T& object)
	{
		m_isDirty = true;
		if(m_elemCount >= m_capacity)
		{
			Realloc(std::max(m_capacity, 1) * 2);
		}
		m_data[m_elemCount++] = object;
	}

	void Resize(uint elemCount)
	{
		Realloc(elemCount);
		m_elemCount = elemCount;
	}

	void AddSize(uint elemCount)
	{
		if(elemCount == 0)
		{
			// no need to add zero size
			return;
		}
		if(m_elemCount != 1)
		{
			elemCount *= 2;
		}
		Realloc(m_elemCount + elemCount);
		m_elemCount += elemCount;
	}

private:

	void Update()
	{
		if(m_isDirty)
		{
			m_isDirty = false;
			D3D11_BOX box = { 0,0,0,sizeof(T)*GetElemCount(),1,1 };
			m_context->UpdateSubresource(m_buffer.get(), 0, &box, m_data.get(),0,0);
		}
	}

	void Realloc(uint elemCount)
	{
		if(m_miscFlags.is_enabled(GPUARR_USE_CPU))
		{
			unique_ptr<T[]> newData(new T[elemCount]);

			memcpy(newData.get(), m_data.get(), min(m_elemCount, elemCount) * sizeof(T));
			// always set uninitialized memory to 0 on GPU
			if(elemCount > m_elemCount)
			{
				memset(&newData[m_elemCount], 0, (elemCount - m_elemCount) * sizeof(T));
			}

			m_data = move(newData);
		}
		else
		{
			m_data = nullptr;
			m_isDirty = false;
		}

		m_capacity = elemCount;

		CreateD3D11Objects();
	}

	void CreateD3D11Objects()
	{
		D3D11_BUFFER_DESC desc;

		desc.BindFlags = m_bindFlags.get();
		desc.ByteWidth = m_capacity * sizeof(T);
		desc.CPUAccessFlags = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.StructureByteStride = sizeof(T);
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		HRESULT hr = m_device->CreateBuffer(&desc, nullptr, mst::initialize(m_buffer));

		if(FAILED(hr))
		{
			Renderer::Get().window()->fullScreen(false);
			MST_FATAL_ERROR("unable to resize GPUarray: Buffer creation failed");
		}

		if(desc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC desc = {};
			desc.Format = DXGI_FORMAT_UNKNOWN;
			desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
			desc.Buffer.FirstElement = 0;
			desc.Buffer.NumElements = m_capacity;
			if(m_miscFlags.is_enabled(GPUARR_USE_COUNTER))
			{
				desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;
			}
			hr = m_device->CreateUnorderedAccessView(m_buffer.get(), &desc, mst::initialize(m_UAV));

			if(FAILED(hr))
			{
				_MST_BREAK;
				throw "unable to resize GPUarray: UAV creation failed";
			}
		}
		if(desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			hr = m_device->CreateShaderResourceView(m_buffer.get(), nullptr, mst::initialize(m_SRV));
			
			if(FAILED(hr))
			{
				_MST_BREAK;
				throw "unable to resize GPUarray: SRV creation failed";
			} 
		}

		if(m_readBuffer)
		{
			D3D11_BUFFER_DESC desc = {};
			desc.ByteWidth = sizeof(T) * m_capacity;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			desc.Usage = D3D11_USAGE_STAGING;

			hr = m_device->CreateBuffer(&desc, nullptr, mst::initialize(m_readBuffer));

			if(FAILED(hr))
			{
				_MST_BREAK;
				throw "unable to resize GPUarray: Read buffer creation failed";
			} 
		}
	}

private:
	bool m_isDirty, m_successfulRead;
	mst::flag<D3D11_BIND_FLAG> m_bindFlags;
	mst::flag<GPUarrayFlags> m_miscFlags;
	unique_ptr<T[]> m_data;
	uint m_elemCount, m_capacity;
	com_ptr<ID3D11Device> m_device;
	com_ptr<ID3D11DeviceContext> m_context;
	com_ptr<ID3D11Buffer> m_buffer;
	com_ptr<ID3D11ShaderResourceView> m_SRV;
	com_ptr<ID3D11UnorderedAccessView> m_UAV;
	com_ptr<ID3D11Buffer> m_readBuffer;
};

};