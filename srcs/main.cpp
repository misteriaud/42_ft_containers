#include "../hdrs/vector.hpp"

#include <string>
#include <iostream>

int main(void)
{
	ft::vector<std::string>	test;

	ft::vector<std::string>::iterator	it = test.begin();

	std::cout << it[1] << std::endl;

	return 0;
}
