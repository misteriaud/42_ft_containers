#include "../../hdrs/common.hpp"

#define FILE_PATH "./unit_test"

TEMPLATE_PRODUCT_TEST_CASE("Vector constructors", "[vector][constructor]", CONTAINER_TYPES, VALUE_TYPES) {

	srand (time(NULL));

	typedef typename TestType::value_type 				value_type;
	typedef typename std::vector<value_type>			std_vec;
	typedef typename std::vector<value_type>::iterator	std_iterator;

	SECTION("default constructor") {
		TestType	vec;

		REQUIRE(vec.size() == 0);
		REQUIRE(vec.capacity() >= 0);
	}

	SECTION("fill constructor w/ n < 0") {
		TestType*	vec = NULL;
		CHECK_THROWS(vec = new TestType(-100));
	}
	SECTION("fill constructor w/ n == 0") {
		TestType	vec(0);

		REQUIRE(vec.size() == 0);
		REQUIRE(vec.capacity() >= 0);
	}
	SECTION("fill constructor w/ n > 0") {
		TestType	vec(1000);

		REQUIRE(vec.size() == 1000);
		REQUIRE(vec.capacity() >= 1000);
	}

	std_vec range = generate_vec<value_type>();

	std_iterator	range_begin = range.begin();
	std_iterator	range_end = range.end();

	SECTION("range constructor begin-end") {
		TestType	vec(range_begin, range_end);

		REQUIRE_THAT(vec, VectorEqual<TestType>(range));
	}
	SECTION("range constructor somwhere-end") {
		++(++(range_begin));
		std_vec		ref(range_begin, range_end);
		TestType	vec(range_begin, range_end);

		REQUIRE_THAT(vec, VectorEqual<TestType>(ref));
	}
	SECTION("range constructor somwhere-end") {
		--(--(range_end));
		std_vec		ref(range_begin, range_end);
		TestType	vec(range_begin, range_end);

		REQUIRE_THAT(vec, VectorEqual<TestType>(ref));
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
		REQUIRE(ft::equal(my_it, is_iterator(), vec.begin(), vec.end()) == true);
		file.close();
	}


	SECTION("copy constructor") {
		TestType	origin_vec(++(++range_begin), --(--(--range_end)));
		TestType	copy_vec(origin_vec);

		REQUIRE(same_vec(origin_vec, copy_vec) == true);
	}
}
