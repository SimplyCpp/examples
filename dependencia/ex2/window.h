#pragma once

#include <string>

namespace msgbox {
	bool inform(const std::string &s);
}

struct main_window;

struct window {
	window(main_window &parent) : _parent(parent) { }
	void close();

private:
	main_window &_parent;
};
