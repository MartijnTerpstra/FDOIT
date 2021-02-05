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

class Texture2D
{
public:
	Texture2D()
	{
		mst::zeromem(m_desc);
	}

	~Texture2D()
	{
	}

	void Init(const com_ptr<ID3D11Device>& device, mst::flag<D3D11_BIND_FLAG> bindFlags, DXGI_FORMAT format, uint2 size, UINT sampleCount = 1)
	{
		// resize array
		m_device = device;
		m_bindFlags = bindFlags;
		m_device->GetImmediateContext(mst::initialize(m_context));

		m_desc.BindFlags = m_bindFlags.get();
		m_desc.CPUAccessFlags = 0;
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.ArraySize = 1;
		m_desc.Format = format;
		m_desc.Width = 0;
		m_desc.Height = 0;
		m_desc.MipLevels = 1;
		m_desc.SampleDesc.Count = sampleCount;

		Resize(size);
	}

	void PSSetShaderResource(uint bufferSlot)
	{
		CHECK_IF(m_SRV == null, "not set as SRV");
		
		m_context->PSSetShaderResources(bufferSlot, 1, &m_SRV);
	}

	void CSSetShaderResource(uint bufferSlot)
	{
		CHECK_IF(m_SRV == null, "not set as SRV");
		
		m_context->CSSetShaderResources(bufferSlot, 1, &m_SRV);
	}

	void CSSetUnorderedAccessViews(uint bufferSlot)
	{
		CHECK_IF(m_UAV == null, "not set as UAV");

		UINT initCount = 0;
		m_context->CSSetUnorderedAccessViews(bufferSlot, 1, &m_UAV, &initCount);
	}

	const com_ptr<ID3D11Texture2D>& GetResource()
	{
		CHECK_IF(m_texture == null, "bad call: no texture available");
		return m_texture;
	}

	const com_ptr<ID3D11UnorderedAccessView>& GetUAV()
	{
		CHECK_IF(m_UAV == null, "bad call: no UAV available");
		return m_UAV;
	}

	const com_ptr<ID3D11RenderTargetView>& GetRTV()
	{
		CHECK_IF(m_RTV == null, "bad call: no RTV available");
		return m_RTV;
	}

	const com_ptr<ID3D11ShaderResourceView>& GetSRV()
	{
		CHECK_IF(m_SRV == null, "bad call: no SRV available");

		return m_SRV;
	}

	void ClearUAV(UINT value)
	{
		CHECK_IF(m_UAV == null, "cannot fill this object");
		UINT values[4] = { value, value, value, value };
		m_context->ClearUnorderedAccessViewUint(m_UAV.get(), values);
	}

	void ClearUAV(INT value)
	{
		ClearUAV((UINT)value);
	}

	void ClearUAV(FLOAT value)
	{
		CHECK_IF(m_UAV == null, "cannot fill this object");
		FLOAT values[4] = { value, value, value, value };
		m_context->ClearUnorderedAccessViewFloat(m_UAV.get(), values);
	}

	void ClearRTV(const float4& color)
	{
		CHECK_IF(m_RTV == null, "cannot fill this object");
		m_context->ClearRenderTargetView(m_RTV.get(), color.data());
	}

	void Resize(uint2 newSize)
	{
		Realloc(newSize);
	}

	uint2 GetSize() const
	{
		return uint2(m_desc.Width, m_desc.Height);
	}

private:

	void Realloc(uint2 newSize)
	{
		if(GetSize() != newSize)
		{
			m_desc.Width = newSize.x;
			m_desc.Height = newSize.y;
			CreateD3D11Objects();
		}
	}

	void CreateD3D11Objects()
	{
		m_device->CreateTexture2D(&m_desc, null, mst::initialize(m_texture));

		if(m_bindFlags.is_enabled(D3D11_BIND_UNORDERED_ACCESS))
		{
			m_device->CreateUnorderedAccessView(m_texture.get(), null, mst::initialize(m_UAV));
		}
		if(m_bindFlags.is_enabled(D3D11_BIND_SHADER_RESOURCE))
		{
			m_device->CreateShaderResourceView(m_texture.get(), null, mst::initialize(m_SRV));
		}
		if(m_bindFlags.is_enabled(D3D11_BIND_RENDER_TARGET))
		{
			m_device->CreateRenderTargetView(m_texture.get(), null, mst::initialize(m_RTV));
		}

	}


private:
	D3D11_TEXTURE2D_DESC m_desc;
	mst::flag<D3D11_BIND_FLAG> m_bindFlags;
	com_ptr<ID3D11Device> m_device;
	com_ptr<ID3D11DeviceContext> m_context;
	com_ptr<ID3D11Texture2D> m_texture;
	com_ptr<ID3D11ShaderResourceView> m_SRV;
	com_ptr<ID3D11RenderTargetView> m_RTV;
	com_ptr<ID3D11UnorderedAccessView> m_UAV;
};



