#pragma once
#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP

#include <cstddef>
#include "IteratorUtils.hpp"

namespace ft {
	template <typename T>
	class BidirectionalIterator {

		public:
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::bidirectional_iterator_tag	iterator_category;

			BidirectionalIterator(): _elem(NULL) {};
			BidirectionalIterator(const pointer from): _elem(from) {};
			BidirectionalIterator(const BidirectionalIterator& from): _elem(from._elem) {};
			virtual BidirectionalIterator&	operator=(const BidirectionalIterator& rhs) {
				if (this == &rhs)
					return (*this);
				_elem = rhs._elem;
				return (*this);

			};
			virtual ~BidirectionalIterator() {};

			// Comp overloading
			virtual bool	operator==(const BidirectionalIterator& rhs) {
				return (_elem == rhs._elem);
			};
			virtual bool	operator!=(const BidirectionalIterator& rhs) {
				return !(*this == rhs);
			};
			virtual reference		operator*() {
				if (!_elem)
					throw std::exception();
				return (*_elem);
			};
			virtual reference		operator->() {
				return (operator*());
			};
			virtual const reference		operator*() const {
				if (!this->_elem)
					throw std::exception();
				return (*this->_elem);
			};
			virtual const reference		operator->() const {
				return (operator*());
			};

			// Increment / decrement
			BidirectionalIterator&	operator++(int) {
				_elem++;
				return (*this);
			};
			BidirectionalIterator&	operator--(int) {
				_elem--;
				return (*this);
			};
			BidirectionalIterator	operator++(void) {
				BidirectionalIterator tmp = *this;
				tmp++;
				return (tmp);
			};
			BidirectionalIterator	operator--(void) {
				BidirectionalIterator tmp = *this;
				tmp--;
				return (tmp);
			};

		protected:
			pointer	_elem;

	};
}

#endif
