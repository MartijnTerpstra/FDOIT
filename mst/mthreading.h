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
#include <mdebug.h>
#include <matomics.h>

#if _MST_COMPILER_VER >= 11
#include <chrono>
#endif

#if _MST_HAS_DEFAULT_DELETE
#define _MST_EQUALS_DELETE = delete
#else // !_MST_HAS_DEFAULT_DELETE
#define _MST_EQUALS_DELETE
#endif

#include <mx_threading.h>

namespace mst {
namespace threading {


class critical_section
{
public:
	critical_section()
	{
		_Myatomic = 0;
	}

	inline void enter() const
	{
		while(::mst::atomic::compare_and_swap(_Myatomic, 0, 1) != 0) {}
	}

	inline void leave() const
	{
		atomic::swap(_Myatomic, 0);
	}

private:
	// do not copy
	critical_section(const critical_section&) {}
	critical_section& operator = (const critical_section&) {}

private:
	mutable unsigned long _Myatomic;

}; // class critical_section

class rw_lock
{
public:
	rw_lock();
	~rw_lock();

	bool try_lock_read() const;
	bool try_lock_write() const;

	void lock_read() const;
	void lock_write() const;

	void unlock_read() const;
	void unlock_write() const;

private:
	mutable void* _Myhandle;
};

class recursive_mutex
{
public:
	recursive_mutex(bool initalOwner = false);

	~recursive_mutex();

	void signal() const;

#if _MST_COMPILER_VER >= 11

	template< class _Rep, class _Period >
	inline bool wait(const ::std::chrono::duration<_Rep, _Period>& waitDuration) const
	{
		return wait(std::chrono::duration_cast<std::chrono::milliseconds>(waitDuration).count());
	}

	template< class _Clock, class _Duration >
	inline bool wait_until(const ::std::chrono::time_point<_Clock, _Duration>& timePoint) const
	{
		return _Wait_until(timePoint.time_since_epoch());
	}

#endif

	bool wait(long long milliseconds = -1) const;

private:
	// do not copy
	recursive_mutex(const recursive_mutex&) {}
	recursive_mutex& operator = (const recursive_mutex&) {}

private:

#if _MST_COMPILER_VER >= 11

	template< class _Rep, class _Period >
	inline bool _Wait_until(const ::std::chrono::duration<_Rep, _Period>& durationFromEpoch) const
	{
		return _Wait_until(::std::chrono::duration_cast<::std::chrono::milliseconds>(durationFromEpoch).count());
	}

	bool _Wait_until(long long durationFromEpoch) const;

#endif

private:

	void* _Myhandle;
	mutable unsigned long _Myholder;
	mutable unsigned long _Mycount;
};



class threading_object
{
public:

#if _MST_COMPILER_VER >= 11

	template< class _Rep, class _Period >
	inline bool wait(const ::std::chrono::duration<_Rep, _Period>& waitDuration) const
	{
		return wait(std::chrono::duration_cast<std::chrono::milliseconds>(waitDuration).count());
	}

	template< class _Clock, class _Duration >
	inline bool wait_until(const ::std::chrono::time_point<_Clock, _Duration>& timePoint) const
	{
		return _Wait_until(timePoint.time_since_epoch());
	}

#endif

	bool wait(long long milliseconds = -1) const;

	inline void* handle() const
	{
		return _Myhandle;
	}

protected:

	threading_object();

	// not supposed to be virtual
	~threading_object();

private:
	// do not copy
	threading_object(const threading_object&) _MST_EQUALS_DELETE;
	threading_object& operator = (const threading_object&) _MST_EQUALS_DELETE;

private:

#if _MST_COMPILER_VER >= 11
	template< class _Rep, class _Period >
	inline bool _Wait_until(const ::std::chrono::duration<_Rep, _Period>& durationFromEpoch) const
	{
		return _Wait_until(::std::chrono::duration_cast<::std::chrono::milliseconds>(durationFromEpoch).count());
	}

	bool _Wait_until(long long durationFromEpoch) const;
#endif

protected:

