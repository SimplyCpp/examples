//Sample provided by Fabio Galuppo
//December 2015
//http://www.simplycpp.com

//compile clang++:
//clang++ -Wall -O2 -std=c++11 -o _sort.exe _sort.cpp

//compile g++:
//g++ -Wall -O2 -std=c++11 -o _sort.exe _sort.cpp

//compile msvc:
//cl.exe /Wall /EHsc /Ox _sort.cpp /link /out:_sort.exe

#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

void sort(std::vector<std::string>&& ss)
{
	std::sort(ss.begin(), ss.end());
    for (auto& s : ss) std::cout << s << "\n";
}

std::vector<std::string> read_all_lines(std::istream& istr)
{
	std::vector<std::string> temp;
    std::string buffer;
	while (std::getline(istr, buffer, '\n'))
	{
		temp.emplace_back(std::move(buffer));
	}
	return std::move(temp);
}

int main(int argc, char* argv[])
{
    if (argc >= 2)
	{
		std::ifstream ifs;
		ifs.open(argv[1], std::ifstream::in);
		if (ifs.is_open())
		{
			sort(read_all_lines(ifs));
		}
		ifs.close();
	}
	else
	{
        sort(read_all_lines(std::cin));
	}
}