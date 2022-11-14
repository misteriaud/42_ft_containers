#include "../../hdrs/common.hpp"

TEST_CASE("Vector capacity", "[vector][capacity]") {

	StdVec				ref = Custom::generate_vec<TestValueType>();
	TestContainerType	vec(ref.begin(), ref.end());
	TestValueType		tmp = Custom::mocking_value<TestValueType>();

	SECTION("size()") {
		REQUIRE(ref.size() == vec.size());
	}
	SECTION("max_size()") {
		CHECK(ref.max_size() == vec.max_size());
	}
	SECTION("resize()") {
		ref.resize(REF_SIZE / 2);
		vec.resize(REF_SIZE / 2);
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(ref));

		ref.resize(REF_SIZE * 2, tmp);
		vec.resize(REF_SIZE * 2, tmp);
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(ref));

		ref.resize(ref.size());
		vec.resize(ref.size());
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(ref));

	}
	SECTION("resize(n) with  n > max_size() - IF STUCK HERE -> MAY BE CAUSED BY SLOW IMPLEMENTATION OF RESIZE") {
		REQUIRE_THROWS(vec.resize(vec.max_size() * 2)); // IF STUCK HERE -> MAY BE CAUSED BY SLOW IMPLEMENTATION OF RESIZE
	}

	SECTION("empty()") {
		TestContainerType tmp_vec;
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
