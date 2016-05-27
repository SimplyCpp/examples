//Sample provided by Fabio Galuppo
//May 2016
//http://www.simplycpp.com

//compile msvc:
//cl.exe /EHsc /Ox /DUNICODE username_sample.cpp /link /out:username_sample.exe

#include "support.hpp"

#include <windows.h>
#include <string>
#include <vector>
#include <iostream>

std::wstring username()
{
	wchar_t buffer[64];
	DWORD size = sizeof(buffer) / sizeof(buffer[0]);
	if (GetUserName(buffer, &size))
		return buffer; //converted implicitly to std::wstring
	throw std::runtime_error("GetUserName failed");
}

std::wstring username2()
{
	std::wstring buffer;
	buffer.resize(64);
	DWORD size = buffer.size();
	wchar_t* buffer_ptr = const_cast<wchar_t*>(buffer.c_str());
	if (GetUserName(buffer_ptr, &size))
		return buffer;
	throw std::runtime_error("GetUserName failed");
}

std::wstring username3()
{
	std::wstring buffer;
	buffer.resize(64);
	DWORD size = buffer.size();
	wchar_t* buffer_ptr = const_cast<wchar_t*>(buffer.c_str());
	if (GetUserName(buffer_ptr, &size))
	{
		--size; //The second argument of GetUserName computes the '\0'
		buffer.resize(size); //The (w)string resize performs the actual size + 1 
		return buffer;
	}
	throw std::runtime_error("GetUserName failed");
}

int main()
{
	for (const std::wstring& s : { username(), username2(), username3() })
	{
		std::wcout << s << "\n";
		std::cout << hex_rep(buffer_to_transmit(s)) << "\n";
	}
	
	return 0;
}