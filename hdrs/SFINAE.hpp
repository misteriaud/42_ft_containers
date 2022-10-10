#pragma once
#ifndef SFINAE_HPP
# define SFINAE_HPP

namespace ft {

	template <bool Cond, typename Result=void>
	struct enable_if { };

	template <typename Result>
	struct enable_if<true, Result> {
		using type = Result;
	};

	template<typename> struct is_integral_base: std::false_type {};

	template<> struct is_integral_base<bool>: std::true_type {};
	template<> struct is_integral_base<int>: std::true_type {};
	template<> struct is_integral_base<short>: std::true_type {};

	template<typename T> struct is_integral: is_integral_base<std::remove_cv_t<T>> {};

}

#endif
