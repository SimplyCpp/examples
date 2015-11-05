#pragma once

#include "window.h"

struct main_window {
	main_window();
	~main_window();
	void close_child();
	void add_child(window* child);
	void inform_closed(window *w);
private:	
	window* _child;
};
