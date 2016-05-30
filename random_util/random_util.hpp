//Sample provided by Fabio Galuppo 
//May 2016
//http://www.simplycpp.com 

#ifndef RANDOM_UTIL_HPP
#define RANDOM_UTIL_HPP

//PRE-PROCESSOR MACROS:
//INT_RANDOM_UTIL_SLOTS_PER_THREAD    > 0	enables rand_int
//DOUBLE_RANDOM_UTIL_SLOTS_PER_THREAD > 0	enables rand_double
//RANDOM_UTIL_DEBUG				enables debug traces

#ifndef INT_RANDOM_UTIL_SLOTS_PER_THREAD
#define INT_RANDOM_UTIL_SLOTS_PER_THREAD 1
#endif

#ifndef DOUBLE_RANDOM_UTIL_SLOTS_PER_THREAD
#define DOUBLE_RANDOM_UTIL_SLOTS_PER_THREAD 1
#endif

#if INT_RANDOM_UTIL_SLOTS_PER_THREAD > 0 || DOUBLE_RANDOM_UTIL_SLOTS_PER_THREAD > 0
#include <random>
#include <functional>
#include <array>
#include <cassert>

#ifdef RANDOM_UTIL_DEBUG
#include <iostream>
#include <typeinfo>
#include <thread>
#endif

namespace internals
{
	using random_engine = std::mt19937;

	thread_local random_engine tls_engine;

	template<typename T = int, template <typename> class TDistribution = std::uniform_int>
	struct rand_state final
	{
		rand_state() :
			distr() { 
#ifdef RANDOM_UTIL_DEBUG
			std::cout << "tid #" << std::this_thread::get_id() << " " << typeid(T).name() << "\n"; //dbg
#endif
		}

		rand_state(T min_value, T max_value) :
			distr(min_value, max_value) {
#ifdef RANDOM_UTIL_DEBUG
			std::cout << "tid #" << std::this_thread::get_id() << " " << typeid(T).name() << "\n"; //dbg
#endif
		}

		~rand_state() = default;

		rand_state(const rand_state<T, TDistribution>&) = default;

		rand_state<T, TDistribution>& operator=(const rand_state<T, TDistribution>&) = default;

		T operator()() { return distr(tls_engine); }

		T min() const { return distr.min(); }

		T max() const { return distr.max(); }

	private:
		TDistribution<T> distr;		
	};

#if INT_RANDOM_UTIL_SLOTS_PER_THREAD > 0
	using int_slots = std::array<rand_state<>, INT_RANDOM_UTIL_SLOTS_PER_THREAD>;
	
	thread_local int_slots tls_int_random_util;
#endif

#if DOUBLE_RANDOM_UTIL_SLOTS_PER_THREAD > 0
	using double_rand_state = rand_state<double, std::uniform_real>;

	using double_slots = std::array<double_rand_state, DOUBLE_RANDOM_UTIL_SLOTS_PER_THREAD>;

	thread_local double_slots tls_double_random_util;	
#endif

}
#endif

#if INT_RANDOM_UTIL_SLOTS_PER_THREAD > 0 || DOUBLE_RANDOM_UTIL_SLOTS_PER_THREAD > 0
inline void seed_rand(size_t seed)
{
	internals::tls_engine = internals::random_engine(seed);
}
#endif

#if INT_RANDOM_UTIL_SLOTS_PER_THREAD > 0
inline void range_rand_int(int min_inclusive, int max_inclusive, internals::int_slots::size_type slot)
{
	assert(slot < INT_RANDOM_UTIL_SLOTS_PER_THREAD);
	internals::tls_int_random_util[slot] = internals::rand_state<>(min_inclusive, max_inclusive);
}

inline void range_rand_int(int min_inclusive, int max_inclusive)
{
	range_rand_int(min_inclusive, max_inclusive, 0);
}

inline int rand_int(internals::int_slots::size_type slot = 0)
{
	return internals::tls_int_random_util[slot].operator()();
}
#endif

#if DOUBLE_RANDOM_UTIL_SLOTS_PER_THREAD > 0
inline void range_rand_double(double min_inclusive, double max_exclusive, internals::double_slots::size_type slot)
{
	assert(slot < DOUBLE_RANDOM_UTIL_SLOTS_PER_THREAD);
	assert(min_inclusive < max_exclusive);
	internals::tls_double_random_util[slot] = internals::double_rand_state(min_inclusive, max_exclusive);
}

inline void range_rand_double(double min_inclusive, double max_exclusive)
{
	range_rand_double(min_inclusive, max_exclusive, 0);
}

inline double rand_double(internals::double_slots::size_type slot = 0)
{
	return internals::tls_double_random_util[slot].operator()();
}
#endif

#endif /* RANDOM_UTIL_HPP */
