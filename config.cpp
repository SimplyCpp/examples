//Sample provided by Thiago Massari Guedes
//February 2016
//http://www.simplycpp.com/

#include <fstream>
#include <iostream>

#include "config.h"

struct my_value {
	std::string sval;
	using const_iterator = std::string::const_iterator;
};

int main() {
	
	std::string fname = "example.cfg";
	
	//-------- Using my_value as a value ------------
	/*
	using iter_type = std::string::const_iterator;
	auto cfg = configuration::load<std::string, my_value>(fname, 
		//[](configuration::config_holder<std::string, my_value> &config, iter_type b, iter_type m, iter_type e) {
		[](auto &config, iter_type b, iter_type m, iter_type e) {
			std::string k(b, m);
			my_value mv;
			//TODO: Trocar
			mv.sval = std::string(m+1, e);
			//b-m => key / m+1-e => value
			
			config.add_item( k, mv );
		});
	const my_value &log_dir = cfg.get("log.base_dir");
	std::cout << log_dir.sval << std::endl;
	*/
	
	//-------- Using string as a value --------------
	//*
	auto cfg = configuration::load(fname);
	
	const std::string &log_dir = cfg.get("log.base_dir");
	std::cout << log_dir << std::endl;
	
	auto plugins = cfg.prefix("log.");

	for(auto p : plugins) {
		std::cout << p.first << "=>" << p.second << std::endl;
	}
	std::cout << "--------------" << std::endl;

	auto suf = cfg.after("plugin.socket");
	for(auto p : suf) {
		std::cout << p << std::endl;
	}
	std::cout << "--------------" << std::endl;

	auto tok = cfg.next_token("plugin.", '.');
	for(auto p : tok) {
		std::cout << "Plugins: " << p << std::endl;
	}
	
	const std::string &id = cfg.get(std::string("plugin.fix.id"));
	std::cout << "-> " << id << std::endl;
	//*/
	
}
