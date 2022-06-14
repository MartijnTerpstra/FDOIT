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

#include "Light.h"
#include "Scene.h"

using namespace Demo;

Light::Light(string&& name)
	: NamedObject(move(name))
{
}

Light::~Light()
{
}

shared_ptr<Light> Light::Create(string name, float intensity, float3 color, LightType type)
{
	WTRACE;
	auto retval = make_shared<Light>(move(name));

	retval->m_Color = color;

	retval->m_Type = type;

	retval->intensity(intensity);

	retval->coneAngle(10);

	retval->penumbraAngle(5);

	return retval;
}

void Light::color(const float3& color)
{
	m_Color = color;
}

void Light::coneAngle(const float& cone_angle)
{
	m_CosIntensAngle = cos(Common::DegreeToRadian(cone_angle));
}

float Light::coneAngle() const
{
	return Common::RadianToDegree(acos(m_CosIntensAngle));
}

void Light::penumbraAngle(const float& penumbra_angle)
{
	m_CosMaxAngle = cos(Common::DegreeToRadian(coneAngle() + penumbra_angle));
}

float Light::penumbraAngle() const
{
	return Common::RadianToDegree(acos(m_CosMaxAngle)) - coneAngle();
}

void Light::type(const LightType& type)
{
	LightType old_type = m_Type;
	m_Type = type;
	Scene::Get().LightTypeChanged(shared_this_ptr, old_type);
}

LightType Light::type() const
{
	return m_Type;
}

void Light::intensity(const float& intensity)
{
	m_Intensity = intensity;
	m_Radius = intensity * RADIUS_PER_INTENSITY;
}

float Light::areaOfInflunce() const
{
	return m_Radius;
}