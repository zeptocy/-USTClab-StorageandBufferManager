//
// Created by zzpus on 2023/1/6.
//

#include "LRUCache.h"

LRUCache::LRUCache(int capacity) : cap(capacity) {
}
int LRUCache::get(int key) {
    if (map.find(key) == map.end()) return -1;
    auto key_value = *map[key];
    cache.erase(map[key]);
    cache.push_front(key_value);
    map[key] = cache.begin();
    return key_value.second;
}
void LRUCache::put(int key, int value) {
    if (map.find(key) == map.end()) {
        if (cache.size() == cap) {
            map.erase(cache.back().first);
            cache.pop_back();
        }
    }
    else {
        cache.erase(map[key]);
    }
    cache.push_front({key, value});
    map[key] = cache.begin();
}
std::pair<int, int> LRUCache::getTail() const { return cache.back(); }
