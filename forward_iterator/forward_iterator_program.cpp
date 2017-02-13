//Sample provided by Fabio Galuppo
//February 2017
//http://www.simplycpp.com

//compile clang++:
//clang++ -Wall -O2 -std=c++14 -o forward_iterator_program.exe forward_iterator_program.cpp

//compile g++:
//g++ -Wall -O2 -std=c++14 -o forward_iterator_program.exe forward_iterator_program.cpp

//compile msvc:
//cl.exe /EHsc /Ox /std:c++14 forward_iterator_program.cpp /link /out:forward_iterator_program.exe

#include "bst_node.hpp"
#include "bst_depth_first_traversal.hpp"
#include "bst_breadth_first_traversal.hpp"

template<typename T>
struct interval_state
{
	using reference = interval_state<T>;
	using const_reference = const interval_state<T>;

	interval_state(const T& val) : current(val) {}

	bool operator!=(const_reference that) const
	{
		return current != that.current;
	}

	//Command–query separation (https://en.wikipedia.org/wiki/Command–query_separation):
	//Command
	reference operator++()
	{
		++current;
		return *this;
	}
	//Query
	T operator*() const
	{
		return current;
	}	

private:
	T current;
};

template<typename T>
struct interval
{
	interval(T start_inclusive, T finish_exclusive) :
		start_inclusive(start_inclusive),
		finish_exclusive(finish_exclusive) {}

	interval_state<T> begin()
	{
		return interval_state<T>(start_inclusive);
	}

	interval_state<T> end()
	{ 
		return interval_state<T>(finish_exclusive);
	}

private:
	T start_inclusive, finish_exclusive;
};

#include <iostream>

void interval_sample()
{
	for (int i : interval<int>{ 0, 5 })
		std::cout << i << " ";
	std::cout << "\n";
}

#include <algorithm>
#include <iterator>
#include <vector>

void dfs_sample(bst_node<int>& root)
{
	std::cout << "dfs inorder traversal: ";
	for (auto first = begin(dfs(root)), last = end(dfs(root)); first != last; ++first)
	{
		std::cout << (*first).value << " ";
	}
	std::cout << "\n";

	std::cout << "dfs inorder traversal: ";
	for (auto& iter : dfs(root)) //argument dependent lookup
	{
		std::cout << iter.value << " ";
	}
	std::cout << "\n";

	auto iter = std::find(begin(dfs(root)), end(dfs(root)), 3);
	if (iter != end(dfs(root)))
	{
		std::cout << "value " << (*iter).value << " was ";
		std::cout << "found at address " << std::hex << static_cast<void*>(&*iter) << "\n";
	}
	else
	{
		std::cout << "not found\n";
	}
}

void bfs_sample(bst_node<int>& root)
{
	std::cout << "bfs traversal: ";
	for (auto& iter : bfs(root)) //argument dependent lookup
	{
		std::cout << iter.value << " ";
	}
	std::cout << "\n";

	std::vector<float> xs;
	std::transform(begin(dfs(root)), end(dfs(root)), std::back_inserter(xs), 
		[](bst_node<int>& x) { return x.value * 100.f; });
	std::cout << "transformed values: ";
	for (auto& x : xs)
	{
		std::cout << x << " ";
	}
	std::cout << "\n";
}

int main()
{
	interval_sample();

	bst_node<int> root(1);
	bst_node<int> a(2);
	bst_node<int> b(3);
	bst_node<int> c(4);
	bst_node<int> d(5);
	bst_node<int> e(6);
	bst_node<int> f(7);
	a.left = &c;
	a.right = &d;
	b.left = &e;
	b.right = &f;
	root.left = &a;
	root.right = &b;
	
	dfs_sample(root);
	bfs_sample(root);

	return 0;
}