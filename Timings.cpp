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

#include "Timings.h"

#include "Renderer.h"

using namespace Demo;
using namespace Implementation;

std::vector<Timings::Frame> Timings::m_frames;
std::vector<shared_ptr<Query>> Timings::m_unusedQueries;
std::vector<com_ptr<ID3D11Query>> Timings::m_unusedFrequencies;
std::map<string, unique_ptr<QueryInfo>> Timings::m_infos;
bool Timings::m_disabled = true;
com_ptr<ID3D11DeviceContext> Timings::m_context;


void operator += (D3D11_QUERY_DATA_PIPELINE_STATISTICS& left, const D3D11_QUERY_DATA_PIPELINE_STATISTICS& right)
{
	left.CInvocations += right.CInvocations;
	left.CPrimitives += right.CInvocations;
	left.CSInvocations += right.CSInvocations;
	left.DSInvocations += right.DSInvocations;
	left.GSInvocations += right.GSInvocations;
	left.GSPrimitives += right.GSPrimitives;
	left.HSInvocations += right.HSInvocations;
	left.IAPrimitives += right.IAPrimitives;
	left.IAVertices += right.IAVertices;
	left.PSInvocations += right.PSInvocations;
	left.VSInvocations += right.VSInvocations;
}

void Timings::Reset()
{
	m_infos.clear();
	for(auto& frame : m_frames)
	{
		for(auto& result : frame.results)
		{
			for(auto& query : result.second.running)
			{
				query->Reset(m_context);
				m_unusedQueries.push_back(query);
			}
		}
	}

	m_frames.clear();
}

void Timings::BeginFrame()
{
	if(m_disabled)
	{
		return;
	}


	//m_frames.emplace_back();
	m_frames.push_back(Frame());
	auto& freq = m_frames.back().frequency;

	freq.frequency = 0;
	if(m_unusedFrequencies.empty())
	{
		com_ptr<ID3D11Device> device;
		m_context->GetDevice(mst::initialize(device));

		D3D11_QUERY_DESC desc;

		desc.MiscFlags = 0;
		desc.Query = D3D11_QUERY_TIMESTAMP_DISJOINT;
		
		device->CreateQuery(&desc, mst::initialize(freq.query));
	}
	else
	{
		freq.query = m_unusedFrequencies.back();
		m_unusedFrequencies.pop_back();
	}

	m_context->Begin(freq.query.get());
}

void Timings::EndFrame()
{
	if(m_disabled)
	{
		return;
	}

	m_context->End(m_frames.back().frequency.query.get());

}

void Timings::Update()
{
	if(m_disabled)
	{
		return;
	}

	TwDefine(" Timings valueswidth=90 ");

	std::erase_if(m_frames, [&](Frame& frame) -> bool
	{
		if(frame.frequency.disjoint())
		{
			if(frame.runningQueries == 0)
			{
				return true;
			}
		}

		if(frame.frequency.query)
		{
			D3D11_QUERY_DATA_TIMESTAMP_DISJOINT data;
			HRESULT hr = m_context->GetData(frame.frequency.query.get(), &data, sizeof(data), D3D11_ASYNC_GETDATA_DONOTFLUSH);
			if(hr == S_OK)
			{
				m_unusedFrequencies.push_back(frame.frequency.query);
				frame.frequency.query = nullptr;

				if(data.Disjoint == FALSE)
				{
					frame.frequency.frequency = data.Frequency;
				}
			}
		}

		uint64_t data;

#if USE_PIPELINE_STATISTICS
		D3D11_QUERY_DATA_PIPELINE_STATISTICS stats;
#endif

		const auto& context = m_context;

		for(auto& result : frame.results)
		{
			std::erase_if(result.second.running, [&](const shared_ptr<Query>& query) -> bool
			{
				if(query->GetData(context, data
#if USE_PIPELINE_STATISTICS
					, stats
#endif
					))
				{
					result.second.data += data;
#if USE_PIPELINE_STATISTICS
					result.second.stats += stats;
#endif
					Timings::m_unusedQueries.push_back(query);
					frame.runningQueries--;
					return true;
				}
				return false;
			} );
		}

		if(frame.frequency.frequency != 0)
		{
			for(auto& result : frame.results)
			{
				if(result.second.running.empty())
				{
					m_infos[result.first]->SetValue(double(result.second.data) / double(frame.frequency.frequency)
#if USE_PIPELINE_STATISTICS
						,result.second.stats
#endif
						);
				}
			}
		}


		return false;
	} );

	if(m_frames.size() > 1 && m_frames[0].runningQueries == 0 && m_frames[1].runningQueries == 0)
	{
		m_frames.erase(m_frames.begin());
	}
}

