//Sample provided by Thiago Massari Guedes
//September 2015
//http://www.simplycpp.com/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

namespace Text {

void _check_size(std::string &buffer, int size, int size_inc) {
	if( size + buffer.size() > buffer.capacity() )
		buffer.reserve(buffer.capacity() + size_inc);
}

namespace internal {
	
	//General implementation
	template <typename T>
	struct add {
		add(std::string &buffer, T val, int size_inc) {
			std::string s = std::to_string(val);
			_check_size(buffer, s.size(), size_inc);
			buffer += s;
		}
	};

	//Specific implementations
	template <>
	struct add<const char *> {
		add(std::string &buffer, const char * val, int size_inc) {
			_check_size(buffer, strlen(val), size_inc);
			buffer += val;
		}
	};

	template <>
	struct add<bool> {
		add(std::string &buffer, bool val, int size_inc) {
			string s = val?"Y":"N";
			_check_size(buffer, s.size(), size_inc);
			buffer += s;
		}
};
}

struct string_builder {

	string_builder(int size = 128) : _size(size) {
		if( size > 0 ) _s.reserve(size);
	}
	
	template<typename T>
	string_builder &add(T v) {
		internal::add<T>(_s, v, _size);
		return *this;
	}
	
	const std::string &str() {
		return _s;
	}

private:
	std::string _s;
	int _size;
	
};

}

int main() {

	using Text::string_builder;
	
	string_builder s;
	s.add(1).add(12.2).add("thiago ").add(true);
	//s2.add(1).add(12.2).add(true);
	cout << s.str() << endl;
	
	return 0;
}
