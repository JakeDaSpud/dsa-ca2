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

template <typename K, typename V>
void TreeMap<K, V>::clear() {
    this->tree.clear();
}

#endif
