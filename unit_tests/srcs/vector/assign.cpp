#include "../../hdrs/common.hpp"

TEMPLATE_PRODUCT_TEST_CASE("Vector assignement operator", "[vector][constructor]", (std::vector, ft::vector), (int, std::string, std::vector<int>, ft::vector<std::string>)) {

	typedef typename TestType::value_type 				value_type;
	// typedef typename std::vector<value_type>::iterator	std_iterator;

	std::vector<value_type>	std_vec(3);

	SECTION("simple assignation test") {
		TestType	foo(3);
		TestType	bar(5);

		bar = foo;

		REQUIRE(bar.size() == 3);
	}
}
