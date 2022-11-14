#pragma once
#ifndef OUTSTREAM_OPERATORS
# define OUTSTREAM_OPERATORS

#include <iostream>
#include <vector>

#include <vector.hpp>


template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& lhs) {
	out << "{ ";
	for (StdVecConstIt it = lhs.begin(); it != lhs.end(); it++)
		out << "\"" << *it << "\", ";
	out << " }" << std::endl;

	return (out);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, ft::vector<T> const& lhs) {
	out << "{ ";
	for (typename ft::vector<T>::iterator it = lhs.begin(); it != lhs.end(); it++)
		out << "\"" << *it << "\", ";
	out << " }" << std::endl;

	return (out);
}

#endif
