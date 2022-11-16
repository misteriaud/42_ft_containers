#include "../../hdrs/common.hpp"

TEST_CASE("Vector assignement operator", "[vector]") {

	StdVec	std_vec(3);

	SECTION("simple assignation test") {
		Vec	foo(3);
		Vec	bar(5);

		bar = foo;

		REQUIRE(bar.size() == 3);
	}
}
