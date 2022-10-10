#pragma once
#ifndef SFINAE_HPP
# define SFINAE_HPP

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


	// IS_INTEGRAL
	struct false_type {
		static const bool value = false;
	};
	struct true_type {
		static const bool value = true;
	};

	template<typename> struct is_integral_base : false_type {};

	template<> struct is_integral_base<bool>: true_type {};
	template<> struct is_integral_base<int>: true_type {};
	template<> struct is_integral_base<short>: true_type {};

	template<typename T> struct is_integral: is_integral_base< typename ft::remove_cv<T>::type > {};

}

#endif
