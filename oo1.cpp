#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct nstring {
	nstring(const std::string &s) : _data(s) { }
	const string &data() const { return _data; }
	const vector<nstring> split(char c) {
		vector<nstring> ret;
		int old = 0;
		for(int i = 0; i < _data.size(); ++i) {
			if( _data[i] == c ) {
				ret.push_back( _data.substr(old, i-old) );
				old=i+1;
			}
		}
		if( old < _data.size() ) { ret.push_back( _data.substr(old) ); }
		return ret;
	}
private:
	string _data;
};

int main() {
	
	nstring nstr("Simply C++ welcome you all");

	vector<nstring> vn = nstr.split(' ');
	for(const nstring &ns : vn) {
		cout << ns.data() << endl;
	}
	
	return 0;
	
}