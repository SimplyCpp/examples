//Sample provided by Fabio Galuppo 
//October 2016
//http://www.simplycpp.com 

//compile clang++: (Apple LLVM version 8.0.0 (clang-800.0.38))
//clang++ -Wall -O2 -std=c++14 -o program.exe program.cpp sample1.cpp sample2.cpp sample3.cpp

//compile g++: (g++ (GCC) 5.3.0)
//g++ -Wall -O2 -std=c++14 -o program.exe program.cpp sample1.cpp sample2.cpp sample3.cpp

//compile msvc: (Visual C++ 2015 Update 3 - Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24215.1)
//cl.exe /EHsc /Ox /std:c++14 program.cpp sample1.cpp sample2.cpp sample3.cpp /link /out:program.exe

#include "sample1.hpp"
#include "sample2.hpp"
#include "sample3.hpp"

int main()
{
	sample1_main();
	sample2_main();
	sample3_main();

	return 0;
}