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