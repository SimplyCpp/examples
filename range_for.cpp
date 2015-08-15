//Sample provided by Thiago Massari Guedes
//August 2015
//http://www.simplycpp.com/

#include "example_main.h"

#include <iostream>
#include <map>

using namespace std;

struct Cash {
	using Date = unsigned int;
	Date date; //yyyymmdd
	double value;
};

template<typename T>
struct CashRange {
	using const_iterator = typename T::const_iterator;
	
	CashRange(const_iterator begin, const_iterator end) 
	{
		_begin = begin;
		_end = end;
	}
	
	const const_iterator begin() const { return _begin; }
	const const_iterator end() const { return _end; }
	
private:
	const_iterator _begin;
	const_iterator _end;
};

class CashFlow {
	using CashMap = multimap<Cash::Date, Cash>;
	using const_iterator = multimap<Cash::Date, Cash>::const_iterator;
	multimap<Cash::Date, Cash> _flow;
	
public:

	CashFlow() 
	{
		int date = 20150000;
		for(int m=1; m < 8; m+=2) {
			for(int d=1; d <= 30; d += 6) {
				int dt = date+(m*100)+d;
				Cash c; c.date = dt; (c.value = m + d * 10.0) / (double)(d*10-m);
				_flow.insert( make_pair(dt, c) );
			}			
		}
		
	}


	auto getMonthlyFlow(int year, int month) -> CashRange<CashMap>
	{
		int kb = (year * 10000) + (month * 100) + 00;	
		int ke = (year * 10000) + (month * 100) + 31;
		cout << kb << " - " << ke << endl;
		const auto b = _flow.lower_bound(kb);
		if( b == _flow.end() ) {
			return CashRange<CashMap>(_flow.cend(), _flow.cend());
		}
		const auto e = _flow.upper_bound(ke);
		return CashRange<CashMap>(b, e);
	}
	
};

EXAMPLE_MAIN(range_for)
{
	
	cout << "Getting data from 2015-03" << endl;
	CashFlow flow;
	for(auto c : flow.getMonthlyFlow(2015, 03)) {
		cout << c.second.date << ": " << c.second.value << endl;
	}
	
	return 0;
}
