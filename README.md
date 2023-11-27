# ft_containers - C++ Standard Template Library Containers

## Introduction

This project involves the implementation of key C++ Standard Template Library (STL) containers, adhering to the C++98 standard. The primary focus is on recoding containers `vector`, `map`, `set` and `stack` while incorporating essential C++98 features.

## Usage
```sh
git clone https://github.com/misteriaud/42_ft_containers.git

g++ your_file.cpp -I42_ft_containers -Wall -Wextra -Werror
```

### Types definitions
```c++
#include <vector.hpp>
#include <map.hpp>
#include <stack.hpp>
#include <set.hpp>

// VECTOR: dynamically reallocated array
ft::vector<T>					vec;
ft::vector<T>::iterator				v_it  = vec.begin();
ft::vector<T>::const_iterator			v_cit = vec.begin();
ft::vector<T>::const_reverse_iterator		v_rit = vec.rbegin();

// MAP: RedBlack Tree data structure
ft::map<KEY_TYPE, MAPPED_TYPE>				map;
ft::map<KEY_TYPE, MAPPED_TYPE>::iterator		m_it = map.begin();
ft::map<KEY_TYPE, MAPPED_TYPE>::const_iterator		m_cit = map.begin();
ft::map<KEY_TYPE, MAPPED_TYPE>::const_reverse_iterator	m_rit = map.rbegin();
ft::pair<const KEY_TYPE, MAPPED_TYPE>			pair = *it;

// STACK: Overlay on other container, providing stack features
ft::stack<T, ft::vector<T>>			stack;

// SET: RedBlack Tree data structure
ft::set<T>				set;
ft::set<T>::iterator			s_it = set.begin();
ft::set<T>::const_iterator		s_cit = set.begin();
ft::set<T>::const_reverse_iterator	s_rit = set.rbegin();
```
### Additional Components
- `ft::iterators_traits`
- `ft::reverse_iterator`
- `ft::enable_if`
- `ft::is_integral`
- `ft::equal` and/or `ft::lexicographical_compare`
- `ft::pair`
- `ft::make_pair`


## Tests and benchmarks
This project was done with a ***Test-driven development*** approach using the powerful [Catch2](https://github.com/catchorg/Catch2) library.
All the tests are available in the `/unit_tests` directory.
You can run them the following way:
```sh
git clone https://github.com/misteriaud/42_ft_containers.git

cd 42_ft_containers/unit_tests
make

./unit_test

# for benchmarks
./unit_test "[benchmark]" -d yes
```

Feel free to use them for your own implementation, you can find them here: [GitHub - Unit tester written with Catch2 in C++98 to test your home made implementation of stl containers vector, map, stack and set.](https://github.com/misteriaud/stl_containters_unit_tester)

## References

Use [cplusplus.com](https://www.cplusplus.com/) and [cppreference.com](https://cppreference.com/) as references.
