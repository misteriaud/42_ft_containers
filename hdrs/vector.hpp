#pragma once
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterators/RandomAccessIterator.hpp"
#include "iterators/iterator_traits.hpp"
#include "iterators/reverse_iterator.hpp"
#include "SFINAE.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"

namespace ft {

	template <
		class T,
		class Allocator = std::allocator<T>
		>
	class vector {
	public:

		//
		//	TYPES DEFINITIONS
		//
		typedef T										value_type;
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



		//
		//	CONSTRUCTORS AND DESTRUCTORS
		//
			// DEFAULT
		explicit vector (const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _buffer(NULL), _capacity(0), _size(0) { };
			// FILL CONSTRUCTEUR
		vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _buffer(_alloc.allocate(n)), _capacity(n), _size(n) {
			for (size_t i = 0; i < n; i++)
				_alloc.construct(_buffer + i, val);
		}
			// RANGE
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type =0)
		: _alloc(alloc), _buffer(NULL), _capacity(0), _size(0) {
			for(; first != last; first++)
				push_back(*first);
		};
			// COPY
		vector(const vector& from)
		: _alloc(from._alloc), _buffer(_alloc.allocate(from._capacity)), _capacity(from._capacity), _size(from._size) {
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_buffer + i, from[i]);
		};
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
			manage_array(rhs._size, 0);
			for (size_type i = 0; i < rhs._size; i++)
				_alloc.construct(_buffer + i, rhs._buffer[i]);
			_size = rhs._size;
			// _capacity = rhs._capacity;
			return (*this);
		}



		//
		//	ITERATORS
		//
		iterator	begin() {
			return (iterator(_buffer));
		}
		iterator	end() {
			return (iterator(_buffer + _size));
		}
		const_iterator	begin() const {
			return (const_iterator(_buffer));
		}
		const_iterator	end() const {
			return (const_iterator(_buffer + _size));
		}
		reverse_iterator rbegin() {
			return (reverse_iterator(_buffer + _size));
		};
		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(_buffer + _size));
		};
		reverse_iterator rend() {
			return (reverse_iterator(_buffer));
		};
		const_reverse_iterator rend() const {
			return (const_reverse_iterator(_buffer));
		};



		//
		//	CAPACITY
		//
		size_type	size(void) const { return (_size); }
		size_type	max_size(void) const {
			// return std::numeric_limits<size_type>::max() / sizeof(value_type);
			return _alloc.max_size();
		}
		void		resize(size_type n, value_type val = value_type()) {
			if (n > _size)
				insert(end(), n - _size, val);
			if (n < _size)
				erase(end() - (_size - n), end());
		};
		size_type	capacity(void) const { return (_capacity); }
		bool		empty() const { return (!_size); }
		void		reserve(size_type n) {
			if (n > _capacity)
				return (manage_array(n, _size));
		}



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
			if (n + 1 < 1 || n >= _size)
				throw std::out_of_range("out of bound request");
			return (_buffer[n]);
		}
		const_reference at (size_type n) const {
			if (n + 1 < 1 || n >= _size)
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
			return (_buffer[_size - 1]);
		}
		const_reference	back() const {
			return (_buffer[_size - 1]);
		}



		//
		//	MODIFIERS
		//
		template <typename InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
					assign(InputIterator first, InputIterator last) {
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
			_alloc.destroy(_buffer + _size - 1);
			_size--;
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
			if (diff > 0)
				diff--;
			manage_array(_size + 1, diff, 1);
			_alloc.construct(_buffer + diff, val);
			return (iterator(_buffer + diff));
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
			if (diff > 0)
				diff--;
			manage_array(_size + n, diff, n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_buffer + diff + i, val);
			return ;
		}
		template <class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
					insert(iterator position, InputIterator first, InputIterator last) {
			typedef typename ft::iterator_traits<InputIterator>::iterator_category tag;
			insert(position, first, last, tag());
		}
		iterator	erase(iterator position) {
			if (position == iterator(_buffer + _size - 1)) {
				pop_back();
				return (iterator(_buffer + _size));
			}
			difference_type	diff = ft::distance<iterator>(begin(), position);
			if (diff > 0)
				diff--;
			manage_array(_capacity, diff, 0, 1);
			return (iterator(_buffer + diff));
		}
		iterator	erase(iterator first, iterator last) {
			difference_type	length = ft::distance<iterator>(begin(), first);
			difference_type	to_erase = ft::distance<iterator>(first, last);
			if (length > 0)
				length--;
			if (to_erase > 0)
				to_erase--;
			manage_array(_capacity, length, 0, to_erase);
			return (iterator(_buffer + length));
		}
		void swap (vector& x) {
			const pointer	tmp_buffer = x._buffer;
			const size_type	tmp_size = x._size;
			const size_type	tmp_capacity = x._capacity;

			x._buffer = _buffer;
			x._size = _size;
			x._capacity = _capacity;
			_buffer = tmp_buffer;
			_size = tmp_size;
			_capacity = tmp_capacity;
		}

	private:
		allocator_type	_alloc;
		T*				_buffer;
		size_type		_capacity;
		size_type		_size;

		/**
		*		Function to manage the reallocation of the array using the Allocator passed at the creation.
		*
		* @param n			The new size to allocate.
		* @param length		The number of first element which will not be affected by this function
		* @param insert		The number of number of space that will be available,
		* 					if offset != 0 the rest of the array will be copy after the offset.
		* @param erase		The number of element to erase
		*/
		void	manage_array(size_type n, size_type length, size_type insert = 0, size_type erase = 0) {
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
			// if insert > erase, we must copy right to left, if not we must copy left to right
			if (insert > erase || (insert && !erase)) // ABC___EF <--
				for (i = n < _size
						? n + insert - erase - 1
						: _size + insert - erase - 1;
					i > length + insert - 1;
					i--) {
						_alloc.construct(new_buffer + i, _buffer[i - insert + erase]);
						if (i - insert + erase >= length + insert)
							_alloc.destroy(_buffer + i - insert + erase);
					}
			else if (insert < erase || (erase && !insert)) // ABC_ --> FGH
				for (i = length + insert;
					i < _size + insert - erase;
					i++) {
						_alloc.destroy(_buffer + i);
						_alloc.construct(new_buffer + i, _buffer[i - insert + erase]);
					}
			// cleaning remaining insert elements
			for (size_type i = length; i < length + insert && i < _size; i++)
				_alloc.destroy(_buffer + i);
			// cleaning remaining erased elements
			for (i = n < _size
					? n + insert - erase
					: _size + insert - erase;
				i < _size;
				i++)
				_alloc.destroy(_buffer + i);
			if (new_buffer != _buffer && _buffer)
				_alloc.deallocate(_buffer, old_capacity);
			_buffer = new_buffer;
			_size += insert - erase;
		}

		// SPECIALIZATION
		template <typename InputIterator>
		void	assign(InputIterator first, InputIterator last, std::input_iterator_tag) {
			clear();
			for (; first != last; first++)
				push_back(*first);
		}
		template <typename Iterator>
		void	assign(Iterator first, Iterator last, std::bidirectional_iterator_tag) {
			size_type 	distance = static_cast<size_type>(ft::distance(first, last));
			size_type	i = 0;
			if (distance < 1)
				return (clear());
			if (distance > _capacity) {
				manage_array(distance, 0);
				for (; first != last; first++)
					_alloc.construct(_buffer + i++, *first);
			}
			else {
				clear();
				for (;i < distance; i++)
					_alloc.construct(_buffer + i, *(first++));
			}
			_size = distance - 1;
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
		void	insert(iterator position, InputIterator first, InputIterator last, typename iterator_traits<InputIterator>::iterator_category) {
			size_type		j = 0;
			difference_type	length = ft::distance<iterator>(begin(), position);
			difference_type	to_insert = static_cast<difference_type>(ft::distance<InputIterator>(first, last));
			if (length > 0)
				length--;
			if (to_insert > 0)
				to_insert--;
			manage_array(_size + to_insert, length, to_insert);
			for (; first != last; first++)
				_alloc.construct(_buffer + length + j++, *first);
			return ;
		}
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(operator==(lhs, rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(operator<(rhs, lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (operator<(rhs, lhs));
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(operator<(lhs, rhs));
	}

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}


#endif
