//Sample provided by Fabio Galuppo 
//October 2016
//http://www.simplycpp.com 

#include "sample3.hpp"

#include "random_real_util.hpp"
#include <chrono>

#include <cstdio>

template<typename Real>
void display_bounds(Real lower_bound = Real(-1), Real upper_bound = Real(-1))
{
	Real a = lower_bound, b = upper_bound;
	if (lower_bound == Real(-1) && upper_bound == Real(-1))
	{
		auto& distr = internals::get_rand_real<Real>().distribution;
		a = distr.a();
		b = distr.b();
	}
	printf("[%f, %f)\n", a, b);
}

int sample3_main()
{
	//[0.000000, 1.000000)
	display_bounds<double>();
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %f\n", i + 1, rand_real<double>());
	std::printf("\n");

	//[-0.5, 0.5)
	seed_rand();
	display_bounds<double>(-0.5, 0.5);
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %9.6f\n", i + 1, rand_real<double>(-0.5, 0.5));
	std::printf("\n");

	//[0.000000, 1.000000)
	display_bounds<double>();
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %f\n", i + 1, rand_double());
	std::printf("\n");

	//[-10.000000, 10.000000)
	display_bounds<double>(-10, 10);
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %10.6f\n", i + 1, rand_double(-10, 10));
	std::printf("\n");

	//[0.000000, 1.000000)
	unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
	seed_rand(seed);
	display_bounds<float>();
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %f\n", i + 1, rand_real<float>());
	std::printf("\n");

	return 0;
}