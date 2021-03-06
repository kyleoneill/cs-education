#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../library.h"
using std::string;

/// Create an int vector that contains 20 values which are equivalent to their position.
/// Ex, some_vec[2] will be 2
Vec<int> create_int_vector() {
    Vec<int> some_vec{};
    for(int i = 0; i < 20; i++) {
        some_vec.push_back(i);
    }
    return some_vec;
}

/// Create a string vector that contains 20 values all set to "test"
Vec<string> create_str_vector() {
    Vec<string> some_vec{};
    for(int i = 0; i < 20; i++) {
        some_vec.push_back("test");
    }
    return some_vec;
}

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

TEST_CASE("Vector push_front") {
    Vec<int> some_vec = create_int_vector();

    // push_front and verify that the new length is correct and the new values were added to the front
    for(int i = 0; i < 5; i++) {
        some_vec.push_front(100);
    }
    CHECK(some_vec.len() == 25);
    CHECK(some_vec[0] == 100);
    CHECK(some_vec[some_vec.len() - 1] == 19);
}

TEST_CASE("Vector pop_front") {
    Vec<int> some_vec = create_int_vector();

    // pop_front and verify that the new length is correct and values were removed from the front
    for(int i = 0; i < 5; i++) {
        some_vec.pop_front();
    }
    CHECK(some_vec.len() == 15);
    CHECK(some_vec[0] == 5);
    CHECK(some_vec[some_vec.len() - 1] == 19);
}

TEST_CASE("Vector insert") {
    Vec<int> some_vec = create_int_vector();

    // Insert at some index, make sure that the first/last and values around that index are all correct
    some_vec.insert(100, 7);
    CHECK(some_vec.len() == 21);
    CHECK(some_vec[0] == 0);
    CHECK(some_vec[some_vec.len() - 1] == 19);
    CHECK(some_vec[6] == 6);
    CHECK(some_vec[7] == 100);
    CHECK(some_vec[8] == 7);
}

TEST_CASE("Vector remove") {
    Vec<int> some_vec = create_int_vector();

    // Remove from some index, make sure that the first/last and values around that index are all correct
    some_vec.remove(10);
    CHECK(some_vec.len() == 19);
    CHECK(some_vec[0] == 0);
    CHECK(some_vec[some_vec.len() - 1] == 19);
    CHECK(some_vec[9] == 9);
    CHECK(some_vec[10] == 11);
    CHECK(some_vec[11] == 12);
}

TEST_CASE("Vector with non-trivial copy type") {
    // This test verifies that vector works with a type that is not trivially copy-able.
    // A type is trivially copy-able if you can just copy their bits.
    // Strings are non-trivially copy-able as they own data through a pointer.
    // When we copy a string we are copying its pointer and length into pre-allocated space in our vector and then
    // copy the bytes of the string and set the pointer to point to those bytes.

    Vec<string> some_vec = create_str_vector();

    // Verify that the constructor helper function added 20 strings, and we have a length of 20
    CHECK(some_vec.len() == 20);

    // Verify that we can index a vector of strings
    CHECK(some_vec[0] == "test");

    // Test that we can push_back with a string vec
    some_vec.push_back("new_back");
    CHECK(some_vec.len() == 21);
    CHECK(some_vec[some_vec.len() - 1] == "new_back");

    // Test that we can push_front with a string vec
    some_vec.push_front("new_front");
    CHECK(some_vec.len() == 22);
    CHECK(some_vec[0] == "new_front");

    // Test that we can insert with a string vec
    some_vec.insert("new_random_position", 1);
    CHECK(some_vec.len() == 23);
    CHECK(some_vec[0] == "new_front");
    CHECK(some_vec[1] == "new_random_position");
    CHECK(some_vec[2] == "test");

    // Test that we can remove values with a string vec
    some_vec.remove(1);
    CHECK(some_vec.len() == 22);
    CHECK(some_vec[0] == "new_front");
    CHECK(some_vec[1] == "test");
}
