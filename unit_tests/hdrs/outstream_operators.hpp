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
			out += " }";
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
			out += " }";
			return (out);
		}
	};


	template<typename T1, typename T2, typename T3, typename T4>
	struct StringMaker<ft::map<T1, T2, T3, T4> > {
		static std::string convert(ft::map<T1, T2, T3, T4> const& value ) {
			typedef typename ft::pair<const T1, T2> pair_type;

			std::string	out;
			typename ft::map<T1, T2, T3, T4>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += Catch::StringMaker<pair_type>::convert(*it);
			it++;
			for (; it != value.end(); it++) {
				out += ", ";
				out += Catch::StringMaker<pair_type>::convert(*it);
			}
			return (out);
		}
	};

	template<typename T1, typename T2, typename T3, typename T4>
	struct StringMaker<std::map<T1, T2, T3, T4> > {
		static std::string convert(std::map<T1, T2, T3, T4> const& value ) {
			typedef typename std::pair<const T1, T2> pair_type;

			std::string	out;
			typename std::map<T1, T2, T3, T4>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += Catch::StringMaker<pair_type>::convert(*it);
			it++;
			for (; it != value.end(); it++) {
				out += ", ";
				out += Catch::StringMaker<pair_type>::convert(*it);
			}
			out += " }";
			return (out);
		}
	};

	// PAIR
	template<typename T1, typename T2>
	struct StringMaker<std::pair<T1, T2> > {
		static std::string convert(std::pair<T1, T2> const& value ) {
			typedef typename std::pair<T1, T2>::first_type	first_type;
			typedef typename std::pair<T1, T2>::second_type	second_type;
			std::string	out;

			out += "[\"";
			out += Catch::StringMaker<first_type>::convert(value.first);
			out += "\", ";
			out += Catch::StringMaker<second_type>::convert(value.second);
			out += "]";
			return (out);
		}
	};
	template<typename T1, typename T2>
	struct StringMaker<ft::pair<T1, T2> > {
		static std::string convert(ft::pair<T1, T2> const& value ) {
			typedef typename ft::pair<T1, T2>::first_type	first_type;
			typedef typename ft::pair<T1, T2>::second_type	second_type;
			std::string	out;

			out += "[\"";
			out += Catch::StringMaker<first_type>::convert(value.first);
			out += "\", ";
			out += Catch::StringMaker<second_type>::convert(value.second);
			out += "]";
			return (out);
		}
	};
}

#endif
