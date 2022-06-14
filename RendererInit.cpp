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

#include "Precomp.h"

#include "Renderer.h"
#include "Window.h"
#include "Timings.h"

using namespace Demo;

namespace {

void __stdcall OnSetRenderMode(const void* value, void* data)
{
	Renderer::Get().renderMode(RenderMode(*(int32_t*)value));
}

void __stdcall OnGetRenderMode(void* value, void* data)
{
	*(int32_t*)value = (int32_t)Renderer::Get().renderMode();
}

void __stdcall OnSetErrorCalculation(const void* value, void* data)
{
	Renderer::Get().errorCalculation(*(bool*)value);
}

void __stdcall OnGetErrorCalculation(void* value, void* data)
{
	*(bool*)value = Renderer::Get().errorCalculation();
}

}

struct alignas(16) ModelBuffer
{
	matrix ModelView;
	matrix ModelViewProj;
};

void Renderer::InitDevice(__in HMODULE d3d11)
{

	//auto PD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)GetProcAddress(d3d11, "D3D11CreateDevice");

#if !USE_DX11_STATIC_LIB
	auto PD3D11CreateDeviceAndSwapChain = (PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN)GetProcAddress(d3d11, "D3D11CreateDeviceAndSwapChain");
#endif

	UINT flags = 0;

#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	std::array lvls = 
	{
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL found_lvl;
	
	/*HRESULT hr = PD3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
		lvls, extentof(lvls), D3D11_SDK_VERSION, mst::initialize(m_Device), &found_lvl, 
		mst::initialize(m_Context));

	if(FAILED(hr))
	{
		throw std::exception("failed to initialize Direct3D11");
	}
	*/

	//com_ptr<IUnknown>(get_device(m_Accelerator))->QueryInterface<ID3D11Device>(&m_Device);
	//m_Device->GetImmediateContext(&m_Context);

	shared_ptr<Window> window(m_Window);

	DEVMODEA devMode;

	if(EnumDisplaySettingsA(nullptr, ENUM_CURRENT_SETTINGS, &devMode) == FALSE)
	{
		devMode.dmDisplayFrequency = 60;
	}

	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = window->m_Size.x;
	desc.BufferDesc.Height = window->m_Size.y;
	desc.BufferDesc.RefreshRate.Numerator = devMode.dmDisplayFrequency;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 2;
	desc.OutputWindow = window->m_NativeHandle;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = 0;

	//

	//hr = _factory->CreateSwapChain(m_Device.get(), &desc, mst::initialize(window->m_SwapChain));
	
	HRESULT hr = PD3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, lvls.data(), (UINT)lvls.size(),
		D3D11_SDK_VERSION, &desc, 
		mst::initialize(window->m_SwapChain), 
		mst::initialize(m_Device), &found_lvl, 
		mst::initialize(m_Context));
	
	if(FAILED(hr))
	{
		throw std::exception("failed to initialize Direct3D11");
	}

	TwInit(TW_DIRECT3D11, m_Device.get());

	auto bar = TwNewBar("Settings");

	TwEnumVal renderModesEnum[] = { {0, "Fixed Depth OIT"}, {1, "Dual depth peeling"},
			{ 2, "Intel's Adaptive OIT" } , {3, "Stochastic Transparency"}, 
			{4, "Unsorted Alpha Blending"}, {5, "High Quality" } };

	TwType rmEnum = TwDefineEnum("RenderModes", renderModesEnum, std::extent_v<decltype(renderModesEnum)>);
	
	TwAddVarCB(bar, "Mode", rmEnum, OnSetRenderMode, OnGetRenderMode, nullptr, nullptr);

	TwDefine("Settings position='16 16' ");
	TwDefine("Settings size='320 320' ");
	TwDefine(" Settings resizable=false ");
	TwDefine(" Settings movable=false ");

	com_ptr<IDXGIDevice> gidev;
	m_Device->QueryInterface<IDXGIDevice>(mst::initialize(gidev));

	com_ptr<IDXGIAdapter> giadap;
	gidev->GetAdapter(mst::initialize(giadap));

	DXGI_ADAPTER_DESC adesc;

	giadap->GetDesc(&adesc);

	wprintf_s(L"Using card: %ls\n", adesc.Description);
	
	if(adesc.VendorId == 0x10DE /* nVidia */)
	{
		
	}

	window->m_SwapChain->ResizeTarget(&desc.BufferDesc);
	
	TwAddVarCB(bar, "Error calculation", TW_TYPE_BOOLCPP, OnSetErrorCalculation, OnGetErrorCalculation
		, nullptr, nullptr);

	Implementation::Timings::Init(m_Context);
}

void Renderer::InitObjects()
{
	shared_ptr<Window> window(m_Window);

	ID3D11Texture2D* _back_buffer;
	window->m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&_back_buffer);
	com_ptr<ID3D11Texture2D> back_buffer(_back_buffer);

	m_Device->CreateRenderTargetView(back_buffer.get(), nullptr, mst::initialize(m_RTV));
	{
		D3D11_TEXTURE2D_DESC desc = {};
		desc.ArraySize = 1;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.Width = window->m_Size.x;
		desc.Height = window->m_Size.y;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;

		com_ptr<ID3D11Texture2D> tex;

		m_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));

		m_Device->CreateDepthStencilView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_DSV));
	}

	{
		D3D11_DEPTH_STENCIL_DESC desc = {};

		desc.DepthEnable = TRUE;
		desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.StencilEnable = FALSE;
		com_ptr<ID3D11DepthStencilState> state;
		m_Device->CreateDepthStencilState(&desc, mst::initialize(state));

		m_Context->OMSetDepthStencilState(state.get(), 0);
	}
	{
		D3D11_RASTERIZER_DESC desc;
		mst::zeromem(desc);
		desc.CullMode = D3D11_CULL_BACK;
		desc.DepthClipEnable = TRUE;
		desc.FillMode = D3D11_FILL_SOLID;
		
		com_ptr<ID3D11RasterizerState> rasterizer;
		m_Device->CreateRasterizerState(&desc, mst::initialize(rasterizer));
		//m_Context->RSSetState(rasterizer.get());
	}

	{
		D3D11_SAMPLER_DESC desc;

		desc.AddressU = desc.AddressV = desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		desc.MaxAnisotropy = 16;
		desc.MinLOD = 0;
		desc.MaxLOD = FLT_MAX;
		desc.MipLODBias = 0;

		com_ptr<ID3D11SamplerState> sampler;
		m_Device->CreateSamplerState(&desc, mst::initialize(sampler));

		m_Context->PSSetSamplers(0, 1, &sampler);
	}

}