#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T, typename Base>
struct nstring_common {
	
	virtual const T &data() const = 0;
	
	vector<Base> split(typename T::value_type c) {
		vector<Base> ret;
		const T &s_data = data();
		int old = 0;
		for(int i = 0; i < s_data.size(); ++i) {
			if( s_data[i] == c ) {
				ret.push_back( s_data.substr(old, i-old) );
				old=i+1;
			}
		}
		if( old < s_data.size() ) { ret.push_back( s_data.substr(old) ); }
		return ret;
	}
	
};

template<typename T>
struct nstring_basic : public nstring_common<T, nstring_basic<T>> {	
	nstring_basic(const T &value) { _data = value; }
	const T &data() const override { return _data; } 
private:
	T _data;
};

using nstring = nstring_basic<string>;
using nwstring = nstring_basic<wstring>;

int main() {
	
	nwstring nstr(L"Simply C++ welcome you all");

	vector<nwstring> vn = nstr.split(' ');
	for(const nwstring &ns : vn) {
		wcout << ns.data() << endl;
	}
	
	return 0;
	
}