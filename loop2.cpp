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

template<typename T>
struct range {

	range(const T &cont) : _b(cont.begin()), _e(cont.end()) {}
	range(typename T::const_iterator b, typename T::const_iterator e) : _b(b), _e(e) {}

	typename T::const_iterator &begin() { return _b; }
	typename T::const_iterator &end() { return _e; }

private:
	typename T::const_iterator _b, _e;

};

template<typename T>
range<T> wide_range(const T &cont, int start, int end) {

	int items = std::distance(cont.cbegin(), cont.cend());

	if( items == 0 || end == 0 ) 
		return range<T>(cont.cend(), cont.cend());

	int range_size;
	if( end > 0 ) {
		range_size = start+end;
	} else {
		range_size = start-end;
	}

	if( items <= range_size ) {
		return range<T>(cont.cend(), cont.cend());
	}

	if( end > 0 ) {
		return range<T>(cont.cbegin()+start, cont.cbegin()+start+end);
	} else 
		return range<T>(cont.cbegin()+start, cont.cend()+end);
}

template<typename T>
void print1(T &msgs) {
	for(const auto &msg : msgs) {
		PublishMessage(msg);
	}
	cout << endl << "==========" << endl;
}

template<typename T>
void print2(T &msgs) {
	for_each(begin(msgs), end(msgs), [](const auto &msg) {
		PublishMessage(msg);
	});
	cout << endl << "==========" << endl;
}


EXAMPLE_MAIN(loop2)
{
	
	vector<Message> msgs {"MSG1","MSG2","MSG3","MSG4","MSG5"};
	vector<Message> empty_msgs {};
	
	auto msgs_sub1 = wide_range(msgs, 1, -1); //[1:-1]
	auto msgs_sub2 = wide_range(msgs, 1, 2);  //[1:2]
	
	auto msgs_sub3 = wide_range(msgs, 1, 5);  //Empty
	auto msgs_sub4 = wide_range(msgs, 1, -5);  //Empty
	auto msgs_sub5 = wide_range(empty_msgs, 1, -1);  //Empty

	print1(msgs_sub1); //shows items 1, 2, 3
	print2(msgs_sub1); //shows items 1, 2, 3

	print2(msgs_sub2); //shows items 1, 2

	print2(msgs_sub3); //empty
	print2(msgs_sub4); //empty
	print2(msgs_sub5); //empty

	
}
