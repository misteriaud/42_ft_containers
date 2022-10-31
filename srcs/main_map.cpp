#include <map.hpp>
#include <string>
#include "../hdrs/RBTree.hpp"

int main()
{
	ft::map<int, std::string>	my_map;
	ft::RBTree<int>					my_tree;

	my_map.insert(7, "coucou");
	my_map.insert(8, "cfeoucou");
	// my_tree.insert(10);
	// my_tree.insert(12);
	// my_tree.insert(7);
	// my_tree.insert(5);
	// my_tree.insert(15);
	// my_tree.find(7);


	return 0;
}
