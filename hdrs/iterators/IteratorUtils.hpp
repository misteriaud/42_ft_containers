#pragma once
#ifndef ITERATORUTILS_HPP
# define ITERATORUTILS_HPP

namespace ft {

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template< class InputIt >
	typename std::iterator_traits<InputIt>::difference_type
	distance( InputIt first, InputIt last ) {
		typename std::iterator_traits<InputIt>::difference_type i = 0;
		if (first == last)
			return (0);
		while (first++ != last)
			i++;
		return (i + 1);
	}

}

#endif
