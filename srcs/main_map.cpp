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
		std::cout << it->first << ", " << it->second << std::endl;
}

int main()
{
	typedef ft::map<int, std::string>::iterator iterator;
	typedef ft::map<int, std::string>::const_iterator const_iterator;
	ft::map<int, std::string>	my_map;
	ft::pair<iterator, bool > ret;
	// ft::map<int, std::string>	my_copy_map;

	my_map.insert(PAIR(7, "coucou"));
	my_map.insert(PAIR(8, "cfeoucou"));
	my_map.insert(PAIR(85, "le dernier"));
	const_iterator it = my_map.begin();
	my_map.insert(PAIR(80, "cfeoucou"));

	print_map(my_map);

	std::cout << "it: " << it->first << ", " << it->second << std::endl;

	ft::vector<ft::pair<int, std::string> > my_vec;

	ft::map<int, std::string>	my_copy_map(my_map);

	my_vec.push_back(PAIR(1, "un"));
	my_vec.push_back(PAIR(2, "deux"));
	my_vec.push_back(PAIR(3, "trois"));
	my_vec.push_back(PAIR(4, "quatre"));
	my_vec.push_back(PAIR(5, "cinq"));
	my_vec.push_back(PAIR(6, "six"));

	my_map.insert(my_vec.begin(), my_vec.end());

	std::cout << "\nAvant echange:\n";
	print_map(my_map);
	print_map(my_copy_map);

	iterator temp = my_map.begin();
	my_map.swap(my_copy_map);

	std::cout << "\nApres echange:\n";
	print_map(my_map);
	print_map(my_copy_map);

	std::cout << (*temp).first << ", " << (*temp).second << std::endl;

	std::cout << "==================\n";

	for (iterator i = my_copy_map.find(13); i != my_copy_map.end(); i++)
		std::cout << i->first << ", " << i->second << std::endl;





	return 0;
}
