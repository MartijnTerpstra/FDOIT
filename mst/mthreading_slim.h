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

#if !_MST_HAS_STL_THREADING_V1 || !_MST_HAS_STL_CHRONO

#error "This functionality requires the threading v1 and chrono libraries of the STL"

#endif

#include <mcore.h>
#include <thread>
#include <mx_threading_slim.h>
#include <chrono>
#include <matomics.h>

namespace mst {
namespace threading {
namespace slim {

class wait_object;

class wait_object
{
public:

	inline void wait() const;

	template<typename RepType, typename PeriodType>
	inline bool wait_for(const ::std::chrono::duration<RepType, PeriodType>& duration) const;

	template<typename ClockType, typename DurationType>
	inline bool wait_until(const ::std::chrono::time_point<ClockType, DurationType>& timePoint) const;

public:
	// statics

	template<size_t WaitObjectCount>
	inline static void wait_all(const wait_object* (&waitObjects)[WaitObjectCount]);

	template<size_t WaitObjectCount>
	inline static void wait_all(wait_object* (&waitObjects)[WaitObjectCount]);

	inline static void wait_all(const wait_object* const * waitObjects, size_t waitObjectCount);

	template<size_t WaitObjectCount>
	inline static size_t wait_any(const wait_object* (&waitObjects)[WaitObjectCount]);

	template<size_t WaitObjectCount>
	inline static size_t wait_any(wait_object* (&waitObjects)[WaitObjectCount]);

	inline static size_t wait_any(const wait_object* const * waitObjects, size_t waitObjectCount);

	template<typename RepType, typename PeriodType, size_t WaitObjectCount>
	inline static bool wait_all_for(const wait_object* (&waitObjects)[WaitObjectCount], const ::std::chrono::duration<RepType, PeriodType>& duration);

	template<typename RepType, typename PeriodType, size_t WaitObjectCount>
	inline static bool wait_all_for(wait_object* (&waitObjects)[WaitObjectCount], const ::std::chrono::duration<RepType, PeriodType>& duration);

	template<typename RepType, typename PeriodType>
	inline static bool wait_all_for(const wait_object* const * waitObjects, size_t waitObjectCount, const ::std::chrono::duration<RepType, PeriodType>& duration);

	template<typename ClockType, typename DurationType, size_t WaitObjectCount>
	inline static bool wait_all_until(const wait_object* (&waitObjects)[WaitObjectCount], const ::std::chrono::time_point<ClockType, DurationType>& timePoint);

	template<typename ClockType, typename DurationType, size_t WaitObjectCount>
	inline static bool wait_all_until(wait_object* (&waitObjects)[WaitObjectCount], const ::std::chrono::time_point<ClockType, DurationType>& timePoint);

	template<typename ClockType, typename DurationType>
	inline static bool wait_all_until(const wait_object* const * waitObjects, size_t waitObjectCount, const ::std::chrono::time_point<ClockType, DurationType>& timePoint);

	template<typename RepType, typename PeriodType, size_t WaitObjectCount>
	inline static size_t wait_any_for(const wait_object* (&waitObjects)[WaitObjectCount], const ::std::chrono::duration<RepType, PeriodType>& duration);

	template<typename RepType, typename PeriodType, size_t WaitObjectCount>
	inline static size_t wait_any_for(wait_object* (&waitObjects)[WaitObjectCount], const ::std::chrono::duration<RepType, PeriodType>& duration);

	template<typename RepType, typename PeriodType>
	inline static size_t wait_any_for(const wait_object* const * waitObjects, size_t waitObjectCount, const ::std::chrono::duration<RepType, PeriodType>& duration);

	template<typename ClockType, typename DurationType, size_t WaitObjectCount>
	inline static size_t wait_any_until(const wait_object* (&waitObjects)[WaitObjectCount], const ::std::chrono::time_point<ClockType, DurationType>& timePoint);

	template<typename ClockType, typename DurationType, size_t WaitObjectCount>
	inline static size_t wait_any_until(wait_object* (&waitObjects)[WaitObjectCount], const ::std::chrono::time_point<ClockType, DurationType>& timePoint);

	template<typename ClockType, typename DurationType>
	inline static size_t wait_any_until(const wait_object* const * waitObjects, size_t waitObjectCount, const ::std::chrono::time_point<ClockType, DurationType>& timePoint);

protected:
	virtual bool _Try_wait() const = 0;

};

class semaphore final : public wait_object
{
public:

	semaphore(unsigned long initialCount = 0);

	void signal() const;

	void signal(unsigned long count) const;

protected:
	inline bool _Try_wait() const override;

private:
	mutable volatile unsigned long m_counter;
};

class mutex final : public wait_object
{
public:
	mutex(bool owned);

	void signal() const;

	inline void lock() const
	{
		wait();
	}

	inline void unlock() const
	{
		signal();
	}

protected:

	inline bool _Try_wait() const override;

private:
	mutable volatile unsigned long m_counter;
};

class recursive_mutex final : public wait_object
{
public:
	recursive_mutex(bool owned);

	void signal() const;

	inline void lock() const
	{
		wait();
	}

	inline void unlock() const
	{
		signal();
	}

protected:

	inline bool _Try_wait() const override;

private:
	mutable volatile unsigned long m_counter;
	mutable volatile unsigned long m_tid;
	mutable volatile unsigned long m_recursiveCounter;
};

class event final : public wait_object
{
public:
	event(bool set, bool manual);

	void set() const;

	void reset() const;

protected:

	inline bool _Try_wait() const override;

private:
	mutable volatile unsigned long m_counter;
	const bool m_manualReset;
};


#include <mx_threading_slim.inl>

}; // slim
}; // namespace threading
}; // namespace mst