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

#include "Texture.h"
#include "Renderer.h"

using namespace Demo;


#define CURRENT_BTF_VERSION 1000
#define BTF_MAGIC_NUMBER 'btf\n'

struct BTFHeader
{
	uint magic_number;
	uint version;
	uint type;
	uint width, height;
	DXGI_FORMAT format;
	uint array_size, mip_lvls, misc_flags;

};

Texture::Texture(string&& name)
	: NamedObject(move(name))
{
}

Texture::~Texture()
{
}

shared_ptr<Texture> Texture::Create(string name)
{
	const string file_name = "Textures\\" + name;

	auto retval = make_shared<Texture>(move(name));

	com_ptr<ID3D11Device> device = Renderer::Get().GetDevice();

	std::ifstream ifstr(file_name, std::ios::binary);

	if(ifstr.fail())
	{
		char str[1028];
		sprintf_s(str, "cannot find file: %s", file_name.c_str());
		throw std::exception(str);
	}

	ifstr.seekg(0, std::ios::end);
	size_t file_size = (size_t)ifstr.tellg();
	ifstr.seekg(0);

	std::unique_ptr<char[]> data(new char[file_size]);

	ifstr.read(data.get(), file_size);

	const BTFHeader* hdr = reinterpret_cast<const BTFHeader*>(data.get());

	const char* current = reinterpret_cast<const char*>(data.get());

	current += sizeof(BTFHeader);


	if(hdr->magic_number != BTF_MAGIC_NUMBER)
	{
		char str[1028];
		sprintf_s(str, "invalid file: %s", file_name.c_str());
		throw std::exception(str);
	}

	retval->m_Type = static_cast<TextureType>(hdr->type);

	const uint num_resources = hdr->array_size * hdr->mip_lvls;

	std::unique_ptr<D3D11_SUBRESOURCE_DATA[]> resources(new D3D11_SUBRESOURCE_DATA[num_resources]);

	uint i = 0;

	for(uint a = 0; a < hdr->array_size; ++a)
	{
		for(uint m = 0; m < hdr->mip_lvls; ++m)
		{
			uint pitch = *reinterpret_cast<const uint*>(current);
			current += sizeof(uint);
			uint size = *reinterpret_cast<const uint*>(current);
			current += sizeof(uint);

			resources[i].SysMemPitch = pitch;
			resources[i].pSysMem = current;

			current += size;

			i++;
		}
	}

	D3D11_TEXTURE2D_DESC desc = {};
	desc.ArraySize = hdr->array_size;
	desc.Format = hdr->format;
	desc.Width = hdr->width;
	desc.Height = hdr->height;
	desc.MipLevels = hdr->mip_lvls;
	desc.MiscFlags = hdr->misc_flags;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.CPUAccessFlags = 0;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.SampleDesc.Count = 1;

	com_ptr<ID3D11Texture2D> tex;
	device->CreateTexture2D(&desc, resources.get(), mst::initialize(tex));

	device->CreateShaderResourceView(tex.get(), nullptr, mst::initialize(retval->m_Texture));

	return retval;
}