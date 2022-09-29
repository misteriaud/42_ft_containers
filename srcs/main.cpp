
#include <string>
#include <iostream>

#if 1
# include "../hdrs/vector.hpp"
# define NS ft
#else
# include <vector>
# define NS std
#endif



int main(void)
{
	NS::vector<std::string>	test;

	test.push_back("coucou");
	NS::vector<std::string>::iterator	it = test.begin();
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
