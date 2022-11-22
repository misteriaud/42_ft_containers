#pragma once
#ifndef SET_UNIT_TEST_HPP
# define SET_UNIT_TEST_HPP

#include "common.hpp"

#include <set.hpp>
#include <set>
typedef NS::set<ValueType, std::less<ValueType>, std::allocator<ValueType> >	Set;
typedef Set::iterator															SetIt;
typedef Set::const_iterator														SetConstIt;
typedef Set::const_reverse_iterator												SetConstRevIt;

typedef std::set<ValueType, std::less<ValueType>, std::allocator<ValueType> >	StdSet;
typedef StdSet::iterator														StdSetIt;
typedef StdSet::const_iterator													StdSetConstIt;
typedef StdSet::const_reverse_iterator											StdSetConstRevIt;

namespace Custom {
	// IS CONTAINER
	template <typename T1, typename T2, typename T3>
	struct is_cont<std::set<T1, T2, T3> > : Custom::true_type { };
	template <typename T1, typename T2, typename T3>
	struct is_cont<ft::set<T1, T2, T3> > : Custom::true_type { };
	// IS VECTOR
	template <typename T>
	struct is_set : Custom::false_type { };
	template <typename T1, typename T2, typename T3>
	struct is_set<std::set<T1, T2, T3> > : Custom::true_type { };
	template <typename T1, typename T2, typename T3>
	struct is_set<ft::set<T1, T2, T3> > : Custom::true_type { };

	// GENERATOR
	template <typename T>
	typename Custom::enable_if<Custom::is_set<T>::value, T>::type
	mocking_value() {
		T		result;

		for (size_t i = 0; i < REF_SIZE; i++)
			result.insert(Custom::mocking_value<typename T::key_type>());

		return (result);
	}


	//
	// EQUALITY CHECKS
	//
	template<typename SetType>
	class SetEqual : public Catch::MatcherBase<SetType> {
	public:

		// typedef typename SetType::value_type		value_type;
		// typedef typename SetType::value_compare		compare_type;
		// typedef typename SetType::allocator_type	allocator_type;
		// typedef std::set<value_type, compare_type, allocator_type>	std_set_type;

		SetEqual(StdSet const &comparator) : std_set(&comparator), ft_set(NULL) {}
		SetEqual(Set const &comparator) : std_set(NULL), ft_set(&comparator) {}

		bool match(SetType const &v) const {
			if (std_set) {
				SetConstIt mapFirst = v.begin(), mapLast = v.end();
				StdSetConstIt refFirst = std_set->begin(), refLast = std_set->end();
				// typename SetType::const_iterator mapFirst = v.begin(), mapLast = v.end();
				// typename std_set_type::const_iterator refFirst = std_set->begin(), refLast = std_set->end();

				while (mapFirst!=mapLast && refFirst!=refLast) {
					if (*mapFirst != *refFirst)
						return false;
					++mapFirst; ++refFirst;
				}
				if (mapFirst == mapLast && refFirst == refLast)
					return true;
				return false;
			}
			else {
				SetConstIt mapFirst = v.begin(), mapLast = v.end();
				SetConstIt refFirst = ft_set->begin(), refLast = ft_set->end();

				while (mapFirst!=mapLast && refFirst!=refLast) {
					if (*mapFirst != *refFirst)
						return false;
					++mapFirst; ++refFirst;
				}
				if (mapFirst == mapLast && refFirst == refLast)
					return true;
				return false;
			}
		}
		std::string describe() const {
			std::ostringstream ss;
			ss << "\nEquality between ft::vector && std::vector: \n";

			if (std_set)
				ss << Catch::StringMaker<StdSet>::convert(*std_set);
			else
				ss << Catch::StringMaker<Set>::convert(*ft_set);
			return ss.str();
		}
		StdSet const	*std_set;
		Set const		*ft_set;
	};
}
#endif
