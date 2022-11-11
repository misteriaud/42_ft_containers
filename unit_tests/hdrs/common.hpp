#pragma once
#ifndef COMMON_HPP_123
# define COMMON_HPP_123

#ifdef DEBUG
# define CONTAINER_TYPES (std::vector, ft::vector)
#else
# define CONTAINER_TYPES (ft::vector)
#endif

#define VALUE_TYPES (int, std::string)
// #define VALUE_TYPES (int, std::string, std::vector<int>, ft::vector<std::string>)

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

template <typename T>
std::vector<T>	generate_vec(){
	std::vector<T>	range;
	for (size_t i = 0; i < REF_SIZE; i++)
		range.push_back(mocking_value<T>());
	return range;
}

// MATCHER
template<typename VectorType>
class VectorEqual : public Catch::MatcherBase<VectorType> {
public:
	typedef typename VectorType::value_type		ValueType;
	typedef typename VectorType::allocator_type	AllocComp;


	VectorEqual(std::vector<ValueType, AllocComp> const &comparator) : m_comparator( comparator ) {}

	bool match(VectorType const &v) const override{
		// !TBD: This currently works if all elements can be compared using !=
		// - a more general approach would be via a compare template that defaults
		// to using !=. but could be specialised for, e.g. std::vector<T, Alloc> etc
		// - then just call that directly
		if (m_comparator.size() != v.size())
			return false;
		for (std::size_t i = 0; i < v.size(); ++i)
			if (m_comparator[i] != v[i])
				return false;
		return true;
	}
	std::string describe() const {
		// return "ft::vector is equal to std::vector\n";
		return "Equals: " + ::Catch::Detail::stringify( m_comparator );
	}
	std::vector<ValueType, AllocComp> const& m_comparator;
};

#endif
