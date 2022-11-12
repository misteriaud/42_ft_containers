#include "../../hdrs/common.hpp"

#define FILE_PATH "./unit_test"

TEST_CASE("Vector constructors", "[vector][constructor]") {

	srand (time(NULL));


	SECTION("default constructor") {
		TestContainerType	vec;

		REQUIRE(vec.size() == 0);
	}

	SECTION("fill constructor w/ n < 0") {
		TestContainerType*	vec = NULL;
		REQUIRE_THROWS(vec = new TestContainerType(-100));
	}
	SECTION("fill constructor w/ n == 0") {
		TestContainerType	vec(0);

		REQUIRE(vec.size() == 0);
	}
	SECTION("fill constructor w/ n > 0") {
		TestContainerType	vec(1000);

		REQUIRE(vec.size() == 1000);
		REQUIRE(vec.capacity() >= 1000);
	}

	StdVec range = Custom::generate_vec<TestValueType>();

	StdVecIt	range_begin = range.begin();
	StdVecIt	range_end = range.end();

	SECTION("range constructor begin-end") {
		TestContainerType	vec(range_begin, range_end);

		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(range));
	}
	SECTION("range constructor somwhere-end") {
		++(++(range_begin));
		StdVec		ref(range_begin, range_end);
		TestContainerType	vec(range_begin, range_end);

		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(ref));
	}
	SECTION("range constructor somwhere-end") {
		--(--(range_end));
		StdVec		ref(range_begin, range_end);
		TestContainerType	vec(range_begin, range_end);

		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(ref));
	}
	SECTION("range with strict input_iterator") {
		typedef std::istream_iterator<char>	is_iterator;
		std::ifstream		file;
		is_iterator			my_it;

		file.open(FILE_PATH);
		my_it = is_iterator(file);
		ft::vector<char>	vec(my_it, is_iterator());

		file.close();
		file.open(FILE_PATH);
		my_it = is_iterator(file);
		REQUIRE(Custom::equal(my_it, is_iterator(), vec.begin(), vec.end()) == true);
		file.close();
	}


	SECTION("copy constructor") {
		TestContainerType	origin_vec(++(++range_begin), --(--(--range_end)));
		TestContainerType	copy_vec(origin_vec);

		REQUIRE(Custom::same_vec(origin_vec, copy_vec) == true);
	}
}
