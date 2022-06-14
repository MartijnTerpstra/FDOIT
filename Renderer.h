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

#include "GPUStructs.h"
#include "ConstantBuffer.h"
#include "Texture2D.h"
#include "GPUarray.h"
#include "RenderBase.h"
#include "RenderHQ.h"

#define USE_DX11_STATIC_LIB 0

#if USE_DX11_STATIC_LIB
#define DXSDK_DIR_INC(x) <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\\##x##>
#define DXSDK_DIR_LIB(x) "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x86\\" #x
#pragma comment(lib, DXSDK_DIR_LIB(d3d11.lib))
#define PD3D11CreateDeviceAndSwapChain D3D11CreateDeviceAndSwapChain
#endif

namespace Demo {

enum RenderMode
{
	RENDER_FDOIT,
	RENDER_DDP,
	RENDER_AOIT,
	RENDER_STOCHASTIC,
	RENDER_PLAIN,
	RENDER_HQ,

	NUM_RENDERMODES
};

class Renderer
{
	friend class Internal;
private:
	// ctor & dtor
	Renderer();
	~Renderer();

public:
	// singleton
	static Renderer& Get();

public:
	// properties

	shared_ptr<Camera> camera() const;

	shared_ptr<Window> window() const;

	shared_ptr<Shader> defaultShader() const;

	float globalAmbient() const; void globalAmbient(const float& value);

	RenderMode renderMode() const; void renderMode(const RenderMode& value);

	bool debugMode() const; void debugMode(const bool& value);

	bool errorCalculation() const; void errorCalculation(const bool& value);

	RenderMode comparisonRenderMode() const; void comparisonRenderMode(const RenderMode& value);

	float rootMeanSquareDeviation() const;

public:
	// main functionality

	com_ptr<ID3D11Device> GetDevice() const;

	void RecalculateRMSD();

	void CreateTestReport();

#if USE_DX11_STATIC_LIB
	void ScreenShot();
#endif

private:
	// for Internal
	void Init(__in shared_ptr<Window>, __in_opt HMODULE);
	void Render();
	void Exit();

	void Resize(uint2);

private:
	// implementation



	void InitDevice(__in HMODULE);
	void InitObjects();

	void CalcRMSD(const matrix& view, const shared_ptr<Window>& window);

	void RenderForward(const shared_ptr<Window>& window);
	std::unique_ptr<Implementation::RenderBase> CreateRenderMode(RenderMode mode, uint targetRTV = 0);

private:
	// AntTweakBar callbacks

	ANTTWEAK_FRIEND_CALLBACK(RenderMode);
	ANTTWEAK_FRIEND_CALLBACK(CompRenderMode);
	ANTTWEAK_FRIEND_CALLBACK(ErrorCalculation);
	friend ANTTWEAK_BUTTON_CALLBACK(Recalculate);

private:
	com_ptr<ID3D11Device> m_Device;
	com_ptr<ID3D11DeviceContext> m_Context;
	
	weak_ptr<Window> m_Window;
	shared_ptr<Camera> m_Camera;
	shared_ptr<Shader> m_DefShader;
	HMODULE m_D3D11;
	bool m_DebugMode, m_CalcError;
	RenderMode m_Mode;
	com_ptr<ID3D11RenderTargetView> m_RTV;
	unique_ptr<Implementation::RenderBase> m_RendererImpls[2];
	unique_ptr<Implementation::RenderHQ> m_HQ;
	float m_RMSD;
	RenderMode m_CompMode;

}; // class Renderer

}; // namespace Demo