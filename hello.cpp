#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[]) {

	/*
	 * I don’t want to make the choice between elegant, 
	 * which Simula was for this problem,
	 * and efficient, which BCPL was. I want both
	 * (Bjarne Stroustrup, 2015-02-05)
	 */
        
	std::vector<std::string> authors { "Fabio", "Thiago" };
	
	std::for_each(std::begin(authors), std::end(authors), 
		[](const std::string &author) { 
			std::cout << "Hello from " << author << "  !\n" ; 
		});
 
 	return 0;

}
