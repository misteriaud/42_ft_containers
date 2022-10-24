#pragma once
#ifndef MAP_HPP
# define MAP_HPP

#include <functional>
#include <memory>
#include "pair.hpp"

namespace ft {

	template < class Key,                                     // map::key_type
		class T,                                       // map::mapped_type
		class Compare = std::less<Key>,                     // map::key_compare
		class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
		>
	class map {
		//
		//	TYPES DEFINITIONS
		//
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef pair<const key_type, const mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Allocator								allocator_type;
		typedef allocator_type::reference				reference;
		typedef allocator_type::const_reference			const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef ft::BidirectionalIterator<T>			iterator;
		typedef ft::BidirectionalIterator<const T>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;

		//
		// FUNCTION OBJECT
		//
		class value_compare: public binary_function<value_type, value_type, bool> {
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
		};
	};
}

#endif
