#include "window.h"
#include "main_window.h"

#include <iostream>

using namespace std;

namespace msgbox {
	
	bool inform(const std::string &s) {
		cout << s << endl;
		char c;
		cin >> c;
		if( c != 'N' && c != 'n' )
			return true;
		return false;
	}
	
}

void window::close() {
	//Closing window stuff...
	
	if( msgbox::inform("Really?") ) {
		cout << "Closing window" << endl;
		_parent.inform_closed(this);
	} else {
		cout << "Thanks for this 2nd chance!" << endl;
	}
	
}