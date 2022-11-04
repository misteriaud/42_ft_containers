#pragma once
#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

#include <cstddef>
#include "IteratorUtils.hpp"
#include "../SFINAE.hpp"

namespace ft {
	template <typename T>
	class RandomAccessIterator {
		private:
			typedef RandomAccessIterator<typename remove_cv<T>::type >	unconstIt;
			typedef RandomAccessIterator								it;

		public:
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;

			RandomAccessIterator(): _elem(NULL) {};
			RandomAccessIterator(const pointer from): _elem(from) {};
			RandomAccessIterator(const RandomAccessIterator<typename remove_cv<T>::type>& src): _elem(&(*src)) {};
			~RandomAccessIterator() {};
			it&	operator=(const it& rhs) {
				if (this == &rhs)
					return (*this);
				_elem = rhs._elem;
					return (*this);
			};

			// Comp overloading
			// Here we have to use friend keyword to be able to access to the protected attribute _elem of both of the iterators
			friend bool 		operator==(const it& lhs, const it& rhs) { return (lhs._elem == rhs._elem); };
			friend bool 		operator!=(const it& lhs, const it& rhs) { return (lhs._elem != rhs._elem); };
			friend bool			operator<(const it& lhs, const it& rhs) { return (lhs._elem < rhs._elem); };
			friend bool			operator>(const it& lhs, const it& rhs) { return (lhs._elem > rhs._elem); };
			friend bool			operator<=(const it& lhs, const it& rhs) { return (lhs._elem <= rhs._elem); };
			friend bool			operator>=(const it& lhs, const it& rhs) { return (lhs._elem >= rhs._elem); };


			pointer					operator->() { return &(operator*()); };
			reference				operator*() const { return (*_elem); };
			reference				operator->() const { return (operator*()); };
			reference				operator[](difference_type index) const { return (_elem[index]); };

			// Increment / decrement
			it&	operator++() { _elem++; return (*this);};
			it&	operator--() { _elem--; return (*this);};
			it	operator++(int) { it tmp = *this; _elem++; return (tmp);};
			it	operator--(int) { it tmp = *this; _elem--; return (tmp);};

			// TO DEFINE LATER
			// a - b
			difference_type	operator-(const it& rhs) const { return (_elem - rhs._elem); }
			it&				operator+=(const difference_type diff) { _elem += diff; return (*this); };
			it&				operator-=(const difference_type diff) {
				_elem -= diff;
				return (*this);
			};

		private:
			pointer	_elem;
	};

	template< typename T>
	RandomAccessIterator<T>	operator+(const RandomAccessIterator<T>& lhs, const typename RandomAccessIterator<T>::difference_type rhs) {
		RandomAccessIterator<T> temp(lhs);
		return temp += rhs;
	};

	template< typename T>
	RandomAccessIterator<T>	operator-(const RandomAccessIterator<T>& lhs, const typename RandomAccessIterator<T>::difference_type rhs) {
		RandomAccessIterator<T> temp(lhs);
		return temp -= rhs;
	};

	template< typename T>
	RandomAccessIterator<T>	operator+(const typename RandomAccessIterator<T>::difference_type lhs, const RandomAccessIterator<T>& rhs) {
		RandomAccessIterator<T> temp(rhs);
		return temp += lhs;
	};
	template< typename T>
	RandomAccessIterator<T>	operator-(const typename RandomAccessIterator<T>::difference_type lhs, const RandomAccessIterator<T>& rhs) {
		RandomAccessIterator<T> temp(rhs);
		return temp -= lhs;
	};
}

#endif
