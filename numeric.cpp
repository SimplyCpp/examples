//Sample provided by Thiago Massari Guedes
//December 2015
//http://www.simplycpp.com/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

namespace concrete {
	//C++98 version ----------------------------
	struct numerical_appender {
		numerical_appender(std::string &buf) : _buf(buf) { }
		void operator()(const char c) {
			if( c >= '0' && c <= '9' ) _buf.push_back(c);
		}
	private:
		std::string &_buf;
	};

	void get_numeric(const std::string &input, std::string &output) 
	{
		numerical_appender appender(output);
		std::for_each(input.begin(), input.end(), appender);
	}

	//C++14 version ----------------------------
	std::string get_numeric(const std::string &input) 
	{
		std::string output;
		std::for_each(begin(input), end(input), [&output](const char c) {
			if( c >= '0' && c <= '9' ) output.push_back(c);
		});
		return output;
	}
}

namespace generic {
	//Generic version - C++98 ------------------
	template<class OutputIterator, class ValueType>
	struct numerical_appender {
		numerical_appender(OutputIterator it) : _it(it) { }
		void operator()(const ValueType c) {
			if( c >= '0' && c <= '9' ) {
				*_it = c;
				_it++;
			}
		}
	private:
		OutputIterator _it;
	};

	template<class T>
	void get_numeric(const T &input, T &output) 
	{
		typedef std::back_insert_iterator<T> it_type;
		it_type it = std::back_inserter(output);
		numerical_appender<it_type, typename T::value_type> appender(it);
		std::for_each(input.begin(), input.end(), appender);
	}
	
	//Generic version - C++14 ------------------
	template<typename T>
	T get_numeric(const T &input) 
	{
		T output;
		std::for_each(begin(input), end(input), [&output](auto c) {
			if( c >= '0' && c <= '9' ) output.push_back(c);
		});
		return output;
	}

}

namespace with_stl {
	template<typename T>
	T get_numeric(const T &input) 
	{
		T output;
		std::copy_if(begin(input), end(input), std::back_inserter(output), [](auto c) {
			if( c >= '0' && c <= '9' ) return true;
			return false;
		});
		return output;
	}
}

int main() {
	
	//C++98 version
	std::string value = "12asew3d45ddf678ee9 0";
	std::string num;
	concrete::get_numeric(value, num);
	std::cout << value << " - " << num << std::endl;
	num.clear();
	generic::get_numeric(value, num);
	std::cout << value << " - " << num << std::endl;

	//C++14 version
	std::cout << value << " - " << concrete::get_numeric(value) << std::endl;
	std::cout << value << " - " << generic::get_numeric(value) << std::endl;
	std::cout << value << " - " << with_stl::get_numeric(value) << std::endl;
	
	std::vector<char> v_in {'1', 'a', '2', 'b', 'c', '3'};
	decltype(v_in) v_out = generic::get_numeric(v_in);
	for(auto &i : v_out) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	
}
