
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


struct s_test {
	const int	a;
	int			b;
};


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

	try
	{
		NS::vector<s_test> 	test;

		// s_test a

		test.push_back()
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


	return 0;
}
