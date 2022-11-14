#include "../../hdrs/common.hpp"

TEST_CASE("Vector non-members functions", "[vector][modifier]") {

	StdVec 				ref = Custom::generate_vec<TestValueType>();
	StdVec				tmp;
	TestContainerType	vec;
	TestValueType		tmp_val = Custom::mocking_value<TestValueType>();

	SECTION("assign(first, last)") {

	}
}
