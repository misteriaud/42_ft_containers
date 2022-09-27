#pragma once
#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

#include "IteratorUtils.hpp"
#include "BidirectionalIterator.hpp"

namespace ft {
	template <typename T>
	class RandomAccessIterator: public BidirectionalIterator<T> {
		public:

			typedef ft::random_access_iterator_tag							iterator_category;
			typedef RandomAccessIterator									it;
			using typename ft::BidirectionalIterator<T>::difference_type;
			using typename ft::BidirectionalIterator<T>::value_type;
			using typename ft::BidirectionalIterator<T>::pointer;
			using typename ft::BidirectionalIterator<T>::reference;

			RandomAccessIterator(): BidirectionalIterator<T>() {};
			RandomAccessIterator(pointer from): BidirectionalIterator<T>(from) {};
			RandomAccessIterator(const RandomAccessIterator& from): BidirectionalIterator<T>(from) {};
			virtual ~RandomAccessIterator() {};

			// arythmetic operator
			// a + n
			it	operator+(const difference_type a) const {
				it temp(*this);
				return temp += a;
			};
			// a - n
			it	operator-(const difference_type a) const {
				it temp(*this);
				return temp -= a;
			};

			// TO DEFINE LATER
			// a - b
			difference_type	operator-(const it& rhs) const {
				return (this->_elem - rhs._elem);
			}
			bool	operator<(const it& rhs) {
				return (this->_elem < rhs._elem);
			};
			bool	operator>(const it& rhs) {
				return (this->_elem > rhs._elem);
			};
			bool	operator<=(const it& rhs) {
				return (this->_elem <= rhs._elem);
			};
			bool	operator>=(const it& rhs) {
				return (this->_elem >= rhs._elem);
			};
			it&		operator+=(const difference_type diff) {
				this->_elem += diff;
				return (*this);
			};
			it&		operator-=(const difference_type diff) {
				this->_elem -= diff;
				return (*this);
			};
			reference	operator[](int index) {
				return (this->_elem[index]);
			};
			const reference		operator[](int index) const {
				return (this->_elem[index]);
			};
	};
}

#endif
