#include <string>
#include <array>
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[]) {

	/*
	 * I don’t want to make the choice between elegant, 
	 * which Simula was for this problem,
	 * and efficient, which BCPL was. I want both
	 * (Bjarne Stroustrup, 2015-02-05)
	 */

	//If it was plain C:
	printf("Hello from Fabio !\n");
	printf("Hello from Thiago !\n");
	printf("Fabio hopes you like the site !\n");
	printf("Thiago hopes you like the site !\n");

	//If it was real C++ (supposing you found a reason for
	//writing professionally a hello world program).
	std::cout << "Hello from Fabio !" << std::endl;
	std::cout << "Hello from Thiago !" << std::endl;
	std::cout << "Fabio hopes you like the site !" << std::endl;
	std::cout << "Thiago hopes you like the site !" << std::endl;

	//Now let's just put some fun in this code
	//using new c++1x features
	std::array<std::string, 2> authors { "Fabio", "Thiago" };
	
	std::for_each(std::begin(authors), std::end(authors), 
		[](const std::string &author) { 
			std::cout << "Hello from " << author << " !\n" ;
		});
		
	for(const auto &author : authors) {
		std::cout << author << " hopes you like the site !\n" ; 
	}
 
 	return 0;

}
