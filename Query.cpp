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

#include "Query.h"

using namespace Demo;
using namespace Implementation;

bool Query::s_gatherStatistics = false;

Query::Query(const com_ptr<ID3D11Device>& device)
	: m_inUse(false)
{
	mst::zeromem(m_results);

	D3D11_QUERY_DESC desc = {};

	desc.Query = D3D11_QUERY_TIMESTAMP;

	device->CreateQuery(&desc, mst::initialize(m_query[0]));
	device->CreateQuery(&desc, mst::initialize(m_query[1]));

#if USE_PIPELINE_STATISTICS
	m_statsDone = false;
	m_usingStats = s_gatherStatistics;

	desc.Query = D3D11_QUERY_PIPELINE_STATISTICS;
	device->CreateQuery(&desc, mst::initialize(m_statsQuery));
#endif
}

void Query::Begin(const com_ptr<ID3D11DeviceContext>& context)
{
	CHECK_IF(InUse(), "already in use");
	context->End(m_query[0].get());
#if USE_PIPELINE_STATISTICS
	if(s_gatherStatistics)
		context->Begin(m_statsQuery.get());
	m_usingStats = s_gatherStatistics;
#endif
	m_inUse = true;
}

void Query::End(const com_ptr<ID3D11DeviceContext>& context)
{
	CHECK_IFNOT(InUse(), "not in use");
	context->End(m_query[1].get());
#if USE_PIPELINE_STATISTICS
	if(m_usingStats)
		context->End(m_statsQuery.get());
#endif
	m_inUse = false;
}

bool Query::GetData(const com_ptr<ID3D11DeviceContext>& context, uint64& outData
#if USE_PIPELINE_STATISTICS
		, D3D11_QUERY_DATA_PIPELINE_STATISTICS& outStats
#endif
		)
{

#if USE_PIPELINE_STATISTICS
	if(m_usingStats && !m_statsDone)
	{
		mst::zeromem(m_stats);
		if(context->GetData(m_statsQuery.get(), &m_stats, sizeof(m_stats), D3D11_ASYNC_GETDATA_DONOTFLUSH) == S_OK)
		{
			m_statsDone = true;
		}
	}
#endif

	if(m_results[0] == 0)
	{
		if(context->GetData(m_query[0].get(), &m_results[0], sizeof(m_results[0]), D3D11_ASYNC_GETDATA_DONOTFLUSH) != S_OK)
		{
			m_results[0] = 0;
		}
	}

	if(m_results[1] == 0)
	{
		if(context->GetData(m_query[1].get(), &m_results[1], sizeof(m_results[1]), D3D11_ASYNC_GETDATA_DONOTFLUSH) != S_OK)
		{
			m_results[1] = 0;
		}
	}

	if(m_results[0] != 0 && m_results[1] != 0
#if USE_PIPELINE_STATISTICS
		&& (m_statsDone || !m_usingStats)
#endif
		)
	{
		outData = m_results[1] - m_results[0];

		m_results[0] = m_results[1] = 0;

#if USE_PIPELINE_STATISTICS

		m_statsDone = false;
		mst::zeromem(outStats);
		if(m_usingStats)
		{
			outStats = m_stats;
		}
#endif

		return true;
	}

	return false;
}


void Query::WaitAndGetData(const com_ptr<ID3D11DeviceContext>& context, uint64& outData
#if USE_PIPELINE_STATISTICS
						   , D3D11_QUERY_DATA_PIPELINE_STATISTICS& outStats
#endif
						   )
{
#if USE_PIPELINE_STATISTICS
	if(m_usingStats)
	while(context->GetData(m_statsQuery.get(), &m_stats, sizeof(m_stats), 0) != S_OK)
	{
	}
#endif

	while(context->GetData(m_query[0].get(), &m_results[0], sizeof(m_results[0]), 0) != S_OK)
	{
	}

	while(context->GetData(m_query[1].get(), &m_results[1], sizeof(m_results[1]), 0) != S_OK)
	{
	}

	if(m_results[0] != 0 && m_results[1] != 0)
	{
		outData = m_results[1] - m_results[0];

		m_results[0] = m_results[1] = 0;

#if USE_PIPELINE_STATISTICS
		if(m_usingStats)
		{
			outStats = m_stats;
		}
		m_statsDone = false;
#endif

		return;
	}

	// should not happen
	_MST_BREAK;
}

bool Query::InUse() const
{
	return m_inUse;
}

void Query::Reset(const com_ptr<ID3D11DeviceContext>& context)
{
#if USE_PIPELINE_STATISTICS
	m_statsDone = false;
	if(m_usingStats)
		while(context->GetData(m_statsQuery.get(), &m_stats, sizeof(m_stats), 0) != S_OK)
		{}
#endif
	if(m_results[0] == 0)
		while(context->GetData(m_query[0].get(), &m_results[0], sizeof(m_results[0]), 0) != S_OK)
		{}
	if(m_results[1] == 0)
		while(context->GetData(m_query[1].get(), &m_results[1], sizeof(m_results[1]), 0) != S_OK)
		{}
	m_results[0] = m_results[1] = 0;
	m_inUse = false;
}