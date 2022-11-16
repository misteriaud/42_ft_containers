#include "../../hdrs/common.hpp"

TEST_CASE("Vector non-members functions", "[vector][operator]") {

	// StdVec 				ref = Custom::generate_vec<ValueType>();
	// StdVec				tmp;
	Vec		ref;
	for(size_t i = 0; i < REF_SIZE; i++)
		ref.push_back(Custom::mocking_value<ValueType>());

	Vec		vec(ref);
	// ValueType		tmp_val = Custom::mocking_value<ValueType>();


	// cmp(vct, vct);  // 0
	// cmp(vct, vct2); // 1

	// vct2.resize(10);

	// cmp(vct, vct2); // 2
	// cmp(vct2, vct); // 3

	// vct[2] = 42;

	// cmp(vct, vct2); // 4
	// cmp(vct2, vct); // 5

	// swap(vct, vct2);

	// cmp(vct, vct2); // 6
	// cmp(vct2, vct); // 7
	SECTION("operator == && !=") {
		REQUIRE(ref == vec);
		REQUIRE(ref <= vec);
		REQUIRE(ref >= vec);
		vec.pop_back();
		REQUIRE(ref != vec);
		REQUIRE_FALSE(ref < vec);
	}
	SECTION("operator < && >") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (ref.back() < vec.back())
				REQUIRE(ref < vec);
			else if (ref.back() > vec.back())
				REQUIRE(ref > vec);
			else {
				REQUIRE_FALSE(ref < vec);
				REQUIRE_FALSE(ref > vec);
			}
			ref.pop_back();
			vec.pop_back();
		}
	}
	SECTION("operator <= && >=") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (ref.back() < vec.back())
				REQUIRE(ref <= vec);
			else if (ref.back() > vec.back())
				REQUIRE(ref >= vec);
			else {
				REQUIRE(ref <= vec);
				REQUIRE(ref >= vec);
			}
			ref.pop_back();
			vec.pop_back();
		}
	}

	SECTION("swap()") {
		VecConstIt	it;
		VecConstIt	it2;

		it = ref.begin();
		it2 = vec.begin();

		ref.swap(vec);
		REQUIRE(it == vec.begin());
		REQUIRE(it2 == ref.begin());
	}
}
