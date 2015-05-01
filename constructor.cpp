//Sample provided by Thiago Massari Guedes
//April 2015
//http://www.simplycpp.com/

#ifdef __EXAMPLE_PKG__
#define EXAMPLE_MAIN(ex_name) int run_##ex_name ()
#else
#define EXAMPLE_MAIN(ex_name) int main(int argc, char *argv[])
#endif


#include <iostream>
#include <vector>

using namespace std;

template<typename T = int>
class TestCopy {
public:

	T val;

	TestCopy() {
		cout << "[CONSTR 1]" << endl;
		this->val = 0;
	}

	TestCopy(T val) {
		cout << "[CONSTR 2:" << val << "]" << endl;
		this->val = val;
	}

	TestCopy(const TestCopy &src) {
		cout << "[COPY]" << endl;
		this->val = src.val;
	}

	TestCopy(TestCopy &&src) {
		cout << "[MOVE]" << endl;
		this->val = std::move(src.val);
	}

	TestCopy &operator =(const TestCopy &src) {
		cout << "[OP=" << src.val << "]" << endl;
		this->val = src.val;
	}

	void ts() {
		cout << val << "===============" << endl;
	}

};

EXAMPLE_MAIN(constructor)
{

	TestCopy<> t1;
	TestCopy<> t2 {1};
	TestCopy<> t3 = t2;
	TestCopy<> t4 {t2};
	TestCopy<> t5 = TestCopy<>{5};
	TestCopy<> t6 = {6};
	TestCopy<> t7 = 7;

	t5.ts();
	t1 = t3;
	t1.ts();
	t1 = TestCopy<>{3};

	t3.ts();

	vector<TestCopy<>> tm;
	tm.push_back(TestCopy<>(99));
	tm[0].ts();

}
