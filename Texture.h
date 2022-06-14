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

enum TextureType
{
	TEX_TYPE_NO_ALPHA,
	TEX_TYPE_ALPHA,
	TEX_TYPE_SINGLE_VALUE,
	TEX_TYPE_CUBE_MAP,
	TEX_TYPE_CUSTOM,
};

class Texture : public NamedObject
{
	friend class Material;
public:
	// ctor & dtor
	Texture(string&& name);
	~Texture();

public:
	// creation
	static shared_ptr<Texture> Create(string file);

public:
	// properties

	uint2 size() const;

	uint width() const;

	uint height() const;

	TextureType type() const;

private:
	com_ptr<ID3D11ShaderResourceView> m_Texture;
	TextureType m_Type;
}; // class Texture

}; // namespace Demo
