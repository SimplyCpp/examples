//Sample provided by Fabio Galuppo
//May 2016
//http://www.simplycpp.com

//compile clang++:
//clang++ -Wall -O2 -std=c++11 -o timestamp_sample.exe timestamp_sample.cpp

//compile g++:
//g++ -Wall -O2 -std=c++11 -o timestamp_sample.exe timestamp_sample.cpp

//compile msvc:
//cl.exe /EHsc /Ox /DUNICODE timestamp_sample.cpp /link /out:timestamp_sample.exe

#include "support.hpp"

#include <time.h>
#include <string>
#include <cstring>

std::string timestamp()
{
	time_t now = time(nullptr);
	tm* t = localtime(&now);
	if (nullptr == t)
		throw std::runtime_error("localtime failed");
	char buffer[64];
	if (0 == strftime(buffer, sizeof(buffer), "%Y-%m-%d %T", t))
		throw std::runtime_error("strftime failed");
	return buffer; //converted implicitly to std::string
}

std::string timestamp2()
{
	time_t now = time(nullptr);
	tm* t = localtime(&now);
	if (nullptr == t)
		throw std::runtime_error("localtime failed");
	std::string buffer(64, ' ');
	char* buffer_ptr = const_cast<char*>(buffer.c_str());
	if (0 == strftime(buffer_ptr, buffer.size(), "%Y-%m-%d %T", t))
		throw std::runtime_error("strftime failed");
	return buffer; //converted implicitly to std::string
}

std::string timestamp3()
{
	time_t now = time(nullptr);
	tm* t = localtime(&now);
	if (nullptr == t)
		throw std::runtime_error("localtime failed");
	std::string buffer(64, ' ');
	char* buffer_ptr = const_cast<char*>(buffer.c_str());
	if (0 == strftime(buffer_ptr, buffer.size(), "%Y-%m-%d %T", t))
		throw std::runtime_error("strftime failed");
	std::string temp(buffer_ptr, std::strlen(buffer_ptr)); //converted explicitly to std::string using ptr and len
	return temp;
}

int main()
{
	for (const std::string& s : { timestamp(), timestamp2(), timestamp3() })
	{
		std::cout << s << "\n";
		std::cout << hex_rep(buffer_to_transmit(s)) << "\n";
	}

	return 0;
}