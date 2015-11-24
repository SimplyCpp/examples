//Sample provided by Fabio Galuppo
//November 2015
//http://www.simplycpp.com

//compile with clang++:
//clang++ -Wall -O2 -std=c++11 -o understanding_accumulate_program.exe understanding_accumulate_program.cpp

//compile g++:
//g++ -Wall -O2 -std=c++11 -o understanding_accumulate_program.exe understanding_accumulate_program.cpp

//compile msvc:
//cl.exe /Wall /EHsc /Ox understanding_accumulate_program.cpp /link /out:understanding_accumulate_program.exe

#include <numeric>
#include <functional>
#include <iterator>
#include <array>
#include <vector>
#include <string>

template<typename T>
struct accumulator_with_predicate final
{
	using UnaryPredicate = std::function<bool(T)>;
	
	explicit accumulator_with_predicate(T init, UnaryPredicate pred)
		: acc(init), pred(pred) {}

	accumulator_with_predicate& operator+(const T& val)
	{
		acc += pred(val) ? val : T{};
		return *this;
	}

	operator T() const { return acc; }

	accumulator_with_predicate() = delete; //default-constructible	
	accumulator_with_predicate(const accumulator_with_predicate&) = default; //copy-constructible
	accumulator_with_predicate& operator=(const accumulator_with_predicate&) = default; //copy-assignable
	~accumulator_with_predicate() = default; //destructor

private:
	T acc;	
	UnaryPredicate pred;
};

//sum
template<class InputIterator>
inline typename InputIterator::value_type sum(InputIterator first, InputIterator last)
{
    typename InputIterator::value_type init{};
	return std::accumulate(first, last, init);
}

template<class Container>
inline typename Container::value_type sum(const Container& cont)
{
	typename Container::value_type init{};
	return std::accumulate(std::begin(cont), std::end(cont), init);
}

//fold/left fold
template<class InputIterator, typename T, class Function>
T fold(InputIterator first, InputIterator last, T init, Function f) 
{
	T acc{ init };
	while (first != last)
	{
		acc = f(acc, *first);
		++first;
	}
	return acc;
}
 
//arithmetic progression (AP) or arithmetic sequence
template<class InputIterator, typename T>
void fill_ap(InputIterator first, InputIterator last, T first_term, T common_difference)
{
	T n{};
	while (first != last)
	{
		*first = first_term + n * common_difference;
		++n;
		++first;
	}
}

//geometric progression (GP) or geometric sequence
template<class InputIterator, typename T>
void fill_gp(InputIterator first, InputIterator last, T first_term, T common_ratio)
{
	T n{1};
	while (first != last)
	{
		*first = first_term * n;
		n *= common_ratio;
		++first;
	}
}

template<class OutputIterator, typename T>
void unfold_ap(T value, T first_term, T common_difference, OutputIterator result)
{
	T n{};
	while (value > T{})
	{
		T x = first_term + n * common_difference;
		*result = x;
		value -= x;
		++n;
	}
}

#include <iostream>

template <class Iter>
void display(Iter& iter)
{
	for (auto i : iter) std::cout << i << " ";
	std::cout << "\n";
}

//std::accumulate Ref.: http://www.cplusplus.com/reference/numeric/accumulate/

void understanding_accumulate_run()
{
	auto is_even = [](int i) { return (i & 0x1) == 0x0;	};
	
	std::array<int, 10> xs { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	int initial = 0;
	int total = std::accumulate(std::begin(xs), std::end(xs), initial);
	std::cout << total << "\n";
    
    std::cout << (std::accumulate(std::begin(xs), std::end(xs), 0.0) / xs.size()) << "\n";

	initial = 0;
	total = std::accumulate(std::begin(xs), std::begin(xs) + 6, 
								accumulator_with_predicate  <int>(initial, is_even));	
	std::cout << total << "\n";

	total = sum(std::begin(xs), std::begin(xs) + 4);
	std::cout << total << "\n";

	total = sum(xs);
	std::cout << total << "\n";

	initial = 0;
	total = fold(std::begin(xs), std::begin(xs) + 5, initial, [](int acc, int x) { return acc + x; });
	std::cout << total << "\n";

	initial = 1;
	//4!
	total = fold(std::begin(xs), std::begin(xs) + 4, initial, [](int acc, int x) { return acc * x; });
	std::cout << total << "\n";

	initial = 0;
	total = std::accumulate(std::begin(xs), std::end(xs), initial, std::plus<int>());
	std::cout << total << "\n";
	
	initial = 1;
	//4!
	total = std::accumulate(std::begin(xs), std::begin(xs) + 4, initial, [](int acc, int x) { return acc * x; });
	std::cout << total << "\n";

	bool equals = std::accumulate(xs.begin(), xs.end(), 0) == std::accumulate(xs.rbegin(), xs.rend(), 0);
	std::cout << equals << "\n";

	std::array<char, 5> ys{ 'A', 'B', 'C', 'D', 'E' };
	
	std::string s_initial = "";
	//fold/left fold
	std::string s_total = std::accumulate(ys.begin(), ys.end(), s_initial);
	std::cout << s_total << "\n";

	s_initial = "";
	//fold back/right fold
	s_total = std::accumulate(ys.rbegin(), ys.rend(), s_initial);
	std::cout << s_total << "\n";

	std::array<int, 10> zs;
	fill_ap(zs.begin(), zs.end(), 2, 3);
	display(zs);
	
	initial = 0;
	total = std::accumulate(zs.rbegin(), zs.rend(), initial);
	std::cout << total << "\n";

	std::vector<int> ws;
	/*
	int a = 2;
	int d = 3;
	int n = 0;
	while (total > 0)
	{
		int x = a + n * d;
		ws.push_back(x);
		total -= x;
		++n;
	}
	*/
	unfold_ap(total, 2, 3, std::back_inserter(ws));
	display(ws);
	
	fill_gp(zs.begin(), zs.end(), 2, 3);
	display(zs);

	//unfold_gp as exercise to the reader... ;-)
}

int main()
{
	understanding_accumulate_run();
	return 0;
}
