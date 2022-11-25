#pragma once
#ifndef MAP_HPP
# define MAP_HPP

#include <functional>
#include <memory>
#include "iterators/BidirectionalIterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "utils/pair.hpp"
#include "utils/RBTree.hpp"
#include "utils/equal.hpp"
#include "utils/lexicographical_compare.hpp"

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
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename Alloc::reference						reference;
			typedef typename Alloc::const_reference					const_reference;
			typedef typename Alloc::pointer							pointer;
			typedef typename Alloc::const_pointer					const_pointer;
			typedef ft::BidirectionalIterator<value_type>			iterator;
			typedef ft::BidirectionalIterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef std::ptrdiff_t									difference_type;
			typedef std::size_t										size_type;

			//
			// FUNCTION OBJECT
			//
			class value_compare {
					friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
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
							_tree_alloc.construct(_rb_tree, tree_type(value_comp(), alloc));
						}
			// range (2)
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _tree_alloc(alloc), _rb_tree(_tree_alloc.allocate(1)) {
					_tree_alloc.construct(_rb_tree, tree_type(value_comp(), alloc));
					for (; first != last; first++)
						_rb_tree->insert(*first);
				}
			// copy (3)
			map (const map& from): _comp(from._comp), _alloc(from._alloc), _tree_alloc(from._tree_alloc), _rb_tree(_tree_alloc.allocate(1)) {
				_tree_alloc.construct(_rb_tree, *from._rb_tree);
			};
			~map() {
				_tree_alloc.destroy(_rb_tree);
				_tree_alloc.deallocate(_rb_tree, 1);
			};
			map& operator= (const map& rhs) {
				if (this == &rhs)
					return (*this);
				_comp = rhs._comp;
				// _alloc = rhs._alloc;
				// _tree_alloc = rhs._tree_alloc;
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
			// ELEMENT ACCESS
			//
			mapped_type& operator[] (const key_type& k) {
				return (**(_rb_tree->insert(ft::make_pair<Key, T>(k, mapped_type())))).second;
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
			size_type erase (const key_type& k) {
				value_type	to_find = ft::make_pair<key_type, mapped_type>(k, mapped_type());
				Node<value_type>*	z = _rb_tree->find(to_find);
				return (_rb_tree->remove(z));
			}
			void erase (iterator first, iterator last) {
				iterator next = first;
				for (; first != last; first = next) {
					++next;
					_rb_tree->remove(first._elem);
				}
			}
			void swap (map& x) {
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
				return (value_compare(_comp));
			}

			//
			// OPERATIONS
			//
			iterator find (const key_type& k) {
				value_type	to_find = ft::make_pair<key_type, mapped_type>(k, mapped_type());
				return (iterator(_rb_tree->find(to_find)));
			}
			const_iterator find (const key_type& k) const {
				value_type	to_find = ft::make_pair<key_type, mapped_type>(k, mapped_type());
				return (const_iterator(_rb_tree->find(to_find)));
			}
			size_type count (const key_type& k) const {
				value_type	to_find = ft::make_pair<key_type, mapped_type>(k, mapped_type());
				if (_rb_tree->find(to_find) == _rb_tree->sentinel())
					return (0);
				return (1);
			}
			iterator lower_bound (const key_type& k) {
				value_type	to_find = ft::make_pair<key_type, mapped_type>(k, mapped_type());
				return (iterator(_rb_tree->lower_bound(to_find)));
			}
			const_iterator lower_bound (const key_type& k) const {
				value_type	to_find = ft::make_pair<key_type, mapped_type>(k, mapped_type());
				return (const_iterator(_rb_tree->lower_bound(to_find)));
			}
			iterator upper_bound (const key_type& k) {
				value_type	to_find = ft::make_pair<key_type, mapped_type>(k, mapped_type());
				return (iterator(_rb_tree->upper_bound(to_find)));
			}
			const_iterator upper_bound (const key_type& k) const {
				value_type	to_find = ft::make_pair<key_type, mapped_type>(k, mapped_type());
				return (const_iterator(_rb_tree->upper_bound(to_find)));
			}
			ft::pair<iterator,iterator>	equal_range (const key_type& k) {
				// iterator	result = lower_bound(k);
				return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}
			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
				// const_iterator	result = find(k);
				return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
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

	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(operator==(lhs, rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(operator<(rhs, lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return (operator<(rhs, lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(operator<(lhs, rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
		x.swap(y);
	}
}

#endif
