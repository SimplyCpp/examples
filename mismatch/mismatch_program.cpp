//Sample provided by Fabio Galuppo
//December 2015
//http://www.simplycpp.com

//compile with clang++:
//clang++ -Wall -O2 -std=c++11 -o mismatch_program.exe mismatch_program.cpp

//compile g++:
//g++ -Wall -O2 -std=c++11 -o mismatch_program.exe mismatch_program.cpp

//compile msvc:
//cl.exe /Wall /EHsc /Ox mismatch_program.cpp /link /out:mismatch_program.exe

//Pipeline representation:
//makewords sentence | lowercase | sort | unique | mismatch dictionary

//run on Windows as example:
//mismatch_program .\tests\words.txt .\tests\alice.txt

#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
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

std::vector<std::string> makewords(std::string&& s)
{
    std::vector<std::string> temp;
    std::string buffer;
    for (char ch : s)
    {
        if (is_ascii_lower(ch) || is_ascii_upper(ch))
        {
            buffer += ch;
        }
        else if (!buffer.empty())
        {
            temp.emplace_back(std::move(buffer));
        }
    }
    return std::move(temp);
}

std::vector<std::string> lowercase(std::vector<std::string>&& ss)
{
    for (auto& s : ss)
    {
        for (char& ch : s)
        {
            if (is_ascii_upper(ch))
            {
                ch = ch - 'A' + 'a';
            }
        }
    }
    return std::move(ss);
    
    /*
    std::for_each(ss.begin(), ss.end(), 
        [](std::string& s) {
            std::transform(s.begin(), s.end(), s.begin(),
                [](char ch){ return ('A' <= ch && ch <= 'Z') ? (ch - 'A' + 'a') : ch; });
        });
    return std::move(ss);
    */
}

std::vector<std::string> sort(std::vector<std::string>&& ss)
{
    std::sort(ss.begin(), ss.end());
    return std::move(ss);
}

std::vector<std::string> unique(std::vector<std::string>&& ss)
{
    ss.resize(std::distance(ss.begin(),
                            std::unique(ss.begin(), ss.end())));
    return std::move(ss);
}

std::vector<std::string> mismatch(const char* dic_path, std::vector<std::string>&& ss)
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

    if (!dic.empty())
    {
        auto erase_point = std::remove_if(ss.begin(), ss.end(),
                                          [&dic](std::string& s){ return dic.find(s) != dic.end(); });
        ss.erase(erase_point, ss.end());
    }

    return std::move(ss);
}

void run(const char* dic_path, std::istream& is)
{
    for (auto x : mismatch(dic_path, unique(sort(lowercase(makewords(read_all_text(is)))))))
        std::cout << x << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc >= 3)
    {
        std::ifstream ifs;
        ifs.open(argv[2], std::ifstream::in);
        if (ifs.is_open())
        {
            run(argv[1], ifs);
        }
        ifs.close();
    }
    else if (argc == 2)
    {
        run(argv[1], std::cin);
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " dictionary.txt text.txt\n";
        std::cout << "\tExample: " << argv[0] << " words.txt alice.txt\n";
    }
}