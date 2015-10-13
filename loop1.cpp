//Sample provided by Thiago Massari Guedes
//October 2015
//http://www.simplycpp.com/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "example_main.h"

using namespace std;

using Message = string;

void PublishMessage(const Message &msg)
{
	cout << msg << " ";
}

EXAMPLE_MAIN(loop1)
{
	
	vector<Message> msgs {"MSG1","MSG2","MSG3","MSG4","MSG5"};
	
	unsigned int a = -1;
	printf("%u %X\n", a, a);

	//First block - bad code. Don't try at home.
	//How I found in the original code
	int count = 1;
	while (count < msgs.size() - 1)
	{
		const Message &item = msgs[count];
		PublishMessage(item);
		count++;
	}
	cout << endl << "==========" << endl;

	// Problems:
	// 1. Bug in code: msgs.size() - 1
	// 2. msgs[count] doesn't support dinamic range. 
	
	//First possibility
	for(auto it = msgs.cbegin(); it != msgs.cend(); it++) {
		PublishMessage(*it);
	}
	cout << endl << "==========" << endl;

	//Second possibility
	for(const auto &msg : msgs) {
		PublishMessage(msg);
	}
	cout << endl << "==========" << endl;

	//Thrird possibility
	for_each(begin(msgs), end(msgs), [](const auto &msg) {
		PublishMessage(msg);
	});
	cout << endl << "==========" << endl;

	//First possibility - unsafe
	for(auto it = msgs.cbegin()+1; it != msgs.cend()-1; it++) {
		PublishMessage(*it);
	}
	cout << endl << "==========" << endl;
	
	
}