void Timings::BeginQuery(string name)
{
	if(m_disabled)
	{
		return;
	}

	auto& queryList = m_frames.back().results[name].running;

	if(m_infos.find(name) == m_infos.end())
	{
		//m_infos.emplace(name, unique_ptr<QueryInfo>(new QueryInfo(m_infos.size(), name)));
		m_infos.insert(std::make_pair(name, unique_ptr<QueryInfo>(new QueryInfo(m_infos.size(), name))));
	}

	if(m_unusedQueries.empty())
	{
		com_ptr<ID3D11Device> device;
		m_context->GetDevice(mst::initialize(device));

		queryList.push_back(make_shared<Query>(device));
	}
	else
	{
		queryList.push_back(m_unusedQueries.back());
		m_unusedQueries.pop_back();
	}

	queryList.back()->Begin(m_context);

	m_frames.back().runningQueries++;

}

void Timings::EndQuery(string name)
{
	if(m_disabled)
	{
		return;
	}

	MST_ASSERT(m_frames.back().results.find(name) != m_frames.back().results.end(), "Query not found");
	auto& queryList = m_frames.back().results[name].running;

	queryList.back()->End(m_context);

}

void Timings::Init(const com_ptr<ID3D11DeviceContext>& context)
{
	m_context = context;
	m_disabled = true;

	TwAddVarCB(TwGetBarByName("Settings"), "Timings", TW_TYPE_BOOLCPP, OnSetEnabled, OnGetEnabled, nullptr, nullptr);
}

void Timings::Exit()
{
	Reset();
	m_context = nullptr;
	m_frames.clear();
	m_unusedFrequencies.clear();
	m_unusedQueries.clear();
	m_disabled = true;
}

void __stdcall Timings::OnSetEnabled(__in const void* value, __inout_opt void* data)
{
	SetEnabled(m_disabled);
}

void __stdcall Timings::OnGetEnabled(__inout void* value, __inout_opt void* data)
{
	*(bool*)value = !m_disabled;
}

void Timings::SetEnabled(bool enabled)
{
	if(m_disabled == enabled)
	{

		m_disabled = !enabled;

		if(m_disabled)
		{
			Reset();
			TwDeleteBar(TwGetBarByName("Timings"));
		}
		else
		{
			Renderer::Get().errorCalculation(false);

			auto timings = TwNewBar("Timings");

			TwAddVarRW(timings, "Get pipeline statistics", TW_TYPE_BOOLCPP, &Query::s_gatherStatistics, nullptr);

			TwDefine(" Timings color='17 143 129'");
			//float4 clr;
			//TwGetParam(timings, nullptr, "color", TwParamValueType::TW_PARAM_FLOAT, 4, &clr);
			TwDefine("Timings size='320 320' ");
			TwDefine("Timings position='16 352' ");

			TwDefine(" Timings resizable=false ");
			TwDefine(" Timings movable=false ");
		}
	}
}

void Timings::PrintResults(std::ofstream& outFile)
{
	Wait();

	for(uint i = 0; i < m_infos.size(); ++i)
	{
		for(const auto& it : m_infos)
		{
			if(it.second->GetIndex() == i)
			{
				it.second->Print(outFile);
			}
		}
	}

}

void Timings::Wait()
{
	m_context->Flush();

	Sleep(500);

	std::erase_if(m_frames, [&](Frame& frame) -> bool
	{
		if(frame.frequency.disjoint())
		{
			if(frame.runningQueries == 0)
			{
				return true;
			}
		}


		uint64_t data;
#if USE_PIPELINE_STATISTICS
		D3D11_QUERY_DATA_PIPELINE_STATISTICS stats;
#endif

		for(auto& result : frame.results)
		{
			
			for(const auto& query : result.second.running)
			{
				query->WaitAndGetData(m_context, data
#if USE_PIPELINE_STATISTICS
					, stats
#endif
					);
				result.second.data += data;
#if USE_PIPELINE_STATISTICS
				result.second.stats += stats;
#endif
				m_unusedQueries.push_back(query);
				frame.runningQueries--;
			}
			
			result.second.running.clear();
		}

		if(frame.frequency.query)
		{
			D3D11_QUERY_DATA_TIMESTAMP_DISJOINT data;
			while(m_context->GetData(frame.frequency.query.get(), &data, sizeof(data), 0) != S_OK)
			{}
			m_unusedFrequencies.push_back(frame.frequency.query);
			frame.frequency.query = nullptr;

			if(data.Disjoint == TRUE)
			{
				return true;
			}
			frame.frequency.frequency = data.Frequency;
		}

		if(frame.frequency.frequency != 0)
		{
			for(auto& result : frame.results)
			{
				if(result.second.running.empty())
				{
					m_infos[result.first]->SetValue(double(result.second.data) / double(frame.frequency.frequency)
#if USE_PIPELINE_STATISTICS
						, result.second.stats
#endif
						);
				}
			}
		}

		return false;
	} );
}