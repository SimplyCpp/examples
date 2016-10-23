//Sample provided by Fabio Galuppo 
//October 2016
//http://www.simplycpp.com 

#ifndef RANDOM_UTIL_HPP
#define RANDOM_UTIL_HPP

#include <random>

namespace internals
{
	using random_engine = std::default_random_engine;
	static thread_local random_engine current_engine;

	inline random_engine::result_type rd()
	{
		return std::random_device{}();
	}

	inline random_engine& rand_engine()
	{
		static thread_local random_engine engine{ rd() };
		return engine;
	}

	inline void seed_rand()
	{
		rand_engine().seed(rd());
	}

	inline void seed_rand(random_engine::result_type seed)
	{
		rand_engine().seed(seed);
	}

	struct rand_int_func
	{
		using int_distribution = std::uniform_int_distribution<int>;
		int_distribution distribution;

		int operator()()
		{
			return distribution(rand_engine());
		}

		int operator()(int min_inclusive, int max_inclusive)
		{
			return distribution(rand_engine(), int_distribution::param_type{ min_inclusive, max_inclusive });
		}
	};

	static thread_local rand_int_func rand_int;
}

inline void seed_rand()
{
	internals::seed_rand();
}

inline void seed_rand(internals::random_engine::result_type seed)
{
	internals::seed_rand(seed);
}

inline int rand_int()
{
	return internals::rand_int();
}

inline int rand_int(int min_inclusive, int max_inclusive)
{
	return internals::rand_int(min_inclusive, max_inclusive);
}

#endif /* RANDOM_UTIL_HPP */
