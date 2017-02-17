//Sample provided by Fabio Galuppo
//February 2017
//http://www.simplycpp.com

//compile clang++:
//clang++ -Wall -O2 -std=c++14 -o horner_method_program.exe horner_method_program.cpp

//compile g++:
//g++ -Wall -O2 -std=c++14 -o horner_method_program.exe horner_method_program.cpp

//compile msvc:
//cl.exe /EHsc /Ox /std:c++14 horner_method_program.cpp /link /out:horner_method_program.exe

template <typename T>
constexpr inline T axpy(T a, T x, T y)
{
	return a * x + y;
}

//Horner's method references: 
//https://en.wikipedia.org/wiki/Horner%27s_method  
//http://mathworld.wolfram.com/HornersMethod.html

/* overload resolution */
template <typename T>
constexpr inline double ov_horner_method(T x, T arg0, T arg1)
{
	return axpy(x, arg1, arg0);
}
	
template <typename T>
constexpr inline double ov_horner_method(T x, T arg0, T arg1, T arg2)
{
	return axpy(x, ov_horner_method(x, arg1, arg2), arg0);
}

template <typename T>
constexpr inline double ov_horner_method(T x, T arg0, T arg1, T arg2, T arg3)
{
	return axpy(x, ov_horner_method(x, arg1, arg2, arg3), arg0);
}
/* overload resolution */

/* variadic functions */
#include <cstdarg>

//an * x^n + ... + a2 * x^2 + a1 * x^1 + a0
//fold right: (x * (x * ((argn * x) + argm) + argo) ...)
template <typename T>
T va_horner_method(int n, T x, T argn, T argm, ...)
{
	T result = axpy(x, argn, argm);
	va_list args;
	va_start(args, argm);
	for (int i = 3; i < n; ++i)
	{
		T arg = va_arg(args, T);
		result = axpy(x, result, arg);		
	}
	va_end(args);
	return result;
}
/* variadic functions */

/* variadic templates */
template <typename T, typename... Ts> 
struct Horner
{
	constexpr static T apply(T x, T arg0, Ts... args)
	{
		return axpy(x, Horner<Ts...>::apply(x, args...), arg0);
	}
};

template <typename T>
struct Horner<T, T>
{
	constexpr static T apply(T x, T arg0, T arg1)
	{
		return axpy(x, arg1, arg0);
	}
};

//a0 + a1 * x^1  + a2 * x^2 + ... + an * x^n
//fold left: (x * (x * ((argn * x) + argm) + argo) ...)
template <typename T, typename... Ts> 
constexpr inline T horner_method(T x, Ts... args)
{
	return Horner<Ts...>::apply(x, args...);
}
/* variadic templates */

#include <iostream>
#include <iomanip>

void display(double value, const char* delimiter = "\t", int width = 6)
{
	std::cout.width(width);
	std::cout << std::right << value << delimiter;
}

int main()
{
	//overload resolution
	double ov0 = ov_horner_method(1.0, 2.0, 3.0);
	double ov1 = ov_horner_method(2.0, 2.0, 3.0, 4.0);
	double ov2 = ov_horner_method(2.0, 2.0, 3.0, 4.0, 5.0);
	double ov3 = ov_horner_method(3.0, 2.0, 3.0, 4.0, 5.0);
	display(ov0); display(ov1); display(ov2); display(ov3, "\n");
	
	//variadic templates
	double vt0 = Horner<double, double, double>::apply(2.0, 2.0, 3.0, 4.0);
	double vt1 = Horner<double, double, double, double>::apply(2.0, 2.0, 3.0, 4.0, 5.0);
	display(vt0); display(vt1, "\n");
	double vth0 = horner_method(1.0, 2.0, 3.0);
	double vth1 = horner_method(2.0, 2.0, 3.0, 4.0);
	double vth2 = horner_method(2.0, 2.0, 3.0, 4.0, 5.0);
	double vth3 = horner_method(3.0, 2.0, 3.0, 4.0, 5.0);
	display(vth0); display(vth1); display(vth2); display(vth3, "\n");

	//variadic functions
	double va0 = va_horner_method(3, 1.0, 2.0, 3.0);
	double va1 = va_horner_method(4, 2.0, 2.0, 3.0, 4.0);
	double va2 = va_horner_method(5, 2.0, 2.0, 3.0, 4.0, 5.0);
	double va3 = va_horner_method(5, 3.0, 2.0, 3.0, 4.0, 5.0);
	display(va0); display(va1); display(va2); display(va3, "\n");
}