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
			typedef typename ft::map<T1, T2, T3, T4>::value_type::first_type first_type;
			typedef typename ft::map<T1, T2, T3, T4>::value_type::second_type second_type;

			std::string	out;
			typename ft::map<T1, T2, T3, T4>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += "[\"";
			out += Catch::StringMaker<first_type>::convert(it->first);
			out += "\", ";
			out += Catch::StringMaker<second_type>::convert(it->second);
			out += "]";
			it++;
			for (; it != value.end(); it++) {
				out += ", [\"";
				out += Catch::StringMaker<first_type>::convert(it->first);
				// out += it->first;
				out += "\", ";
				out += Catch::StringMaker<second_type>::convert(it->second);
				// out += it->second;
				out += "]";
			}
			out += " }";
			return (out);
		}
	};

	template<typename T1, typename T2, typename T3, typename T4>
	struct StringMaker<std::map<T1, T2, T3, T4> > {
		static std::string convert(std::map<T1, T2, T3, T4> const& value ) {
			typedef typename std::map<T1, T2, T3, T4>::value_type::first_type first_type;
			typedef typename std::map<T1, T2, T3, T4>::value_type::second_type second_type;

			std::string	out;
			typename std::map<T1, T2, T3, T4>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += "[\"";
			out += Catch::StringMaker<first_type>::convert(it->first);
			out += "\", ";
			out += Catch::StringMaker<second_type>::convert(it->second);
			out += "]";
			it++;
			for (; it != value.end(); it++) {
				out += ", [\"";
				out += Catch::StringMaker<first_type>::convert(it->first);
				// out += it->first;
				out += "\", ";
				out += Catch::StringMaker<second_type>::convert(it->second);
				// out += it->second;
				out += "]";
			}
			out += " }";
			return (out);
		}
	};
}

#endif
