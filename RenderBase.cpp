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
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

// shaders
#include "ShaderHeaders\VertexShader.h"
#include "ShaderHeaders\QuadVS.h"


using namespace Demo;
using namespace Demo::Implementation;


com_ptr<ID3D11RenderTargetView> RenderBase::s_RTVs[3];
com_ptr<ID3D11ShaderResourceView> RenderBase::s_SRVs[3];
com_ptr<ID3D11DepthStencilView> RenderBase::s_DSV;
com_ptr<ID3D11Device> RenderBase::s_Device;
com_ptr<ID3D11DeviceContext> RenderBase::s_Context;
Graphics::ConstantBuffer<Graphics::GPULightingBuffer> RenderBase::s_LightingBuffer;
Graphics::ConstantBuffer<Graphics::GPUModelBuffer> RenderBase::s_ModelBuffer;
com_ptr<ID3D11VertexShader> RenderBase::s_VertexShader;
com_ptr<ID3D11VertexShader> RenderBase::s_QuadVS;

RenderBase::RenderBase(uint RTVindex)
	: m_RTVindex(RTVindex)
{
}

RenderBase::~RenderBase()
{
}

void RenderBase::RenderMeshes(const matrix& view, const shared_ptr<Window>& window, com_ptr<ID3D11PixelShader> pixel)
{
	if(pixel == nullptr)
	{
		pixel = Renderer::Get().defaultShader()->m_Pixel;
	}

	const auto& meshes = Scene::Get().m_Meshes;
	auto camera = Renderer::Get().camera();

	s_ModelBuffer.VSSetConstantBuffer(s_Context, 1);

	s_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	s_Context->VSSetShader(s_VertexShader.get(), nullptr, 0);
	s_Context->PSSetShader(pixel.get(), nullptr, 0);

	for(const auto& mesh : meshes)	
	{
		s_ModelBuffer.data.modelView = view * mesh.second;
		s_ModelBuffer.data.modelViewProj = camera->m_Projection * s_ModelBuffer.data.modelView;
		
		s_ModelBuffer.Update(s_Context);

		mesh.first->Update(camera, s_ModelBuffer.data.modelView);

		const auto& materials = mesh.first->m_SubMeshes;

		UINT zero = 0;
		UINT stride = sizeof(Vertex);
		s_Context->IASetVertexBuffers(0, 1, &mesh.first->m_VertexBuffer, &stride, &zero);
		s_Context->IASetIndexBuffer(mesh.first->m_IndexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);

		uint index_offset = 0;
		for(const auto& submesh : materials)
		{

			submesh.material->Upload(s_Context);

			s_Context->RSSetState(submesh.material->m_Rasterizer.get());

			s_Context->DrawIndexed(submesh.num_indices, index_offset, 0);
			index_offset += submesh.num_indices;
		}
	}

}

void RenderBase::RenderQuad()
{
	/*
	{
		// temp vertex buffer for debugging

		static com_ptr<ID3D11Buffer> vbuffer;
		if(!vbuffer)
		{
			D3D11_BUFFER_DESC desc = {};
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.ByteWidth = 12 * 4;
			desc.Usage = D3D11_USAGE_IMMUTABLE;

			float3 positions[4] = { float3(-1,-1, 0),float3(-1, 1, 0),float3( 1,-1, 0), float3( 1, 1, 0) };

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = positions;

			s_Device->CreateBuffer(&desc, &data, &vbuffer);

			

		}
		UINT stride = 12;
			UINT offset = 0;

		s_Context->IASetVertexBuffers(0, 1, &vbuffer, &stride, &offset);
	}
	*/

	s_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	s_Context->VSSetShader(s_QuadVS.get(), nullptr, 0);

	s_Context->Draw(4, 0);
}

void RenderBase::InitStatics(const com_ptr<ID3D11Device>& device)
{
	s_Device = device;
	device->GetImmediateContext(mst::initialize(s_Context));

	s_Device->CreateVertexShader(g_VertexShader, sizeof(g_VertexShader), nullptr, mst::initialize(s_VertexShader));
	s_Device->CreateVertexShader(g_QuadVS, sizeof(g_QuadVS), nullptr, mst::initialize(s_QuadVS));

	std::array inputElements =
	{
		D3D11_INPUT_ELEMENT_DESC{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,		0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC{"BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0} // BITANGENT
	};

	com_ptr<ID3D11InputLayout> inputLayout;

	s_Device->CreateInputLayout(inputElements.data(), inputElements.size(), g_VertexShader, sizeof(g_VertexShader), mst::initialize(inputLayout));

	s_Context->IASetInputLayout(inputLayout.get());

}

void RenderBase::ReleaseStatics()
{
	s_RTVs[0] = nullptr;
	s_RTVs[1] = nullptr;
	s_DSV = nullptr;

	s_LightingBuffer.Reset();
	s_ModelBuffer.Reset();
	s_VertexShader = nullptr;
	s_QuadVS = nullptr;

	s_Context->ClearState();
	s_Context->Flush();

	s_Context = nullptr;
	/*
	com_ptr<ID3D11Debug> debug;
	s_Device->QueryInterface<ID3D11Debug>(mst::initialize(debug));

	if(debug)
	{
		debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	}
	*/
	s_Device = nullptr;
}

void RenderBase::Clear()
{
	s_Context->ClearDepthStencilView(s_DSV.get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	s_Context->ClearRenderTargetView(s_RTVs[m_RTVindex].get(), &float4::zero[0]);
}

const com_ptr<ID3D11RenderTargetView>& RenderBase::GetRTV()
{
	return s_RTVs[m_RTVindex];
}

TwBar* RenderBase::GetGUIBar()
{
	switch(m_RTVindex)
	{
	case 0:
		return TwGetBarByName("Settings");
	case 1:
		return TwGetBarByName("Error calculation");
	default:
		return nullptr;
	}
}