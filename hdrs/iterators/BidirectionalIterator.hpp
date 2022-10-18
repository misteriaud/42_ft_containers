#pragma once
#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP

#include <cstddef>
#include "IteratorUtils.hpp"
#include "SFINAE.hpp"

namespace ft {

	template <typename T>
	class BidirectionalIterator{

		public:
			typedef BidirectionalIterator			it;
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			BidirectionalIterator(): _elem(NULL) {};
			BidirectionalIterator(const pointer from): _elem(from) {};
			BidirectionalIterator(const BidirectionalIterator<typename remove_cv<T>::type>& src): _elem(src._elem) {};
			virtual it&	operator=(const it& rhs) {
				if (this == &rhs)
					return (*this);
				_elem = rhs._elem;
					return (*this);
			};
			virtual ~BidirectionalIterator() {};

			// Comp overloading
			virtual bool					operator==(const it& rhs) const { return (_elem == rhs._elem); };
			virtual bool					operator!=(const it& rhs) const { return (_elem != rhs._elem); };
			virtual pointer					operator->() { return &(operator*()); };
			virtual reference				operator*() const { return (*_elem); };
			virtual reference				operator->() const { return (operator*()); };

			// Increment / decrement
			virtual it&	operator++() { _elem++; return (*this);};
			virtual it&	operator--() { _elem--; return (*this);};
			virtual it	operator++(int) { it tmp = *this; _elem++; return (tmp);};
			virtual it	operator--(int) { it tmp = *this; _elem--; return (tmp);};

			// protected:
				pointer	_elem;
	};
}

#endif
