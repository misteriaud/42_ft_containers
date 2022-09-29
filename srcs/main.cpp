
#include <string>
#include <iostream>
#include <algorithm>

#if 1
# include "../hdrs/vector.hpp"
# define NS ft
#else
# include <vector>
# define NS std
#endif



int main(void)
{
	NS::vector<size_t>	test;

	for (size_t i = 0; i < 10; i++)
	{
		test.push_back(i);
		std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << std::endl;

	}

	NS::vector<size_t>::iterator	it = test.begin();
	for (; it != test.end(); it++)
		std::cout << *it << std::endl;

	// NS::vector<std::string>::iterator	it = test.begin();
	// NS::vector<std::string>::iterator	it2 = test.begin();

	// *it = "coucou";
	// it2++;
	// it2++;
	// it2++;
	// it2++;
	// std::cout << *it << std::endl;
	// it = it2;
	// *it2 = "test";
	// std::cout << *it << std::endl;

	return 0;
}
