#include <map.hpp>
#include <string>
#include <vector.hpp>
#include "../hdrs/RBTree.hpp"

#define PAIR(a, b) (ft::make_pair<int, std::string>(a, b))

template <typename T1, typename T2>
void 	print_map(ft::map<T1, T2>& to_print) {

	typedef typename ft::map<T1, T2>::iterator iterator;

	std::cout << std::endl << "Le map: \n";
	for (iterator it = to_print.begin(); it != to_print.end(); it++)
		std::cout << (*it).first << ", " << (*it).second << std::endl;
}

int main()
{
	typedef typename ft::map<int, std::string>::iterator iterator;
	ft::map<int, std::string>	my_map;
	ft::pair<iterator, bool > ret;
	// ft::map<int, std::string>	my_copy_map;

	my_map.insert(PAIR(7, "coucou"));
	my_map.insert(PAIR(8, "cfeoucou"));
	my_map.insert(PAIR(85, "le dernier"));
	my_map.insert(PAIR(80, "cfeoucou"));

	print_map(my_map);

	ft::vector<ft::pair<int, std::string> > my_vec;

	my_vec.push_back(PAIR(1, "un"));
	my_vec.push_back(PAIR(2, "deux"));
	my_vec.push_back(PAIR(3, "trois"));
	my_vec.push_back(PAIR(4, "quatre"));
	my_vec.push_back(PAIR(5, "cinq"));
	my_vec.push_back(PAIR(6, "six"));

	my_map.insert(my_vec.begin(), my_vec.end());


	print_map(my_map);

	for (iterator ite = my_map.begin(); ite != my_map.end(); ite++)
		my_map.erase(ite);
	// std::cout << (my_map.erase(8) ? "true" : "false") << std::endl;
	print_map(my_map);


	return 0;
}
