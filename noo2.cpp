#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace buffer_utils {
	
	template<typename T>
	vector<T> split(T &data, typename T::value_type c) {
		vector<T> ret;
		auto old = cbegin(data);
		for(auto it = old; it != cend(data); ++it) {
			if( *it == c ) {
				ret.emplace_back( old, it ); 
				old=it+1;
			}
		}
		if( old != cend(data) ) { 
			ret.emplace_back( old, cend(data) ); 
		}
		return ret;
	}
}

int main() {
	
	wstring str(L"Simply C++ welcome you all");
	
	using namespace buffer_utils;
	vector<wstring> v = split(str, ' ');
	for(const wstring &s : v) {
		wcout << s << endl;
	}
	
	return 0;
	
}