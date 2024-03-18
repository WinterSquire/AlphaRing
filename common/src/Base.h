#ifndef ALPHA_RING_BASE_H
#define ALPHA_RING_BASE_H

#include <unordered_map>
#include <vector>

#include <cstdint>

#include <cstdio>
#include <string>

#define CPrint(str) printf("%s", str)

using string = std::string;

template<typename T> using vector = std::vector<T>;

template<typename K, typename V> using unordered_map = std::unordered_map<K,V>;

#endif //ALPHA_RING_BASE_H
