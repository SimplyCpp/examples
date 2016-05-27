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
				T out_val;
				std::copy( old, it, std::back_inserter(out_val));
				ret.push_back( out_val ); 
				old=it+1;
			}
		}
		if( old != cend(data) ) { 
			T out_val;
			std::copy( old, cend(data), std::back_inserter(out_val));
			ret.push_back( out_val ); 
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