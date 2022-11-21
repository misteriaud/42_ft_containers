#include "../../hdrs/common.hpp"

TEST_CASE("Map iterator", "[map][iterator]") {

	StdMap	ref = Custom::mocking_value<StdMap>();
	Map		map;
	Custom::copy_map(ref, map);

	SECTION("same begin && end it") {
		REQUIRE(*ref.begin() == *map.begin());
		REQUIRE(*(--ref.end()) == *(--map.end()));
	}

	SECTION("same reverse_begin && reverse_end it") {
		REQUIRE(*ref.rbegin() == *map.rbegin());
		REQUIRE(*(--ref.rend()) == *(--map.rend()));
	}

	SECTION("constructor") {
		MapIt	it = map.begin();

		MapIt	temp; // default constructor
		(void)temp;

		MapIt	it2(it);
		REQUIRE(*it == *it2); // copy constructor

		it++;
		it++;
		it2 = it;
		REQUIRE(*it == *it2); // assignement

		MapConstIt	const_it(it);
		REQUIRE(*const_it == *it); // construct iterator from const_iterator
	}

	SECTION("operator==() && operator!=()") {
		MapIt	it;
		it = map.begin();

		REQUIRE((it == map.begin()) == true);
		REQUIRE((it == map.end()) == false);
		REQUIRE((it != map.begin()) == false);
		REQUIRE((it != map.end()) == true);
	}

	SECTION("mutable operator *it = a") {
		MapSecondType tmp_second = Custom::mocking_value<MapSecondType>();

		ref.begin()->second = tmp_second;
		map.begin()->second = tmp_second;

		REQUIRE(*ref.begin() == *map.begin());
	}

	StdMapConstIt	ref_tmp = ++(++(--(++(++ref.begin()))));
	MapConstIt		 tmp = ++(++(--(++(++map.begin()))));

	StdMapConstRevIt	r_ref_tmp = ++(++(--(++(++ref.rbegin()))));
	MapConstRevIt		r_tmp = ++(++(--(++(++map.rbegin()))));

	SECTION("++it && --it") {
		REQUIRE(*ref_tmp == *tmp);
		REQUIRE(*r_ref_tmp == *r_tmp);
	}
	SECTION("it++ && it--") {
		ref_tmp++;
		ref_tmp--;
		ref_tmp++;
		tmp++;
		tmp--;
		tmp++;
		REQUIRE(*ref_tmp == *tmp);

		r_ref_tmp++;
		r_ref_tmp--;
		r_ref_tmp++;
		r_tmp++;
		r_tmp--;
		r_tmp++;
		REQUIRE(*r_ref_tmp == *r_tmp);
	}
	SECTION("*it++ && *it--") {
		REQUIRE(*ref_tmp == *tmp);
		REQUIRE(*ref_tmp++ == *tmp++);
		REQUIRE(*ref_tmp-- == *tmp--);
		REQUIRE(*ref_tmp == *tmp);

		REQUIRE(*r_ref_tmp == *r_tmp);
		REQUIRE(*r_ref_tmp++ == *r_tmp++);
		REQUIRE(*r_ref_tmp-- == *r_tmp--);
		REQUIRE(*r_ref_tmp == *r_tmp);
	}
}
