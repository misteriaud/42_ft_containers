#pragma once
#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

#include <string>
#include <ostream>

namespace ft {

	template<typename It, typename T>
	class ReverseIterator {
	private:
		It base() const { return current; }

	protected:
		It current = It();

	public:
		reverse_iterator() = default;
		reverse_iterator(It itr) : current(itr) {}
		T operator*() const {
			return *std::prev(current); // <== returns the content of prev
		}

		reverse_iterator& operator++() { --current; return *this; }
		reverse_iterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }

		reverse_iterator& operator--() { ++current; return *this; }
		reverse_iterator operator--(int) { auto tmp = *this; --(*this); return tmp; }
	};

}

#endif
