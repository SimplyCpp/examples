#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include <vector>
#include <iostream>
#include <iomanip>
#include <utility>
#include <string>
#include <sstream>

std::vector<char> buffer_to_transmit(const std::wstring& s)
{
	std::vector<char> temp;
	size_t N = 2 * s.size();
	temp.resize(N);
	const char* ptr = reinterpret_cast<const char*>(s.c_str());
	std::copy(ptr, ptr + N, temp.begin());
	return std::move(temp);
}

std::vector<char> buffer_to_transmit(const std::string& s)
{
	std::vector<char> temp;
	size_t N = s.size();
	temp.resize(N);
	const char* ptr = s.c_str();
	std::copy(ptr, ptr + N, temp.begin());
	return std::move(temp);
}

std::string hex_rep(const std::vector<char>& xs)
{
	std::stringstream ss;
	ss << "Size: " << (xs.size()) << " bytes\n";
	for (char ch : xs)
	{
		short x = static_cast<short>(ch);
		if (x < 0) x -= 0xFF00;
		ss << std::setw(2)
			<< std::hex
			<< std::uppercase
			<< std::setfill('0')
			<< x;
	}
	return std::move(ss.str());
}

#endif //SUPPORT_HPP