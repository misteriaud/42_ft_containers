#include "../../hdrs/common.hpp"

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
	SECTION("push_back()") {
		for (size_t i = 0; i < REF_SIZE; i++)
		{
			ref.pop_back();
			vec.pop_back();
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<TestContainerType>(ref));
	}

}
