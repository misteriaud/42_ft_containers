#pragma once
#ifndef EQUAL_HPP
# define EQUAL_HPP

namespace ft {
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1,
					InputIterator2 first2, InputIterator2 last2) {
		while (first1!=last1 && first2!=last2) {
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		if (first1 == last1 && first2 == last2)
			return true;
		return false;
	};
}

#endif
