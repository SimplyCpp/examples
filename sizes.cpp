//Sample provided by Thiago Massari Guedes
//April 2015
//http://www.simplycpp.com/

//g++ -O2 -std=c++14 -o sizes sizes.cpp && ./sizes

#include "example_main.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;

struct Field {
	unsigned int f1;  //int=4 bytes
	unsigned char f2; //char=1 byte
};

struct FieldC {
	unsigned char f1; //char=1 byte
	unsigned int f2;  //int=4 bytes
};

struct FieldS {
	unsigned short f1; //short=2 bytes
	unsigned int f2;   //int=4 bytes
};

struct Field3 {
	unsigned short f1; //short=2 bytes
	unsigned char f2;  //char=1 byte
	unsigned int f3;   //int=4 bytes
};

struct Field4 {
	unsigned char f1; //char=1 byte
	unsigned int f2;  //int=4 bytes
	unsigned char f3; //char=1 byte
};

struct Field5 {
	unsigned int f2;  //int=4 bytes
	unsigned char f1; //char=1 byte
	unsigned char f3; //char=1 byte
};

template<typename T>
void dump2(initializer_list<string> header) {
	T t;
	vector<string> vs = header;
	int f1 = ((long long)&t.f1 - (long long)&t);
	int f2 = ((long long)&t.f2 - (long long)&t);
	cout << setbase(10) 
		<< vs[0] << ":" << f1 << "-" << sizeof(t.f1) << ", " 
		<< vs[1] << ":" << f2 << "-" << sizeof(t.f2) 
		<< " => Total bytes: " << sizeof(T) <<  endl;

	const int size = sizeof(T);
	memset(&t, 0xFF, size); //fill w/ FF
	t.f1=0; t.f2=0;
	uint8_t *c = (uint8_t *)&t;
	for(int i=0; i < size; i++) {
	  cout<< setbase(16) << (int)*c << " ";
	  c++;
	}
	cout << setbase(10) << " Wasted bytes: " << (sizeof(T)-sizeof(t.f1)-sizeof(t.f2));
	cout << endl << endl;
}

template<typename T>
void dump3(initializer_list<string> header) {
	T t;
	vector<string> vs = header;

	int f1 = ((long long)&t.f1 - (long long)&t);
	int f2 = ((long long)&t.f2 - (long long)&t);
	int f3 = ((long long)&t.f3 - (long long)&t);
	cout << setbase(10) 
		<< vs[0] << ":" << f1 << "-" << f1+sizeof(t.f1) << ", " 
		<< vs[1] << ":" << f2 << "-" << f2+sizeof(t.f2) << ", " 
		<< vs[2] << ":" << f3 << "-" << f3+sizeof(t.f3) 
		<< " => Total bytes: " << sizeof(T) <<  endl;

	const int size = sizeof(T);
	memset(&t, 0xFF, size); //fill w/ FF
	t.f1=0; t.f2=0; t.f3=0;
	uint8_t *c = (uint8_t *)&t;
	for(int i=0; i < size; i++) {
	  cout<< setbase(16) << (int)*c << " ";
	  c++;
	}
	cout << setbase(10) << " Wasted bytes: " << (sizeof(T)-sizeof(t.f1)-sizeof(t.f2)-sizeof(t.f3));
	cout << endl << endl;
}


EXAMPLE_MAIN(sizes) {

	dump2<Field>( {"int", "char"} );
	dump2<FieldC>( {"char", "int"} );
	dump2<FieldS>( {"short", "int"} );
	dump3<Field3>( {"short", "char", "int"} );
	dump3<Field4>( {"char", "int", "char"} );
	dump3<Field5>( {"int", "char", "char"} );

}
