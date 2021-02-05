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

class Window
{
	friend class Internal;
	friend class Renderer;
	friend class std::_Ref_count_obj<Window>;
private:
	// ctor & dtor
	Window(uint2);
	~Window();

public:
	// properties

	declare_property(uint2, size);

	declare_get_property(uint, width);

	declare_get_property(uint, height);

	declare_property(string, caption);

	declare_get_property(float, aspectRatio);

	declare_get_property(bool, active);

	declare_property(bool, fullScreen);

public:
	// main functionality

private:
	// for Internal

	void CheckForMessages();
	void SystemMessages();
	void SetCallback(const shared_ptr<IGame>&);

private:
	// internal

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	LRESULT OnWndProc(HWND, UINT, WPARAM, LPARAM);

private:
	HWND m_NativeHandle;
	bool m_Initialized;
	bool m_Destroyed;
	bool m_Minimized;
	weak_ptr<IGame> m_Game;
	com_ptr<IDXGISwapChain> m_SwapChain;
	uint2 m_Size;
};

}; // namespace Demo
