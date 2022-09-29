#pragma once
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterators/RandomAccessIterator.hpp"
#include <stdexcept>

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

		// CONSTRUCTORS AND DESTRUCTOR
		explicit vector (const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _buffer(NULL), _capacity(0), _size(0) { };
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _buffer(_alloc.allocate(n)), _capacity(n), _size(n)
		{
			// _alloc.allocate(n, &_buffer);
			for (size_t i = 0; i < n; i++)
				_alloc.construct(_alloc + n, val);
		}
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _buffer(NULL), _capacity(0), _size(0) {
			for(; first != last; first++)
				push_back(*first);
		};
		vector(const vector&);
		~vector() {};

		//
		//	ITERATORS
		//
		iterator	begin() {
			return iterator(_buffer);
		}
		iterator	end() {
			return iterator(_buffer + _size);
		}
		const_iterator	cbegin() const {
			return const_iterator(_buffer);
		}
		const_iterator	cend() {
			return const_iterator(_buffer + _size);
		}



		//
		//	CAPACITY
		//
		size_type	size(void) const { return (_size); }
		size_type	max_size(void) const {
			// return std::numeric_limits<size_type>::max() / sizeof(value_type);
			return _alloc.max_size();
		}
		void	resize(size_type n, value_type val = value_type()) {
			while (_size < n)
				push_back(val);
			while (_size > n)
				pop_back();
		};
		size_type	capacity(void) const { return (_capacity); }
		bool		empty() const { return (!_size); }
		void		reserve(size_type n) {
			if (n <= _capacity)
				return ;
			if (n > max_size())
				throw std::length_error("max size over");
			size_type	new_capacity = _capacity ? _capacity * 2 : 1;
			while (new_capacity < n)
				new_capacity *= 2;
			T*	new_buffer = _alloc.allocate(new_capacity);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(new_buffer + i, _buffer[i]);
				_alloc.destroy(_buffer + i);
			}
			_alloc.deallocate(_buffer, _capacity);
			_capacity = new_capacity;
			_buffer = new_buffer;
		}



		//
		//	ELEMENT ACCESS
		//



		//
		//	MODIFIERS
		//
		void	push_back(const value_type& val) {
			reserve (_size + 1);
			_buffer[_size] = val;
			_size++;
		}
		void	pop_back() {
			if (_size == 0)
				return ;
			_alloc.destroy(_buffer[_size - 1]);
		}

		vector&	operator=(const vector&);

	private:
		Allocator	_alloc;
		T*			_buffer;
		size_type	_capacity;
		size_type	_size;
	};
}


#endif
