//Sample provided by Fabio Galuppo 
//October 2016
//http://www.simplycpp.com 

#include "sample2.hpp"

#include "random_int_util.hpp"

#include <cstdio>

template<typename Integer>
void display_bounds(Integer lower_bound = Integer(-1), Integer upper_bound = Integer(-1))
{
	Integer a = lower_bound, b = upper_bound;
	if (lower_bound == Integer(-1) && upper_bound == Integer(-1))
	{
		auto& distr = internals::get_rand_int<Integer>().distribution;
		a = distr.a();
		b = distr.b();
	}
	printf("[%d, %d]\n", a, b);
}

int sample2_main()
{
	//[0, 2147483647]
	display_bounds<int>();
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %10d\n", i + 1, rand_int<int>());
	std::printf("\n");

	//[1, 5]
	display_bounds<int>(1, 5);
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %1d\n", i + 1, rand_int<int>(1, 5));
	std::printf("\n");

	//[-1, 1]
	seed_rand();
	display_bounds<int>(-1, 1);
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %2d\n", i + 1, rand_int<int>(-1, 1));
	std::printf("\n");

	//[0, 2147483647]
	display_bounds<int>();
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %10d\n", i + 1, rand_int());
	std::printf("\n");

	//[0, 255]
	display_bounds<int>(0, 255);
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %3d\n", i + 1, rand_int(0, 255));
	std::printf("\n");

	//[0, 65535]
	display_bounds<unsigned short>();
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %5d\n", i + 1, rand_int<unsigned short>());
	std::printf("\n");

	//[-50, 50]
	display_bounds<short>(-50, 50);
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %3d\n", i + 1, rand_int<short>(internals::int_distribution<short>::param_type(-50, 50)));
	std::printf("\n");

	return 0;
}