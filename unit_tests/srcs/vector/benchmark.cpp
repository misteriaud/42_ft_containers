#include "../../hdrs/vector_utils.hpp"
#include <iostream>

#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


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
}

