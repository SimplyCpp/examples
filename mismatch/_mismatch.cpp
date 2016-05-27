//Sample provided by Fabio Galuppo
//December 2015
//http://www.simplycpp.com

//compile clang++:
//clang++ -Wall -O2 -std=c++11 -o _mismatch.exe _mismatch.cpp

//compile g++:
//g++ -Wall -O2 -std=c++11 -o _mismatch.exe _mismatch.cpp

//compile msvc:
//cl.exe /Wall /EHsc /Ox _mismatch.cpp /link /out:_mismatch.exe

//run on Windows as example - requires (_makewords, _lowercase, _sort, _unique):
//_makewords .\tests\alice.txt | _lowercase | _sort | _unique | _mismatch .\tests\words.txt

#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <utility>

void mismatch(const char* dic_path, std::istream& istr)
{
    std::unordered_set<std::string> dic;
    
    std::ifstream ifs;
    ifs.open(dic_path, std::ifstream::in);
    if (ifs.is_open())
    {
        std::string buffer;
        while (std::getline(ifs, buffer))
        {
            dic.emplace(std::move(buffer));
        }
    }
    ifs.close();

    if (!dic.empty())
    {
        std::string s;
        while (std::getline(istr, s))
        {
            if (dic.find(s) == dic.end())
            {
                std::cout << s << std::endl;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc >= 3)
    {
        std::ifstream ifs;
        ifs.open(argv[2], std::ifstream::in);
        if (ifs.is_open())
        {
            mismatch(argv[1], ifs);
        }
        ifs.close();
    }
    else if (argc == 2)
    {
        mismatch(argv[1], std::cin);
    }
    else
    {
        std::cerr << "Dictionary is missing\n";
    }
}