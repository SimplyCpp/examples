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

int main() {
	
	//file_writer f("teste.log");
	console_writer out_writer;
	//log_writer<console_writer, std::function<string(const string&)>> logger(out_writer, dt_format);
	//log_writer<console_writer, std::function<decltype(dt_format)>> logger(out_writer, dt_format);
	auto l_fmt = [](const string& s) -> string {
		return "--> " + s;
	};
	log_writer<console_writer, decltype(l_fmt)> logger(out_writer, l_fmt);
	
	//my_formatter fmt;
	//log_writer<console_writer, my_formatter> logger(out_writer, fmt);
	
	logger.info("Starting...");
	logger.error("Ouch!");
	
	
	return 0;
}