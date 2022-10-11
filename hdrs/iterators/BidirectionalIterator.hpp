#pragma once
#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP

#include <cstddef>
#include "IteratorUtils.hpp"
#include "SFINAE.hpp"

namespace ft {
	template <typename T, typename It>
	class BidirectionalIterator {

		public:
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::bidirectional_iterator_tag	iterator_category;

			BidirectionalIterator(): _elem(NULL) {};
			BidirectionalIterator(const pointer from): _elem(from) {};
			BidirectionalIterator(const It& from): _elem(from._elem) {};
			virtual It&	operator=(const It& rhs) {
				if (this == &rhs)
					return (dynamic_cast<It&>(*this));
				_elem = rhs._elem;
				return (dynamic_cast<It&>(*this));

			};
			virtual ~BidirectionalIterator() {};

			// Comp overloading
			virtual bool					operator==(const It& rhs) { return (_elem == rhs._elem); };
			virtual bool					operator!=(const It& rhs) { return !(*this == rhs); };
			virtual reference				operator*() { if (!_elem) throw std::exception(); return (*_elem); };
			virtual reference				operator->() { return (operator*()); };
			virtual reference				operator*() const { return (*this->_elem); };
			// virtual reference				operator*() const { if (!this->_elem) throw std::exception(); return (*this->_elem); };
			virtual reference				operator->() const { return (operator*()); };

			// Increment / decrement
			virtual It&	operator++() = 0;
			virtual It&	operator--() = 0;
			virtual It	operator++(int) = 0;
			virtual It	operator--(int) = 0;

		protected:
			pointer	_elem;
	};
}

#endif