class Texture2DArray
{
public:
	Texture2DArray()
	{
		mst::zeromem(m_desc);
	}

	~Texture2DArray()
	{
	}

	void Init(const com_ptr<ID3D11Device>& device, mst::flag<D3D11_BIND_FLAG> bindFlags, DXGI_FORMAT format, UINT arraySize, uint2 size, UINT sampleCount = 1)
	{
		// resize array
		m_device = device;
		m_bindFlags = bindFlags;
		m_device->GetImmediateContext(mst::initialize(m_context));

		m_desc.BindFlags = m_bindFlags.get();
		m_desc.CPUAccessFlags = 0;
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.ArraySize = arraySize;
		m_desc.Format = format;
		m_desc.Width = 0;
		m_desc.Height = 0;
		m_desc.MipLevels = 1;
		m_desc.SampleDesc.Count = sampleCount;

		Resize(size);
	}

	void PSSetShaderResource(uint bufferSlot)
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_SHADER_RESOURCE), "not set as SRV");
		
		CreateSRV();

		m_context->PSSetShaderResources(bufferSlot, 1, &m_SRV);
	}

	void PSSetShaderResourceSlice(uint bufferSlot, UINT arraySlice)
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_SHADER_RESOURCE), "not set as SRV");

		CreateSRVSlice(arraySlice);
		
		m_context->PSSetShaderResources(bufferSlot, 1, &m_SRV);
	}

	void CSSetShaderResource(uint bufferSlot)
	{
		CHECK_IF(m_SRV == null, "not set as SRV");
		
		m_context->CSSetShaderResources(bufferSlot, 1, &m_SRV);
	}

	void CSSetUnorderedAccessViews(uint bufferSlot)
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_UNORDERED_ACCESS), "not set as UAV");

		UINT initCount = 0;
		m_context->CSSetUnorderedAccessViews(bufferSlot, 1, &m_UAV, &initCount);
	}

	const com_ptr<ID3D11Texture2D>& GetResource()
	{
		CHECK_IF(m_texture == null, "bad call: no texture available");
		return m_texture;
	}

	const com_ptr<ID3D11UnorderedAccessView>& GetUAV()
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_UNORDERED_ACCESS), "not set as UAV");

		CreateUAV();

		return m_UAV;
	}

	const com_ptr<ID3D11RenderTargetView>& GetRTV()
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_RENDER_TARGET), "not set as RTV");

		CreateRTV();

		return m_RTV;
	}

	const com_ptr<ID3D11ShaderResourceView>& GetSRV()
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_SHADER_RESOURCE), "not set as SRV");

		CreateSRV();

		return m_SRV;
	}

	void ClearUAV(UINT value)
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_UNORDERED_ACCESS), "cannot clear this object");

		CreateUAV();

		UINT values[4] = { value, value, value, value };
		m_context->ClearUnorderedAccessViewUint(m_UAV.get(), values);
	}

	void ClearUAV(INT value)
	{
		ClearUAV((UINT)value);
	}

	void ClearUAV(FLOAT value)
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_UNORDERED_ACCESS), "cannot clear this object");

		CreateUAV();

		FLOAT values[4] = { value, value, value, value };
		m_context->ClearUnorderedAccessViewFloat(m_UAV.get(), values);
	}

	void ClearRTV(const float4& color)
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_RENDER_TARGET), "cannot clear this object");
		
		CreateRTV();

		m_context->ClearRenderTargetView(m_RTV.get(), color.data());
	}

	void ClearRTVSlice(const float4& color, UINT arraySlice)
	{
		CHECK_IFNOT(m_bindFlags.is_enabled(D3D11_BIND_RENDER_TARGET), "cannot clear this object");
		
		CreateRTVSlice(arraySlice);

		m_context->ClearRenderTargetView(m_RTVSlices[arraySlice].get(), color.data());
	}

	void Resize(uint2 newSize)
	{
		Realloc(newSize);
	}

	uint2 GetSize() const
	{
		return uint2(m_desc.Width, m_desc.Height);
	}

