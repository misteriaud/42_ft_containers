#pragma once
#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> > class stack {
		public:
			typedef T									value_type;
			typedef Container							container_type;
			typedef	typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference const_reference;

			explicit stack (const container_type& ctnr = container_type()): c(ctnr) {};
			~stack() {};
			stack& operator=( const stack& other ) {
				c = other.c;
				return (*this);
			}

			reference top() { return (c.back()); }
			const_reference top() const { return (c.back()); }
			bool empty() const { return (c.empty()); }
			size_type size() const { return (c.size()); }
			void push( const value_type& value ) { c.push_back(value); }
			void pop() { c.pop_back(); }

			template <typename Type, typename Cont>
			friend bool operator==(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);
			template <typename Type, typename Cont>
			friend bool operator!=(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);
			template <typename Type, typename Cont>
			friend bool operator<(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);
			template <typename Type, typename Cont>
			friend bool operator<=(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);
			template <typename Type, typename Cont>
			friend bool operator>(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);
			template <typename Type, typename Cont>
			friend bool operator>=(const stack<Type, Cont>& lhs, const stack<Type, Cont>& rhs);

		protected:
			container_type	c;
	};

	template< class T, class Container >
	bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c == rhs.c);
	}
	template< class T, class Container >
	bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c != rhs.c);
	}
	template< class T, class Container >
	bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c < rhs.c);
	}
	template< class T, class Container >
	bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c <= rhs.c);
	}
	template< class T, class Container >
	bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c > rhs.c);
	}
	template< class T, class Container >
	bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c >= rhs.c);
	}
}

#endif
