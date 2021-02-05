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

inline void wait_object::wait() const
{
	while(1)
	{
		if(_Try_wait())
		{
			return;
		}

		::std::this_thread::yield();
	}
}

template<typename RepType, typename PeriodType>
inline bool wait_object::wait_for(const ::std::chrono::duration<RepType, PeriodType>& duration) const
{
	typedef ::std::chrono::duration<RepType, PeriodType> DurationType;

	if(duration.count() == 0)
	{
		return _Try_wait();
	}
	else
	{
		auto start = ::std::chrono::high_resolution_clock::now();

		while(1)
		{
			const unsigned long currentValue = m_counter;

			if(_Try_wait())
			{
				return true;
			}
			if(duration_cast<DurationType>(::std::chrono::high_resolution_clock::now() - start).count() > duration)
			{
				return false;
			}

			::std::this_thread::yield();
		}
	}
}

template<typename ClockType, typename DurationType>
inline bool wait_object::wait_until(const ::std::chrono::time_point<ClockType, DurationType>& timePoint) const
{
	if(ClockType::now() > timePoint)
	{
		return _Try_wait();
	}
	else
	{

		while(1)
		{
			const unsigned long currentValue = m_counter;

			if(_Try_wait())
			{
				return true;
			}
			if(ClockType::now() > timePoint)
			{
				return false;
			}

			::std::this_thread::yield();
		}
	}
}

template<size_t WaitObjectCount>
inline void wait_object::wait_all(const wait_object *(&waitObjects)[WaitObjectCount])
{
	wait_object::wait_all(waitObjects, WaitObjectCount);
}

inline void wait_object::wait_all(const wait_object * const * waitObjects, size_t waitObjectCount)
{
	for(size_t i = 0; i < waitObjectCount; ++i)
	{
		waitObjects[i]->wait();
	}
}

template<size_t WaitObjectCount>
inline size_t wait_object::wait_any(const wait_object *(&waitObjects)[WaitObjectCount])
{
	return wait_object::wait_any(waitObjects, WaitObjectCount);
}

template<size_t WaitObjectCount>
inline size_t wait_object::wait_any(wait_object *(&waitObjects)[WaitObjectCount])
{
	return wait_object::wait_any(waitObjects, WaitObjectCount);
}

inline size_t wait_object::wait_any(const wait_object * const * waitObjects, size_t waitObjectCount)
{
	if(waitObjectCount == 0)
		return (size_t)-1;

	while(1)
	{
		for(size_t i = 0; i < waitObjectCount; ++i)
		{
			if(waitObjects[i]->_Try_wait())
			{
				return i;
			}
		}

		std::this_thread::yield();
	}
}

template<typename RepType, typename PeriodType, size_t WaitObjectCount>
inline bool wait_object::wait_all_for(const wait_object *(&waitObjects)[WaitObjectCount], const::std::chrono::duration<RepType, PeriodType>& duration)
{
	return wait_object::wait_all_for(waitObjects, WaitObjectCount, duration);
}

template<typename RepType, typename PeriodType, size_t WaitObjectCount>
inline bool wait_object::wait_all_for(wait_object *(&waitObjects)[WaitObjectCount], const::std::chrono::duration<RepType, PeriodType>& duration)
{
	return wait_object::wait_all_for(waitObjects, WaitObjectCount, duration);
}

