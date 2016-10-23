//Sample provided by Fabio Galuppo 
//October 2016
//http://www.simplycpp.com 

#ifndef RANDOM_REAL_UTIL_HPP
#define RANDOM_REAL_UTIL_HPP

#include "random_engine_util.hpp"
#include <type_traits>

namespace internals
{
	template<typename Real>
	using real_distribution = std::uniform_real_distribution<Real>; //default real distribution

	template<typename Real>
	struct rand_real_func
	{
		static_assert(std::is_floating_point<Real>::value, "Real must be an floating point type");

		real_distribution<Real> distribution;

		Real operator()()
		{
			return distribution(rand_engine());
		}

		//compatible with uniform_real_distribution (our default real_distribution)
		Real operator()(Real min_inclusive, Real max_exclusive)
		{
			using param_type = typename real_distribution<Real>::param_type;
			return distribution(rand_engine(), param_type(min_inclusive, max_exclusive));
		}

		Real operator()(typename real_distribution<Real>::param_type params)
		{
			return distribution(rand_engine(), params);
		}
	};

	template<typename Real>
	inline rand_real_func<Real>& get_rand_real()
	{
		static thread_local rand_real_func<Real> rand_real;
		return rand_real;
	}
}

template<typename Real>
inline Real rand_real()
{
	return internals::get_rand_real<Real>()();
}

//compatible with uniform_real_distribution
template<typename Real>
inline Real rand_real(Real min_inclusive, Real max_exclusive)
{
	return internals::get_rand_real<Real>()(min_inclusive, max_exclusive);
}

template<typename Real>
inline Real rand_real(typename internals::real_distribution<Real>::param_type params)
{
	return internals::get_rand_real<Real>()(params);
}

inline double rand_double()
{
	return rand_real<double>();
}

inline double rand_double(double min_inclusive, double max_exclusive)
{
	return rand_real<>(min_inclusive, max_exclusive);
}

#endif /* RANDOM_REAL_UTIL_HPP */