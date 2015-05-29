//Sample provided by Thiago Massari Guedes
//April 2015
//http://www.simplycpp.com/

#include "example_main.h"

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

//alignment to 4 bytes
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
	unsigned int f2;   //int=4 bytes;
};

struct Field3 {
	unsigned short f1; //short=2 bytes
	unsigned char f2;  //char=4 bytes;
	unsigned int f3;   //int=4 bytes;
};

template<typename T>
void dump2() {
	T t;
	int f1 = ((long long)&t.f1 - (long long)&t);
	int f2 = ((long long)&t.f2 - (long long)&t);
	cout << std::setbase(10) << "f: " << f1 << "-" << sizeof(t.f1) << ", " << f2 << "-" << sizeof(t.f2) 
		<< " => Total bytes: " << sizeof(T) <<  endl;

	const int size = sizeof(T);
	memset(&t, 0xFF, size); //fill w/ FF
	t.f1=0; t.f2=0;
	uint8_t *c = (uint8_t *)&t;
	for(int i=0; i < size; i++) {
	  cout<< std::setbase(16) << (int)*c << " ";
	  c++;
	}
	cout << std::setbase(10) << " Wasted bytes: " << (sizeof(T)-sizeof(t.f1)-sizeof(t.f2));
	cout << endl << endl;
}

template<typename T>
void dump2(int vezes) {
	T t;
	T tv[vezes];
	int f1 = ((long long)&t.f1 - (long long)&t);
	int f2 = ((long long)&t.f2 - (long long)&t);
	cout << "f: " << f1 << ", " << f2 << " => Total bytes: " << sizeof(T) <<  endl;

	const int size = sizeof(T);
	memset(&t, 0xFF, size); //fill w/ FF
	t.f1=0; t.f2=0;
	uint8_t *c = (uint8_t *)&t;
	for(int i=0; i < size; i++) {
	  cout<< std::setbase(16) << (int)*c << " ";
	  c++;
	}
	cout << endl << endl;
}

template<typename T>
void dump3() {
	T t;
	int f1 = ((long long)&t.f1 - (long long)&t);
	int f2 = ((long long)&t.f2 - (long long)&t);
	int f3 = ((long long)&t.f3 - (long long)&t);
	cout << "f: " << f1 << "-" << sizeof(t.f1) << ", " << f2 << "-" << sizeof(t.f2) << ", " << f3 << "-" << sizeof(t.f3) 
		<< " => Total bytes: " << sizeof(T) <<  endl;

	const int size = sizeof(T);
	memset(&t, 0xFF, size); //fill w/ FF
	t.f1=0; t.f2=0; t.f3=0;
	uint8_t *c = (uint8_t *)&t;
	for(int i=0; i < size; i++) {
	  cout<< std::setbase(16) << (int)*c << " ";
	  c++;
	}
	cout << std::setbase(10) << " Wasted bytes: " << (sizeof(T)-sizeof(t.f1)-sizeof(t.f2)-sizeof(t.f3));
	cout << endl << endl;
}


EXAMPLE_MAIN(sizes) {
/*
"int, char"
"char, int"
"short, int"
"short, char, int"
*/
	dump2<Field>();
	dump2<FieldC>();
	dump2<FieldS>();
	dump2<FieldS>(2);
	dump3<Field3>();

}
