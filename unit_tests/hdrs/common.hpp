#pragma once
#ifndef COMMON_HPP_123
# define COMMON_HPP_123

#include "catch.hpp"

//CONFIG
#define REF_SIZE 500
#define RANGE 500

// INCLUDE OF CONTAINERS
#include <vector.hpp>
#include <vector>

// INCLUDE OF REQUIRED LIBS
#include <string>
#include <fstream>
#include <iterator>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using MyTypes = std::tuple<int, std::string>;
// using MyTypes = std::tuple<int, std::string, std::vector<int>, ft::vector<int>>;

template <typename T1, typename T2>
bool same_vec(const T1& vec1, const T2& vec2) {
	if (vec1.size() != vec2.size())
		return (false);
	return (ft::equal(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));
}

// IS VECTOR
template <typename T>
struct is_vector : ft::false_type { };

template <typename T>
struct is_vector<std::vector<T> > : ft::true_type { };
template <typename T>
struct is_vector<ft::vector<T> > : ft::true_type { };

template <typename T, typename ft::enable_if<!is_vector<T>::value, int>::type =0>
T mocking_value() {
	return (rand() % 500);
}

template <>
std::string mocking_value<std::string>();


template <typename T, typename ft::enable_if<is_vector<T>::value, int>::type =0>
T	mocking_value() {
	size_t	vector_size = 10;
	T		result;

	for (size_t i = 0; i < vector_size; i++)
		result.push_back(mocking_value<typename T::value_type>());

	return (result);
}

#endif
