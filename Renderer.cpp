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
#include "Camera.h"
#include "Scene.h"
#include "Shader.h"
#include "Window.h"
#include "RenderDDP.h"
#include "RenderPlain.h"
#include "RenderFDOIT.h"
#include "RenderAOIT.h"
#include "RenderStochastic.h"
#include "RenderHQ.h"
#include "Timings.h"

using namespace Demo;

Renderer& Renderer::Get()
{
	static Renderer* instance = new Renderer;
	return *instance;
}

Renderer::Renderer()
	: m_Mode(RENDER_FDOIT),
	m_CompMode((RenderMode)-1),
	m_DebugMode(false),
	m_CalcError(false)
{
}

Renderer::~Renderer()
{
	FreeLibrary(m_D3D11);
}

void Renderer::Init(shared_ptr<Window> window, __in_opt HMODULE d3d11)
{
	WTRACE;

	m_Window = window;

	m_Camera = make_shared<Camera>();

	Scene::Get().m_Camera = m_Camera;

	InitDevice(d3d11);
	InitObjects();

	m_DefShader = Shader::Create("SimpleBlender");

	Implementation::RenderBase::InitStatics(m_Device);
	Implementation::RenderBase::s_RTVs[0] = m_RTV;
	Implementation::RenderBase::s_RTVs[1] = m_RTV;
	Implementation::RenderBase::s_RTVs[2] = m_RTV;

	m_RendererImpls[0] = CreateRenderMode(m_Mode);
}

void Renderer::Render()
{
	shared_ptr<Window> window = m_Window.lock();

	if(window && window->m_NativeHandle)
	{
		RenderForward(window);


		Implementation::Timings::Update();


		//auto timings = TwGetBarByName("Timings");

		//TwRemoveAllVars(timings);

		/*

		for(auto& it : results)
		{
			TwAddVarRO(timings, it.second.first.c_str(), TW_TYPE_FLOAT, &it.second.second, nullptr);
		} */

		TwDefine(" Settings valueswidth=160 ");

		if(errorCalculation())
		{
			TwDefine(" 'Error calculation' valueswidth=160 ");
		}
		TwDraw();

		window->m_SwapChain->Present(0, 0);
	}
}

void Renderer::Exit()
{

	m_DefShader = nullptr;

	m_RendererImpls[0] = nullptr;
	m_RendererImpls[1] = nullptr;

	TwDeleteAllBars();
	TwTerminate();

	Implementation::RenderBase::ReleaseStatics();
}

com_ptr<ID3D11Device> Renderer::GetDevice() const
{
	return m_Device;
}

void Renderer::Resize(uint2 new_size)
{
	
	auto window = m_Window.lock();

	m_Context->OMSetRenderTargets(0,nullptr, nullptr);

	com_ptr<ID3D11Resource> res;

	Implementation::RenderBase::s_RTVs[0] = nullptr;
	Implementation::RenderBase::s_RTVs[1] = nullptr;
	Implementation::RenderBase::s_RTVs[2] = nullptr;
	m_RTV = nullptr;

	auto swap_chain = window->m_SwapChain;

	HRESULT result = swap_chain->ResizeBuffers(1, window->width(), window->height(), DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	ID3D11Texture2D* backbuffer;

	swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(&backbuffer));

	com_ptr<ID3D11Texture2D> back(backbuffer);

	m_Device->CreateRenderTargetView(back.get(), nullptr, mst::initialize(m_RTV));

	Implementation::RenderBase::s_RTVs[0] = m_RTV;
	Implementation::RenderBase::s_RTVs[1] = m_RTV;
	Implementation::RenderBase::s_RTVs[2] = m_RTV;

	if(errorCalculation() && comparisonRenderMode() != (RenderMode)-1)
	{
		com_ptr<ID3D11Texture2D> tex;
		Implementation::RenderBase::s_RTVs[0]->GetResource(mst::initialize(res));
		res->QueryInterface<ID3D11Texture2D>(mst::initialize(tex));
		D3D11_TEXTURE2D_DESC desc;
		tex->GetDesc(&desc);
		desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;

		m_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));
		m_Device->CreateRenderTargetView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_RTVs[0]));
		m_Device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_SRVs[0]));

		m_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));
		m_Device->CreateRenderTargetView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_RTVs[1]));
		m_Device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_SRVs[1]));

		m_Device->CreateTexture2D(&desc, nullptr, mst::initialize(tex));
		m_Device->CreateRenderTargetView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_RTVs[2]));
		m_Device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(Implementation::RenderBase::s_SRVs[2]));
	}

	m_RendererImpls[0]->Resize(new_size);
	if(m_RendererImpls[1])
	{
		m_RendererImpls[1]->Resize(new_size);
	}

	m_Camera->CalcProjectionMatrix();
}

