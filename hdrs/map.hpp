#pragma once
#ifndef MAP_HPP
# define MAP_HPP

#include <functional>
#include <memory>
#include "pair.hpp"
#include "iterators/BidirectionalIterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "RBTree.hpp"

namespace ft {

	template < class Key,                                     // map::key_type
		class T,                                       // map::mapped_type
		class Compare = std::less<Key>,                     // map::key_compare
		class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
		>
	class map {
		public:
			//
			//	TYPES DEFINITIONS
			//
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef pair<const key_type, const mapped_type>	value_type;
			typedef Compare									key_compare;
			typedef Alloc									allocator_type;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef ft::BidirectionalIterator<T>			iterator;
			typedef ft::BidirectionalIterator<const T>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef std::ptrdiff_t							difference_type;
			typedef std::size_t								size_type;

			//
			// FUNCTION OBJECT
			//
			class value_compare {
				protected:
					Compare comp;
				public:
					value_compare (Compare c = Compare()) : comp(c) {}  // constructed with map's comparison object
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};

			//
			// Constructors
			//
			map() {};

			void	insert(const Key& key, const T& value) {
				_rb_tree.insert(ft::make_pair<Key, T>(key, value));
			}

		private:
			ft::RBTree<value_type, value_compare, Alloc>	_rb_tree;
	};
}

#endif
