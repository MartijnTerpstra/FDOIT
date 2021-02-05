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

#include "Camera.h"
#include "Renderer.h"
#include "Window.h"

using namespace Demo;

Camera::Camera()
	: m_Matrix(matrix::identity),
	m_EulerAngles(0,0,0),
	m_FOV(70.0f), m_NearZ(3.0f), m_FarZ(3000.0f)
{
	_CalcProjectionMatrix();
}

Camera::~Camera()
{
}

float3 Camera::_eulerAngles() const
{
	return m_EulerAngles;
}

void Camera::_eulerAngles(const float3& angles)
{ // ZYX rotation
	float3 pos = position;

//	m_Matrix = g_Identity.rotated_z(Common::DegreeToRadian(angles.z)).rotated_y(Common::DegreeToRadian(angles.y)).rotated_x(Common::DegreeToRadian(angles.x));

	m_Matrix = matrix::identity.rotated_z(Common::DegreeToRadian(angles.z)).rotated_x(Common::DegreeToRadian(angles.x)).rotated_y(Common::DegreeToRadian(angles.y));

	//m_Matrix = g_Identity.rotated_z(Common::DegreeToRadian(angles.z)).rotated_y(Common::DegreeToRadian(angles.y));
	
	position = pos;

	m_EulerAngles = angles;
}

float3 Camera::_position() const
{
	return m_Matrix.position;
}

void Camera::_position(const float3& position)
{
	m_Matrix.position = position;
}

void Camera::_CalcProjectionMatrix()
{

	double sine, cotangent, deltaZ;
	double radians = float(m_FOV / 2.0 * 3.14159265 / 180.0) / 2.0f;
	double aspect = Renderer::Get().window->aspectRatio;
  
	deltaZ = m_FarZ - m_NearZ;
	sine = sin(radians);
	/* Should be non-zero to avoid division by zero. */
	CHECK_IFNOT(deltaZ, "internal error: CreatePerspectiveMatrix(): (E1)");
	CHECK_IFNOT(sine, "internal error: CreatePerspectiveMatrix(): (E2)");
	CHECK_IFNOT(aspect, "internal error: CreatePerspectiveMatrix(): (E2)");
	cotangent = cos(radians) / sine;

	memset(&m_Projection, 0, sizeof(m_Projection));

	/* First row */
	m_Projection[0].x = (float) (cotangent / aspect);
  
	/* Second row */
	m_Projection[1].y = (float) cotangent;
  
	/* Third row */
	m_Projection[2].z = (float) ((m_FarZ) / deltaZ);
	m_Projection[2].w = (float) (-m_NearZ * m_FarZ / deltaZ);
	
	/* Fourth row */
	m_Projection[3].z = 1.0f;

}

float3 Camera::_forwardDirection() const
{
	return float3(m_Matrix[0].z, m_Matrix[1].z, m_Matrix[2].z);
}

float3 Camera::_backwardDirection() const
{
	return -forwardDirection;
}

float3 Camera::_leftDirection() const
{
	return -rightDirection;
}

float3 Camera::_rightDirection() const
{
	return float3(m_Matrix[0].x, m_Matrix[1].x, m_Matrix[2].x);
}

float3 Camera::_upDirection() const
{
	return float3(m_Matrix[0].y, m_Matrix[1].y, m_Matrix[2].y);
}

float3 Camera::_downDirection() const
{
	return -upDirection;
}

float Camera::_farDistance() const
{
	return m_FarZ;
}

matrix Camera::_projectionMatrix() const
{
	return m_Projection;
}