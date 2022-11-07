#pragma once
#ifndef SFINAE_HPP
# define SFINAE_HPP

#include "pair.hpp"

namespace ft {

	// REMOVE POSSIBLE Const, Volatile, Const Volatile
	template< class T > struct remove_cv                   { typedef T type; };
	template< class T > struct remove_cv<const T>          { typedef T type; };
	template< class T > struct remove_cv<volatile T>       { typedef T type; };
	template< class T > struct remove_cv<const volatile T> { typedef T type; };

	template< class T > struct remove_const                { typedef T type; };
	template< class T > struct remove_const<const T>       { typedef T type; };

	template< class T > struct remove_volatile             { typedef T type; };
	template< class T > struct remove_volatile<volatile T> { typedef T type; };


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
	template<typename> struct is_integral_base : false_type {};

	template<> struct is_integral_base<bool>: true_type {};
	template<> struct is_integral_base<int>: true_type {};
	template<> struct is_integral_base<short>: true_type {};

	template<typename T> struct is_integral: is_integral_base< typename ft::remove_cv<T>::type > {};


	// CONDITIONAL
	template<bool B, class T, class F>
	struct conditional { typedef T type; };

	template<class T, class F>
	struct conditional<false, T, F> { typedef F type; };

	// IS CONST
	template<class T> struct is_const          : false_type {};
	template<class T> struct is_const<const T> : true_type {};

	template<class T> struct add_cv { typedef const volatile T type; };

	template<class T> struct add_const { typedef const T type; };

	template<class T> struct add_volatile { typedef volatile T type; };


	// IS PAIR
	template <typename T>
	struct is_pair : false_type { };

	template <typename T1, typename T2>
	struct is_pair<ft::pair<T1,T2> > : true_type { };

}

#endif
