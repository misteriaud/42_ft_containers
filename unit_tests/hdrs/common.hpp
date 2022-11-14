#pragma once
#ifndef COMMON_HPP_123
# define COMMON_HPP_123

#ifdef DEBUG
# define CONTAINER_TYPE std::vector
#else
# define CONTAINER_TYPE ft::vector
#endif

#define VALUE_TYPE int
// #define VALUE_TYPE std::vector<int>

//CONFIG
#define REF_SIZE 500
#define RANGE 500
#define FILE_PATH "./unit_test"

// INCLUDE OF CONTAINERS
#include <vector.hpp>
#include <vector>
// INCLUDE OF REQUIRED LIBS
#include <string>
#include <fstream>
#include <iterator>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

typedef VALUE_TYPE													TestValueType;

typedef CONTAINER_TYPE<TestValueType>						TestContainerType;
typedef TestContainerType::iterator							TestIt;
typedef TestContainerType::const_iterator					TestConstIt;
typedef TestContainerType::const_reverse_iterator			TestConstRevIt;


typedef std::vector<TestValueType>							StdVec;
typedef std::vector<TestValueType>::iterator				StdVecIt;
typedef std::vector<TestValueType>::const_iterator			StdVecConstIt;
typedef std::vector<TestValueType>::const_reverse_iterator	StdVecConstRevIt;

#include "outstream_operators.hpp"
#include "catch.hpp"

namespace Custom {

	template <class InputIterator1, class InputIterator2>
	bool equal( InputIterator1 first1, InputIterator1 last1,
					InputIterator2 first2, InputIterator2 last2) {
		while (first1!=last1 && first2!=last2) {
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		if (first1 == last1 && first2 == last2)
			return true;
		return false;
	};

	template <typename T1, typename T2>
	bool same_vec(const T1& vec1, const T2& vec2) {
		if (vec1.size() != vec2.size())
			return (false);
		return (Custom::equal(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));
	}


//
//	SFINAE
//
	// ENABLE IF
	template <bool Cond, typename Result=void>
	struct enable_if { };

	template <typename Result>
	struct enable_if<true, Result> {
		typedef Result	type;
	};

	struct false_type { static const bool value = false; };
	struct true_type { static const bool value = true; };

	// IS VECTOR
	template <typename T>
	struct is_vector : Custom::false_type { };

	template <typename T>
	struct is_vector<std::vector<T> > : Custom::true_type { };
	template <typename T>
	struct is_vector<ft::vector<T> > : Custom::true_type { };


//
//	GENERATOR
//
	template <typename T>
	typename Custom::enable_if<!Custom::is_vector<T>::value, T>::type
	mocking_value() {
		return (rand() % 500);
	}

	template <>
	std::string mocking_value<std::string>();


	template <typename T>
	typename Custom::enable_if<Custom::is_vector<T>::value, T>::type
	mocking_value() {
		size_t	vector_size = 10;
		T		result;

		for (size_t i = 0; i < vector_size; i++)
			result.push_back(Custom::mocking_value<typename T::value_type>());

		return (result);
	}

	template <typename T>
	std::vector<T>	generate_vec(){
		std::vector<T>	range;
		for (size_t i = 0; i < REF_SIZE; i++)
			range.push_back(Custom::mocking_value<T>());
		return range;
	}


//
// MATCHER
//
	template<typename VectorType>
	class VectorEqual : public Catch::MatcherBase<VectorType> {
	public:
		typedef typename VectorType::value_type		ValueType;
		typedef typename VectorType::allocator_type	AllocComp;


		VectorEqual(std::vector<ValueType, AllocComp> const &comparator) : m_comparator( comparator ) {}

		bool match(VectorType const &v) const {
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
			std::ostringstream ss;
			ss << "\nEquality between ft::vector && std::vector: \n";

			// IF YOU GET A COMPILATION ERROR HERE, NEED TO IMPLEMENT : `std::ostream& operator<< (std::ostream& out, const YourType& rhs)`
			ss << m_comparator;
			return ss.str();
		}
		std::vector<ValueType, AllocComp> const& m_comparator;
	};

}

#endif