template<typename RepType, typename PeriodType>
inline bool wait_object::wait_all_for(const wait_object * const * waitObjects, size_t waitObjectCount, const::std::chrono::duration<RepType, PeriodType>& duration)
{
	if(waitObjectCount == 0)
		return true;

	if(duration.count() == 0)
	{
		for(size_t i = 0; i < waitObjectCount; ++i)
		{
			if(waitObjects[i]->_Try_wait())
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		auto start = ::std::chrono::high_resolution_clock::now();

		for(size_t i = 0; i < waitObjectCount; ++i)
		{
			while(1)
			{
				if(waitObjects[i]->_Try_wait())
				{
					break;
				}

				if((::std::chrono::high_resolution_clock::now() - start) > duration)
				{
					return false;
				}

				std::this_thread::yield();
			}
		}
		return true;
	}
}

template<typename ClockType, typename DurationType, size_t WaitObjectCount>
inline bool wait_object::wait_all_until(const wait_object *(&waitObjects)[WaitObjectCount], const::std::chrono::time_point<ClockType, DurationType>& timePoint)
{
	return wait_object::wait_all_until(waitObjects, WaitObjectCount, timePoint);
}

template<typename ClockType, typename DurationType, size_t WaitObjectCount>
inline bool wait_object::wait_all_until(wait_object *(&waitObjects)[WaitObjectCount], const::std::chrono::time_point<ClockType, DurationType>& timePoint)
{
	return wait_object::wait_all_until(waitObjects, WaitObjectCount, timePoint);
}

template<typename ClockType, typename DurationType>
inline bool wait_object::wait_all_until(const wait_object * const * waitObjects, size_t waitObjectCount, const::std::chrono::time_point<ClockType, DurationType>& timePoint)
{
	if(waitObjectCount == 0)
		return true;

	if(ClockType::now() > timePoint)
	{
		for(size_t i = 0; i < waitObjectCount; ++i)
		{
			if(waitObjects[i]->_Try_wait())
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		for(size_t i = 0; i < waitObjectCount; ++i)
		{
			while(1)
			{
				if(waitObjects[i]->_Try_wait())
				{
					break;
				}

				if(ClockType::now() > timePoint)
				{
					return false;
				}

				std::this_thread::yield();
			}
		}
		return true;
	}
}

template<typename RepType, typename PeriodType, size_t WaitObjectCount>
inline size_t (wait_object::wait_any_for)(const wait_object *(&waitObjects)[WaitObjectCount], const::std::chrono::duration<RepType, PeriodType>& duration)
{
	return wait_object::wait_any_for(waitObjects, WaitObjectCount, duration);
}

template<typename RepType, typename PeriodType, size_t WaitObjectCount>
inline size_t(wait_object::wait_any_for)(wait_object *(&waitObjects)[WaitObjectCount], const::std::chrono::duration<RepType, PeriodType>& duration)
{
	return wait_object::wait_any_for(waitObjects, WaitObjectCount, duration);
}

template<typename RepType, typename PeriodType>
inline size_t (wait_object::wait_any_for)(const wait_object * const * waitObjects, size_t waitObjectCount, const::std::chrono::duration<RepType, PeriodType>& duration)
{
	if(waitObjectCount == 0)
		return -1;

	if(duration.count() == 0)
	{
		for(size_t i = 0; i < waitObjectCount; ++i)
		{
			if(waitObjects[i]->_Try_wait())
			{
				return i;
			}
		}
		return -1;
	}
	else
	{
		auto start = ::std::chrono::high_resolution_clock::now();

		while(1)
		{
			for(size_t i = 0; i < waitObjectCount; ++i)
			{
				if(waitObjects[i]->_Try_wait())
				{
					return i;
				}
			}

			if((::std::chrono::high_resolution_clock::now() - start) > duration)
			{
				return -1;
			}

			std::this_thread::yield();
		}
	}
}

template<typename ClockType, typename DurationType, size_t WaitObjectCount>
inline size_t (wait_object::wait_any_until)(const wait_object *(&waitObjects)[WaitObjectCount], const::std::chrono::time_point<ClockType, DurationType>& timePoint)
{
	return wait_object::wait_any_until(waitObjects, WaitObjectCount, timePoint);
}

template<typename ClockType, typename DurationType, size_t WaitObjectCount>
inline size_t(wait_object::wait_any_until)(wait_object *(&waitObjects)[WaitObjectCount], const::std::chrono::time_point<ClockType, DurationType>& timePoint)
{
	return wait_object::wait_any_until(waitObjects, WaitObjectCount, timePoint);
}

template<typename ClockType, typename DurationType>
inline size_t mst::threading::slim::wait_object::wait_any_until(const wait_object * const * waitObjects, size_t waitObjectCount, const::std::chrono::time_point<ClockType, DurationType>& timePoint)
{
	if(waitObjectCount == 0)
		return -1;

	if(ClockType::now() > timePoint)
	{
		for(size_t i = 0; i < waitObjectCount; ++i)
		{
			if(waitObjects[i]->_Try_wait())
			{
				return i;
			}
		}
		return -1;
	}
	else
	{
		while(1)
		{
			for(size_t i = 0; i < waitObjectCount; ++i)
			{
				if(waitObjects[i]->_Try_wait())
				{
					return i;
				}
			}

			if(ClockType::now() > timePoint)
			{
				return -1;
			}

			std::this_thread::yield();
		}
	}
}

inline semaphore::semaphore(unsigned long initialCount)
	: m_counter(initialCount)
{
}

inline void semaphore::signal() const
{
	mst::atomic::increment(m_counter);
}

inline void semaphore::signal(unsigned long count) const
{
	mst::atomic::add(m_counter, count);
}

inline bool semaphore::_Try_wait() const
{
	const unsigned long currentValue = m_counter;

	return (currentValue != 0) && (mst::atomic::compare_and_swap(m_counter, currentValue, currentValue - 1) == currentValue);
}

inline mutex::mutex(bool owned)
	: m_counter(owned ? 1 : 0)
{
}

inline void mutex::signal() const
{
	mst::atomic::swap(m_counter, 0);
}

inline bool mutex::_Try_wait() const
{
	return mst::atomic::compare_and_swap(m_counter, 0, 1) == 0;
}

inline recursive_mutex::recursive_mutex(bool owned)
	: m_counter(owned ? 1 : 0),
	m_tid(owned ? ::mst::_Details::_Get_tid() : -1),
	m_recursiveCounter(owned ? 1 : 0)
{
}

inline void recursive_mutex::signal() const
{
	if((--m_recursiveCounter) == 0)
	{
		m_tid = (unsigned long)-1;
		mst::atomic::swap(m_counter, 0);
	}
}

inline bool recursive_mutex::_Try_wait() const
{
	unsigned long tid = ::mst::_Details::_Get_tid();

	if(m_tid == tid)
	{
		++m_recursiveCounter;
		return true;
	}

	bool success = (mst::atomic::compare_and_swap(m_counter, 0, 1) == 0);

	if(success)
	{
		m_tid = tid;
		++m_recursiveCounter;
	}

	return success;
}

inline event::event(bool set, bool manual)
	: m_counter(set ? 1 : 0),
	m_manualReset(manual)
{
}

inline void event::set() const
{
	mst::atomic::swap(m_counter, 1);
}

inline void event::reset() const
{
	mst::atomic::swap(m_counter, 0);
}

inline bool event::_Try_wait() const
{
	if(m_manualReset)
	{
		const unsigned long currentValue = m_counter;

		return currentValue == 1;
	}
	else
	{
		return mst::atomic::compare_and_swap(m_counter, 1, 0) == 0;
	}
}