#pragma once
#ifndef _KVPAIR_H_
#define _KVPAIR_H_

template <typename K, typename V>
class KVPair {
private:
    K key;
    V value;
public:
    KVPair(K key, V value);
    KVPair(KVPair<K, V> &other);
    K& getKey();
    V& getValue();
    bool operator==(const KVPair<K, V> &other);
    bool operator<(const KVPair<K, V> &other);
    bool operator>(const KVPair<K, V> &other);
};

template <typename K, typename V>
KVPair<K, V>::KVPair(K key, V value) {
    this->key = key;
    this->value = value;
};

template <typename K, typename V>
KVPair<K, V>::KVPair(KVPair<K, V> &other) {
    this->key = other.getKey();
    this->value = other.getValue();
};

template <typename K, typename V>
bool KVPair<K, V>::operator==(const KVPair<K, V> &other) {
    return this->getKey == other.getKey();
};

template <typename K, typename V>
bool KVPair<K, V>::operator<(const KVPair<K, V> &other) {
    return this->getKey < other.getKey();
};

template <typename K, typename V>
bool KVPair<K, V>::operator>(const KVPair<K, V> &other) {
    return this->getKey > other.getKey();
};

#endif
