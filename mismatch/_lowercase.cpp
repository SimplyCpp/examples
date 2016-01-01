//Sample provided by Fabio Galuppo
//December 2015
//http://www.simplycpp.com

//compile clang++:
//clang++ -Wall -O2 -std=c++11 -o _unique.exe _unique.cpp

//compile g++:
//g++ -Wall -O2 -std=c++11 -o _unique.exe _unique.cpp

//compile msvc:
//cl.exe /Wall /EHsc /Ox _lowercase.cpp /link /out:_lowercase.exe

#include <istream>
#include <fstream>
#include <iostream>
#include <string>

inline bool is_ascii_upper(char ch) { return 'A' <= ch && ch <= 'Z'; }

void lowercase(std::istream& istr)
{
	std::string s;
    while (std::getline(istr, s, '\n'))
	{
        for (char& ch : s)
		{
			if (is_ascii_upper(ch))
			{
                ch = ch - 'A' + 'a';
			}
		}
        std::cout << s << "\n";
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
			lowercase(ifs);
		}
		ifs.close();
	}
	else
	{
        lowercase(std::cin);
	}
}