#pragma once
#ifndef set_HPP
# define set_HPP

#include <functional>
#include <memory>
#include "pair.hpp"
#include "iterators/BidirectionalIterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "RBTree.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

namespace ft {

	template < class T,
			class Compare = std::less<T>,
			class Alloc = std::allocator<T>
	>
	class set {
		public:
			//
			//	TYPES DEFINITIONS
			//
			typedef T										key_type;
			typedef T		value_type;
			typedef Compare									key_compare;
			typedef Compare 								value_compare;
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
			// Constructors AND Sestrucor
			//
			// empty (1)
			explicit set (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
						: _comp(comp), _alloc(alloc), _tree_alloc(alloc), _rb_tree(_tree_alloc.allocate(1)) {
							_tree_alloc.construct(_rb_tree, tree_type(value_comp(), alloc));
						}
			// range (2)
			template <class InputIterator>
			set (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _tree_alloc(alloc), _rb_tree(_tree_alloc.allocate(1)) {
					_tree_alloc.construct(_rb_tree, tree_type(value_comp(), alloc));
					for (; first != last; first++)
						_rb_tree->insert(*first);
				}
			// copy (3)
			set (const set& from): _comp(from._comp), _alloc(from._alloc), _tree_alloc(from._tree_alloc), _rb_tree(_tree_alloc.allocate(1)) {
				_tree_alloc.construct(_rb_tree, *from._rb_tree);
			};
			~set() {
				_tree_alloc.destroy(_rb_tree);
				_tree_alloc.deallocate(_rb_tree, 1);
			};
			set& operator= (const set& rhs) {
				if (this == &rhs)
					return (*this);
				_comp = rhs._comp;
				*_rb_tree = *rhs._rb_tree;
				return (*this);
			}

			//
			// Iterators
			//
			iterator	begin() {
				return (iterator(_rb_tree->min()));
			}
			iterator	end() {
				return (iterator(_rb_tree->sentinel()));
			}
			const_iterator	begin() const {
				return (const_iterator(_rb_tree->min()));
			}
			const_iterator	end() const {
				return (const_iterator(_rb_tree->sentinel()));
			}
			reverse_iterator rbegin() {
				return (reverse_iterator(_rb_tree->sentinel()));
			};
			const_reverse_iterator rbegin() const {
				return (const_reverse_iterator(_rb_tree->sentinel()));
			};
			reverse_iterator rend() {
				return (reverse_iterator(_rb_tree->min()));
			};
			const_reverse_iterator rend() const {
				return (const_reverse_iterator(_rb_tree->min()));
			};


			//
			// CAPACITY
			//
			bool empty() const {
				return (_rb_tree->empty());
			}
			size_type size() const {
				return (_rb_tree->size());
			}
			size_type max_size() const {
				return (_rb_tree->max_size());
			}

			//
			// MODIFIERS
			//
			// single element (1)
			ft::pair<iterator,bool> insert(const value_type& val) {
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
			size_type erase (const value_type& val) {
				Node<value_type>*	z = _rb_tree->find(val);
				return (_rb_tree->remove(z));
			}
			void erase (iterator first, iterator last) {
				iterator next = first;
				for (; first != last; first = next) {
					++next;
					_rb_tree->remove(first._elem);
				}
			}
			void swap (set& x) {
				key_compare		_comp_temp = _comp;
				allocator_type	_alloc_temp = _alloc;
				allocator_type	_tree_alloc_temp = _tree_alloc;
				tree_type*		_rb_tree_temp = _rb_tree;

				_comp = x._comp;
				_alloc = x._alloc;
				_tree_alloc = x._tree_alloc;
				_rb_tree = x._rb_tree;

				x._comp = _comp_temp;
				x._alloc = _alloc_temp;
				x._tree_alloc = _tree_alloc_temp;
				x._rb_tree = _rb_tree_temp;
			}
			void clear() {
				_rb_tree->clear();
			}


			//
			// OBSERVERS
			//
			key_compare key_comp() const {
				return (_comp);
			}
			value_compare value_comp() const {
				return (_comp);
			}

			//
			// OPERATIONS
			//
			iterator find (const value_type& val) const {
				return (iterator(_rb_tree->find(val)));
			}
			size_type count (const value_type& val) const {
				if (_rb_tree->find(val) == _rb_tree->sentinel())
					return (0);
				return (1);
			}
			iterator lower_bound (const value_type& val) const {
				return (iterator(_rb_tree->lower_bound(val)));
			}
			iterator upper_bound (const value_type& val) const {
				return (iterator(_rb_tree->upper_bound(val)));
			}
			ft::pair<iterator,iterator>	equal_range (const value_type& val) const {
				return ft::make_pair<iterator, iterator>(lower_bound(val), upper_bound(val));
			}


			//
			// ALLOCATOR
			//
			allocator_type get_allocator() const {
				return (_alloc);
			}

		private:
			typedef ft::RBTree<value_type, value_compare, Alloc>			tree_type;
			typedef typename allocator_type::template rebind<tree_type>::other	tree_allocator_type;

			key_compare			_comp;
			allocator_type		_alloc;
			tree_allocator_type _tree_alloc;
			tree_type*			_rb_tree;
	};

	// template <class Key, class T, class Compare, class Alloc>
	// bool operator== ( const set<Key,T,Compare,Alloc>& lhs, const set<Key,T,Compare,Alloc>& rhs ) {
	// 	if (lhs.size() != rhs.size())
	// 		return (false);
	// 	return (equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	// }

	// template <class Key, class T, class Compare, class Alloc>
	// bool operator!= ( const set<Key,T,Compare,Alloc>& lhs, const set<Key,T,Compare,Alloc>& rhs ) {
	// 	return !(operator==(lhs, rhs));
	// }

	// template <class Key, class T, class Compare, class Alloc>
	// bool operator<  ( const set<Key,T,Compare,Alloc>& lhs, const set<Key,T,Compare,Alloc>& rhs ) {
	// 	return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	// }

	// template <class Key, class T, class Compare, class Alloc>
	// bool operator<= ( const set<Key,T,Compare,Alloc>& lhs, const set<Key,T,Compare,Alloc>& rhs ) {
	// 	return !(operator<(rhs, lhs));
	// }

	// template <class Key, class T, class Compare, class Alloc>
	// bool operator>  ( const set<Key,T,Compare,Alloc>& lhs, const set<Key,T,Compare,Alloc>& rhs ) {
	// 	return (operator<(rhs, lhs));
	// }

	// template <class Key, class T, class Compare, class Alloc>
	// bool operator>= ( const set<Key,T,Compare,Alloc>& lhs, const set<Key,T,Compare,Alloc>& rhs ) {
	// 	return !(operator<(lhs, rhs));
	// }

	// template <class Key, class T, class Compare, class Alloc>
	// void swap (set<Key,T,Compare,Alloc>& x, set<Key,T,Compare,Alloc>& y) {
	// 	x.swap(y);
	// }
}

#endif
