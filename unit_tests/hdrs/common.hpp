#pragma once
#ifndef COMMON_HPP_123
# define COMMON_HPP_123

#ifdef DEBUG
# define NS std
#else
# define NS ft
#endif

#define VALUE_TYPE		std::string
#define KEY_TYPE		int
#define MAPPED_TYPE		std::string

//CONFIG
#define REF_SIZE 5000
// #define RANGE 500
#define FILE_PATH "./unit_test"

// INCLUDE OF CONTAINERS
#include <vector.hpp>
#include <vector>
#include <map.hpp>
#include <map>

// INCLUDE OF REQUIRED LIBS
#include <string>
#include <fstream>
#include <iterator>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

typedef VALUE_TYPE										ValueType;

typedef NS::vector<ValueType>							Vec;
typedef Vec::iterator									VecIt;
typedef Vec::const_iterator								VecConstIt;
typedef Vec::const_reverse_iterator						VecConstRevIt;

typedef std::vector<ValueType>							StdVec;
typedef std::vector<ValueType>::iterator				StdVecIt;
typedef std::vector<ValueType>::const_iterator			StdVecConstIt;
typedef std::vector<ValueType>::const_reverse_iterator	StdVecConstRevIt;


// typedef PAIR_TYPE										PairType;
typedef const KEY_TYPE									MapFirstType;
typedef MAPPED_TYPE										MapSecondType;

typedef NS::map<KEY_TYPE, MAPPED_TYPE, std::less<KEY_TYPE>, std::allocator<NS::pair<const KEY_TYPE, MAPPED_TYPE> > >		Map;
typedef Map::iterator									MapIt;
typedef Map::const_iterator								MapConstIt;
typedef Map::const_reverse_iterator						MapConstRevIt;
typedef NS::pair<const KEY_TYPE, MAPPED_TYPE>			MapPair;

typedef std::map<KEY_TYPE, MAPPED_TYPE, std::less<KEY_TYPE>, std::allocator<std::pair<const KEY_TYPE, MAPPED_TYPE> > >		StdMap;
typedef StdMap::iterator								StdMapIt;
typedef StdMap::const_iterator							StdMapConstIt;
typedef StdMap::const_reverse_iterator					StdMapConstRevIt;
typedef std::pair<const KEY_TYPE, MAPPED_TYPE>			StdMapPair;

#include "catch.hpp"
#include "outstream_operators.hpp"
#include "matchers.hpp"

template <typename T1, typename T2>
bool operator==(const ft::pair<const T1, T2>& lhs, const std::pair<const T1, T2>& rhs) {
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}
template <typename T1, typename T2>
bool operator==(const std::pair<const T1, T2>& lhs, const ft::pair<const T1, T2>& rhs) {
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

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

	// IS_INTEGRAL
	template<typename> struct is_integral: Custom::false_type {};

	template<> struct is_integral<bool>: Custom::true_type {};
	template<> struct is_integral<int>: Custom::true_type {};
	template<> struct is_integral<size_t>: Custom::true_type {};

	// IS VECTOR
	template <typename T>
	struct is_vector : Custom::false_type { };

	template <typename T>
	struct is_vector<std::vector<T> > : Custom::true_type { };
	template <typename T>
	struct is_vector<ft::vector<T> > : Custom::true_type { };

	// IS MAP
	template <typename T>
	struct is_map : Custom::false_type { };
	template <typename T1, typename T2, typename T3, typename T4>
	struct is_map<std::map<T1, T2, T3, T4> > : Custom::true_type { };
	template <typename T1, typename T2, typename T3, typename T4>
	struct is_map<ft::map<T1, T2, T3, T4> > : Custom::true_type { };

	// IS CONT
	template <typename T>
	struct is_cont : Custom::false_type { };
	template <typename T>
	struct is_cont<std::vector<T> > : Custom::true_type { };
	template <typename T>
	struct is_cont<ft::vector<T> > : Custom::true_type { };
	template <typename T1, typename T2, typename T3, typename T4>
	struct is_cont<std::map<T1, T2, T3, T4> > : Custom::true_type { };
	template <typename T1, typename T2, typename T3, typename T4>
	struct is_cont<ft::map<T1, T2, T3, T4> > : Custom::true_type { };

	// REMOVE CONST
	template< class T > struct remove_const                { typedef T type; };
	template< class T > struct remove_const<const T>       { typedef T type; };

//
//	GENERATOR
//
	template <typename T>
	typename Custom::enable_if<!Custom::is_cont<T>::value, T>::type
	mocking_value() {
		return (rand() % REF_SIZE);
	}

	template <>
	std::string mocking_value<std::string>();

	template <typename T>
	typename Custom::enable_if<Custom::is_vector<T>::value, T>::type
	mocking_value() {
		T		result;

		for (size_t i = 0; i < REF_SIZE; i++)
			result.push_back(Custom::mocking_value<typename T::value_type>());

		return (result);
	}

	template <typename T>
	typename Custom::enable_if<Custom::is_map<T>::value, T>::type
	mocking_value() {
		typedef typename T::value_type	value_type;
		typedef typename T::key_type	Key;
		typedef typename T::mapped_type	Value;

		T		result;

		for (size_t i = 0; i < REF_SIZE; i++)
			result.insert(
				value_type(
					Custom::mocking_value<Key>(),
					Custom::mocking_value<Value>()
				)
			);

		return (result);
	}


	template <typename T1, typename T2, typename T3, typename T4>
	void	copy_map(const std::map<T1, T2, T3, T4>& from, std::map<T1, T2, T3, T4>&	to) {
		to = from;
	}

	template <typename T1, typename T2, typename T3, typename T4,
				typename T5, typename T6, typename T7, typename T8>
	void	copy_map(const std::map<T1, T2, T3, T4>& from, ft::map<T5, T6, T7, T8>&	to) {
		typedef typename std::map<T1, T2, T3, T4>::const_iterator	const_it;
		typedef typename std::map<T1, T2, T3, T4>::key_type			first_type;
		typedef typename std::map<T1, T2, T3, T4>::mapped_type		second_type;

		to.clear();
		for (const_it it = from.begin(); it != from.end(); it++)
			to.insert(ft::pair<first_type, second_type>(it->first, it->second));
	}
}

#endif
