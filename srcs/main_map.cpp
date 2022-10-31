#include <map.hpp>
#include <string>
#include "../hdrs/RBTree.hpp"

int main()
{
	ft::map<int, std::string>	my_map;
	// ft::map<int, std::string>	my_copy_map;

	my_map.insert(7, "coucou");
	my_map.insert(8, "cfeoucou");
	my_map.insert(2, "yooo");


	ft::map<int, std::string>	my_copy_map(my_map.begin(), my_map.end());
	for (ft::map<int, std::string>::iterator it = my_copy_map.begin(); it != my_copy_map.end(); it++)
		std::cout << (*it).first << ", " << (*it).second << std::endl;



	return 0;
}
