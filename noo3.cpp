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

// struct my_type : vector<int> {
// 	using value_type = int;
// 	my_type(std::initializer_list<int> )
// };

int main() {
	
	//Simply C++ welcome you all!
	
	using namespace buffer_utils;
	
	using my_type = vector<int>;	
	my_type x = {1, 2, 3, 4, 5, 6, 4, 7, 8, 4, 9, 10};
	vector<my_type> xs = split(x, 4);
	
	for(my_type &ix : xs) {
		for(int i : ix)
			wcout << i << " ";
		wcout << endl;
	}
	
	return 0;
	
}