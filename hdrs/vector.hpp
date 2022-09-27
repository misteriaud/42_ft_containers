#pragma once
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterators/RandomAccessIterator.hpp"

namespace ft {

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
		typedef ft::RandomAccessIterator<T>			iterator;
		typedef ft::RandomAccessIterator<const T>	const_iterator;

		vector(): _pool(new T[50]) {
			_pool[1] = "test";
		};
		vector(const vector&);
		vector&	operator=(const vector&);
		~vector() {};
		iterator	begin() {
			return iterator(_pool);
		}

	private:
		T*	_pool;

	};
}


#endif
