//
// Created by zzpus on 2023/1/6.
//

#ifndef STORAGEBUFFERMANAGER_LRUCACHE_H
#define STORAGEBUFFERMANAGER_LRUCACHE_H
#include <unordered_map>
#include <list>

class LRUCache {
  public:
    explicit LRUCache(int capacity);

    int get(int key);

    void put(int key, int value);

    std::pair<int,int> getTail()const ;
  private:
    int cap;
    std::list<std::pair<int, int>> cache{};
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map{};
};



#endif // STORAGEBUFFERMANAGER_LRUCACHE_H
