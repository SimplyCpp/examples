#pragma once

#include "window.h"

struct main_window {
	
	void close_child() {
		child.close();
	}
	
	window child;
	
};
