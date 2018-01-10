//Sample provided by Fabio Galuppo
//January 2018
//http://www.simplycpp.com

//compile clang++:
//clang++ -Wall -O2 -std=c++14 -o handy_union.t.exe handy_union.t.cpp

//compile g++:
//g++ -Wall -O2 -std=c++14 -o handy_union.t.exe handy_union.t.cpp

//compile msvc:
//cl.exe /EHsc /Ox /std:c++14 handy_union.t.cpp /link /out:handy_union.t.exe

#include "handy_union.hpp"
#include <iostream>
#include <algorithm>

int test4()
{
	//little endian to big endian (or vice-versa depending on running)
	//https://www.cs.umd.edu/class/sum2003/cmsc311/Notes/Data/endian.html
	handy_union<unsigned int> x;
	x.value = 0x90AB12CD;	
	
	//if the last byte from value is the first item in bytes then is little endian
	bool is_little_endian = x.bytes[0] == 0xCD; 

	std::cout.setf(std::ios::hex, std::ios::basefield);

	std::cout << (is_little_endian ? "little" : "   big") << " endian: ";
	for (size_t i = 0; i < x.size(); ++i)
		std::cout << static_cast<int>(x.bytes[i]) << " ";
	std::cout << "\n";

	//changing endianness
	is_little_endian = !is_little_endian;
	std::reverse(x.bytes, x.bytes + x.size());

	std::cout << (is_little_endian ? "little" : "   big") << " endian: ";
	for (size_t i = 0; i < x.size(); ++i)
		std::cout << static_cast<int>(x.bytes[i]) << " ";
	std::cout << "\n";
	
	std::cout.unsetf(std::ios::hex);

	return 0;
}

int test3()
{
	handy_union<unsigned int> x;
	std::fill(x.bytes, x.bytes + x.size(), 0);
	x.bytes[0] = 1;
	return x == 1 ? 0 : -1;
}

int test2()
{
	handy_union<unsigned int> x(0xFFEEDDCC);
	std::reverse(x.bytes, x.bytes + x.size());
	return x == 0xCCDDEEFF ? 0 : -1;
}

int test1()
{
	handy_union<unsigned int> x(0xFFEEDDCC);
	return (x.bytes[3] == 0xFF) &&
		   (x.bytes[2] == 0xEE) &&
		   (x.bytes[1] == 0xDD) &&
		   (x.bytes[0] == 0xCC) ? 0 : -1;
}

void assert_test(int value, int expected = 0)
{
	static int counter = 0;
	std::cout << "Test #" << (++counter) << (value == expected ? " SUCCEEDED\n" : " FAILED\n");
	std::cout << "------------------------------------------\n";
}

int main()
{
	assert_test(test1());
	assert_test(test2());
	assert_test(test3());
	assert_test(test4());

	return 0;
}