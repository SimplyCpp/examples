#include "main_window.h"

#include <iostream>
#include <memory>

main_window::main_window() : _child(nullptr) {
	
}

main_window::~main_window() {
	delete _child;
}

void main_window::close_child() {
	_child->close();
}

void main_window::add_child(window* child) {
	_child = child;
}

void main_window::inform_closed(window *w) 
{
	std::cout << "Child window " << std::hex << w << " closed" << std::endl;
	delete w;
	//... necessary asserts
	_child = nullptr;
}

int main() {
	
	std::cout << sizeof(unsigned long int) << std::endl;
	std::cout << sizeof(unsigned long long) << std::endl;

	main_window mw;
	window *w = new window(mw);
	mw.add_child(w);
	
	mw.close_child();

	return 0;
	
}
