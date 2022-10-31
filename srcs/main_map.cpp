#include <map.hpp>
#include <string>
#include <vector.hpp>
#include "../hdrs/RBTree.hpp"

#define PAIR(a, b) (ft::make_pair<int, std::string>(a, b))

int main()
{
	typedef typename ft::map<int, std::string>::iterator iterator;
	ft::map<int, std::string>	my_map;
	ft::pair<iterator, bool > ret;
	// ft::map<int, std::string>	my_copy_map;

	my_map.insert(PAIR(7, "coucou"));
	ret = my_map.insert(PAIR(8, "cfeoucou"));
	std::cout << ret.first->value.first << ", " << ret.second << std::endl;
	my_map.insert(PAIR(2, "yooo"));
	std::string	&str_ref = my_map[1];
	std::cout << str_ref << std::endl;
	str_ref = "Moi c'est max";
	ret = my_map.insert(PAIR(85, "le dernier"));
	std::cout << ret.first->value.first << ", " << ret.second << std::endl;
	ret = my_map.insert(PAIR(80, "cfeoucou"));
	std::cout << ret.first->value.first << ", " << ret.second << std::endl;

	iterator test = my_map.insert(ret.first, PAIR(81, "insert with hint"));
	std::cout << (*test).second << std::endl;

	ft::map<int, std::string>	my_copy_map(my_map.begin(), my_map.end());
	for (ft::map<int, std::string>::iterator it = my_copy_map.begin(); it != my_copy_map.end(); it++)
		std::cout << (*it).first << ", " << (*it).second << std::endl;


	ft::vector<ft::pair<int, std::string> > my_vec;

	my_vec.push_back(PAIR(1, "un"));
	my_vec.push_back(PAIR(2, "deux"));
	my_vec.push_back(PAIR(3, "trois"));
	my_vec.push_back(PAIR(4, "quatre"));
	my_vec.push_back(PAIR(5, "cinq"));
	my_vec.push_back(PAIR(6, "six"));

	my_map.insert(my_vec.begin(), my_vec.end());

	std::cout << std::endl << "Le map: \n";
	for (ft::map<int, std::string>::iterator it = my_map.begin(); it != my_map.end(); it++)
		std::cout << (*it).first << ", " << (*it).second << std::endl;


	return 0;
}