unique_ptr<Implementation::RenderBase> Renderer::CreateRenderMode(RenderMode mode, uint targetRTV)
{
	Implementation::Timings::Reset();

	if(targetRTV == 0)
	{
		RecalculateRMSD();
	}

	switch(mode)
	{
	case RENDER_FDOIT:
		return std::make_unique<Implementation::RenderFDOIT>(targetRTV, window());
	case RENDER_DDP:
		return std::make_unique<Implementation::RenderDDP>(targetRTV, window());
	case RENDER_AOIT:
		return std::make_unique<Implementation::RenderAOIT>(targetRTV, window());
	case RENDER_STOCHASTIC:
		return std::make_unique<Implementation::RenderStochastic>(targetRTV, window());
	case RENDER_PLAIN:
		return std::make_unique<Implementation::RenderPlain>(targetRTV, window());
	case RENDER_HQ:
		return std::make_unique<Implementation::RenderHQ>(targetRTV, window());
	default:
		__debugbreak();
		// unimplemented render mode
		return nullptr;
	}
}

void Renderer::RecalculateRMSD()
{
	m_RMSD = -1;
}

void Renderer::CalcRMSD(const matrix& view, const shared_ptr<Window>& window)
{
	MST_ASSERT(m_RMSD == -1, "invalid call");

	com_ptr<ID3D11Texture2D> tex;

	com_ptr<ID3D11Texture2D> stagingHQ;
	com_ptr<ID3D11Texture2D> stagingAlg;

	D3D11_TEXTURE2D_DESC desc;
	com_ptr<ID3D11Resource> res;
	
	Implementation::RenderBase::s_RTVs[0]->GetResource(mst::initialize(res));
	res->QueryInterface<ID3D11Texture2D>(mst::initialize(tex));
	
	tex->GetDesc(&desc);
	desc.BindFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.Usage = D3D11_USAGE_STAGING;
	m_Device->CreateTexture2D(&desc, nullptr, mst::initialize(stagingHQ));
	
	m_Device->CreateTexture2D(&desc, nullptr, mst::initialize(stagingAlg));

	m_Context->CopyResource(stagingAlg.get(), tex.get());

	if(m_HQ == nullptr)
	{
		Implementation::RenderHQ(2, window).Render(view, window);
	}
	else
	{
		Implementation::RenderBase::s_RTVs[2]->GetResource(mst::initialize(res));
		res->QueryInterface<ID3D11Texture2D>(mst::initialize(tex));
	}

	m_Context->CopyResource(stagingHQ.get(), tex.get());

	D3D11_MAPPED_SUBRESOURCE resourceHQ, resourceAlg;
	m_Context->Map(stagingHQ.get(), 0, D3D11_MAP_READ, 0, &resourceHQ);
	m_Context->Map(stagingAlg.get(), 0, D3D11_MAP_READ, 0, &resourceAlg);

	long double totalDeviation = 0;

	const uint8* algPixels = reinterpret_cast<const uint8*>(resourceHQ.pData);
	const uint8* hqPixels = reinterpret_cast<const uint8*>(resourceAlg.pData);

	uint pitch = resourceAlg.RowPitch;

	long double maxDeviation = 0;

	for(uint y = 0; y < desc.Height; ++y) for(uint x = 0; x < pitch; ++x)
	{
		if((x % 4) == 3)
		{
			continue;
		}
		long double pixelDeviation = algPixels[y * pitch + x] / 255.0L - hqPixels[y * pitch + x] / 255.0L;

		maxDeviation = max(pixelDeviation, maxDeviation);

		totalDeviation += pixelDeviation * pixelDeviation;

	}
	totalDeviation /= resourceHQ.RowPitch * desc.Height;
	
	m_RMSD = (float)sqrt(totalDeviation);

	m_Context->Unmap(stagingHQ.get(), 0);
	m_Context->Unmap(stagingAlg.get(), 0);

}

