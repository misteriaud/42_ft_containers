#include "../../hdrs/common.hpp"

TEMPLATE_PRODUCT_TEST_CASE("Vector modifiers", "[vector][modifier]", CONTAINER_TYPES, VALUE_TYPES) {

	typedef typename TestType::value_type 						value_type;
	typedef typename std::vector<value_type>					std_vec;

	// typedef typename TestType::const_iterator					const_iterator;
	// typedef typename std::vector<value_type>::const_iterator	const_std_iterator;

	std_vec ref = Custom::generate_vec<value_type>();
	TestType	vec(ref.begin(), ref.end());
	value_type	tmp = Custom::mocking_value<value_type>();

	// const_std_iterator	ref_it;
	// const_iterator		vec_it;
	SECTION("assign()") {
		REQUIRE(ref.size() == vec.size());
	}

}
