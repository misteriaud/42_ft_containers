#pragma once
#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

#include "IteratorUtils.hpp"
#include "BidirectionalIterator.hpp"

namespace ft {
	template <typename T, typename It>
	class RandomAccessIterator: public BidirectionalIterator<T, It> {
		public:

			typedef ft::random_access_iterator_tag							iterator_category;
			using typename ft::BidirectionalIterator<T, It>::difference_type;
			using typename ft::BidirectionalIterator<T, It>::value_type;
			using typename ft::BidirectionalIterator<T, It>::pointer;
			using typename ft::BidirectionalIterator<T, It>::reference;

			RandomAccessIterator(): BidirectionalIterator<T, It>() {};
			RandomAccessIterator(const pointer from): BidirectionalIterator<T, It>(from) {};
			RandomAccessIterator(const It& from): BidirectionalIterator<T, It>(from) {};
			virtual ~RandomAccessIterator() {};

			// arythmetic operator
			// a +/- n
			virtual It	operator+(const difference_type a) const = 0;
			virtual It	operator-(const difference_type a) const = 0;

			// TO DEFINE LATER
			// a - b
			virtual difference_type	operator-(const It& rhs) const = 0;
			virtual bool			operator<(const It& rhs) const = 0;
			virtual bool			operator>(const It& rhs) const = 0;
			virtual bool			operator<=(const It& rhs) const = 0;
			virtual bool			operator>=(const It& rhs) const = 0;
			virtual It&				operator+=(const difference_type diff) = 0;
			virtual It&				operator-=(const difference_type diff) = 0;
			virtual reference		operator[](int index) = 0;
			virtual const reference	operator[](int) const = 0;
	};
}

#endif
