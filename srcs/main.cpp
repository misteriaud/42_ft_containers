
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

#if 0
# include "../hdrs/vector.hpp"
# define NS ft
#else
# include <vector>
# define NS std
#endif



int main(void)
{
	// {
	// 	NS::vector<size_t>	test;

	// 	for (size_t i = 0; i < 10; i++)
	// 	{
	// 		test.push_back(i);
	// 		std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << std::endl;
	// 	}

	// 	NS::vector<size_t>::iterator	it = test.begin();
	// 	for (; it != test.end(); it++)
	// 		std::cout << *it << std::endl;
	// }
	try
	{
		NS::vector<std::string>	test;
		NS::vector<std::string>	test2;

		test.push_back("un");
		test.push_back("deux");
		test.push_back("trois");
		test.push_back("quatre");

		// test2.assign(500, "coucou");
		test.assign(test.begin(), test.end());
		// test.assign(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>());
		/* code */
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

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
