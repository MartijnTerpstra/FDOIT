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
#include <sstream>
#include <fstream>
#include <iostream>

namespace mst {

class logger
{
	typedef int _Log_type;
	
	enum
	{
		_Log_info = 0,
		_Log_error,
		_Log_warning
	};
public:

#ifndef MST_DEBUG_LOGGING
	static inline void error(const std::string& text)
	{
		_Message(_Log_error,text);
	}

	static inline void warning(const std::string& text)
	{
		_Message(_Log_warning,text);
	}

	static inline void info(const std::string& text)
	{
		_Message(_Log_info,text);
	}

	template<typename _Type>
	static inline void error(const std::string& text, const _Type& value)
	{
		_Message(_Log_error,text, value);
	}

	template<typename _Type>
	static inline void warning(const std::string& text, const _Type& value)
	{
		_Message(_Log_warning,text, value);
	}

	template<typename _Type>
	static inline void info(const std::string& text, const _Type& value)
	{
		_Message(_Log_info,text, value);
	}

#else
	static inline void error(const std::string& text) {}

	static inline void warning(const std::string& text) {}

	static inline void info(const std::string& text) {}

	template<typename _Type>
	static inline void error(const std::string& text, _Type value) {}

	template<typename _Type>
	static inline void warning(const std::string& text, _Type value) {}

	template<typename _Type>
	static inline void info(const std::string& text, _Type value) {}

#endif

private:
	logger()
	{
		_Is_active = true;
	}
	~logger()
	{
		_Is_active = false;
		if(_MyFile)
		{
			_MyFile->close();
			delete _MyFile;
		}
	}

	std::ofstream* _MyFile;
	bool _Is_active;
	
	inline static logger& _Get_instance()
	{
		static logger _MyInstance;
		return _MyInstance;
	}

	inline static void _Message(_Log_type type, const ::std::string& text)
	{
		logger& _Instance = _Get_instance();

		if(!_Instance._Is_active)
		{
			_Slow_append_message(type, text);
			return;
		}
		else if(!_Instance._MyFile)
		{
			_Open_file();
			if(!_Instance._MyFile)
			{
				return;
			}
		}

		std::stringstream str;

		switch(type)
		{
		case _Log_info:
			str << "< INFO>: ";
			break;
		case _Log_warning:
			str << "< WARN>: ";
			break;
		case _Log_error:
			str << "<ERROR>: ";
			break;
		}

		str << text;

		std::string res;

		getline(str, res);

		res.push_back('\n');

		(*_Instance._MyFile) << res << ::std::flush;
		std::cout << res;
	}

	template<typename _Type>
	inline static void _Message(_Log_type type, const ::std::string& text, const _Type& value)
	{
		logger& _Instance = _Get_instance();

		if(!_Instance._Is_active)
		{
			_Slow_append_message(type, text, value);
			return;
		}
		else if(!_Instance._MyFile)
		{
			_Open_file();
			if(!_Instance._MyFile)
			{
				return;
			}
		}

		std::stringstream str;


		switch(type)
		{
		case _Log_info:
			str << "< INFO>: ";
			break;
		case _Log_warning:
			str << "< WARN>: ";
			break;
		case _Log_error:
			str << "<ERROR>: ";
			break;
		}

		str << text << ": " << value;

		std::string res;

		getline(str, res);

		res.push_back('\n');

		(*_Instance._MyFile) << res << ::std::flush;
		std::cout << res;
	}

	template<typename _Type>
	inline static void _Slow_append_message(_Log_type type, const std::string& text, const _Type& value)
	{
		std::ofstream _Out_file;
		_Open_file_append(_Out_file);

		std::stringstream str;
		switch(type)
		{
		case _Log_info:
			str << "< INFO>: ";
			break;
		case _Log_warning:
			str << "< WARN>: ";
			break;
		case _Log_error:
			str << "<ERROR>: ";
			break;
		}

		str << text << ": " << value;

		std::string res;

		getline(str, res);

		res.push_back('\n');

		_Out_file << res << ::std::flush;
		::std::cout << res;
	}

	inline static void _Slow_append_message(_Log_type type, const std::string& text)
	{
		std::ofstream _Out_file;
		_Open_file_append(_Out_file);

		std::stringstream str;

		switch(type)
		{
		case _Log_info:
			str << "< INFO>: ";
			break;
		case _Log_warning:
			str << "< WARN>: ";
			break;
		case _Log_error:
			str << "<ERROR>: ";
			break;
		}

		str << text;

		std::string res;

		getline(str, res);

		res.push_back('\n');

		_Out_file << res << ::std::flush;
		::std::cout << res;
	}

	static void _Open_file();
	static void _Open_file_append(std::ofstream&);
};

};