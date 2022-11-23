#pragma once
#ifndef STACK_UNIT_TEST_HPP
# define STACK_UNIT_TEST_HPP

#include "common.hpp"

#include <stack.hpp>
#include <stack>

typedef	Vec										StackCont;
typedef	StdVec									StdStackCont;

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


	template<typename T>
	class MutantStack : public Stack
	{
	public:
		MutantStack(const Stack& ref): Stack(ref) {}
		~MutantStack() {}

		const StackCont& get_cont() const {
			return (this->c);
		}
	};

	template<typename T>
	class StdMutantStack : public StdStack
	{
	public:
		StdMutantStack(const StdStack& ref): StdStack(ref) {}
		~StdMutantStack() {}

		const StdStackCont& get_cont() const {
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
			const StdStackCont&	std_cont = Custom::StdMutantStack<StdStackCont>(m_comparator).get_cont();
			const StackCont&		cont = Custom::MutantStack<StackCont>(v).get_cont();

			typename StackCont::const_iterator mapFirst = cont.begin(), mapLast = cont.end();
			typename StdStackCont::const_iterator refFirst = std_cont.begin(), refLast = std_cont.end();

			while (mapFirst!=mapLast && refFirst!=refLast) {
				if (*mapFirst != *refFirst)
					return false;
				++mapFirst; ++refFirst;
			}
			if (mapFirst == mapLast && refFirst == refLast)
				return true;
			return false;
		}
		std::string describe() const {
			std::ostringstream ss;
			ss << "\nEquality between ft::stack && std::stack: \n";

			// IF YOU GET A COMPILATION ERROR HERE, NEED TO IMPLEMENT : `std::ostream& operator<< (std::ostream& out, const YourType& rhs)`
			ss << Catch::StringMaker<StdStackCont>::convert(Custom::StdMutantStack<StdStackCont>(m_comparator).get_cont());
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
