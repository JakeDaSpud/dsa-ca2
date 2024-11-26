// Catch needs this definition to work
#define CATCH_CONFIG_MAIN

#include "../libs/catch.hpp"
#include "../src/TreeMap.h"

TEST_CASE("TreeMap BinaryTree Functions") {
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
}

TEST_CASE("TreeMap keySet() Tests") {
    // This TreeMap gets instatiated at the start of every SECTION()
    TreeMap<std::string, int> TM;
    
    // --- keySet ---

    SECTION("An empty TreeMap returns an empty keySet") {
        BinaryTree<std::string> treeOut = TM.keySet();

        CHECK(treeOut.count() == TM.size());
        CHECK(treeOut.root == nullptr);
    }

    SECTION("A TreeMap with 1 node will return the correct keySet") {
        TM.put("red", 45);
        CHECK(TM.size() == 1);

        BinaryTree<std::string> treeOut = TM.keySet();
    
        // Shoud be same size
        CHECK(treeOut.count() == TM.size());

        CHECK(treeOut.root != nullptr);
        CHECK_NOTHROW(TM.getRoot()); // Shouldn't throw logic_error because there IS a root node

        std::string outRoot = treeOut.root->getItem();
        std::string tmRoot = TM.getRoot()->getItem().getKey();

        // Should be same Key
        CHECK(outRoot == tmRoot);
    }

    SECTION("A TreeMap with 3 nodes will return the correct keySet") {
        TM.put("red", 45);
        TM.put("yellow", 90);
        TM.put("blue", 60);
        CHECK(TM.size() == 3);

        BinaryTree<std::string> treeOut = TM.keySet();
    
        // Shoud be same size
        CHECK(treeOut.count() == TM.size());

        CHECK(treeOut.root != nullptr);
        CHECK_NOTHROW(TM.getRoot()); // Shouldn't throw logic_error because there IS a root node

        std::string outRoot = treeOut.root->getItem();
        std::string tmRoot = TM.getRoot()->getItem().getKey();
        
        // Should be same Keys
        CHECK(outRoot == tmRoot);

        if (treeOut.root->getLeft() != nullptr) {
            std::string outRootLeft = treeOut.root->getLeft()->getItem();
            std::string tmRootLeft = TM.getRoot()->getLeft()->getItem().getKey();
            CHECK(outRootLeft == tmRootLeft);
        }

        if (treeOut.root->getRight() != nullptr) {
            std::string outRootRight = treeOut.root->getRight()->getItem();
            std::string tmRootRight = TM.getRoot()->getRight()->getItem().getKey();
            CHECK(outRootRight == tmRootRight);
        }
    }
}


TEST_CASE("TreeMap containsKey() Tests") {
    // This TreeMap gets instatiated at the start of every SECTION()
    TreeMap<std::string, int> TM;

    // --- containsKey ---

    SECTION("An existing key returns true") {
        CHECK(TM.size() == 0);
        
        TM.put("red", 45);
        CHECK(TM.size() == 1);

        CHECK(TM.containsKey("red") == true);
    }

    SECTION("A non-existing key returns false") {
        CHECK(TM.size() == 0);
        
        TM.put("red", 45);
        CHECK(TM.size() == 1);

        CHECK(TM.containsKey("yellow") == false);
    }

    SECTION("An existing key returns true, then, once removed, returns false") {
        CHECK(TM.size() == 0);
        
        TM.put("red", 45);
        CHECK(TM.size() == 1);

        CHECK(TM.containsKey("red") == true);

        TM.removeKey("red");
        CHECK(TM.size() == 0);

        CHECK(TM.containsKey("red") == false);
    }
}

TEST_CASE("TreeMap clear() Tests") {
    // This TreeMap gets instatiated at the start of every SECTION()
    TreeMap<std::string, int> TM;

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

TEST_CASE("TreeMap get() Tests") {
    // This TreeMap gets instatiated at the start of every SECTION()
    TreeMap<std::string, int> TM;

    // --- get ---

    SECTION("Getting an existing Key") {
        CHECK(TM.size() == 0);
        TM.put("red", 45);
        CHECK(TM.get("red") == 45);
    }

    SECTION("Getting with square brackets is the same as getting with function") {
        CHECK(TM.size() == 0);
        TM.put("red", 45);
        CHECK(TM.get("red") == 45);
        CHECK(TM["red"] == TM.get("red"));
    }

    SECTION("Getting a non-existing Key throws a logic_error") {
        CHECK(TM.size() == 0);
        TM.put("red", 45);
        CHECK_THROWS_AS(TM.get("yellow"), std::logic_error);
    }

    SECTION("Getting a non-existing Key with square brackets throws a logic_error") {
        CHECK(TM.size() == 0);
        TM.put("red", 45);
        CHECK_THROWS_AS(TM["yellow"], std::logic_error);
    }
}

TEST_CASE("TreeMap size() Tests") {
    // This TreeMap gets instatiated at the start of every SECTION()
    TreeMap<std::string, int> TM;

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
}

TEST_CASE("TreeMap removeKey() Tests") {
    // This TreeMap gets instatiated at the start of every SECTION()
    TreeMap<std::string, int> TM;

    // --- removeKey ---
    
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
}

TEST_CASE("TreeMap put() Tests") {
    // This TreeMap gets instatiated at the start of every SECTION()
    TreeMap<std::string, int> TM;
    
    // --- put ---
    
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
    }
}