//Sample provided by Fabio Galuppo
//January 2016
//http://www.simplycpp.com

//compile with clang++:
//clang++ -Wall -O2 -std=c++14 -o understanding_inference_program.exe understanding_inference_program.cpp

//compile g++:
//g++ -Wall -O2 -std=c++14 -o understanding_inference_program.exe understanding_inference_program.cpp

//compile msvc:
//cl.exe /Wall /EHsc /Ox understanding_inference_program.cpp /link /out:understanding_inference_program.exe

#include <string>

inline std::string operator*(std::string s1, std::string s2)
{
    return s1 + s2;
}

template <typename T>
struct f_pair { T x; T y; };

template <typename T>
inline f_pair<T> make_square_pair(T x)
{
    return f_pair<T>{ x, x * x };
}

template <typename T>
inline T get_y(const f_pair<T>& p)
{
    return p.y;
}

#include <iostream>
#include <typeinfo>

template <typename T>
void display(T x)
{
    T y = get_y(make_square_pair(x));
    std::cout << y << " -> "<< (typeid(y).name()) << "\n";
}

#include <unordered_map>

template <typename TKey, typename TValue>
inline std::unordered_map<TKey, TValue> make_dic(typename std::unordered_map<TKey, TValue>::size_type capacity)
{
    return std::unordered_map<TKey, TValue>(capacity);
}

#include <random>
#include <functional>

inline const std::string generate_ascii_random_string(std::string::size_type n)
{
    static std::default_random_engine generator;
    static std::uniform_int_distribution<short> distribution(0x20, 0x7A); //ascii range for space to z
    static auto rnd = std::bind(distribution, generator);
    std::string s;
    s.resize(n);
    for (auto& ch : s)
        ch = static_cast<char>(rnd());
    return s;
}

void understanding_inference_run()
{
    //limited inference with templates
    display(2);
    display(2.71828);
    display(std::string("..."));
    
    //auto type deduction
    int x = 2;
    double e = 2.71828;
    std::string s = "Simply C++";
    std::cout << x << " -> "<< typeid(x).name() << "\n";
    std::cout << e << " -> "<< typeid(e).name() << "\n";
    std::cout << s << " -> "<< typeid(s).name() << "\n";
    
    auto x_ = x;
    auto e_ = e;
    auto s_ = s;
    std::cout << x_ << " -> "<< typeid(x_).name() << "\n";
    std::cout << e_ << " -> "<< typeid(e_).name() << "\n";
    std::cout << s_ << " -> "<< typeid(s_).name() << "\n";
    
    const int y = 4;
    auto y1 = y; //y1 is int, not const int
    std::cout << y1 << "\n";
    y1 = 16;
    std::cout << y1 << "\n";
    const auto y2 = y; //const int
    std::cout << y2 << "\n";
    //y2 = 16; //compilation will fail, because y2 is read-only
    
    //Type deduction with auto drops const and reference attributes,
    //you can qualify auto with const, reference, or both
    
    int z = 4;
    int& w = z;
    auto w1 = z; //int
    std::cout << z << " " << w << " " << w1 << "\n";
    w = 16;
    std::cout << z << " " << w << " " << w1 << "\n";
    w1 = 256;
    std::cout << z << " " << w << " " << w1 << "\n";
    auto& w2 = z; //int&
    w2 = 65536;
    std::cout << z << " " << w << " " << w2 << "\n";
    
    const auto& v = y;
    std::cout << v << "\n";
    
    auto dic = make_dic<std::string, std::string>(1024);
    //better than:
    //std::unordered_map<std::string, std::string> dic = make_dic<std::string, std::string>(1024);
    std::cout << (typeid(dic).name()) << "\n";
    
    //type deduction with decltype(expression)
    decltype(z) u = 4;
    decltype(w) t = u;
    std::cout << u << " " << t << "\n";
    t = 16;
    std::cout << u << " " << t << "\n";
    
    //Type deduction with decltype keeps const and reference attributes
    
    decltype(e + e) a1 = e + e; //decltype with expression
    std::cout << a1 << "\n";
    decltype(make_square_pair(10)) a2 = make_square_pair(10);
    std::cout << get_y(a2) <<  " -> "<< typeid(a2).name() << "\n";
    
    //type deduction with decltype(auto)
    decltype(auto) a3 = (e + e + e + e + e);
    std::cout << a3 << "\n";
    
    decltype(auto) a4 = generate_ascii_random_string(8);
    std::cout << a4 << "\n";
    decltype(auto) a5 = generate_ascii_random_string(8);
    std::cout << a5 << "\n";
    //a4 = a5; //compilation will fail, because a4 is read-only
}

int main()
{
    understanding_inference_run();
    return 0;
}
