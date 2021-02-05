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

class QueryInfo
{
public:
	QueryInfo(uint index, const string& name);
	~QueryInfo();

	void SetValue(double value
#if USE_PIPELINE_STATISTICS
		, const D3D11_QUERY_DATA_PIPELINE_STATISTICS& stats
#endif
		);

	static void UseAverage(bool useAverage);

	uint GetIndex() const;

	void Print(std::ofstream& outFile);

private:
	static bool s_useAverage;

private:
	float m_value;
	std::vector<double> m_preciseValues;
#if USE_PIPELINE_STATISTICS
	D3D11_QUERY_DATA_PIPELINE_STATISTICS m_stats;
#endif
	uint m_valueCount;
	uint m_index;
	string m_string;
};

}; // namespace Implementation
}; // namespace Demo