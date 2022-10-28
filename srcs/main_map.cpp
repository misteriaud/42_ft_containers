#include <map.hpp>
#include <string>
#include "../hdrs/RBTree.hpp"

int main()
{
	ft::map<int, std::string>	my_map;
	ft::RBTree<int>					my_tree;

	my_map.insert(7, "coucou");
	my_map.insert(7, "cfeoucou");
	my_tree.insert(10);

	return 0;
}
