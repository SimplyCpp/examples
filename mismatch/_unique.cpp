//Sample provided by Fabio Galuppo
//December 2015
//http://www.simplycpp.com

//compile clang++:
//clang++ -Wall -O2 -std=c++11 -o _unique.exe _unique.cpp

//compile g++:
//g++ -Wall -O2 -std=c++11 -o _unique.exe _unique.cpp

//compile msvc:
//cl.exe /Wall /EHsc /Ox _unique.cpp /link /out:_unique.exe

#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

void unique(std::vector<std::string>&& ss)
{
    ss.resize(std::distance(ss.begin(),
                            std::unique(ss.begin(), ss.end())));
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
            unique(read_all_lines(ifs));
        }
        ifs.close();
    }
    else
    {
        unique(read_all_lines(std::cin));
    }
}