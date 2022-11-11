#include "../hdrs/common.hpp"

template <>
std::string mocking_value<std::string>() {
	size_t string_size = rand() % 50;
	std::string result;

	for (size_t i = 0; i < string_size; i++)
		result.push_back(rand() % 26 + 97);

	return (result);
}
