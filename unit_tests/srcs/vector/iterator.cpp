#include "../../hdrs/common.hpp"

TEMPLATE_PRODUCT_TEST_CASE("Vector iterator", "[vector][iterator]", CONTAINER_TYPES, VALUE_TYPES) {

	typedef typename TestType::value_type 						value_type;
	typedef typename std::vector<value_type>					std_vec;
	typedef typename TestType::iterator							iterator;
	typedef typename TestType::const_iterator					const_iterator;
	// typedef typename TestType::reverse_iterator					reverse_iterator;
	typedef typename std::vector<value_type>::iterator			std_iterator;
	typedef typename std::vector<value_type>::reverse_iterator	std_r_iterator;

	std_vec ref = generate_vec<value_type>();

	std_iterator	ref_begin = ref.begin();
	std_iterator	ref_end = ref.end();

	TestType	vec(ref_begin, ref_end);

	SECTION("same begin && end it") {
		REQUIRE(*ref_begin == *vec.begin());
		REQUIRE(*(--ref_end) == *(--vec.end()));
	}

	std_r_iterator	ref_rbegin = ref.rbegin();
	std_r_iterator	ref_rend = ref.rend();
	SECTION("same reverse_begin && reverse_end it") {
		REQUIRE(*ref_rbegin == *vec.rbegin());
		REQUIRE(*(--ref_rend) == *(--vec.rend()));
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
		*ref_begin = tmp;
		*vec.begin() = tmp;

		REQUIRE(*ref_begin == *vec.begin());
	}

	std_iterator ref_tmp = ++(++(--(++(++ref_begin))));
	iterator tmp = ++(++(--(++(++vec.begin()))));

	SECTION("++it && --it") {
		REQUIRE(*ref_tmp == *tmp);
	}
	SECTION("it++ && it--") {
		ref_tmp++;
		ref_tmp--;
		ref_tmp--;
		ref_tmp++;
		REQUIRE(*ref_tmp == *tmp);
	}
	SECTION("*it++ && *it--") {
		REQUIRE(*ref_tmp == *tmp);
		REQUIRE(*ref_tmp++ == *tmp++);
		REQUIRE(*ref_tmp-- == *tmp--);
		REQUIRE(*ref_tmp == *tmp);
	}

	ref_tmp = ref.begin() + REF_SIZE / 2;
	tmp = vec.begin() + REF_SIZE / 2;

	SECTION("it + n && n + it && it - n  && it - it2") {
		ref_tmp = ref_tmp + 15;
		tmp = tmp + 15;
		REQUIRE(*ref_tmp == *tmp);
	}

	SECTION("n + it") {
		ref_tmp = 30 + ref_tmp;
		tmp = 30 + tmp;
		REQUIRE(*ref_tmp == *tmp);
	}

	SECTION("it - n") {
		ref_tmp = ref_tmp - 5;
		tmp = tmp - 5;
		REQUIRE(*ref_tmp == *tmp);
	}

	SECTION("it - it2") {
		auto ref_diff = ref_tmp - ref.begin();
		auto diff = tmp - vec.begin();
		REQUIRE(ref_diff == diff); // it - it2
	}

	SECTION("it += n") {
		ref_tmp += 30;
		tmp += 30;
		REQUIRE(*ref_tmp == *tmp);
	}

	SECTION("it -= n") {
		ref_tmp -= 30;
		tmp -= 30;
		REQUIRE(*ref_tmp == *tmp);
	}

	SECTION("it < it2 && it > it2") {
		REQUIRE((tmp > vec.begin()) == (ref_tmp > ref.begin()));
		REQUIRE((tmp > vec.end()) == (ref_tmp > ref.end()));
		REQUIRE((tmp < vec.begin()) == (ref_tmp < ref.begin()));
		REQUIRE((tmp < vec.end()) == (ref_tmp < ref.end()));

		// with equal it
		REQUIRE((vec.begin() > vec.begin()) == (ref.begin() > ref.begin()));
		REQUIRE((vec.end() > vec.end()) == (ref.end() > ref.end()));
		REQUIRE((vec.begin() < vec.begin()) == (ref.begin() < ref.begin()));
		REQUIRE((vec.end() < vec.end()) == (ref.end() < ref.end()));
	}
	SECTION("it <= it2 && it >= it2") {
		REQUIRE((tmp >= vec.begin()) == (ref_tmp >= ref.begin()));
		REQUIRE((tmp >= vec.end()) == (ref_tmp >= ref.end()));
		REQUIRE((tmp <= vec.begin()) == (ref_tmp <= ref.begin()));
		REQUIRE((tmp <= vec.end()) == (ref_tmp <= ref.end()));

		// with equal it
		REQUIRE((vec.begin() >= vec.begin()) == (ref.begin() >= ref.begin()));
		REQUIRE((vec.end() >= vec.end()) == (ref.end() >= ref.end()));
		REQUIRE((vec.begin() <= vec.begin()) == (ref.begin() <= ref.begin()));
		REQUIRE((vec.end() <= vec.end()) == (ref.end() <= ref.end()));
	}

	SECTION("it[n]") {
		REQUIRE(tmp[0] == ref_tmp[0]);
		REQUIRE(tmp[-100] == ref_tmp[-100]);
		REQUIRE(tmp[100] == ref_tmp[100]);
	}
}
