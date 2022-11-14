#include "../../hdrs/common.hpp"

#include <iostream>

TEST_CASE("Vector modifiers", "[vector][modifier]") {

	StdVec 				ref = Custom::generate_vec<TestValueType>();
	TestContainerType	vec;
	TestValueType		tmp_val = Custom::mocking_value<TestValueType>();

	SECTION("assign(first, last)") {
		vec.assign(ref.begin(), ref.end());
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(ref)); // assign all of other container

		{
			StdVec		tmp;
			tmp.assign(ref.begin() + REF_SIZE / 4, ref.end() - REF_SIZE / 4);
			vec.assign(ref.begin() + REF_SIZE / 4, ref.end() - REF_SIZE / 4);
			REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(tmp)); // assign middle of other container
		}
		{
			StdVec		tmp;
			TestIt		it = vec.begin();
			tmp.assign(ref.begin(), ref.begin());
			vec.assign(ref.begin(), ref.begin());
			REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(tmp)); // assign am empty container
			REQUIRE(it == vec.begin());
		}
	}
	SECTION("assing(first, last) with input_iterator") {
		typedef std::istream_iterator<char>	is_iterator;
		std::ifstream		file;
		is_iterator			file_it;

		file.open(FILE_PATH);
		file_it = is_iterator(file);
		ft::vector<char>	vec;
		vec.assign(file_it, is_iterator());

		file.close();
		file.open(FILE_PATH);
		file_it = is_iterator(file);
		REQUIRE(Custom::equal(file_it, is_iterator(), vec.begin(), vec.end()) == true);
		file.close();
	}

	SECTION("assign(n, val)") {
		StdVec		tmp;
		TestIt		it = vec.begin();

		REQUIRE_THROWS(vec.assign(-5, tmp_val));
		{
			tmp.assign(REF_SIZE, tmp_val);
			vec.assign(REF_SIZE, tmp_val);
			REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(tmp));
		}
		{
			it = vec.begin();
			tmp.assign(0, tmp_val);
			vec.assign(0, tmp_val);
			REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(tmp));
			REQUIRE(it == vec.begin());
		}
		{
			it = vec.begin();
			tmp.assign(REF_SIZE / 2, tmp_val);
			vec.assign(REF_SIZE / 2, tmp_val);
			REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(tmp));
			REQUIRE(it == vec.begin());
		}
	}

	SECTION("push_back()") {
		ref.clear();
		vec.clear();
		for (size_t i = 0; i < REF_SIZE + 100; i++)
		{
			tmp_val = Custom::mocking_value<TestValueType>();
			ref.push_back(tmp_val);
			vec.push_back(tmp_val);
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(ref));
	}
	SECTION("pop_back()") {
		for (size_t i = 0; i < REF_SIZE; i++)
		{
			ref.pop_back();
			vec.pop_back();
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(ref));
	}

	StdVecConstIt	std_it;
	TestConstIt		it;

	SECTION("insert(position, val)") {
		StdVec		tmp;

		vec.clear();
		for (size_t i = 0; i < REF_SIZE; i++)
		{
			// std::cout << i << std::endl;
			tmp_val = Custom::mocking_value<TestValueType>();
			if (i % 3 == 0) {
				std_it = tmp.insert(tmp.begin(), tmp_val);
				it = vec.insert(vec.begin(), tmp_val);
			}
			else if (i % 3 == 1) {
				std_it = tmp.insert(tmp.begin() + tmp.size() / 2, tmp_val);
				it = vec.insert(vec.begin() + vec.size() / 2, tmp_val);
			}
			else {
				std_it = tmp.insert(tmp.end(), tmp_val);
				it = vec.insert(vec.end(), tmp_val);
			}
			if (std_it == tmp.end())
				REQUIRE(it == vec.end());
			else
				REQUIRE(*std_it == *it);
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(tmp));
	}
	SECTION("insert(position, n, val)") {
		StdVec		tmp;
		size_t		n;

		vec.clear();
		for (size_t i = 0; i < REF_SIZE; i++)
		{
			tmp_val = Custom::mocking_value<TestValueType>();
			n = Custom::mocking_value<size_t>();
			if (i % 3 == 0) {
				tmp.insert(tmp.begin(), n, tmp_val);
				vec.insert(vec.begin(), n, tmp_val);
			}
			else if (i % 3 == 1) {
				tmp.insert(tmp.begin() + tmp.size() / 2, n, tmp_val);
				vec.insert(vec.begin() + vec.size() / 2, n, tmp_val);
			}
			else {
				tmp.insert(tmp.end(), n, tmp_val);
				vec.insert(vec.end(), n, tmp_val);
			}
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(tmp));
	}
	SECTION("insert(position, first, last)") {
		StdVec			tmp;
		size_t			n;
		StdVecConstIt	first;
		StdVecConstIt	last;


		vec.clear();
		ref.clear();
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			ref = Custom::generate_vec<TestValueType>();
			first = ref.begin();
			last = ref.end();
			if (i % 2 == 0)
				first = ref.begin() + ref.size() / 3;
			if (i % 3 == 0)
				last = ref.end() - ref.size() / 3;

			tmp.insert(tmp.end(), first, last);
			vec.insert(vec.end(), first, last);

		}
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(tmp));
	}

}
