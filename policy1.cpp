#include <iostream>
#include <string>
#include <tuple>


using namespace std;

struct log_writer {
	
	void error(const std::string &s) {
		cout << s << endl;
	}

	void info(const std::string &s) {
		cout << s << endl;
	}
	
};

int main() {
	
	log_writer logger;
	
	logger.info("Starting...");
	logger.error("Ouch!");
	
	return 0;
}