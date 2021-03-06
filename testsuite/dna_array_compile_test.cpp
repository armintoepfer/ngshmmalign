#include <cstdint>
#include <iostream>

#include <dna_array.hpp>
#include <utility_functions.hpp>

int main()
{
	dna_array<double, 5> arr_double = { 1.0, 2.0, 3.0, 4.0 };
	dna_array<int, 5> arr_int = { -1, -2, -3, -4 };
	std::cout << arr_double << '\n';
	std::cout << arr_int << '\n';

	dna_array<double, 5> arr_double2(std::move(arr_double));
	std::cout << arr_double2 << '\n';

	dna_array<int, 5> arr_int2(arr_double2);
	std::cout << arr_int2 << '\n';

	return 0;
}