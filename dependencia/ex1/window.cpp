#include "window.h"

#include <iostream>

using namespace std;

namespace msgbox {
	
	bool inform(const std::string &s) {
		char c;
		cin >> c;
		if( c != 'N' && c != 'n' )
			return true;
		return false;
	}
	
}

void window::close() {
	//Closing window stuff...
	cout << "Closing window" << endl;
}