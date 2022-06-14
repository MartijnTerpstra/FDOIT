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

#include "Query.h"
#include "QueryInfo.h"

namespace Demo {
namespace Implementation {

class Timings
{
public:
	static void Reset();
	
	static void Update();

	static void BeginFrame();
	static void EndFrame();

	static void BeginQuery(string name);
	static void EndQuery(string name);

	static void SetEnabled(bool enabled);

	static void UseAverage(bool useAverage);

	static void Init(const com_ptr<ID3D11DeviceContext>& context);
	static void Exit();

	static void PrintResults(std::ofstream& outFile);

private:
	struct Frequency
	{
		Frequency() : frequency(0) {}

		bool disjoint() const
		{
			return frequency == 0 && query == nullptr;
		}
		uint64_t frequency;
		com_ptr<ID3D11Query> query;
	};

	struct Results
	{
		Results() : data(0) {
#if USE_PIPELINE_STATISTICS
			mst::zeromem(stats);
#endif
		}

		std::vector<shared_ptr<Query>> running;
		uint64_t data;
#if USE_PIPELINE_STATISTICS
		D3D11_QUERY_DATA_PIPELINE_STATISTICS stats;
#endif
	};

	struct Frame
	{
		Frame() : runningQueries(0) {}

		Frequency frequency;
		uint64_t runningQueries;
		std::map<string, Results> results;
	};


	static void __stdcall OnSetEnabled(const void* data, void* client);
	static void __stdcall OnGetEnabled(void* data, void* client);

	static void Wait();

private:
	static std::vector<Frame> m_frames;
	static std::vector<shared_ptr<Query>> m_unusedQueries;
	static std::vector<com_ptr<ID3D11Query>> m_unusedFrequencies;
	static std::map<string, unique_ptr<QueryInfo>> m_infos;
	static bool m_disabled;
	static com_ptr<ID3D11DeviceContext> m_context;
};

}; // namespace Implementation
}; // namespace Demo