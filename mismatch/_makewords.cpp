//Sample provided by Fabio Galuppo
//December 2015
//http://www.simplycpp.com

//compile clang++:
//clang++ -Wall -O2 -std=c++11 -o _makewords.exe _makewords.cpp

//compile g++:
//g++ -Wall -O2 -std=c++11 -o _makewords.exe _makewords.cpp

//compile msvc:
//cl.exe /Wall /EHsc /Ox _makewords.cpp /link /out:_makewords.exe

#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

std::string read_all_text(std::istream& istr)
{
	std::string temp, buffer;
	while (std::getline(istr, buffer))
	{
		temp += buffer;
		temp += '\n';
	}
	return std::move(temp);
}

inline bool is_ascii_upper(char ch) { return 'A' <= ch && ch <= 'Z'; }

inline bool is_ascii_lower(char ch) { return 'a' <= ch && ch <= 'z'; }

void makewords(std::string&& s)
{
	std::string buffer;
	for (char ch : s)
	{
		if (is_ascii_lower(ch) || is_ascii_upper(ch))
		{
			buffer += ch;
		}
		else if (!buffer.empty())
		{
			std::cout << buffer << "\n";
            buffer.clear();
		}
	}
}

int main(int argc, char* argv[])
{
    if (argc >= 2)
	{
		std::ifstream ifs;
		ifs.open(argv[1], std::ifstream::in);
		if (ifs.is_open())
		{
			makewords(read_all_text(ifs));
		}
		ifs.close();
	}
	else
	{
        makewords(read_all_text(std::cin));
	}
}