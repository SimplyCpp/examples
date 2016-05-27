#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace buffer_utils {
	vector<string> split(const string &data, char c) {
		vector<string> ret;
		auto old = cbegin(data);
		for(auto it = old; it != cend(data); ++it) {
			if( *it == c ) {
				std::string out_val;
				std::copy( old, it, std::back_inserter(out_val));
				ret.push_back( out_val ); 
				old=it+1;
			}
		}
		if( old != cend(data) ) { 
			std::string out_val;
			std::copy( old, cend(data), std::back_inserter(out_val));
			ret.push_back( out_val ); 
		}
		return ret;
	}
}

int main() {
	
	string str("Simply C++ welcome you all");
	
	using namespace buffer_utils;
	vector<string> v = split(str, ' ');
	for(const string &s : v) {
		cout << s << endl;
	}
	
	return 0;
	
}