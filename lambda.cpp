#include <iostream>

using namespace std;

void run(auto f, auto v) {
	cout << f(v) << endl;
}

template<typename T>
class F {
	T b;
public:
	F(T &b) {
		this->b = b;
	}
	auto operator()(T v) {
		return v*b;		
	}
};

int main()
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
