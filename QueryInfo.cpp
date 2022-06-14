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

#include "QueryInfo.h"

using namespace Demo;
using namespace Implementation;

bool QueryInfo::s_useAverage = false;



QueryInfo::QueryInfo(uint index, const string&  name)
	: m_string("0. " + name + " (ms)"),
	m_valueCount(0),
	m_index(index)
{
	m_value = -1.0f;
	m_string[0] += m_index;

	TwAddVarRO(TwGetBarByName("Timings"), m_string.c_str(), TW_TYPE_FLOAT, &m_value, nullptr);
#if USE_PIPELINE_STATISTICS

	char trisRendered[] = "0. Tris rendered";
	char shadersCount[] = "0. Pixel shader count";

	trisRendered[0] += m_index;
	shadersCount[0] += m_index;

	TwAddVarRO(TwGetBarByName("Timings"), trisRendered, TW_TYPE_UINT32, &m_stats.CPrimitives, nullptr);
	TwAddVarRO(TwGetBarByName("Timings"), shadersCount, TW_TYPE_UINT32, &m_stats.PSInvocations, nullptr);
#endif
}

QueryInfo::~QueryInfo()
{
	char trisRendered[] = "0. Tris rendered";
	char shadersCount[] = "0. Pixel shader count";

	trisRendered[0] += m_index;
	shadersCount[0] += m_index;

	TwRemoveVar(TwGetBarByName("Timings"), m_string.c_str());

#if USE_PIPELINE_STATISTICS
	TwRemoveVar(TwGetBarByName("Timings"), trisRendered);
	TwRemoveVar(TwGetBarByName("Timings"), shadersCount);
#endif
}

void QueryInfo::SetValue(double value
#if USE_PIPELINE_STATISTICS
						 , const D3D11_QUERY_DATA_PIPELINE_STATISTICS& stats
#endif
						 )
{

#if USE_PIPELINE_STATISTICS
	m_stats = stats;
#endif

	if(s_useAverage)
	{
		m_preciseValues.push_back(1000.0 * value);

		if(m_preciseValues.size() > 101)
		{
			m_preciseValues.erase(m_preciseValues.begin());
		}

		double total = 0;
		for(size_t i = 0; i < min(100U, m_preciseValues.size()); ++i)
		{
			total += m_preciseValues[i];
		}
		m_value = float(total / min(100U, m_preciseValues.size()));
	}
	else
	{
		m_value = float(1000.0 * value);
	}
}

void QueryInfo::UseAverage(bool useAverage)
{
	s_useAverage = useAverage;
}

uint QueryInfo::GetIndex() const
{
	return m_index;
}

void QueryInfo::Print(std::ofstream& outFile)
{
	std::string str = m_string + ": ";

	char trisRendered[] = "0. Tris rendered";
	char shadersCount[] = "0. Pixel shader count";

	trisRendered[0] += m_index;
	shadersCount[0] += m_index;

	outFile << str << "<b>" << m_value << "</b><br>";
#if USE_PIPELINE_STATISTICS
	outFile << trisRendered << ": " << m_stats.CPrimitives << "<br>";
	outFile << shadersCount << ": " << m_stats.PSInvocations << "<br>";
#endif
}