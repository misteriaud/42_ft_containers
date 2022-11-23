#pragma once
#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP

#include <cstddef>
#include "IteratorUtils.hpp"
#include "../utils/SFINAE.hpp"
#include "../utils/RBTree.hpp"

namespace ft {

	template <typename T>
	class BidirectionalIterator{

		public:
			typedef BidirectionalIterator			it;
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef Node<value_type>				node_type;
			typedef typename ft::conditional<ft::is_const<T>::value, const Node<typename remove_cv<value_type>::type >* , Node<value_type>* >::type pair_node_pointer;
			typedef typename ft::conditional<ft::is_pair<typename remove_const<value_type>::type >::value, pair_node_pointer, node_type*>::type node_pointer;
			typedef std::bidirectional_iterator_tag	iterator_category;

			BidirectionalIterator(): _elem(NULL) {};
			BidirectionalIterator(const node_pointer src): _elem(src) {};
			BidirectionalIterator(const BidirectionalIterator< typename remove_cv<T>::type>& src): _elem(src._elem) {};
			it&	operator=(const it& rhs) {
				if (this == &rhs)
					return (*this);
				_elem = rhs._elem;
					return (*this);
			};
			~BidirectionalIterator() {};

			// Comp overloading
			bool					operator==(const it& rhs) const { return (_elem == rhs._elem); };
			bool					operator!=(const it& rhs) const { return (_elem != rhs._elem); };
			pointer					operator->() const { return &(_elem->value); };
			reference				operator*() const { return (_elem->value); };
			// reference				operator->() const { return (_elem->value); };

			// Increment / decrement
			it&	operator++() { _elem = _elem->next(); return (*this);};
			it&	operator--() { _elem = _elem->previous(); return (*this); };
			it	operator++(int) { it tmp = *this; _elem = _elem->next(); return (tmp);};
			it	operator--(int) { it tmp = *this; _elem = _elem->previous(); return (tmp); };

			node_pointer	_elem;
	};
}

#endif