void Renderer::CreateTestReport()
{

	std::ofstream outfile("results.html");

	outfile << "<!DOCTYPE html><html><body>";

	com_ptr<IDXGIDevice> device;
	m_Device->QueryInterface<IDXGIDevice>(mst::initialize(device));

	com_ptr<IDXGIAdapter> adapter;
	device->GetAdapter(mst::initialize(adapter));

	DXGI_ADAPTER_DESC desc;
	adapter->GetDesc(&desc);

	char description[std::extent_v<decltype(desc.Description)>];

	for(uint i = 0; i < std::extent_v<decltype(desc.Description)>; ++i)
	{
		description[i] = (char)desc.Description[i];
	}

	outfile << "<h1>GPU: " << description << "<h1><br>";

	std::vector<std::pair<float3,float3>> cameraPositions;

	std::ifstream inf("cameraPositions", std::ios::binary);
	uint count = cameraPositions.size();
	inf.read((char*)&count, sizeof(count));
	for(uint i = 0; i < count; ++i)
	{
		std::pair<float3, float3> p;
		inf.read((char*)p.first.data(), sizeof(float3));
		inf.read((char*)p.second.data(), sizeof(float3));
		cameraPositions.push_back(p);
	}

	const char* algNames[] =
	{
		"Fixed Depth OIT",
		"Dual Depth Peeling",
		"Intel's AOIT",
		"nVidia's Stochastic Transparency",
		"Unsorted Alpha Blended",
		"High Quality reference",
	};

	const char* nodeCount[] =
	{
		"4",
		"8",
		"16",
		"32",
	};

	const char* camPosName[] =
	{
		"'Vegetation'",
		"'Simple'",
		"'Particles'",
		"'Filled Scene'",
	};

	const char* dontCompress[] =
	{
		"enabled",
		"disabled"
	};

	const char* alphaCorrection[] =
	{
		"enabled",
		"disabled"
	};

	for(uint mode = 0; mode != NUM_RENDERMODES; ++mode)
	{
		std::cout << "Algorithms to go: " << NUM_RENDERMODES - mode << "\n";

		RenderMode currentMode = (RenderMode)mode;

		outfile << "<br><hr><br><h1>Algorithm: " << algNames[mode] << "</h1><br><br>";

		Renderer::Get().renderMode(currentMode);

		bool notDone = true;

		uint setting1 = 0, setting2 = 0;

#define RenderType(type) static_cast<Implementation::Render##type*>(m_RendererImpls[0].get())


		while(notDone)
		{
			switch(currentMode)
			{
			case RENDER_FDOIT:
				{
					RenderType(FDOIT)->layerDepth((Implementation::FDOITDepth)setting1++);
					if(setting1 == Implementation::FDOIT_NUM_DEPTHS)
					{
						notDone = false;

					}

					outfile << "<h3>Settings:</h3><br>Layer depth: " << nodeCount[RenderType(FDOIT)->layerDepth()] << "<br><br>";
				}
				break;
			case RENDER_DDP:
				{
					if(setting1 == 0)
					{
						setting1 = 1;
					}
					RenderType(DDP)->numLayers(setting1);
					setting1 *= 2;
					if(setting1 > 32)
					{
						notDone = false;
					}

					outfile << "<h3>Settings:</h3><br>Num layers: " << setting1 << "<br><br>";
				}
				break;
			case RENDER_AOIT:
				{
					RenderType(AOIT)->nodeCount((Implementation::AOITNodeCount)setting1++);
					RenderType(AOIT)->dontCompress(setting2 != 0);
					if(setting1 == Implementation::AOIT_NUM_NODE_COUNTS)
					{
						if(setting2 == 1)
						{
							notDone = false;
						}
						setting2 = 1;
						
						setting1 = 0;
					}

					outfile << "<h3>Settings:</h3><br>Node count: " << nodeCount[RenderType(AOIT)->nodeCount()];
					outfile << "<br>Compression opt: " << (RenderType(AOIT)->dontCompress() ? "enabled" : "disabled") << "<br><br>";
				}
				break;
			case RENDER_STOCHASTIC:
				{
					RenderType(Stochastic)->numPasses(setting1);
					setting1 += 4;
					RenderType(Stochastic)->alphaCorrection(setting2 != 0);
					if(setting1 == STOCHASTIC_MAX_NUM_PASSES + 4)
					{
						if(setting2 == 1)
						{
							notDone = false;
						}
						setting2 = 1;
						
						setting1 = 0;
					}

					outfile << "<h3>Settings:</h3><br>Num passes: " << RenderType(Stochastic)->numPasses();
					outfile << "<br>Alpha correction: " << (RenderType(Stochastic)->alphaCorrection() ? "enabled" : "disabled") << "<br><br>";
				}
				break;
			case RENDER_PLAIN:
				notDone = false;
				break;
			case RENDER_HQ:
				notDone = false;
				break;
			default:
				// invalid type
				_MST_BREAK;
			}

			uint camPos = 0;
			for(auto& it : cameraPositions)
			{
				outfile << "<br><b>Camera position " << camPosName[camPos++] << ":</b><br>";

				m_Camera->position(it.first);
				m_Camera->eulerAngles(it.second);

				Implementation::Query::s_gatherStatistics = false;
				Implementation::Timings::SetEnabled(true);
				for(uint i = 0; i < 120; ++i)
				{
					Renderer::Get().Render();

					window()->SystemMessages();
				}
				Implementation::Query::s_gatherStatistics = true;
				Renderer::Get().Render();
				Implementation::Timings::PrintResults(outfile);

				Renderer::Get().errorCalculation(true);

				Renderer::Get().Render();

				outfile << "RMSD: <b>" << Renderer::Get().rootMeanSquareDeviation() << "</b><br>";
			}

			outfile << "<br>";
		}
	}

	std::cout << "DONE! results.html created";

	outfile << "</body></html>";

}

#if USE_DX11_STATIC_LIB
#include DXSDK_DIR_INC(D3DX11.h)
#pragma comment(lib, DXSDK_DIR_LIB(D3DX11.lib))

void Renderer::ScreenShot()
{
	//HMODULE module = LoadLibraryA("D3DX11.dll");

	com_ptr<ID3D11Resource> resource;
	m_RTV->GetResource(mst::initialize(resource));

	//auto PD3DX11SaveTextureToFileA = (decltype(D3DX11SaveTextureToFileA)*)GetProcAddress(module, "D3DX11SaveTextureToFileA");

	D3DX11SaveTextureToFileA(m_Context.get(), resource.get(), D3DX11_IMAGE_FILE_FORMAT::D3DX11_IFF_JPG, "Screenshot.jpg");

	//FreeLibrary(module);
}

#endif