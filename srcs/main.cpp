
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "../hdrs/colors.h"

#if 1
# include "../hdrs/vector.hpp"
# define NS ft
#else
# include <vector>
# define NS std
#endif

#define TESTED_TYPE int

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
	// try
	// {
	// 	NS::vector<std::string>	test;
	// 	NS::vector<std::string>	test2;

	// 	test.push_back("un");
	// 	test.push_back("deux");
	// 	test.push_back("trois");
	// 	test.push_back("quatre");

	// 	// test2.assign(500, "coucou");
	// 	test.assign(test.begin(), test.end());
	// 	// test.assign(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>());
	// 	/* code */
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }

	try
	{
		// NS::vector<BaseTest>		 	test;
		// BaseTest						max("Maxime Riaud", 25);
		// BaseTest						alina("Alina Ray Zamora", 31);
		// BaseTest						nicolas("Nicolas Riaud", 30);
		// NS::vector<BaseTest>::iterator	it;

		// typedef NS::vector<BaseTest>::iterator It;

		// // s_test a

		// std::cout << BOLDWHITE << "insert max 2 times\n" << RESET;
		// test.push_back(max);
		// test.push_back(max);
		// it = test.begin();
		// it++;
		// std::cout << "it: " << *it << std::endl;
		// std::cout << BOLDWHITE << "insert Alina in the middle\n" << RESET;
		// test.insert(it, alina);
		// std::cout << BOLDWHITE << "Content of test vector:\n" << RESET;
		// for (It i = test.begin(); i != test.end(); i++)
		// 	std::cout << "i: " << *i << std::endl;
		// std::cout << test.size() << std::endl;
		// it = test.begin();
		// // it++;
		// std::cout << BOLDWHITE << "insert Nicolas at the begining 5 times\n" << RESET;
		// test.insert(it, 5, nicolas);
		// std::cout << BOLDWHITE << "Content of test vector:\n" << RESET;
		// for (It i = test.begin(); i != test.end(); i++)
		// 	std::cout << "i: " << *i << std::endl;
		// std::cout << test.size() << std::endl;

		// NS::vector<BaseTest>		toFill;
		// BaseTest						nathan("Nathan Alhachimi", 24);
		// BaseTest						leslie("Leslie Gaborieau", 26);
		// toFill.push_back(nathan);
		// toFill.push_back(leslie);
		// toFill.push_back(nathan);
		// it = toFill.begin();
		// it++;
		// toFill.insert(it, test.begin(), test.end());

		// std::cout << BOLDWHITE << " Content of toFill vector:\n" << RESET;
		// for (It i = toFill.begin(); i != toFill.end(); i++)
		// 	std::cout << "i: " << *i << std::endl;
		// std::cout << toFill.size() << std::endl;

		// it = toFill.begin();
		// it++;
		// it++;
		// it++;
		// toFill.erase(it);
		// std::cout << BOLDWHITE << " Content of toFill vector after erase:\n" << RESET;
		// for (It i = toFill.begin(); i != toFill.end(); i++)
		// 	std::cout << "i: " << *i << std::endl;
		// std::cout << toFill.size() << std::endl;

		// it = toFill.begin();
		// it++;
		// it++;
		// it++;
		// toFill.erase(it, toFill.end());
		// std::cout << BOLDWHITE << " Content of toFill vector after erase range:\n" << RESET;
		// for (It i = toFill.begin(); i != toFill.end(); i++)
		// 	std::cout << "i: " << *i << std::endl;
		// std::cout << toFill.size() << std::endl;

		// toFill.swap(test);
		// std::cout << BOLDWHITE << " Content of toFill vector after swap:\n" << RESET;
		// for (It i = toFill.begin(); i != toFill.end(); i++)
		// 	std::cout << "i: " << *i << std::endl;
		// std::cout << toFill.size() << std::endl;

		// NS::vector<int>		intvec;

		// intvec.push_back(1);
		// intvec.push_back(2);
		// intvec.push_back(3);
		// intvec.push_back(4);
		// intvec.push_back(5);

		// intvec.assign(5, 7);
		// std::cout << BOLDWHITE << " Content of intvec vector after assign:\n" << RESET;
		// for (NS::vector<int>::iterator i = intvec.begin(); i != intvec.end(); i++)
		// 	std::cout << "i: " << *i << std::endl;
		// std::cout << intvec.size() << std::endl;

		// NS::vector<std::string>					myvect;
		// for(size_t i = 0; i < 10; i++)
		// 	myvect.push_back("coucou");

		// NS::vector<std::string>::const_iterator	cit = myvect.begin();
		// for(; cit != myvect.end(); cit++)
		// 	std::cout << *cit << std::endl;

		NS::vector<TESTED_TYPE> foo(3, 15);
		NS::vector<TESTED_TYPE> bar(5, 42);

		NS::vector<TESTED_TYPE>::const_iterator it_foo = foo.begin();
		NS::vector<TESTED_TYPE>::const_iterator it_bar = bar.begin();
		for(; it_foo != foo.end(); it_foo++)
			std::cout << *it_foo << std::endl;
		for(; it_bar != bar.end(); it_bar++)
			std::cout << *it_bar << std::endl;




	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


	return 0;
}
