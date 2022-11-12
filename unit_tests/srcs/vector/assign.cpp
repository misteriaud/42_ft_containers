#include "../../hdrs/common.hpp"

TEST_CASE("Vector assignement operator", "[vector]") {

	StdVec	std_vec(3);

	SECTION("simple assignation test") {
		TestContainerType	foo(3);
		TestContainerType	bar(5);

		bar = foo;

		REQUIRE(bar.size() == 3);
	}
}
