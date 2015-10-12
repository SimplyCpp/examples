//Sample provided by Fabio Galuppo
//Octorber 2015
//http://www.simplycpp.com

//compile with clang++:
//clang++ -Wall -O2 -std=c++11 -o forward_iterator_with_predicate_program.exe forward_iterator_with_predicate_program.cpp

//compile g++:
//g++ -Wall -O2 -std=c++11 -o forward_iterator_with_predicate_program.exe forward_iterator_with_predicate_program.cpp

//compile msvc:
//cl.exe /Wall /EHsc /Ox forward_iterator_with_predicate_program.cpp /link /out:forward_iterator_with_predicate_program.exe

#include "forward_iterator_with_predicate.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

template <class Iter> 
void display(Iter& iter)
{
	for (auto i : iter) std::cout << i << " ";
	std::cout << "\n";
}

void forward_iterator_with_predicate_run()
{
	auto is_even = [](int i) {
		return (i & 0x1) == 0x0;
	};

	auto is_odd = [](int i) {
		return (i & 0x1) == 0x1;
	};

	auto force_true = [](int) { return true; };

	auto force_false = [](int) { return false; };

	std::vector<int> xs = { 1, 2, 3, 4, 5, 6, 7, 8 };

	display(xs);

	auto iwp = make_iterator_with_predicate(xs, is_even);

	auto iwp2 = make_iterator_with_predicate(xs, is_odd);

	auto iwp3 = make_iterator_with_predicate(xs, force_true);

	display(iwp);

	display(iwp2);

	display(iwp3);
	
	std::vector<int> ys;
	ys.resize(4);
	std::copy(iwp.begin(), iwp.end(), ys.begin());

	display(iwp);

	std::vector<int> zs;
	zs.resize(4);
	std::copy_if(xs.begin(), xs.end(), zs.begin(), is_even);

	display(zs);

	xs.push_back(9);
	xs.push_back(10);

	display(xs);

	std::vector<int> ws;
	ws.resize(5);
	iwp.refresh();
	std::copy(begin(iwp), end(iwp), begin(ws));

	display(iwp);

	std::transform(begin(iwp), end(iwp), begin(iwp), [](int i) { return i + 10; });
	
	display(iwp);

	display(xs);

	*begin(iwp) += 100;

	display(xs);
}

int main()
{
	forward_iterator_with_predicate_run();
	return 0;
}
