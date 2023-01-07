//
// Created by zzpus on 2023/1/6.
//

#ifndef STORAGEBUFFERMANAGER_LRUCACHE_H
#define STORAGEBUFFERMANAGER_LRUCACHE_H
#include <memory>
#include <unordered_map>

//双链表，用于辅助LRU实现结构
struct DLinkedNode {
    int key, value;
    std::shared_ptr<DLinkedNode> prev;
    std::shared_ptr<DLinkedNode> next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value)
        : key(_key),
          value(_value),
          prev(nullptr),
          next(nullptr) {}
};

class LRUCache {
  public:
    explicit LRUCache(int _capacity);

    int get(int key); // 读取lru中key值对应的vaule，并将节点置头部，不存在则返回-1，

    void put(int key, int value); // 将（key，value）放入lru

    std::shared_ptr<DLinkedNode> getTail(); // 返回lru尾部节点，即换出节点

    int size() const;

  private:
    std::unordered_map<int, std::shared_ptr<DLinkedNode>> cache; //可通过key快速定位节点
    std::shared_ptr<DLinkedNode> head;
    std::shared_ptr<DLinkedNode> tail;
    int _size;
    int capacity;

    void addToHead(const std::shared_ptr<DLinkedNode>& node);

    void removeNode(const std::shared_ptr<DLinkedNode>& node);

    void moveToHead(const std::shared_ptr<DLinkedNode>& node);

    std::shared_ptr<DLinkedNode> removeTail();
};

#endif // STORAGEBUFFERMANAGER_LRUCACHE_H
