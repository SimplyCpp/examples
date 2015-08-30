//Sample provided by Thiago Massari Guedes
//August 2015
//http://www.simplycpp.com/

#include "example_main.h"

#include <iostream>

using namespace std;

//void run(auto f, auto v) {
template<typename F, typename T>
void run(F f, T v) {
	cout << f(v) << endl;
}

template<typename T>
class F {
	T &_b;
public:
	F(T &b) : _b(b) { }
	auto operator()(T v) {
		return v * _b;		
	}
};

EXAMPLE_MAIN(lambda)
{
	int a, b;
	a = 1; b = 3;
	
	auto f = [&b](auto v) {
		return v*b;
	};
	
	F<int> fc(b);
	
	run(f, 2);
	run(fc, 2);
	
	//rg - end - cpf
	
	return 0;
}
