int sumNonTemplated(int a, int b) {
	return a+b;
}

template <typename T>
T sumTemplated(T a, T b) {
	return a+b;
}

class NonTemplated {
	int value;
public:
	using value_type = int;
	NonTemplated(int a) : value(a) {}
	int sum(int a) {
		return value + a;
	}
};

template <typename T>
class Templated {
	T value;
public:
	using value_type = T;
	Templated(T a) : value(a) {}
	T sum(T a) {
		return value + a;
	}
};

// template<typename C>
// struct Runner {
// 	int run(typename C::value_type v) {
// 		C c(v);
// 		return c.sum(v+1);
// 	}
// };

void run() {

	// Runner<NonTemplated> rn;
	// Runner<Templated<int>> rt;
	// rn.run(1);
	// rt.run(2);

	sumTemplated(1, 2);
	sumTemplated(1.0, 2.0);
	sumTemplated(1.0f, 2.0f);

	NonTemplated nt{1};
	Templated<int> ti{1};
	Templated<double> td{1.0};
	nt.sum(2);
	ti.sum(2);
	td.sum(2.0);

}