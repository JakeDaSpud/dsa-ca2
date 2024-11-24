// Catch needs this definition to work
#define CATCH_CONFIG_MAIN

#include "../libs/catch.hpp"
#include "../src/TreeMap.h"

TEST_CASE("TreeMap Functions") {
    // This TreeMap gets instatiated at the start of every SECTION()
    TreeMap<std::string, int> TM;

    SECTION("New TreeMap has a count of 0") {
        CHECK(TM.count() == 0);
    }

    SECTION("BinaryTree add() works") {
        KVPair<std::string, int> red = KVPair<std::string, int>("red", 45);
        TM.add(red);
        CHECK(TM.count() == 1);
    }

    // Add a bunch of TM tests here

    // --- containskey ---
    // existing key
    // non existing key
    // after removing a key: add key, contains key it true, remove it, contains key should be false now

    SECTION("An existing key returns true") {
        CHECK(TM.size() == 0);
        
        TM.put("red", 45);
        CHECK(TM.size() == 1);

        CHECK(TM.containsKey("red") == true);
    }

    // --- put ---
    // one insert
    // multiple inserts
    // duplicate key: insert k1 v1, then k1 v2, make sure count() is still 1 and the k1 value has changed
    SECTION("Inserting 1 works") {
        KVPair<std::string, int> red = KVPair<std::string, int>("red", 45);
        CHECK_NOTHROW(TM.put("red", 45));
    }

    SECTION("Inserting 3 works") {
        CHECK(TM.size() == 0);
        TM.put("red", 45);
        CHECK(TM.size() == 1);
        TM.put("yellow", 70);
        CHECK(TM.size() == 2);
        TM.put("blue", 60);
        CHECK(TM.size() == 3);
    }

    SECTION("Inserting a duplicate Key will overwrite the old Value Mapping") {
        CHECK(TM.size() == 0);
        
        TM.put("red", 45);
        CHECK(TM.size() == 1);
        
        TM.put("red", 999);
        CHECK(TM.size() == 1);
        
        CHECK(TM.get("red") == 999);

        TM.printInOrder();
    }

    // --- remove key ---
    
    SECTION("Removing 1 existing Key works") {
        TM.put("red", 45);
        CHECK(TM.size() == 1);
        CHECK(TM.removeKey("red") == true);
        CHECK(TM.size() == 0);
    }

    SECTION("Removing 1 non-existing Key works correctly") {
        TM.put("red", 45);
        CHECK(TM.size() == 1);
        CHECK(TM.removeKey("yellow") == false);
        CHECK(TM.size() == 1);
    }

    SECTION("Removing from empty TreeMap works correctly") {
        CHECK(TM.size() == 0);
        CHECK(TM.removeKey("yellow") == false);
    }

    // --- size ---
    
    SECTION("Size is 0 before adding") {
        CHECK(TM.size() == 0);
    }

    SECTION("Size is 1 after adding 1, and 0 after removing it") {
        CHECK(TM.size() == 0);
        TM.put("red", 45);
        CHECK(TM.size() == 1);
        TM.removeKey("red");
        CHECK(TM.size() == 0);
    }

    // --- get ---
    // get existing key
    // get non existent key

    // --- clear ---

    SECTION("Full TreeMap clears properly") {
        TM.put("red", 45);
        TM.put("yellow", 70);
        CHECK(TM.size() == 2);
        TM.clear();
        CHECK(TM.size() == 0);
    }

    SECTION("Empty TreeMap clears properly") {
        CHECK_NOTHROW(TM.clear());
        CHECK(TM.size() == 0);
    }

}