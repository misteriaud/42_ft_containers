#include "../../hdrs/common.hpp"

TEST_CASE("Stacktor constructors", "[stack][constructor]") {

	SECTION("default constructor") {

		StdStackCont	std_cont = Custom::mocking_value<StdStackCont>();
		StackCont		cont(std_cont.begin(), std_cont.end());

		StdStack		std_stack(std_cont);
		Stack			stack(cont);

		// REQUIRE(Custom::equal(std_cont.begin(), std_cont.end(), cont.begin(), cont.end()));
		REQUIRE_THAT(stack, Custom::StackEqual<Stack>(std_stack));
	}
}