private:

	void Realloc(uint2 newSize)
	{
		if(GetSize() != newSize)
		{
			m_desc.Width = newSize.x;
			m_desc.Height = newSize.y;
			CreateD3D11Objects();
		}
	}

	void CreateD3D11Objects()
	{
		m_device->CreateTexture2D(&m_desc, null, mst::initialize(m_texture));

		m_RTVSlices = null;
		m_SRVSlices = null;
		m_UAVSlices = null;
		m_UAV = null;
		m_SRV = null;
		m_RTV = null;

		if(m_bindFlags.is_enabled(D3D11_BIND_RENDER_TARGET))
		{
			m_RTVSlices = make_unique_array<com_ptr<ID3D11RenderTargetView>>(m_desc.ArraySize);
		}
		if(m_bindFlags.is_enabled(D3D11_BIND_SHADER_RESOURCE))
		{
			m_SRVSlices = make_unique_array<com_ptr<ID3D11ShaderResourceView>>(m_desc.ArraySize);
		}
		if(m_bindFlags.is_enabled(D3D11_BIND_UNORDERED_ACCESS))
		{
			m_UAVSlices = make_unique_array<com_ptr<ID3D11UnorderedAccessView>>(m_desc.ArraySize);
		}
	}

	void CreateUAV()
	{
		if(m_UAV == null)
		{
			m_device->CreateUnorderedAccessView(m_texture.get(), null, mst::initialize(m_UAV));
		}
	}

	void CreateSRV()
	{
		if(m_SRV == null)
		{
			m_device->CreateShaderResourceView(m_texture.get(), null, mst::initialize(m_SRV));
		}
	}

	void CreateRTV()
	{
		if(m_RTV == null)
		{
			m_device->CreateRenderTargetView(m_texture.get(), null, mst::initialize(m_RTV));
		}
	}

	void CreateUAVSlice(UINT index)
	{
		if(m_UAVSlices[index] == null)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC desc;

			desc.Format = m_desc.Format;
			desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.ArraySize = 1;
			desc.Texture2DArray.FirstArraySlice = index;
			desc.Texture2DArray.MipSlice = 0;
			m_device->CreateUnorderedAccessView(m_texture.get(), &desc, mst::initialize(m_UAVSlices[index]));
		}
	}

	void CreateSRVSlice(UINT index)
	{
		if(m_SRVSlices[index] == null)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;

			desc.Format = m_desc.Format;
			if(m_desc.SampleDesc.Count == 1)
			{
				desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
				desc.Texture2DArray.ArraySize = 1;
				desc.Texture2DArray.FirstArraySlice = index;
				desc.Texture2DArray.MipLevels = m_desc.MipLevels;
				desc.Texture2DArray.MostDetailedMip = 0;
			}
			else
			{
				desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
				desc.Texture2DMSArray.ArraySize = 1;
				desc.Texture2DMSArray.FirstArraySlice = index;
			}
			m_device->CreateShaderResourceView(m_texture.get(), &desc, mst::initialize(m_SRVSlices[index]));
		}
	}

	void CreateRTVSlice(UINT index)
	{
		if(m_RTVSlices[index] == null)
		{
			D3D11_RENDER_TARGET_VIEW_DESC desc;

			desc.Format = m_desc.Format;
			desc.Format = m_desc.Format;
			if(m_desc.SampleDesc.Count == 1)
			{
				desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
				desc.Texture2DArray.ArraySize = 1;
				desc.Texture2DArray.FirstArraySlice = index;
				desc.Texture2DArray.MipSlice = 0;
			}
			else
			{
				desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
				desc.Texture2DMSArray.ArraySize = 1;
				desc.Texture2DMSArray.FirstArraySlice = index;
			}
			m_device->CreateRenderTargetView(m_texture.get(), null, mst::initialize(m_RTVSlices[index]));
		}
	}


private:
	D3D11_TEXTURE2D_DESC m_desc;
	mst::flag<D3D11_BIND_FLAG> m_bindFlags;
	com_ptr<ID3D11Device> m_device;
	com_ptr<ID3D11DeviceContext> m_context;
	com_ptr<ID3D11Texture2D> m_texture;
	com_ptr<ID3D11ShaderResourceView> m_SRV;
	com_ptr<ID3D11RenderTargetView> m_RTV;
	com_ptr<ID3D11UnorderedAccessView> m_UAV;
	unique_ptr<com_ptr<ID3D11ShaderResourceView>[]> m_SRVSlices;
	unique_ptr<com_ptr<ID3D11RenderTargetView>[]> m_RTVSlices;
	unique_ptr<com_ptr<ID3D11UnorderedAccessView>[]> m_UAVSlices;
};

}; // Demo
