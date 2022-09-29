#pragma once
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterators/RandomAccessIterator.hpp"

namespace ft {

	template <typename T>
	class VectorIt: public ft::RandomAccessIterator<T, VectorIt<T> > {
		public:
			// TYPEDEF
			typedef VectorIt									it;
			using typename ft::RandomAccessIterator<T, VectorIt<T> >::difference_type;
			using typename ft::RandomAccessIterator<T, VectorIt<T> >::value_type;
			using typename ft::RandomAccessIterator<T, VectorIt<T> >::pointer;
			using typename ft::RandomAccessIterator<T, VectorIt<T> >::reference;
			using typename ft::RandomAccessIterator<T, VectorIt<T> >::iterator_category;

			// CONSTRUCTORS/DESTRUCTORS
			VectorIt(): RandomAccessIterator<T, VectorIt<T> >() {};
			VectorIt(const pointer from): RandomAccessIterator<T, VectorIt<T> >(from) {};
			VectorIt(const it& from): RandomAccessIterator<T, VectorIt<T> >(from) {};
			virtual ~VectorIt() {};

			//operators
			// Increment / decrement
			it&	operator++(int) { this->_elem++; return (*this);};
			it&	operator--(int) { this->_elem--; return (*this);};
			it	operator++(void) { it tmp = *this; tmp++; return (tmp);};
			it	operator--(void) { it tmp = *this; tmp--; return (tmp);};
			// arythmetic operator
			// a +/- n
			it	operator+(const difference_type a) const { it temp(*this); return temp += a; };
			it	operator-(const difference_type a) const { it temp(*this); return temp -= a; };

			// TO DEFINE LATER
			// a - b
			difference_type	operator-(const it& rhs) const { return (this->_elem - rhs._elem); }
			bool			operator<(const it& rhs) const { return (this->_elem < rhs._elem); };
			bool			operator>(const it& rhs) const { return (this->_elem > rhs._elem); };
			bool			operator<=(const it& rhs) const { return (this->_elem <= rhs._elem); };
			bool			operator>=(const it& rhs) const { return (this->_elem >= rhs._elem); };
			it&				operator+=(const difference_type diff) { this->_elem += diff; return (*this); };
			it&				operator-=(const difference_type diff) { this->_elem -= diff; return (*this); };
			reference		operator[](int index) { return (this->_elem[index]); };
			const reference	operator[](int index) const { return (this->_elem[index]); };
	};

	template <
		class T,
		class Allocator = std::allocator<T>
		>
	class vector {
	public:

		typedef T									value_type;
		typedef Allocator							allocator_type;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef ft::VectorIt<T>						iterator;
		typedef ft::VectorIt<const T>				const_iterator;

		vector(): _pool(new T[50]) {
			_pool[1] = "test";
		};
		vector(const vector&);
		vector&	operator=(const vector&);
		~vector() {};
		iterator	begin() {
			return iterator(_pool);
		}
		const_iterator	cbegin() const {
			return const_iterator(_pool);
		}

	private:
		T*	_pool;

	};
}


#endif
