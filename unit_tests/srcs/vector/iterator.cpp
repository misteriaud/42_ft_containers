#include "../../hdrs/common.hpp"

TEMPLATE_PRODUCT_TEST_CASE("Vector iterator", "[vector]", (std::vector, ft::vector), (int, std::string, std::vector<int>, ft::vector<std::string>)) {

	typedef typename TestType::value_type 						value_type;
	typedef typename TestType::iterator							iterator;
	typedef typename TestType::const_iterator					const_iterator;
	// typedef typename TestType::reverse_iterator					reverse_iterator;
	typedef typename std::vector<value_type>::iterator			std_iterator;
	typedef typename std::vector<value_type>::reverse_iterator	std_r_iterator;

	std::vector<value_type>	range;
	for (size_t i = 0; i < REF_SIZE; i++)
		range.push_back(mocking_value<value_type>());

	std_iterator	range_begin = range.begin();
	std_iterator	range_end = range.end();

	TestType	vec(range_begin, range_end);

	SECTION("same begin && end it") {
		REQUIRE(*range_begin == *vec.begin());
		REQUIRE(*(--range_end) == *(--vec.end()));
	}

	std_r_iterator	range_rbegin = range.rbegin();
	std_r_iterator	range_rend = range.rend();
	SECTION("same reverse_begin && reverse_end it") {
		REQUIRE(*range_rbegin == *vec.rbegin());
		REQUIRE(*(--range_rend) == *(--vec.rend()));
	}

	SECTION("constructor") {
		iterator	it = vec.begin();

		iterator	temp; // default constructor
		(void)temp;

		iterator	it2(it);
		REQUIRE(*it == *it2); // copy constructor

		it++;
		it++;
		it2 = it;
		REQUIRE(*it == *it2); // assignement

		const_iterator	const_it(it);
		REQUIRE(*const_it == *it); // construct iterator from const_iterator
	}

	SECTION("operator==() && operator!=()") {
		iterator	it;
		it = vec.begin();

		REQUIRE((it == vec.begin()) == true);
		REQUIRE((it == vec.end()) == false);
		REQUIRE((it != vec.begin()) == false);
		REQUIRE((it != vec.end()) == true);
	}

	SECTION("mutable operator *it = a") {
		value_type tmp = mocking_value<value_type>();
		*range_begin = tmp;
		*vec.begin() = tmp;

		REQUIRE(*range_begin == *vec.begin());
	}
	SECTION("++it && it++ && --it && it--") {
		std_iterator range_tmp = ++(++(--(++(++range_begin))));
		iterator tmp = ++(++(--(++(++vec.begin()))));

		REQUIRE(*range_tmp == *tmp);
		range_tmp++;
		range_tmp--;
		range_tmp--;
		range_tmp++;
		tmp++;
		tmp--;
		tmp--;
		tmp++;
		REQUIRE(*range_tmp == *tmp);
	}

}
