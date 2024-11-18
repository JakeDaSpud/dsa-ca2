#pragma once
#ifndef _TREEMAP_H_
#define _TREEMAP_H_

#include "BinaryTree.h"
#include "KVPair.h"

template <typename K, typename V>
class TreeMap {
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
    return false;
};

/// @brief Get the value of the mapping with a specified key.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @param key Specified Key
/// @return Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
template <typename K, typename V>
V& TreeMap<K, V>::get(K key) {
    return nullptr;
};

/// @brief Returns a Set view of the keys contained in this map.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @return Returns a Set view of the keys contained in this map.
template <typename K, typename V>
BinaryTree<K> TreeMap<K, V>::keySet() {
    return nullptr;
};

/// @brief Associates the specified value with the specified key in this map.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @param key Specified Input Key
/// @param value Specified Input Value
template <typename K, typename V>
void TreeMap<K, V>::put(K key, V value) {
    
};

/// @brief Get the integer value amount of key-value mappings in the map.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @return Returns the integer of key-value mappings in this map.
template <typename K, typename V>
int TreeMap<K, V>::size() {
    return 0;
};

/// @brief Removes the item denoted by the given key.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @param key Specified Key
/// @return True if successful, false otherwise.
template <typename K, typename V>
bool TreeMap<K, V>::removeKey(K key) {
    return false;
};

/// @brief Get the value of the mapping with a specified key.
/// @tparam K Datatype of the KVPair Key
/// @tparam V Datatype of the KVPair Value
/// @param key Specified Key
/// @return Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
template <typename K, typename V>
V& TreeMap<K, V>::operator[](K key) {
    return nullptr;
};

#endif
