#include <DriverLA\LongInt.h>

#include <iostream>

using LA::operator""_lint;

int main()
{
	auto a = 9_lint;
	std::cout << std::sqrt(a);
	return 0;
}