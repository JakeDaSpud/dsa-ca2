#pragma once
#ifndef _TREEMAP_H_
#define _TREEMAP_H_

#include "BinaryTree.h"
#include "KVPair.h"
#include <queue>

template <typename K, typename V>
class TreeMap : public BinaryTree<KVPair<K, V>> {
private:
    BinaryTree<KVPair<K, V>> tree;

public:
    TreeMap();
    void clear();
    bool containsKey(K key);
    V& get(K key);
    BinaryTree<K> keySet();
    void put(K key, V value);
    int size();
    bool removeKey(K key);
    V& operator[](K key);
};

template <typename K, typename V>
TreeMap<K, V>::TreeMap() {};

/// @brief Removes all entries from the Map.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
template <typename K, typename V>
void TreeMap<K, V>::clear() {
    this->tree.clear();
};

/// @brief Check if a mapping has a specified key.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @param key Specified Key
/// @return Returns true if this map contains a mapping for the specified key.
template <typename K, typename V>
bool TreeMap<K, V>::containsKey(K key) {

    if (this->tree.count() == 0) {
        return false;
    }

    V defaultValue = V();
    KVPair<K, V> toFind = KVPair(key, defaultValue);

    BSTNode<KVPair<K, V>> *currentNode = this->tree.root;
    while (currentNode != nullptr) {
        if (currentNode->getItem() == toFind) {
            return true;
        }

        if (currentNode->getItem() > toFind) {
            currentNode = currentNode->getLeft();
        }

        else if (currentNode->getItem() < toFind) {
            currentNode = currentNode->getRight();
        }
    }
    
    return false;
};

/// @brief Get the value of the mapping with a specified key.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @param key Specified Key
/// @return Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
template <typename K, typename V>
V& TreeMap<K, V>::get(K key) {
    V defaultValue = V();
    KVPair<K, V> toGet = KVPair(key, defaultValue);
    return this->tree.get(toGet).getValue();
};

/// @brief Returns a Set view of the keys contained in this map.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @return Returns a Set view of the keys contained in this map.
template <typename K, typename V>
BinaryTree<K> TreeMap<K, V>::keySet() {
    BinaryTree<K> treeOut;
    std::queue<BSTNode<KVPair<K, V>>*> toVisit;

    if (this->size() == 0) {
        return treeOut;
    }

    // Start at root
    BSTNode<KVPair<K, V>> *currentNode = this->tree.root;
    toVisit.push(currentNode);

    while (!toVisit.empty()) {
        currentNode = toVisit.front();
        toVisit.pop();

        // Add the Key to treeOut
        treeOut.add(currentNode->getItem().getKey());

        // Check for left and right nodes and add them
        if (currentNode->getLeft() != nullptr) {
            toVisit.push(currentNode->getLeft());
        }

        if (currentNode->getRight() != nullptr) {
            toVisit.push(currentNode->getRight());
        }
    }

    return treeOut;
};

/// @brief Associates the specified value with the specified key in this map.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @param key Specified Input Key
/// @param value Specified Input Value
template <typename K, typename V>
void TreeMap<K, V>::put(K key, V value) {
    KVPair<K, V> newNode = KVPair(key, value);

    if (this->containsKey(key)) {
        BSTNode<KVPair<K, V>> *currentNode = this->tree.root;
        while (currentNode->getItem() != newNode) {

            if (currentNode->getItem() < newNode) {
                currentNode = currentNode->getRight();
            } 
            
            else {
                currentNode = currentNode->getLeft();
            }
        }

        currentNode->getItem().setValue(value);
    }

    tree.add(newNode);
};

/// @brief Get the integer value amount of key-value mappings in the map.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @return Returns the integer of key-value mappings in this map.
template <typename K, typename V>
int TreeMap<K, V>::size() {
    return this->tree.count();
};

/// @brief Removes the item denoted by the given key.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @param key Specified Key
/// @return True if successful, false otherwise.
template <typename K, typename V>
bool TreeMap<K, V>::removeKey(K key) {
    V defaultValue = V();
    KVPair<K, V> toRemove = KVPair(key, defaultValue);
    return this->tree.remove(toRemove);
};

/// @brief Get the value of the mapping with a specified key.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @param key Specified Key
/// @return Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
template <typename K, typename V>
V& TreeMap<K, V>::operator[](K key) {
    return this->get(key);
};

#endif
