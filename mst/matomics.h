//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//		MST Utility Library							 										//
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

#include <mcore.h>

namespace mst {
namespace atomic {

	/*
		atomic

		{
		retval = atomicValue;
		atomicValue = swapValue;
		return retval;
		}
	*/

	// atomic
	int swap(int volatile& atomicValue, int swapValue);
	// atomic
	long swap(long volatile& atomicValue, long swapValue);
	// atomic
	long long swap(long long volatile& atomicValue, long long swapValue);
	// atomic
	unsigned int swap(unsigned int volatile& atomicValue, unsigned int swapValue);
	// atomic
	unsigned long swap(unsigned long volatile& atomicValue, unsigned long swapValue);
	// atomic
	unsigned long long swap(unsigned long long volatile& atomicValue, unsigned long long swapValue);

	/*
		atomic

		{
		return ++atomicValue;
		}
		*/

	// atomic
	int increment(int volatile& atomicValue);
	// atomic
	long increment(long volatile& atomicValue);
	// atomic
	long long increment(long long volatile& atomicValue);
	// atomic
	unsigned int increment(unsigned int volatile& atomicValue);
	// atomic
	unsigned long increment(unsigned long volatile& atomicValue);
	// atomic
	unsigned long long increment(unsigned long long volatile& atomicValue);

	/*
		atomic

		{
		return atomicValue++;
		}
	*/

	// atomic
	int fetch_increment(int volatile& atomicValue);
	// atomic
	long fetch_increment(long volatile& atomicValue);
	// atomic
	long long fetch_increment(long long volatile& atomicValue);
	// atomic
	unsigned int fetch_increment(unsigned int volatile& atomicValue);
	// atomic
	unsigned long fetch_increment(unsigned long volatile& atomicValue);
	// atomic
	unsigned long long fetch_increment(unsigned long long volatile& atomicValue);

	/*
		atomic

		{
		return --atomicValue;
		}
	*/

	// atomic
	int decrement(int volatile& atomicValue);
	// atomic
	long decrement(long volatile& atomicValue);
	// atomic
	long long decrement(long long volatile& atomicValue);
	// atomic
	unsigned int decrement(unsigned int volatile& atomicValue);
	// atomic
	unsigned long decrement(unsigned long volatile& atomicValue);
	// atomic
	unsigned long long decrement(unsigned long long volatile& atomicValue);

	/*
		atomic

		{
		return atomicValue--;
		}
	*/

	// atomic
	int fetch_decrement(int volatile& atomicValue);
	// atomic
	long fetch_decrement(long volatile& atomicValue);
	// atomic
	long long fetch_decrement(long long volatile& atomicValue);
	// atomic
	unsigned int fetch_decrement(unsigned int volatile& atomicValue);
	// atomic
	unsigned long fetch_decrement(unsigned long volatile& atomicValue);
	// atomic
	unsigned long long fetch_decrement(unsigned long long volatile& atomicValue);


	/*
		atomic

		{
		return atomicValue += addValue;
		}
	*/

	// atomic
	int add(int volatile& atomicValue, int addValue);
	// atomic
	long add(long volatile& atomicValue, long addValue);
	// atomic
	long long add(long long volatile& atomicValue, long long addValue);
	// atomic
	unsigned int add(unsigned int volatile& atomicValue, unsigned int addValue);
	// atomic
	unsigned long add(unsigned long volatile& atomicValue, unsigned long addValue);
	// atomic
	unsigned long long add(unsigned long long volatile& atomicValue, unsigned long long addValue);

	/*
		atomic

		{
		retval = atomicValue;
		atomicValue += subtractValue;
		return retval;
		}
	*/

	// atomic
	int fetch_add(int volatile& atomicValue, int addValue);
	// atomic
	long fetch_add(long volatile& atomicValue, long addValue);
	// atomic
	long long fetch_add(long long volatile& atomicValue, long long addValue);
	// atomic
	unsigned int fetch_add(unsigned int volatile& atomicValue, unsigned int addValue);
	// atomic
	unsigned long fetch_add(unsigned long volatile& atomicValue, unsigned long addValue);
	// atomic
	unsigned long long fetch_add(unsigned long long volatile& atomicValue, unsigned long long addValue);


	/*
		atomic

		{
		return atomicValue -= subtractValue;
		}
	*/

	// atomic
	unsigned int subtract(unsigned int volatile& atomicValue, unsigned int subtractValue);
	// atomic
	unsigned long subtract(unsigned long volatile& atomicValue, unsigned long subtractValue);
	// atomic
	unsigned long long subtract(unsigned long long volatile& atomicValue, unsigned long long subtractValue);

	/*
		atomic

		{
		retval = atomicValue;
		atomicValue -= subtractValue;
		return retval;
		}
	*/

	// atomic
	unsigned int fetch_subtract(unsigned int volatile& atomicValue, unsigned int subtractValue);
	// atomic
	unsigned long fetch_subtract(unsigned long volatile& atomicValue, unsigned long subtractValue);
	// atomic
	unsigned long long fetch_subtract(unsigned long long volatile& atomicValue, unsigned long long subtractValue);


	/*
		atomic

		{
		if(atomicValue == compareValue)
		atomicValue = swapValue;
		return atomicValue;
		}
	*/

	// atomic
	int compare_and_swap(int volatile& atomicValue, int compareValue, int swapValue);
	// atomic
	long compare_and_swap(long volatile& atomicValue, long compareValue, long swapValue);
	// atomic
	long long compare_and_swap(long long volatile& atomicValue, long long compareValue, long long swapValue);
	// atomic
	unsigned int compare_and_swap(unsigned int volatile& atomicValue, unsigned int compareValue, unsigned int swapValue);
	// atomic
	unsigned long compare_and_swap(unsigned long volatile& atomicValue, unsigned long compareValue, unsigned long swapValue);
	// atomic
	unsigned long long compare_and_swap(unsigned long long volatile& atomicValue, unsigned long long compareValue, unsigned long long swapValue);

}; // namespace atomic
}; // namespace mst