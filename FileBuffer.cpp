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

#include "precomp.h"

#include "FileBuffer.h"
#include "Texture.h"

using namespace ADAM;

FileBuffer::FileBuffer()
	: m_FileSize(0)
{
}

FileBuffer::~FileBuffer()
{
	//CHECK_IF(m_InfilePtr && m_InfilePtr != GetEndPtr(), "end of file not reached");
}

bool FileBuffer::ReadFromFile(const char* file)
{
	m_File.open(file, std::ios::in | std::ios::binary);

	if(m_File.fail())
	{
		return false;
	}

	m_File.seekg(0, std::ios::end);
	m_FileSize = m_File.tellg();
	m_File.seekg(0);

	return true;
}

bool FileBuffer::WriteToFile(const char* file)
{
	m_File.open(file, std::ios::out | std::ios::binary);
	//std::ofstream outfile(file, std::ios::binary);

	if(m_File.fail())
	{
		return false;
	}

	return true;
}

void FileBuffer::Reset()
{
	m_File.seekg(0);
}

void FileBuffer::AdvanceCurrentPtr(uint64_t count)
{
	m_File.seekg((std::streamoff)m_File.tellg() + count);
}

uint64_t FileBuffer::GetFileSize() const
{
	return m_FileSize;
}


void FileBuffer::AddMemory(const void* mem_block, size_t mem_size)
{
	m_File.write((const char*)mem_block, mem_size);
}

void FileBuffer::AddString(const std::string& str)
{
	uint str_size = (uint)str.size();
	AddInt(str_size);

	if(str_size)
	{
		AddMemory(str.data(), str_size);
	}
}

void FileBuffer::AddString(const char* str)
{
	uint str_size = (uint)strlen(str);
	AddInt(str_size);

	if(str_size)
	{
		AddMemory(str, str_size);
	}
}

void FileBuffer::AddFloat(const float& val)
{
	AddData(val);
}

void FileBuffer::AddInt(const uint& val)
{
	AddData(val);
}

void FileBuffer::GetMemory(void* mem_block, size_t mem_size)
{
	m_File.read((char*)mem_block, mem_size);
}

string FileBuffer::GetString()
{
	uint str_size = GetInt();

	string retval(str_size, 0);

	if(str_size)
	{
		m_File.read(&retval[0], str_size);
	}

	return retval;
}

float FileBuffer::GetFloat()
{
	float retval;
	GetData(retval);
	return retval;
}

uint FileBuffer::GetInt()
{
	uint retval;
	GetData(retval);
	return retval;
}