// Catch needs this definition to work
#define CATCH_CONFIG_MAIN

#include "../libs/catch.hpp"
#include "../src/TreeMap.h"

TEST_CASE("TreeMap Functions") {
    TreeMap<std::string, int> TM;

    SECTION("New TreeMap has a count of 0") {
        CHECK(TM.count() == 0);
    }

    SECTION("BinaryTree add() works") {
        KVPair<std::string, int> red = KVPair<std::string, int>("first", 8);
        TM.add(n1);
        CHECK(TM.count() == 1);
    }

    // Add a bunch of TM tests here

    // --- put ---
    // one insert
    // multiple inserts
    // duplicate key: insert k1 v1, then k1 v2, make sure count() is still 1 and the k1 value has changed

    // --- get ---
    // get existing key
    // get non existent key

    // --- clear ---
    // clear a full treemap
    // clear an empty treemap

    // --- size ---
    // check size before adding
    // check size after removing

    // --- containskey ---
    // existing key
    // non existing key
    // after removing a key: add key, contains key it true, remove it, contains key should be false now

    // --- remove key ---
    // remove existing key
    // remove non existing key
    // remve from empty treemap

}