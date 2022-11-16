#include "../../hdrs/common.hpp"

template <typename T1, typename T2>
bool operator==(const ft::pair<const T1, T2>& lhs, const std::pair<const T1, T2>& rhs) {
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}
template <typename T1, typename T2>
bool operator==(const std::pair<const T1, T2>& lhs, const ft::pair<const T1, T2>& rhs) {
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

TEST_CASE("Map iterator", "[map][iterator]") {

	StdMap ref = Custom::mocking_value<StdMap>();
	Map	vec = Custom::convert_map(ref);

	SECTION("same begin && end it") {
		REQUIRE(*ref.begin() == *vec.begin());
		REQUIRE(*(--ref.end()) == *(--vec.end()));
	}

	SECTION("same reverse_begin && reverse_end it") {
		REQUIRE(*ref.rbegin() == *vec.rbegin());
		REQUIRE(*(--ref.rend()) == *(--vec.rend()));
	}

	SECTION("constructor") {
		MapIt	it = vec.begin();

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
		it = vec.begin();

		REQUIRE((it == vec.begin()) == true);
		REQUIRE((it == vec.end()) == false);
		REQUIRE((it != vec.begin()) == false);
		REQUIRE((it != vec.end()) == true);
	}

	// SECTION("mutable operator *it = a") {
	// 	ValueType tmp = Custom::mocking_value<>();
	// 	*ref.begin() = tmp;
	// 	*vec.begin() = tmp;

	// 	REQUIRE(*ref.begin() == *vec.begin());
	// }

	StdMapConstIt	ref_tmp = ++(++(--(++(++ref.begin()))));
	MapConstIt		 tmp = ++(++(--(++(++vec.begin()))));

	StdMapConstRevIt	r_ref_tmp = ++(++(--(++(++ref.rbegin()))));
	MapConstRevIt		r_tmp = ++(++(--(++(++vec.rbegin()))));

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

	// ref_tmp = ref.begin()++;
	// tmp = vec.begin()++;

	// r_ref_tmp = ref.rbegin()++;
	// r_tmp = vec.rbegin()++;

	// SECTION("it < it2 && it > it2") {
	// 	REQUIRE((tmp > vec.begin()) == (ref_tmp > ref.begin()));
	// 	REQUIRE((tmp > vec.end()) == (ref_tmp > ref.end()));
	// 	REQUIRE((tmp < vec.begin()) == (ref_tmp < ref.begin()));
	// 	REQUIRE((tmp < vec.end()) == (ref_tmp < ref.end()));

	// 	// with equal it
	// 	REQUIRE((vec.begin() > vec.begin()) == (ref.begin() > ref.begin()));
	// 	REQUIRE((vec.end() > vec.end()) == (ref.end() > ref.end()));
	// 	REQUIRE((vec.begin() < vec.begin()) == (ref.begin() < ref.begin()));
	// 	REQUIRE((vec.end() < vec.end()) == (ref.end() < ref.end()));

	// 	// REVERSE IT
	// 	REQUIRE((r_tmp > vec.rbegin()) == (r_ref_tmp > ref.rbegin()));
	// 	REQUIRE((r_tmp > vec.rend()) == (r_ref_tmp > ref.rend()));
	// 	REQUIRE((r_tmp < vec.rbegin()) == (r_ref_tmp < ref.rbegin()));
	// 	REQUIRE((r_tmp < vec.rend()) == (r_ref_tmp < ref.rend()));

	// 	// with equal it
	// 	REQUIRE((vec.rbegin() > vec.rbegin()) == (ref.rbegin() > ref.rbegin()));
	// 	REQUIRE((vec.rend() > vec.rend()) == (ref.rend() > ref.rend()));
	// 	REQUIRE((vec.rbegin() < vec.rbegin()) == (ref.rbegin() < ref.rbegin()));
	// 	REQUIRE((vec.rend() < vec.rend()) == (ref.rend() < ref.rend()));
	// }
	// SECTION("it <= it2 && it >= it2") {
	// 	REQUIRE((tmp >= vec.begin()) == (ref_tmp >= ref.begin()));
	// 	REQUIRE((tmp >= vec.end()) == (ref_tmp >= ref.end()));
	// 	REQUIRE((tmp <= vec.begin()) == (ref_tmp <= ref.begin()));
	// 	REQUIRE((tmp <= vec.end()) == (ref_tmp <= ref.end()));
	// 	// with equal it
	// 	REQUIRE((vec.begin() >= vec.begin()) == (ref.begin() >= ref.begin()));
	// 	REQUIRE((vec.end() >= vec.end()) == (ref.end() >= ref.end()));
	// 	REQUIRE((vec.begin() <= vec.begin()) == (ref.begin() <= ref.begin()));
	// 	REQUIRE((vec.end() <= vec.end()) == (ref.end() <= ref.end()));

	// 	//REVERSE
	// 	REQUIRE((r_tmp >= vec.rbegin()) == (r_ref_tmp >= ref.rbegin()));
	// 	REQUIRE((r_tmp >= vec.rend()) == (r_ref_tmp >= ref.rend()));
	// 	REQUIRE((r_tmp <= vec.rbegin()) == (r_ref_tmp <= ref.rbegin()));
	// 	REQUIRE((r_tmp <= vec.rend()) == (r_ref_tmp <= ref.rend()));
	// 	// with equal it
	// 	REQUIRE((vec.rbegin() >= vec.rbegin()) == (ref.rbegin() >= ref.rbegin()));
	// 	REQUIRE((vec.rend() >= vec.rend()) == (ref.rend() >= ref.rend()));
	// 	REQUIRE((vec.rbegin() <= vec.rbegin()) == (ref.rbegin() <= ref.rbegin()));
	// 	REQUIRE((vec.rend() <= vec.rend()) == (ref.rend() <= ref.rend()));
	// }
}
