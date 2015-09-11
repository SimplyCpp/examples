//Sample provided by Thiago Massari Guedes
//September 2015
//http://www.simplycpp.com/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

namespace Text_OO {
	
class string_builder {
protected:
	void _check_size(int size) {
		if( size + _s.size() > _s.capacity() )
			_s.reserve(_s.capacity() + _size);
	}

public:

	string_builder(int size = 128) {
		if( size > 0 )
			_s.reserve(size);
	}
	
	string_builder &add(int v) {
		std::string s = std::to_string(v);
		_check_size(s.size());
		_s += s;
		return *this;
	}
	string_builder & add(const std::string &v) {
		_check_size(v.size());
		_s += v;
		return *this;
	}
	string_builder & add(const char *v) {
		_check_size(strlen(v));
		_s += v;
		return *this;
	}
	string_builder & add(double v) {
		std::string s = std::to_string(v);
		_check_size(s.size());
		_s += s;
		return *this;
	}
	string_builder & add(bool v) {
		std::string s = v?"Y":"N";
		_check_size(s.size());
		_s += s;
		return *this;
	}
	
	//There are much more methods to implement
	//string_builder &add(unsigned int v);
	//string_builder &add(float v);
	//string_builder &add(long long v);
	//string_builder &add(unsigned long long v);
	//.... And much more ....
	
	const std::string &str() {
		return _s;
	}

private:
	std::string _s;
	int _size;
	
};

};

int main() {

	using Text_OO::string_builder;
	
	string_builder s;
	s.add(1).add(12.2).add("thiago ").add(true);
	cout << s.str() << endl;

	return 0;
}
