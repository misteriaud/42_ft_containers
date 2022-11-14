#pragma once
#ifndef OUTSTREAM_OPERATORS
# define OUTSTREAM_OPERATORS

#include <iostream>
#include <vector>

#include <vector.hpp>

namespace Catch {

	template<typename T> struct StringMaker<std::vector<T> > {
		static std::string convert(std::vector<T> const& value ) {
			std::string	out;
			typename std::vector<T>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += "\"" + *it + "\"";
			it++;
			for (; it != value.end(); it++)
				out += ", \"" + *it + "\"";
			out += " }\n";
			return (out);
		}
	};

	template<typename T> struct StringMaker<ft::vector<T> > {
		static std::string convert(ft::vector<T> const& value ) {
			std::string	out;
			typename ft::vector<T>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += "\"" + *it + "\"";
			it++;
			for (; it != value.end(); it++)
				out += ", \"" + *it + "\"";
			out += " }\n";
			return (out);
		}
	};
}

#endif
