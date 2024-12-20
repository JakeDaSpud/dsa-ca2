#pragma once
#ifndef _KVPAIR_H_
#define _KVPAIR_H_

template <typename K, typename V>
class KVPair {
private:
    K key;
    V value;
public:
    KVPair();
    KVPair(K key, V value);
    KVPair(KVPair<K, V> &other);
    
    K& getKey();
    V& getValue();
    void setValue(V value);

    bool operator==(KVPair<K, V> &other);
    bool operator!=(KVPair<K, V> &other);
    bool operator<(KVPair<K, V> &other);
    bool operator>(KVPair<K, V> &other);
};

template <typename K, typename V>
KVPair<K, V>::KVPair() { };

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
K& KVPair<K, V>::getKey() {
    return this->key;
};

template <typename K, typename V>
V& KVPair<K, V>::getValue() {
    return this->value;
};

template <typename K, typename V>
void KVPair<K, V>::setValue(V value) {
    this->value = value;
};

template <typename K, typename V>
bool KVPair<K, V>::operator==(KVPair<K, V> &other) {
    return (this->key == other.getKey());
};

template <typename K, typename V>
bool KVPair<K, V>::operator!=(KVPair<K, V> &other) {
    return (this->key != other.getKey());
};

template <typename K, typename V>
bool KVPair<K, V>::operator<(KVPair<K, V> &other) {
    return (this->key < other.getKey());
};

template <typename K, typename V>
bool KVPair<K, V>::operator>(KVPair<K, V> &other) {
    return (this->key > other.getKey());
};

#endif
