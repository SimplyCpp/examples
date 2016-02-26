#include <iostream>
#include <string>
#include <tuple>
#include <fstream>

using namespace std;

//Writer must define operator <<
#define Writer typename

template<Writer writer_policy>
struct log_writer {

	writer_policy &_writer;
	
	log_writer(writer_policy &writer) : _writer(writer) { }
	
	void error(const std::string &s) {
		_writer << s;
	}

	void info(const std::string &s) {
		_writer << s;
	}
	
};

struct console_writer {
	
	template<typename T>
	console_writer &operator << (const T &s) {
		std::cout << s << endl;
		return *this;
	}
};

struct file_writer {
	ofstream _file_s;
	file_writer(const string &f_name) {
		_file_s.open(f_name); //Example - never fails
	}
	~file_writer() {
		_file_s.close();
	}
	
	template<typename T>
	file_writer &operator << (const T &s) {
		_file_s << s << endl;
		return *this;
	}
};

int main() {
	
	//file_writer f("teste.log");
	console_writer f;
	log_writer<console_writer> logger(f);
	
	logger.info("Starting...");
	logger.error("Ouch!");
	
	return 0;
}