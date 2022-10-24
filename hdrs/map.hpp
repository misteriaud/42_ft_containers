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
		typedef
		typedef Allocator								allocator_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef ft::RandomAccessIterator<T>				iterator;
		typedef ft::RandomAccessIterator<const T>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	};
}

#endif
