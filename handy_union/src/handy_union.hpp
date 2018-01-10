//Sample provided by Fabio Galuppo
//January 2018
//http://www.simplycpp.com

#ifndef HANDY_UNION_HPP
#define HANDY_UNION_HPP

#include <cstddef>

template<typename T>
struct handy_union final
{
	handy_union() = default;
	handy_union(const handy_union&) = default;
	handy_union& operator=(const handy_union&) = default;
	~handy_union() = default;
	
	handy_union(T value) : value(value) {}

	constexpr std::size_t size() const { return sizeof(T); }

	operator T() const { return value; }

	union
	{
		unsigned char bytes[sizeof(T)];
		T value;
	};
};

#endif /* HANDY_UNION_HPP */