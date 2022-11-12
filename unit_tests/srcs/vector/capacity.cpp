
#include "../../hdrs/common.hpp"

TEMPLATE_PRODUCT_TEST_CASE("Vector capacity", "[vector][capacity]", CONTAINER_TYPES, VALUE_TYPES) {

	typedef typename TestType::value_type 						value_type;
	typedef typename std::vector<value_type>					std_vec;

	// typedef typename TestType::const_iterator					const_iterator;
	// typedef typename std::vector<value_type>::const_iterator	const_std_iterator;

	std_vec ref = Custom::generate_vec<value_type>();
	TestType	vec(ref.begin(), ref.end());
	value_type	tmp = Custom::mocking_value<value_type>();

	// const_std_iterator	ref_it;
	// const_iterator		vec_it;

	SECTION("size()") {
		REQUIRE(ref.size() == vec.size());
	}
	SECTION("max_size()") {
		CHECK(ref.max_size() == vec.max_size());
	}
	SECTION("resize()") {
		ref.resize(REF_SIZE / 2);
		vec.resize(REF_SIZE / 2);
		REQUIRE_THAT(vec, Custom::VectorEqual<TestType>(ref));

		ref.resize(REF_SIZE * 2, tmp);
		vec.resize(REF_SIZE * 2, tmp);
		REQUIRE_THAT(vec, Custom::VectorEqual<TestType>(ref));

		ref.resize(ref.size());
		vec.resize(ref.size());
		REQUIRE_THAT(vec, Custom::VectorEqual<TestType>(ref));

		REQUIRE_THROWS(ref.resize(ref.max_size() * 2)); // IF STUCK HERE -> MAY BE CAUSED BY SLOW IMPLEMENTATION OF RESIZE
		REQUIRE_THROWS(vec.resize(vec.max_size() * 2)); // IF STUCK HERE -> MAY BE CAUSED BY SLOW IMPLEMENTATION OF RESIZE
	}
	SECTION("empty()") {
		TestType tmp_vec;
		REQUIRE(tmp_vec.empty());
		REQUIRE_FALSE(vec.empty());
	}
	SECTION("reserve() && capacity()") {
		size_t old_capacity = vec.capacity();
		vec.reserve(vec.capacity() / 2);
		REQUIRE(vec.capacity() == old_capacity);

		vec.reserve(vec.capacity());
		REQUIRE(vec.capacity() == old_capacity);

		size_t to_reserve = Custom::mocking_value<size_t>();
		vec.reserve(vec.capacity() + to_reserve);
		REQUIRE(vec.capacity() >= old_capacity + to_reserve);
	}

}
