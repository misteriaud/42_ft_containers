
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "../hdrs/colors.h"

#if 0
// # include "../hdrs/vector.hpp"
# include <vector>
# define NS ft
#else
# include <vector>
# include <map>
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
	NS::vector<const int>	my_vec;
	std::cout << my_vec.size() << std::endl;
	return 0;
}
