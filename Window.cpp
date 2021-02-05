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

#include "Window.h"
#include "IGame.h"
#include "Internal.h"

using namespace Demo;

LRESULT CALLBACK Window::WndProc(HWND window, UINT message, WPARAM first_param, LPARAM second_param)
{
	if(TwEventWin(window, message, first_param, second_param))
	{
		return 0;
	}

	auto data = GetWindowLongPtrA(window, GWLP_USERDATA);

	if(data == 0)
	{
		if(TwEventWin(window, message, first_param, second_param))
		{
			return 0;
		} 
		return DefWindowProcA(window, message, first_param, second_param);
	}

	Window* actual_window = reinterpret_cast<Window*>(data);

	return actual_window->OnWndProc(window, message, first_param, second_param);
}

Window::Window(uint2 size)
	: m_Minimized(false),
	m_Destroyed(false),
	m_Initialized(false),
	m_Game(),
	m_Size(size)
{
	WTRACE;
	HINSTANCE instance = GetModuleHandleA(null);

	WNDCLASSA wc; 
	if(!GetClassInfoA(instance, "TFR window", &wc))
	{
		// create window class
		wc.style = CS_HREDRAW | CS_VREDRAW; 
		wc.lpfnWndProc = &Window::WndProc; 
		wc.cbClsExtra = 0; 
		wc.cbWndExtra = 0; 
		wc.hInstance = instance;
		wc.hIcon = null;
		wc.hCursor = LoadCursor(null, IDC_ARROW); 
		wc.hbrBackground = (HBRUSH)GetStockObject(0); 
		wc.lpszMenuName =  "MainMenu"; 
		wc.lpszClassName = "TFR window"; 

		// register class
		ATOM result = RegisterClassA(&wc);
	}

	m_NativeHandle = CreateWindowExA(WS_EX_APPWINDOW, "TFR window", null, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, size.x, size.y, null, null, instance, null);

	SetWindowLongA(m_NativeHandle, GWL_USERDATA, reinterpret_cast<LONG>(this));

	ShowWindow(m_NativeHandle, 1);

	m_Initialized = true;
}

Window::~Window()
{
	if(!m_Destroyed)
	{
		DestroyWindow(m_NativeHandle);
	}
}

LRESULT Window::OnWndProc(HWND window, UINT message, WPARAM first_param, LPARAM second_param)
{
	static int prev_x = INT_MAX;
	static int prev_y = INT_MAX;

	bool active = GetActiveWindow() == window;

	/*if(m_Game == null)
	{
		return DefWindowProcA(window, message, first_param, second_param);
	}*/

	switch (message) 
    { 
        case WM_CREATE: 
            // Initialize the window. 
            return 0; 
 
        case WM_PAINT: 
            return 0; 
 
        case WM_SIZE: 
			if(!m_Destroyed && m_Game.use_count() != 0)
			{
				size = uint2(LOWORD(second_param), HIWORD(second_param));

				shared_ptr<IGame>(m_Game)->OnResize(uint2(LOWORD(second_param), HIWORD(second_param)));
			}
            return 0; 

		case WM_LBUTTONDOWN:
			shared_ptr<IGame>(m_Game)->OnMouseDown(int2(LOWORD(second_param), HIWORD(second_param)), LEFT_MOUSE);
			break;
		case WM_MBUTTONDOWN:
			shared_ptr<IGame>(m_Game)->OnMouseDown(int2(LOWORD(second_param), HIWORD(second_param)), MIDDLE_MOUSE);
			break;
		case WM_RBUTTONDOWN:
			shared_ptr<IGame>(m_Game)->OnMouseDown(int2(LOWORD(second_param), HIWORD(second_param)), RIGHT_MOUSE);
 			break;

		case WM_LBUTTONUP:
			shared_ptr<IGame>(m_Game)->OnMouseUp(int2(LOWORD(second_param), HIWORD(second_param)), LEFT_MOUSE);
			break;
		case WM_MBUTTONUP:
			shared_ptr<IGame>(m_Game)->OnMouseUp(int2(LOWORD(second_param), HIWORD(second_param)), MIDDLE_MOUSE);
			break;
		case WM_RBUTTONUP:
			shared_ptr<IGame>(m_Game)->OnMouseUp(int2(LOWORD(second_param), HIWORD(second_param)), RIGHT_MOUSE);
 			break;

		case WM_MOUSEWHEEL:
			shared_ptr<IGame>(m_Game)->OnMouseScroll(int2(LOWORD(second_param), HIWORD(second_param)), GET_WHEEL_DELTA_WPARAM(first_param) / 120);
			break;

		case WM_MOUSEMOVE:
			if(prev_x == INT_MAX)
			{
				prev_x = LOWORD( second_param );
				prev_y = HIWORD( second_param );
			}

			if (active && !m_Destroyed)
			{
				shared_ptr<IGame>(m_Game)->OnMouseMove(int2(LOWORD( second_param ),HIWORD( second_param )),
					int2(LOWORD( second_param ) - prev_x, HIWORD( second_param ) - prev_y));
			}
			
			prev_x = LOWORD( second_param );
			prev_y = HIWORD( second_param );
			break;

		case WM_KEYUP:
			{
			/*uint val = second_param & 0xFFFF;
			uint val2 = (second_param & 0x7F0000) >> 16;*/
			shared_ptr<IGame>(m_Game)->OnKeyUp((int)first_param);
			}
			break;

		case WM_KEYDOWN:
			if(active)
			{
				shared_ptr<IGame>(m_Game)->OnKeyDown((int)first_param, (((second_param >> 30) & 1) != 0));
			}
			break;

		case WM_CLOSE:
			DestroyWindow(window);
			break;

		case WM_DESTROY:
			m_Destroyed = true;
			Internal::Terminate();
			break;

        // 
        // Process other messages. 
        // 


 
        default: 
            return DefWindowProcA(window, message, first_param, second_param); 
    } 

	return 0;
}

void Window::SetCallback(const shared_ptr<IGame>& game)
{
	m_Game = game;
}

void Window::SystemMessages()
{
	if(m_Destroyed)
	{
		return;
	}
	MSG msg = { 0 };
	while(PeekMessageA(&msg, null, 0, 0, PM_REMOVE | PM_QS_POSTMESSAGE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

void Window::CheckForMessages()
{
	if(m_Destroyed)
	{
		return;
	}
	MSG msg = { 0 };
	while(PeekMessageA(&msg, null, 0, 0, PM_REMOVE | PM_QS_INPUT | PM_QS_POSTMESSAGE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

uint2 Window::_size() const
{
	return m_Size;
}

uint Window::_width() const
{
	return m_Size.x;
}

uint Window::_height() const
{
	return m_Size.y;
}

float Window::_aspectRatio() const
{
	return (float)m_Size.x / m_Size.y;
}

bool Window::_active() const
{
	return m_NativeHandle == GetActiveWindow();
}

void Window::_size(const uint2& newSize)
{
	if(m_Size != newSize && newSize != uint2::zero)
	{
		m_Size = newSize;
		Internal::OnResize(newSize);
	}
}

void Window::_fullScreen(const bool& goFullscreen)
{
	if(goFullscreen != fullScreen)
	{
		m_SwapChain->SetFullscreenState(goFullscreen ? TRUE : FALSE, null);
	}
}

bool Window::_fullScreen() const
{
	BOOL isFullscreen;
	m_SwapChain->GetFullscreenState(&isFullscreen, null);
	return isFullscreen != 0;
}