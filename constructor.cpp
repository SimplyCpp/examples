#include <iostream>
#include <vector>

using namespace std;

template<typename T = int>
class TesteCopy {
public:

    T val;

    TesteCopy() {
        cout << "[CONSTR 1]" << endl;
        this->val = 0;
    }

    TesteCopy(T val) {
        cout << "[CONSTR 2:" << val << "]" << endl;
        this->val = val;
    }

    TesteCopy(const TesteCopy &src) {
        cout << "[COPY]" << endl;
        this->val = src.val;
    }

    TesteCopy(TesteCopy &&src) {
        cout << "[MOVE]" << endl;
        this->val = std::move(src.val);
    }

    TesteCopy &operator =(const TesteCopy &src) {
        cout << "[OP=" << src.val << "]" << endl;
        this->val = src.val;
    }

    void ts() {
        cout << val << "===============" << endl;
    }

};

void runConstr() {

	TesteCopy<> t1;
	TesteCopy<> t2 {1};
	TesteCopy<> t3 = t2;
	TesteCopy<> t4 {t2};
	TesteCopy<> t5 = TesteCopy<>{5};
	TesteCopy<> t6 = {6};
	TesteCopy<> t7 = 7;
	
	t5.ts();
	t1 = t3;
	t1.ts();
	t1 = TesteCopy<>{3};

	t3.ts();

	vector<TesteCopy<>> tm;
    tm.push_back(TesteCopy<>(99));
    tm[0].ts();
	
}
