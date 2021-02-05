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

namespace ADAM {

template<typename T>
struct IsAContainer : public std::false_type {};
template<typename T>
struct IsAContainer<std::vector<T>> : public std::true_type {};
template<>
struct IsAContainer<std::string> : public std::true_type {};

class FileBuffer
{
public:
	FileBuffer();
	~FileBuffer();

	bool ReadFromFile(const char* file);
	bool WriteToFile(const char* file);

	void Reset();

	void AdvanceCurrentPtr(uint64 count);
	uint64 GetFileSize() const;

	void AddMemory(const void* mem_block, size_t mem_size);
	void AddString(const std::string& str);
	void AddString(const char* str);
	void AddFloat(const float& val);
	void AddInt(const uint& val);

	void GetMemory(void* mem_block, size_t mem_size);
	string GetString();
	float GetFloat();
	uint GetInt();

public:
	// templated stuff

	template<typename Type>
	void GetData(Type& out_obj)
	{
		GetDataImpl(out_obj, typename IsAContainer<Type>::type());
	}

	template<typename Type>
	void AddData(const Type& obj)
	{
		AddDataImpl(obj, typename IsAContainer<Type>::type());
	}

private:

	template<typename Type>
	void GetDataImpl(Type& out_container, std::true_type)
	{
		GetMemory(out_container.data(), out_container.size() * sizeof(Type::value_type));
	}

	template<typename Type>
	void GetDataImpl(Type& out_obj, std::false_type)
	{
		static_assert(!std::is_pointer<Type>::value, "T may not be a pointer");
		GetMemory(&out_obj, sizeof(Type));
	}

	template<typename Type>
	void AddDataImpl(const Type& container, std::true_type)
	{
		AddMemory(container.data(), container.size() * sizeof(Type::value_type));
	}

	template<typename Type>
	void AddDataImpl(const Type& obj, std::false_type)
	{
		static_assert(std::is_pod<Type>::value, "T is not plain old data");
		static_assert(!std::is_pointer<Type>::value, "T may not be a pointer");
		AddMemory(&obj, sizeof(Type));
	}

private:
	std::fstream m_File;
	uint64 m_FileSize;
};

};