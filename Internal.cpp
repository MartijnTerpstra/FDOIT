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

#include "Internal.h"
#include "Renderer.h"
#include "Window.h"
#include "IGame.h"
#include "Timings.h"

using namespace Demo;

static Internal* g_Internal = 0;

int OnExit();

extern shared_ptr<IGame> CreateGame();

float g_TimeStep;

int main(int argc, char** argv)
{
	CHAR empty = 0;
	WinMain(GetModuleHandleA(nullptr), nullptr, &empty, 0);
}

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	Internal::Create();

	_onexit(OnExit);

	g_Internal->Run();

	return 0;
}

int OnExit()
{
	if(g_Internal)
	{
		Internal* internal = g_Internal;
		g_Internal = nullptr;
		internal->Exit();
		delete internal;
	}

	return 0;
}

Internal::Internal()
{}

Internal::~Internal()
{}

void Internal::Create()
{
	if(g_Internal)
	{
		throw std::exception("invalid call to Internal::Create()");
	}
	g_Internal = new Internal;
}

void Internal::Init()
{
	WTRACE;
	m_Window = make_shared<Window>(uint2(1280, 720));

#if !USE_DX11_STATIC_LIB
	m_D3D11 = LoadLibraryA("D3D11.dll");
#endif
	Renderer::Get().Init(m_Window, m_D3D11);

	com_ptr<ID3D11DeviceContext> context;
	Renderer::Get().GetDevice()->GetImmediateContext(mst::initialize(context));

	m_Game = CreateGame();

	m_Window->SetCallback(m_Game);

	m_Game->Init();
}

void Internal::Run()
{
	/*try
	{*/

		Init();

		double time = 0.0;

		LARGE_INTEGER freq, start, end;

		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);

		while(!m_Game->IsDone())
		{
			QueryPerformanceCounter(&end);
			g_TimeStep = float(double(end.QuadPart - start.QuadPart) / double(freq.QuadPart));
			QueryPerformanceCounter(&start);

			m_Window->CheckForMessages();

			if(g_TimeStep > 1)
			{
				g_TimeStep = 0;
			}

			m_Game->Update();

			Renderer::Get().Render();
		}

	/*}
	catch(std::exception exc)
	{
		printf("uncaught exception: %s\n", exc.what());
		system("pause");
		abort();
	}*/
}

void Internal::Exit()
{
	Implementation::Timings::Exit();
	m_Game->Exit();
	m_Game = nullptr;
	m_Window = nullptr;
	Renderer::Get().Exit();
	delete &Renderer::Get();
#if !USE_DX11_STATIC_LIB
	FreeLibrary(m_D3D11);
#endif
}

void Internal::OnResize(uint2 new_size)
{
	Renderer::Get().Resize(new_size);
}

void Internal::Terminate()
{
	if(g_Internal != nullptr)
	{
		exit(0);
	}
}