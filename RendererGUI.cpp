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

namespace Demo {

void __stdcall OnSetRenderMode(const void* value, void* data)
{
	Renderer::Get().renderMode = RenderMode(*(int32*)value);
}

void __stdcall OnGetRenderMode(void* value, void* data)
{
	*(int32*)value = (int32)Renderer::Get().renderMode;
}

void __stdcall OnSetCompRenderMode(const void* value, void* data)
{
	Renderer::Get().comparisonRenderMode = RenderMode(*(int32*)value);
}

void __stdcall OnGetCompRenderMode(void* value, void* data)
{
	*(int32*)value = (int32)Renderer::Get().comparisonRenderMode;
}

void __stdcall OnSetErrorCalculation(const void* value, void* data)
{
	Renderer::Get().errorCalculation = *(bool*)value;
}

void __stdcall OnGetErrorCalculation(void* value, void* data)
{
	*(bool*)value = Renderer::Get().errorCalculation;
}

void __stdcall OnClickRecalculate(void* data)
{
	Renderer::Get().RecalculateRMSD();
}

}; // namespace Demo