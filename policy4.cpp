#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <functional>

using namespace std;

//Writer must define operator <<
#define Writer typename

//Formatter must define operator (const string &)
#define Formatter typename

template<Writer writer_policy, Formatter formatter_policy>
struct log_writer {

	writer_policy &_writer;
	formatter_policy _formatter;
	
	log_writer(writer_policy &writer, formatter_policy formatter) : 
		_writer(writer), _formatter(formatter) { }
	
	void error(const std::string &s) {
		_writer << _formatter(s);
	}

	void info(const std::string &s) {
		_writer << _formatter(s);
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

#include <ctime>
//Formatter
std::string dt_format(const string &s) {
	char buffer[32];

	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "[%Y-%m-%d %I:%M:%S] ",timeinfo);
	std::string str(buffer);

	return str + s;
}

struct my_formatter {
	std::string operator()(const std::string &s) {
		return dt_format(s);
	}
};

template<Writer writer_policy, Formatter formatter_policy>
auto make_logger(writer_policy &writer, formatter_policy formatter) -> log_writer<writer_policy, formatter_policy>
{
	return log_writer<writer_policy, formatter_policy>(writer, formatter);
}

int main() {
	
	//file_writer out_writer("teste.log");
	console_writer out_writer;
	auto logger = make_logger(out_writer, dt_format);

	logger.info("Starting...");
	logger.error("Ouch!");
	
	
	return 0;
}