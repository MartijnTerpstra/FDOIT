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


#define _WIN32_WINNT _WIN32_WINNT_WIN7

// mst includes
#include <mcommon.h>
#include <mmath2.h>
#include <mcom_ptr.h>
#include <mflag.h>
#include <malgorithm.h>

// includes
#include <vector>
#include <memory>
#include <algorithm>
#include <Windows.h>
#include <map>
#include <fstream>
#include <array>
#include <numeric>

#include <AntTweakBar.h>

#define foreach(iterator, container) mst_foreach(iterator, container)

// DX11

#if _IS_VC10_COMPILER
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3D11.h>
#else
#include <D3D11.h>
#endif

#include "D3D11enums.h"

#define USE_PIPELINE_STATISTICS 1

typedef ::mst::math::matrix<float,4,4> matrix;
typedef ::mst::math::vector<uint, 2> uint2;
typedef ::mst::math::vector<uint, 3> uint3;
typedef ::mst::math::vector<uint, 4> uint4;
typedef ::mst::math::vector<int, 2> int2;
typedef ::mst::math::vector<float, 2> float2;
typedef ::mst::math::vector<float, 3> float3;
typedef ::mst::math::vector<float, 4> float4;

namespace swizzle {
	using namespace ::mst::math::swizzle;
}

// forward declarations
namespace Demo {

class Mesh;
class Material;
class Window;
class Renderer;
class Shader;
class Camera;
class Light;
class Texture;
class IGame;
class Internal;

	namespace Graphics {

	class TileCuller;
	class RawBuffer;
	struct GPUPointLight;

	};

	namespace Implementation {

	class RenderBase;

	};

};

// internal includes
#include "Common.h"
#include "NamedObject.h"

#if 0
#define WTRACE printf(__FUNCTION__ "()\n")
#else
#define WTRACE
#endif

#define TILE_SIZE 8