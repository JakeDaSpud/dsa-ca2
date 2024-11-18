#pragma once
#ifndef _KVPAIR_H_
#define _KVPAIR_H_

template <typename K, typename V>
struct KVPair {
public:
    K key;
    V value;
};

#endif
