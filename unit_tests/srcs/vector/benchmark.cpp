#include "../../hdrs/vector_utils.hpp"
#include <iostream>

#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define BENCHMARK_SIZE 1000000


TEST_CASE("Vector benchmarck", "[!hide][vector][benchmark]") {

	StdVec	sample_vec = Custom::mocking_value<StdVec>();

	SECTION("ft::vector write") {
		Vec	vec;

		for(size_t i = 0; i < REF_SIZE * 10; i++)
			vec.push_back("Sample sentence");

		for(size_t i = 0; i < REF_SIZE; i++)
			vec.insert(vec.begin() + vec.size() / 2, sample_vec.begin(), sample_vec.end());

		std::cout << BOLDBLUE << vec.size() << " elements were written in ft::vector using push_back() and insert()" << RESET << std::endl;
	}
	SECTION("std::vector write") {
		StdVec	vec;

		for(size_t i = 0; i < REF_SIZE * 10; i++)
			vec.push_back("Sample sentence");

		for(size_t i = 0; i < REF_SIZE; i++)
			vec.insert(vec.begin() + vec.size() / 2, sample_vec.begin(), sample_vec.end());

		std::cout << "\n" << BOLDGREEN << vec.size() << " elements were written in std::vector using push_back() and insert()" << RESET << std::endl;
	}

	StdVec	std_vec;
	for(size_t i = 0; i < BENCHMARK_SIZE; i++)
		std_vec.push_back(Custom::mocking_value<ValueType>());
	Vec		vec(std_vec.begin(), std_vec.end());

	SECTION("ft::vector erase") {
		while(vec.size() > 10)
			vec.erase(vec.begin() + vec.size() / 3, vec.begin() + vec.size() / 2);

		std::cout << "\n\n" << BOLDBLUE << BENCHMARK_SIZE - vec.size() << " elements were erased in ft::vector using erase()" << RESET << std::endl;
	}
	SECTION("std::vector erase") {
		while(std_vec.size() > 10)
			std_vec.erase(std_vec.begin() + std_vec.size() / 3, std_vec.begin() + std_vec.size() / 2);

		std::cout << "\n" << BOLDGREEN << BENCHMARK_SIZE - std_vec.size() << " elements were erased in std::vector using erase()" << RESET << std::endl;
	}
}

