#pragma once
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterators/RandomAccessIterator.hpp"
#include "iterators/iterator_traits.hpp"
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

		//
		//	TYPES DEFINITIONS
		//
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



		//
		//	CONSTRUCTORS AND DESTRUCTORS
		//
		explicit vector (const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _buffer(NULL), _capacity(0), _size(0) { };
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _buffer(_alloc.allocate(n)), _capacity(n), _size(n) {
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
		~vector() {
			if (!_buffer)
				return ;
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_buffer + i);
			_alloc.deallocate(_buffer, _capacity);
		};
		vector&	operator=(const vector& rhs) {
			if (this == &rhs)
				return (*this);
			if (_capacity < rhs._size) {
				manage_array(rhs._size, 0);
			}
			for (size_type i = 0; i < rhs._size; i++)
				i < _size
					? _buffer[i] = rhs._buffer[i]
					: _alloc.construct(_buffer + i, rhs._buffer[i]);
			_size = rhs._size;
			_capacity = rhs._capacity;
		}



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
		void		reserve(size_type n) { return (manage_array(n, _size)); }



		//
		//	ELEMENT ACCESS
		//
		reference		operator[](size_type n) {
			return (_buffer[n]);
		}
		const_reference	operator[](size_type n) const {
			return (_buffer[n]);
		}
		reference		at(size_type n) {
			if (n < 0 || n >= _size)
				throw std::out_of_range("out of bound request");
			return (_buffer[n]);
		}
		const_reference at (size_type n) const {
			if (n < 0 || n >= _size)
				throw std::out_of_range("out of bound request");
			return (_buffer[n]);
		}
		reference		front() {
			return (*_buffer);
		}
		const_reference	front() const {
			return (*_buffer);
		}
		reference		back() {
			return (_buffer[_size]);
		}
		const_reference	back() const {
			return (_buffer[_size]);
		}



		//
		//	MODIFIERS
		//
		template <class InputIterator>
		void		assign(InputIterator first, InputIterator last) {
			typedef typename ft::iterator_traits<InputIterator>::iterator_category tag;
			assign(first, last, tag());
		}
		void	 	assign(size_type n, const value_type& val) {
			size_type	i = 0;
			if (n > _capacity) {
				manage_array(n, 0);
				for (; i < n; i++)
					_alloc.construct(_buffer + i, val);
			}
			else {
				for (; i < _size && i < n; i++) {
					_alloc.destroy(_buffer + i);
					_alloc.construct(_buffer + i, val);
				}
				for (; i < _capacity && i < n; i++) {
					_alloc.construct(_buffer + i, val);
				}
			}
			_size = n;
		}
		void		push_back(const value_type& val) {
			reserve(_size + 1);
			_alloc.construct(_buffer + _size, val);
			_size++;
		}
		void		pop_back() {
			if (_size == 0)
				return ;
			_alloc.destroy(_buffer[_size - 1]);
		}
		void		clear() {
			for (size_t i = 0; i < _size; i++)
				_alloc.destroy(_buffer + i);
			_size = 0;
		}
		iterator	insert(iterator position, const value_type& val) {
			if (position ==  end()) {
				push_back(val);
				return (iterator(_buffer + _size - 1));
			}
			difference_type	diff = ft::distance<iterator>(begin(), position);
			manage_array(_capacity + 1, diff, 1);
			_alloc.construct(_buffer + diff, val);
			return (iterator(_buffer + _size - 1));
		}
		void 		insert(iterator position, size_type n, const value_type& val) {
			if (position ==  end()) {
				manage_array(_size + n, _size);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_buffer + _size + i, val);
				_size += n;
				return ;
			}
			difference_type	diff = ft::distance<iterator>(begin(), position);
			manage_array(_capacity + n, diff, n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_buffer + diff + i, val);
			return ;
		}
		template <class InputIterator>
		void 		insert(iterator position, InputIterator first, InputIterator last) {
			typedef typename ft::iterator_traits<InputIterator>::iterator_category tag;
			insert(position, first, last, tag());
		}


	private:
		Allocator		_alloc;
		T*				_buffer;
		size_type		_capacity;
		size_type		_size;

		/**
		*		Function to manage the reallocation of the array using the Allocator passed at the creation.
		*
		* @param n			The new size to allocate.
		* @param length		The number of element to duplicate from the last allocated array
		* @param offset		The number of element to let empty after the *length* first elements,
		* 					if offset != 0 the rest of the array will be copy after the offset.
		* @param skip		The number of element to skip after the *length* first elements
		*/
		void	manage_array(size_type n, size_type length, size_type offset = 0, size_type skip = 0) {
			T*			new_buffer = _buffer;
			size_type	old_capacity = _capacity;
			size_type	i;
			if (n > _capacity) {
				if (n > max_size())
					throw std::length_error("max size over");
				size_type	new_capacity = _capacity ? _capacity * 2 : 1;
				while (new_capacity < n)
					new_capacity *= 2;
				new_buffer = _alloc.allocate(new_capacity);
				for (size_type i = 0; i < length; i++)
				{
					_alloc.construct(new_buffer + i, _buffer[i]);
					_alloc.destroy(_buffer + i);
				}
				_capacity = new_capacity;
			}
			// if offset > skip, we must copy right to left, if not we must copy left to right
			if (skip > offset || (!skip && offset)) // ABC___EF <--
				for (i = n < _size
						? n + offset - skip - 1
						: _size + offset - skip - 1;
					i > length + offset - 1;
					i--) {
						_alloc.construct(new_buffer + i, _buffer[i - offset + skip]);
						if (i - offset + skip >= length + offset)
							_alloc.destroy(_buffer + i - offset + skip);
					}
			else if (skip < offset || (skip && !offset)) // ABC_ --> FGH
				for (i = length + offset - 1;
					i < _size + offset - skip - 1;
					i++) {
						_alloc.destroy(_buffer + i);
						_alloc.construct(new_buffer + i, _buffer[i - offset + skip]);
					}
			for (size_type i = length; i < length + offset && i < _size; i++)
				_alloc.destroy(_buffer + i);
			if (new_buffer != _buffer && _buffer)
				_alloc.deallocate(_buffer, old_capacity);
			_buffer = new_buffer;
			_size += offset;
		}

		// SPECIALIZATION
		template <typename InputIterator>
		void	assign(InputIterator first, InputIterator last, std::input_iterator_tag) {
			// std::cout << "be careful with InputIterator" << std::endl;
			clear();
			for (; first != last; first++)
				push_back(*first);
		}
		template <typename Iterator>
		void	assign(Iterator first, Iterator last, ft::bidirectional_iterator_tag) {
			// std::cout << "some iterator" << std::endl;
			size_type 	distance = static_cast<size_type>(ft::distance(first, last));
			size_type	i = 0;
			if (distance < 1)
				return ;
			if (distance > _capacity) {
				manage_array(distance, 0);
				for (; i < distance; i++) {
					_alloc.construct(_buffer + i, *first);
					first++;
				}
			}
			else {
				for (; i < _size && i < distance; i++) {
					_alloc.destroy(_buffer + i);
					_alloc.construct(_buffer + i, *first);
					first++;
				}
				for (; i < _capacity && i < distance; i++) {
					_alloc.construct(_buffer + i, *first);
					first++;
				}
			}
			_size = distance;
		}
		template <typename InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag) {
			typedef typename ft::iterator_traits<iterator>::iterator_category tag;
			vector<value_type>	temp;
			for (; first != last; first++)
				temp.push_back(*first);
			insert(position, temp.begin(), temp.end(), tag());
		}
		template <typename InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last, ft::bidirectional_iterator_tag) {
			size_type		j = 0;
			difference_type	length = ft::distance<iterator>(begin(), position);
			difference_type	to_insert = static_cast<difference_type>(ft::distance<iterator>(first, last));
			manage_array(_size + to_insert, length, to_insert);
			for (; first != last; first++)
				_alloc.construct(_buffer + length + j++, *first);
			return ;
		}


	};
}


#endif
