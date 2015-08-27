#include <iostream>

using namespace std;

void run(auto f, auto v) {
	cout << f(v) << endl;
}

int main()
{
	int a, b;
	a = 1; b = 3;
	
	//Super duper automatic
	auto f1 = [&b](auto v) {
		return v*b;
	};

	//More restrict
	auto f2 = [&b](auto v) -> decltype(v*b) {
		return v*b;
	};
	
	//very restrict
	auto f3 = [&b](int v) -> int {
		return v*b;
	};
	
	auto f4 = [a, &b](int v) -> int {
		return v*b+a;
	};
	
	run(f1, 2);
	run(f2, 2);
	run(f3, 2);
	
	return 0;
}
