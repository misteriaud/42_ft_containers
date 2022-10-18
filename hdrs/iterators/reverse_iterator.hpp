#pragma once
#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

#include <string>
#include <ostream>

#include "iterator_traits.hpp"
#include "../SFINAE.hpp"

namespace ft {

	template<typename It>
	class reverse_iterator {
		public:

			// TYPEDEF
			typedef It			iterator_type;
			typedef typename ft::iterator_traits<It>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<It>::value_type		value_type;
			typedef typename ft::iterator_traits<It>::difference_type	difference_type;
			typedef typename ft::iterator_traits<It>::pointer			pointer;
			typedef typename ft::iterator_traits<It>::reference			reference;

			reverse_iterator(): _current() {};
			reverse_iterator(const It& itr): _current(itr) {}
			reverse_iterator(const reverse_iterator<typename remove_const<It>::type>& src): _current(src.base()) {}
			template <typename U>
			reverse_iterator(const reverse_iterator<U>& other): _current(other.base()) {};
			template< class U >
			reverse_iterator& operator=(const reverse_iterator<U>& other ) {
				if (this == &other)
					return (*this);
				_current = other.base();
				return (*this);
			}

			// Comp overloading
			// Here we have to use friend keyword to be able to access to the protected attribute _elem of both of the iterators


			pointer			operator->() const { return &(operator*()); }
			reference		operator*() const { return (*_current); }
			reference		operator[]( difference_type index ) const { return (_current[index]); }

			reverse_iterator& operator++() { return (--_current); }
			reverse_iterator& operator--() { return (++_current); }
			reverse_iterator operator++(int) { iterator_type tmp(*this); --(*this); return (tmp); }
			reverse_iterator operator--(int) { iterator_type tmp(*this); ++(this); return (tmp); }


			reverse_iterator operator-(difference_type n) const { reverse_iterator tmp(*this); return (tmp -= n); }
			reverse_iterator& operator+=(difference_type n) { _current -= n; return (*this); }
			reverse_iterator& operator-=(difference_type n) { _current += n; return (*this); }

			iterator_type	base() const { return _current; }


		protected:
			It _current;

	};

	template< typename T> // it + 1
	reverse_iterator<T>	operator+(const reverse_iterator<T>& lhs, const typename reverse_iterator<T>::difference_type rhs) {
		reverse_iterator<T> temp(lhs);
		return temp += rhs;
	};

	template< typename T> // it - 1
	reverse_iterator<T>	operator-(const reverse_iterator<T>& lhs, const typename reverse_iterator<T>::difference_type rhs) {
		reverse_iterator<T> temp(lhs);
		return temp -= rhs;
	};

	template< typename T> // 1 + it
	reverse_iterator<T>	operator+(const typename reverse_iterator<T>::difference_type lhs, const reverse_iterator<T>& rhs) {
		reverse_iterator<T> temp(rhs);
		return temp += lhs;
	};
	template< typename T> // 1 - it
	reverse_iterator<T>	operator-(const typename reverse_iterator<T>::difference_type lhs, const reverse_iterator<T>& rhs) {
		reverse_iterator<T> temp(rhs);
		return temp -= lhs;
	};

	template< class It1, class It2> // it2 - it1
	typename reverse_iterator<It1>::difference_type	operator-(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs ) {
		return (lhs.base() - rhs.base());
	}

	template< class It1, class It2 >
	bool 	operator==(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return (lhs.base() == rhs.base()); };
	template< class It1, class It2 >
	bool 	operator!=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return (lhs.base() != rhs.base()); };
	template< class It1, class It2 >
	bool	operator<(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return (lhs.base() < rhs.base()); };
	template< class It1, class It2 >
	bool	operator>(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return (lhs.base() > rhs.base()); };
	template< class It1, class It2 >
	bool	operator<=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return (lhs.base() <= rhs.base()); };
	template< class It1, class It2 >
	bool	operator>=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return (lhs.base() >= rhs.base()); };

}

#endif
