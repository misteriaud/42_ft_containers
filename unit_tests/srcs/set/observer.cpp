#include "../../hdrs/common.hpp"

TEST_CASE("Set observer", "[set][observer]") {

	Set				set;

	SECTION("key_comp()") {
		typename Set::key_compare	tmp_key_comp = set.key_comp();

		set.insert(Custom::mocking_value<ValueType>());
		set.insert(Custom::mocking_value<ValueType>());
		REQUIRE(tmp_key_comp(*set.begin(), *(++set.begin())) == true);
	}
	SECTION("value_comp()") {
		typename Set::value_compare	tmp_value_comp = set.value_comp();

		set.insert(Custom::mocking_value<ValueType>());
		set.insert(Custom::mocking_value<ValueType>());
		REQUIRE(tmp_value_comp(*set.begin(), *(++set.begin())) == true);
	}

};
