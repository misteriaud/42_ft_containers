#pragma once
#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft {

	template< typename Iter >
	struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template< typename T >
	struct iterator_traits< T* > {
		typedef			 std::ptrdiff_t					difference_type;
		typedef 		 T								value_type;
		typedef 		 T*								pointer;
		typedef 		 T&								reference;
		typedef typename ft::random_access_iterator_tag	iterator_category;
	};

	template< typename T >
	struct iterator_traits< const T* >: iterator_traits < T* > {
		typedef 		 const T*						pointer;
		typedef 		 const T&						reference;
	};
}


#endif
