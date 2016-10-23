//Sample provided by Fabio Galuppo 
//October 2016
//http://www.simplycpp.com 

#include "sample1.hpp"

#include <random>
#include <functional>

#include "random_util.hpp"

#include <cstdio>

int sample1_main()
{
	{
		std::mt19937 engine;
		std::uniform_int_distribution<int> distribution(1, 6);
		//[1, 6]
		for (int i = 0; i < 10; ++i)
			std::printf("%2d -> %1d\n", i + 1, distribution(engine));
		std::printf("\n");
	}

	{
		std::mt19937 engine;
		std::uniform_int_distribution<int> distribution(1, 6);
		auto dice = std::bind(distribution, engine); //distribution applied to engine
		//[1, 6]
		for (int i = 0; i < 10; ++i)
			std::printf("%2d -> %1d\n", i + 1, dice());
		std::printf("\n");
	}
	
	//[0, 2147483647]
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %10d\n", i + 1, rand_int());
	std::printf("\n");

	//[0, 255]
	for (int i = 0; i < 10; ++i)
		std::printf("%2d -> %3d\n", i + 1, rand_int(0, 255));
	std::printf("\n");

	return 0;
}