	void* _Myhandle;
};


class mutex : public threading_object
{
public:
	mutex(bool initalOwner = false);

	void signal() const;
};

class semaphore : public threading_object
{
public:
	semaphore(long maxCount = LONG_MAX, long initialCount = 0);

	void signal(long count = 1) const;
};

class event : public threading_object
{
public:
	event(bool manualReset, bool startFlagged = false);

	void flag() const;

	void reset() const;
};


class thread : threading_object
{
public:
	template<typename Func>
	thread(Func callableObject)
	{
#if _MST_HAS_RVALUE_REFS
		_Execute_func(::std::move(callableObject));
#else
		_Execute_func(callableObject);
#endif
	}

#if _MST_HAS_RVALUE_REFS
	thread(thread&& other)
	{
		_Myhandle = other._Myhandle;
		other._Myhandle = null;
	}
#endif

	void join() const
	{
		wait();
	}

	bool is_joined() const
	{
		wait(0);
	}

	int get_id() const
	{
		return _Get_id();
	}

private:

	template<typename Func>
	inline void _Execute_func(Func func)
	{
#if _MST_HAS_RVALUE_REFS
		_Execute_func_wrapper(new ::mst::threading::_Details::_Thread_func_impl<Func>(::std::move(func)));
#else
		_Execute_func_wrapper(new ::mst::threading::_Details::_Thread_func_impl<Func>(func));
#endif
	}

	void _Execute_func_wrapper(::mst::threading::_Details::_Thread_func_wrapper*);

	int _Get_id() const;
};

template<typename LockableType>
class lock_guard
{
public:
	explicit lock_guard(const LockableType& lock)
		: _Mylock(&lock)
	{
		_Mylock->wait();
	}

#if _MST_HAS_RVALUE_REFS
	lock_guard(lock_guard&& other)
		: _Mylock(other._Mylock)
	{
		other._Mylock = null;
	}
#endif

	~lock_guard()
	{
		if(_Mylock)
		{
			_Mylock->signal();
		}
	}

private:

	lock_guard(const lock_guard&);
	void operator=(const lock_guard&);

private:

	const LockableType* _Mylock;

}; // class lock_guard<LockableType>

template<>
class lock_guard<critical_section>
{
	explicit lock_guard(const critical_section& lock)
		: _Mylock(&lock)
	{
		_Mylock->enter();
	}

#if _MST_HAS_RVALUE_REFS
	lock_guard(lock_guard&& other)
		: _Mylock(other._Mylock)
	{
		other._Mylock = null;
	}
#endif

	~lock_guard()
	{
		if(_Mylock)
		{
			_Mylock->leave();
		}
	}

private:
	// no copy
	lock_guard(const lock_guard&) _MST_EQUALS_DELETE;
	// no copy
	void operator=(const lock_guard&) _MST_EQUALS_DELETE;

private:

	const critical_section* _Mylock;

}; // class lock_guard<critical_section>


template<typename Iterator>
int wait_for_objects(Iterator beginIter, Iterator endIter, bool waitForAllObjects, long long milliseconds = -1)
{
	return ::mst::threading::_Details::_Wait_for_objects(beginIter, endIter, waitForAllObjects, milliseconds);
}

#if _MST_COMPILER_VER >= 11

template<typename Iterator, class _Rep, class _Period>
inline int wait_for_objects(Iterator beginIter, Iterator endIter, bool waitForAllObjects, const ::std::chrono::duration<_Rep, _Period>& waitDuration)
{
	return wait_for_objects(beginIter, endIter, waitForAllObjects, std::chrono::duration_cast<std::chrono::milliseconds>(waitDuration).count());
}

template<typename Iterator, class _Clock, class _Duration>
inline int wait_for_objects_until(Iterator beginIter, Iterator endIter, bool waitForAllObjects, const ::std::chrono::time_point<_Clock, _Duration>& timePoint)
{
	return ::mst::threading::_Details::_Wait_for_objects_until(beginIter, endIter, waitForAllObjects, timePoint.time_since_epoch());
}

#endif

}; // namespace threading
}; // namespace mst