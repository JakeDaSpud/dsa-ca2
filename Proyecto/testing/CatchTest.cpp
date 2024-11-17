// Catch needs this definition to work
#define CATCH_CONFIG_MAIN

#include "../libs/catch.hpp"
#include <stdexcept>

// Example Function to see how to unit test with Catch2
int add(int a, int b) {
    if (a == -1) {
        throw std::logic_error("given sentinel value");
    }

    return a + b;
}

// This is similar to Microsoft's Testing Framework so far
// First param is test name
TEST_CASE("add() function works right") {

    // CHECK() wants the bool expression to be true, otherwise the test fails and the code continues
    CHECK(add(4, 6) == 10);
    CHECK_FALSE(add(10, 0) == 100);

    // REQUIRE() wants the bool expression to be true, otherwise the test fails AND THE CODE STOPS
    REQUIRE(add(1, 2) == 3);
    REQUIRE_FALSE(add(1, 1) == 3);
}

TEST_CASE("add() but with a variable") {
    // This result will be calculated at the start of every REQUIRE() and CHECK()
    // If this was a class being instantiated, this would be costly for every REQUIRE() and CHECK()
    int result = add(2, 4);

    CHECK(result == 6);
    CHECK_FALSE(result == 13);

    REQUIRE(result == 6);
    REQUIRE_FALSE(result == 7);
}

TEST_CASE("add() but for exceptions") {
    // REQUIRE_NOTHROW() and CHECK_NOTHROW() expect no throws

    // These expect ANY throw to happen
    CHECK_THROWS(add(-1, 0));
    REQUIRE_THROWS(add(-1, 0));

    // These expect a specified throw to happen
    CHECK_THROWS_AS(add(-1, 0), std::logic_error);
    REQUIRE_THROWS_AS(add(-1, 0), std::logic_error);
}