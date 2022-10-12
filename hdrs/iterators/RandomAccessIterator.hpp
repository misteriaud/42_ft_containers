#pragma once
#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

#include "IteratorUtils.hpp"
#include "BidirectionalIterator.hpp"

namespace ft {
	template <typename T>
	class RandomAccessIterator {
		public:

			typedef RandomAccessIterator			it;
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::random_access_iterator_tag	iterator_category;

			RandomAccessIterator(): _elem(NULL) {};
			RandomAccessIterator(const pointer from): _elem(from) {};
			RandomAccessIterator(const RandomAccessIterator<typename remove_cv<T>::type>& src): _elem(&(*src)) {};
			~RandomAccessIterator() {};

			// Comp overloading
			bool					operator==(const it& rhs) const { return (_elem == rhs._elem); };
			bool					operator!=(const it& rhs) const { return (_elem != rhs._elem); };
			pointer					operator->() { return &(operator*()); };
			reference				operator*() const { return (*_elem); };
			reference				operator->() const { return (operator*()); };

			// Increment / decrement
			it&	operator++() { _elem++; return (*this);};
			it&	operator--() { _elem--; return (*this);};
			it	operator++(int) { it tmp = *this; _elem++; return (tmp);};
			it	operator--(int) { it tmp = *this; _elem--; return (tmp);};

			// arythmetic operator
			// a +/- n
			it	operator+(const difference_type a) const { it temp(*this); return temp += a; };
			it	operator-(const difference_type a) const { it temp(*this); return temp -= a; };

			// TO DEFINE LATER
			// a - b
			difference_type	operator-(const it& rhs) const { return (_elem - rhs._elem); }
			bool			operator<(const it& rhs) const { return (_elem < rhs._elem); };
			bool			operator>(const it& rhs) const { return (_elem > rhs._elem); };
			bool			operator<=(const it& rhs) const { return (_elem <= rhs._elem); };
			bool			operator>=(const it& rhs) const { return (_elem >= rhs._elem); };
			it&				operator+=(const difference_type diff) { _elem += diff; return (*this); };
			it&				operator-=(const difference_type diff) { _elem -= diff; return (*this); };
			reference		operator[](int index) { return (_elem[index]); };

		private:
			pointer	_elem;
	};
}

#endif
