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

class Camera
{
	friend class Renderer;
	friend class Implementation::RenderBase;
	friend class std::_Ref_count_obj<Camera>;
private:
	// ctor & dtor
	Camera();
	~Camera();

public:
	// properties

	// the euler angles of the camera
	declare_property(float3, eulerAngles);

	// the position of the camera
	declare_property(float3, position);

	declare_get_property(float3, forwardDirection);

	declare_get_property(float3, backwardDirection);

	declare_get_property(float3, leftDirection);

	declare_get_property(float3, rightDirection);

	declare_get_property(float3, upDirection);

	declare_get_property(float3, downDirection);

	declare_get_property(matrix, projectionMatrix);

	declare_property(float, fieldOfView);

	declare_property(float, nearDistance);

	declare_property(float, farDistance);

private:

	void _CalcProjectionMatrix();

private:
	float3 m_EulerAngles;
	matrix m_Matrix;
	float m_FOV, m_NearZ, m_FarZ;
	matrix m_Projection;
}; // class Camera

}; // namespace Demo
