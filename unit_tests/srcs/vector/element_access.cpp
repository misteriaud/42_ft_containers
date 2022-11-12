#include "../../hdrs/common.hpp"
#include <stdexcept>

TEMPLATE_PRODUCT_TEST_CASE("Vector element access", "[vector][access]", CONTAINER_TYPES, VALUE_TYPES) {

	typedef typename TestType::value_type 						value_type;
	typedef typename std::vector<value_type>					std_vec;

	// typedef typename TestType::const_iterator					const_iterator;
	// typedef typename std::vector<value_type>::const_iterator	const_std_iterator;

	const std_vec	ref = Custom::generate_vec<value_type>();
	const TestType	vec(ref.begin(), ref.end());
	// value_type	tmp = Custom::mocking_value<value_type>();

	// const_std_iterator	ref_it;
	// const_iterator		vec_it;


	SECTION("operator[]") {
		REQUIRE(ref[0] == vec[0]);
		REQUIRE(ref[ref.size() /2 ] == vec[vec.size() / 2]);
		REQUIRE(ref[ref.size() - 1] == vec[vec.size() - 1]);

		const value_type& tmp = vec[REF_SIZE / 2];
		REQUIRE(ref[REF_SIZE /2 ] == tmp);
	}

	SECTION("at()") {
		TestType	empty_vec;

		REQUIRE(ref.at(0) == vec.at(0));
		REQUIRE(ref.at(REF_SIZE / 2) == vec.at(REF_SIZE / 2));
		REQUIRE(ref.at(REF_SIZE - 1) == vec.at(REF_SIZE - 1));

		const value_type& tmp = vec.at(REF_SIZE / 2);
		REQUIRE(ref.at(REF_SIZE / 2) == tmp);

		REQUIRE_THROWS_AS(vec.at(-1), std::out_of_range);
		REQUIRE_THROWS_AS(vec.at(REF_SIZE), std::out_of_range);
		REQUIRE_THROWS_AS(empty_vec.at(0), std::out_of_range);
	}
	SECTION("front()") {
		REQUIRE(vec.front() == ref.front());
	}
	SECTION("back()") {
		REQUIRE(vec.back() == ref.back());
	}
}
