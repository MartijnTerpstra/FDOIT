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
namespace Implementation {

class Query
{
public:

	static bool s_gatherStatistics;

	Query(const com_ptr<ID3D11Device>& device);

	void Begin(const com_ptr<ID3D11DeviceContext>& context);
	void End(const com_ptr<ID3D11DeviceContext>& context);

	bool GetData(const com_ptr<ID3D11DeviceContext>& context, uint64_t& outData
#if USE_PIPELINE_STATISTICS
		, D3D11_QUERY_DATA_PIPELINE_STATISTICS& outStats
#endif
		);

	void WaitAndGetData(const com_ptr<ID3D11DeviceContext>& context, uint64_t& outData
#if USE_PIPELINE_STATISTICS
		, D3D11_QUERY_DATA_PIPELINE_STATISTICS& outStats
#endif
		);

	void Reset(const com_ptr<ID3D11DeviceContext>& context);

	bool InUse() const;

private:
	com_ptr<ID3D11Query> m_query[2];
#if USE_PIPELINE_STATISTICS
	com_ptr<ID3D11Query> m_statsQuery;
	D3D11_QUERY_DATA_PIPELINE_STATISTICS m_stats;
	bool m_statsDone, m_usingStats;
#endif
	uint64_t m_results[2];
	bool m_inUse;
};

}; // namespace Implementation
}; // namespace Demo