#pragma once
#ifndef STACK_UNIT_TEST_HPP
# define STACK_UNIT_TEST_HPP

#include "common.hpp"
#include "vector_utils.hpp"

#include <stack.hpp>
#include <stack>

typedef	std::vector<ValueType>					StackCont;
typedef	std::vector<ValueType>					StdStackCont;

typedef NS::stack<ValueType, StackCont >		Stack;
typedef std::stack<ValueType, StdStackCont >	StdStack;

namespace Custom {
	// IS CONTAINER
	template <typename T>
	struct is_cont<std::stack<T> > : Custom::true_type { };
	template <typename T>
	struct is_cont<ft::stack<T> > : Custom::true_type { };
	// IS STACK
	template <typename T>
	struct is_stack : Custom::false_type { };
	template <typename T>
	struct is_stack<std::stack<T> > : Custom::true_type { };
	template <typename T>
	struct is_stack<ft::stack<T> > : Custom::true_type { };

	// GENERATOR
	template <typename T>
	typename Custom::enable_if<Custom::is_stack<T>::value, T>::type
	mocking_value() {
		T		result;

		for (size_t i = 0; i < REF_SIZE; i++)
			result.push(Custom::mocking_value<typename T::value_type>());

		return (result);
	}


	template<typename StackType>
	class MutantStack : public StackType
	{
	public:
		MutantStack(const StackType& ref): StackType(ref) {}
		~MutantStack() {}

		typedef typename StackType::container_type	container_type;

		const container_type& get_cont() const {
			return (this->c);
		}
	};

	//
	// EQUALITY CHECKS
	//
	template<typename StackType>
	class StackEqual : public Catch::MatcherBase<StackType> {
	public:

		StackEqual(StdStack const &comparator) : m_comparator( comparator ) {}

		bool match(StackType const &v) const {
			const Custom::MutantStack<StdStack>	std_mutant(m_comparator);
			const Custom::MutantStack<Stack>	mutant(v);
			const StdStackCont&					std_cont = std_mutant.get_cont();
			const StackCont&					cont = mutant.get_cont();

			typename StackCont::const_iterator stackFirst = cont.begin(), stackLast = cont.end();
			typename StdStackCont::const_iterator refFirst = std_cont.begin(), refLast = std_cont.end();

			while (stackFirst!=stackLast && refFirst!=refLast) {
				if (*stackFirst != *refFirst)
					return false;
				++stackFirst; ++refFirst;
			}
			if (stackFirst == stackLast && refFirst == refLast)
				return true;
			return false;
		}
		std::string describe() const {
			std::ostringstream ss;
			ss << "\nEquality between ft::stack && std::stack: \n";

			// IF YOU GET A COMPILATION ERROR HERE, NEED TO IMPLEMENT : `std::ostream& operator<< (std::ostream& out, const YourType& rhs)`
			ss << Catch::StringMaker<StdStackCont>::convert(Custom::MutantStack<StdStack>(m_comparator).get_cont());
			return ss.str();
		}
		StdStack const& m_comparator;
	};
}


//
// StringMaker
//
namespace Catch {

	// // StringMaker
	// template<typename T> struct StringMaker<std::stack<T> > {
	// 	static std::string convert(std::stack<T> const& value ) {
	// 		std::string	out;

	// 		if (it == value.end())
	// 			return (out);
	// 		out += "{ ";
	// 		out += "\"" + *it + "\"";
	// 		it++;
	// 		for (; it != value.end(); it++)
	// 			out += ", \"" + *it + "\"";
	// 		out += " }";
	// 		return (out);
	// 	}
	// };

	// template<>
	// struct StringMaker<StackCont > {
	// 	static std::string convert(StackCont const& value ) {

	// 		return (Catch::StringMaker<StackCont>::convert(Custom::MutantStack<StackCont>(value).get_cont()));
	// 		// typename ft::stack<T>::const_iterator it = value.begin();

	// 		// if (it == value.end())
	// 		// 	return (out);
	// 		// out += "{ ";
	// 		// out += "\"" + *it + "\"";
	// 		// it++;
	// 		// for (; it != value.end(); it++)
	// 		// 	out += ", \"" + *it + "\"";
	// 		// out += " }";
	// 		// return (out);
	// 	}
	// };
}

#endif
