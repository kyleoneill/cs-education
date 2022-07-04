#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../library.h"

TEST_CASE("Vector constructor") {
    Vec<int> some_vec{};
    CHECK(some_vec.len() == 0);
}

TEST_CASE("Vector push_back") {
    Vec<int> some_vec{};
    some_vec.push_back(1);

    // After the first push_back we should have a len of 1 and a vec[0] of 1
    CHECK(some_vec.len() == 1);
    CHECK(some_vec[0] == 1);

    // Fill the vec, verify that the length and first/last values are correct
    for(int i = 1; i < 10000; i++) {
        some_vec.push_back(i);
    }
    CHECK(some_vec.len() == 10000);
    CHECK(some_vec[0] == 1);
    CHECK(some_vec[some_vec.len() - 1] == 9999);
}

TEST_CASE("Vector indexing") {
    Vec<int> some_vec{};
    some_vec.push_back(1);

    // Make sure the first element is the expected 1
    CHECK(some_vec[0] == 1);

    // Make sure out-of-bounds access throws an exception
    CHECK_THROWS_AS(some_vec[1], std::runtime_error);

    // Add an element and verify that accessing position 1 no longer throws an exception
    some_vec.push_back(2);
    CHECK(some_vec[1] == 2);
}

TEST_CASE("Vector pop_back") {
    Vec<int> some_vec{};

    // pop_back an empty vec, make sure nothing happens
    some_vec.pop_back();
    CHECK(some_vec.len() == 0);

    // Add some data
    for(int i = 0; i < 20; i++) {
        some_vec.push_back(i);
    }

    // Pop back a few times
    for(int i = 0; i < 5; i++) {
        some_vec.pop_back();
    }

    // Verify that after adding 20 elements and then popping back 5 times, the length is 15 and the first/last values are correct
    CHECK(some_vec.len() == 15);
    CHECK(some_vec[0] == 0);
    CHECK(some_vec[some_vec.len() - 1] == 14);

    // Verify that after popping back, the pop-backed indexes are no longer accessible
    CHECK_THROWS_AS(some_vec[15], std::runtime_error);
}
