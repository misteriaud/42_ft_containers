#include "../../hdrs/common.hpp"

#define FILE_PATH "./unit_test"

TEMPLATE_PRODUCT_TEST_CASE("Vector constructors", "[vector]", (std::vector, ft::vector), (int, std::string, std::vector<int>, ft::vector<std::string>)) {

	srand (time(NULL));

	typedef typename TestType::value_type 				value_type;
	typedef typename std::vector<value_type>::iterator	std_iterator;
	// typedef typename TestType::iterator 				iterator;

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


	std::vector<value_type>	range;
	for (size_t i = 0; i < REF_SIZE; i++)
		range.push_back(mocking_value<value_type>());

	std_iterator	range_begin = range.begin();
	std_iterator	range_end = range.end();

	SECTION("range constructor begin-end") {
		TestType	vec(range_begin, range_end);

		REQUIRE(ft::equal(range_begin, range_end, vec.begin(), vec.end()) == true);
	}
	SECTION("range constructor somwhere-end") {
		TestType	vec(++(++range_begin), range_end);

		REQUIRE(ft::equal(range_begin, range_end, vec.begin(), vec.end()) == true);
	}
	SECTION("range constructor somwhere-end") {
		TestType	vec(++(++range_begin), --(--(--range_end)));

		REQUIRE(ft::equal(range_begin, range_end, vec.begin(), vec.end()) == true);
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
