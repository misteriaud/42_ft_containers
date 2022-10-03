
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


class BaseTest {
	private:
		const std::string	_name;
		unsigned int		_age;
	public:
		BaseTest(const std::string name, unsigned int age): _name(name), _age(age) {};
		BaseTest(const BaseTest& ref): _name(ref._name), _age(ref._age) {};
		BaseTest& operator=(const BaseTest& rhs) {
			if (this == &rhs)
				return (*this);
			_age = rhs._age;
			return (*this);
		};
		const std::string	getName() const { return _name; };
		unsigned int 		getAge() const { return _age; };
};

std::ostream& operator<< (std::ostream& out, const BaseTest& character)
{
	out << "Je suis " << character.getName() << " et j'ai " << character.getAge() << " ans";

    return out; // return std::ostream so we can chain calls to operator<<
}



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
		NS::vector<BaseTest>		 	test;
		BaseTest						max("Maxime Riaud", 25);
		BaseTest						alina("Alina Ray Zamora", 31);
		BaseTest						nicolas("Nicolas Riaud", 30);
		NS::vector<BaseTest>::iterator	it;

		typedef NS::vector<BaseTest>::iterator It;

		// s_test a


		test.push_back(max);
		test.push_back(max);
		it = test.begin();
		it++;
		std::cout << "it: " << *it << std::endl;
		test.insert(it, alina);
		for (It i = test.begin(); i != test.end(); i++)
			std::cout << "i: " << *i << std::endl;
		std::cout << test.size() << std::endl;
		it = test.begin();
		// it++;
		test.insert(it, 5, nicolas);
		for (It i = test.begin(); i != test.end(); i++)
			std::cout << "i: " << *i << std::endl;
		std::cout << test.size() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


	return 0;
}
