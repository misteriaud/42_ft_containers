#include "../hdrs/common.hpp"

template <>
std::string mocking_value<std::string>() {
	size_t string_size = mocking_value<size_t>();
	std::string result;

	for (size_t i = 0; i < string_size; i++)
		result.push_back(rand() % 128);

	return (result);
}
