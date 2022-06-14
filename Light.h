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

#define RADIUS_PER_INTENSITY 100.0f

enum LightType
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT
};

class Light : public NamedObject
{
	friend class Renderer;
public:
	// ctor & dtor
	Light(string&& name);
	~Light();

public:
	// creation
	static shared_ptr<Light> Create(string name, float intensity, float3 color, LightType type);

public:
	// properties

	/* the intensity of the light */
	float intensity() const; void intensity(const float& value);

	/* the color of the light */
	float3 color() const; void color(const float3& value);

	/* the type of light */
	LightType type() const; void type(const LightType& value);

	/* the area of influence of the light */
	float areaOfInflunce() const;

	/* cone angle of the spot light, in degrees */
	float coneAngle() const; void coneAngle(const float& value);

	/* penumbra angle of the spot light, in degrees */
	float penumbraAngle() const; void penumbraAngle(const float& value);

private:
	float m_Intensity, m_Radius;
	float3 m_Color;
	LightType m_Type;
	float m_CosMaxAngle, m_CosIntensAngle;
	// spot light

}; // class Light

}; // namespace Demo
