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
			typedef pair<const key_type, mapped_type>		value_type;
			typedef Compare									key_compare;
			typedef Alloc									allocator_type;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef ft::BidirectionalIterator<value_type>	iterator;
			typedef ft::BidirectionalIterator<const value_type>		const_iterator;
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
			// Constructors AND Sestrucor
			//
			// empty (1)
			explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
						: _comp(comp), _alloc(alloc), _tree_alloc(alloc), _rb_tree(_tree_alloc.allocate(1)) {
							_tree_alloc.construct(_rb_tree, tree_type(alloc, value_compare(comp)));
						}
			// range (2)
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _tree_alloc(alloc), _rb_tree(_tree_alloc.allocate(1)) {
					_tree_alloc.construct(_rb_tree, tree_type(alloc, value_compare(comp)));
					for (; first != last; first++)
						_rb_tree.insert(*first);
				}
			// copy (3)
			map (const map& from): _comp(from._comp), _alloc(from._alloc), _tree_alloc(from._tree_alloc), _rb_tree(_tree_alloc.allocate(1)) {
				_tree_alloc.construct(_rb_tree, from._rb_tree);
			};
			~map() {
				_tree_alloc.destroy(_rb_tree);
				_tree_alloc.deallocate(_rb_tree, 1);
			};

			//
			// Iterators
			//
			iterator	begin() {
				return (iterator(_rb_tree->min()));
			}
			iterator	end() {
				return (iterator(Node<value_type>::NIL()));
			}
			const_iterator	begin() const {
				return (const_iterator(_rb_tree->min()));
			}
			const_iterator	end() const {
				return (const_iterator(Node<value_type>::NIL()));
			}
			// reverse_iterator rbegin() {
			// 	return (reverse_iterator(_buffer + _size));
			// };
			// const_reverse_iterator rbegin() const {
			// 	return (const_reverse_iterator(_buffer + _size));
			// };
			// reverse_iterator rend() {
			// 	return (reverse_iterator(_buffer));
			// };
			// const_reverse_iterator rend() const {
			// 	return (const_reverse_iterator(_buffer));
			// };


			//
			// CAPACITY
			//
			bool empty() const {
				return (_rb_tree->empty());
			}
			size_type size() const {
				return (_rb_tree->size());
			}


			//
			// ELEMENT ACCESS
			//
			mapped_type& operator[] (const key_type& k) {
				return (**(_rb_tree->insert(ft::make_pair<Key, T>(k, mapped_type())))).second;
			}


			//
			// MODIFIERS
			//
			// single element (1)
			pair<iterator,bool> insert(const value_type& val) {
				size_type	last_size = size();
				Node<value_type>* ptr = _rb_tree->insert(val);
				ft::pair<iterator, bool> result = ft::make_pair<iterator, bool>(iterator(ptr), true);

				if (size() == last_size)
					result.second = false;

				return (result);
			}
			// with hint (2)
			iterator insert (iterator position, const value_type& val) {

				Node<value_type>* ptr = _rb_tree->insert(val, position._elem);

				return (iterator(ptr));
			}
			template <class InputIterator> // range
			void insert (InputIterator first, InputIterator last) {
				for (; first != last; first++)
					_rb_tree->insert(*first);
			}
			void erase (iterator position) {
				_rb_tree->remove(position._elem);
			}
			size_type erase (const key_type& k) {
				value_type	to_find = ft::make_pair<key_type, mapped_type>(k, mapped_type());
				Node<value_type>*	z = _rb_tree->find(to_find);
				return (_rb_tree->remove(z));
			}
			void erase (iterator first, iterator last) {
				for (; first != last; first++) {
					_rb_tree->remove(first._elem);
				}
			}
			// void swap (map& x) {
			// 	key_compare										_comp_temp = _comp;
			// 	allocator_type									_alloc_temp = _alloc;
			// 	ft::RBTree<value_type, value_compare, Alloc>*	_rb_tree_temp = &;


			// }

		private:
			typedef ft::RBTree<value_type, value_compare, Alloc>			tree_type;
			typedef typename allocator_type::template rebind<tree_type>::other	tree_allocator_type;

			key_compare			_comp;
			allocator_type		_alloc;
			tree_allocator_type _tree_alloc;
			tree_type*				_rb_tree;
	};
}

#endif
