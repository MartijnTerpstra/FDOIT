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

enum MouseButton
{
	LEFT_MOUSE,
	MIDDLE_MOUSE,
	RIGHT_MOUSE
};

enum OutOfFocusResponse
{
	PAUSE_UNTIL_FOCUS,
	PAUSE_UNTIL_NOT_MINIMIZED,
	KEEP_UPDATING
};

class IGame
{
public:
	virtual ~IGame() = 0 {}

	virtual void OnMouseDown(int2 mouse_pos, MouseButton button) {};
	virtual void OnMouseUp(int2 mouse_pos, MouseButton button) {};
	virtual void OnMouseMove(int2 mouse_pos, int2 relative_movement) {};
	virtual void OnMouseScroll(int2 mouse_pos, int num_scrolls) {}
	virtual void OnKeyDown(int keycode, bool repeating) {};
	virtual void OnKeyUp(int keycode) {};

	virtual void OnResize(uint2 new_size) {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
};

}; // namespace Demo