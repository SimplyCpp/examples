//Sample provided by Thiago Massari Guedes
//April 2015
//http://www.simplycpp.com/

#ifdef __EXAMPLE_PKG__
#define EXAMPLE_MAIN(ex_name) int run_##ex_name ()
#else
#define EXAMPLE_MAIN(ex_name) int main(int argc, char *argv[])
#endif

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//Generico. Sem tipos declarados
#define FILL(v, i, start, end, step) { \
	for(i=start; i < end; i+=step) \
		v.push_back(i); \
}

//Repare que aqui eu preciso ter operador []
#define DUMP(v) { \
	for(int i=0; i < v.size(); i++) \
		cout << v[i] << " "; \
	cout << endl; \
}

#define INCREMENT(v, n) { \
	for(int i=0; i < v.size(); i++) \
		v[i] += n; \
}

#define ACCUM(v, ret) { \
	for(int i=0; i < v.size(); i++) \
		ret += v[i]; \
}

void run_macro() {
	vector<int> numbers;
	int i;
	FILL(numbers, i, 0, 20, 2);
	DUMP(numbers);
	INCREMENT(numbers, 1);
	DUMP(numbers);
	int total=0;
	ACCUM(numbers, total);
	cout << "sum: " << total << endl;
}

template<typename T, typename U>
void fill(T &t, U start, U end, U step) {
	for(U i=start; i < end; i += step) {
		t.push_back(i);
	}
}

template<typename T>
void dump(T &t) {
	for(const auto &it : t) {
		cout << it << " ";
	}
	cout << endl;
}

template<typename T, typename U>
void increment(T &t, const U &val) {
	for(auto &item : t) {
		item += val;
	}
}

template<typename RET, typename T>
RET accum(T &t) {
	RET ret{};
	for(auto &item : t) {
		ret += item;
	}
	return ret;
}


void run_templ() {
	vector<int> numbers;
	fill(numbers, 0, 20, 2);
	dump(numbers);
	increment(numbers, 1);
	dump(numbers);
	
	int total = accum<int>(numbers);
	cout << "sum: " << total << endl;
}

template<typename T, typename U>
void fill2(T &v, U start, U step) {
	generate(begin(v), end(v), [&start, &step]() { auto r = start; start += step; return r; }); 
}


template<typename T>
void dump2(T &v) {
	for_each(begin(v), end(v), [](auto &n) { cout << n << " "; });
	cout << endl;
}

template<typename T, typename U>
void increment2(T &v, const U &val) {
	for_each(begin(v), end(v), [&val](U &n) { n += val; });
}

template<typename RET, typename T>
RET accum2(T &v) {
	RET ret{};

	//auto inside lamba, only in c++14
	for_each(begin(v), end(v), [&ret](auto &val) { ret += val; });
	return ret;
}

void run_templ_stl() {
	vector<int> numbers(10);
	
	fill2(numbers, 0, 2);
	dump2(numbers);
	increment2(numbers, 1);
	dump2(numbers);
	
	int total = accum2<int>(numbers);
	cout << "sum: " << total << endl;	
}

EXAMPLE_MAIN(macro_templ) {

	run_macro();     //C-style
	run_templ();     //C++-style without stl
	run_templ_stl(); //C++-style with stl

	return 0;

}
