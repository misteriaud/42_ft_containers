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
			typedef typename ft::BidirectionalIterator<T>::difference_type	difference_type;

			RandomAccessIterator(): BidirectionalIterator<T>() {};
			RandomAccessIterator(T* from): BidirectionalIterator<T>(from) {};
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
			T&		operator[](int index) {
				return (this->_elem[index]);
			};
	};

	// template <typename T>
	// class RandomAccessIterator<const T>: public BidirectionalIterator<const T> {
	// 	RandomAccessIterator(): BidirectionalIterator<T> {};
	// 	RandomAccessIterator(const RandomAccessIterator& from): BidirectionalIterator<T>(from) {};
	// 	virtual ~RandomAccessIterator() {};
	// };
}

#endif
