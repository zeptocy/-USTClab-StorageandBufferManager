//
// Created by zzpus on 2023/1/6.
//

#include "LRUCache.h"
LRUCache::LRUCache(int _capacity)
    : capacity(_capacity),
      _size(0),
      head(new DLinkedNode),
      tail(new DLinkedNode) {
    // 使用伪头部和伪尾部节点
    head->next = tail;
    tail->prev = head;
}

int LRUCache::get(int key) {
    if (!cache.count(key)) {
        return -1;
    }
    // 如果 key 存在，先通过哈希表定位，再移到头部
    auto node = cache[key];
    moveToHead(node);
    return node->value;
}

void LRUCache::put(int key, int value) {
    if (!cache.count(key)) {
        // 如果 key 不存在，创建一个新的节点
        std::shared_ptr<DLinkedNode> node(new DLinkedNode(key, value));
        // 添加进哈希表
        cache[key] = node;
        // 添加至双向链表的头部
        addToHead(node);
        ++_size;
        if (_size > capacity) {
            // 如果超出容量，删除双向链表的尾部节点
            auto removed = removeTail();
            // 删除哈希表中对应的项
            cache.erase(removed->key);
            --_size;
        }
    } else {
        // 如果 key 存在，先通过哈希表定位，再修改 getValue，并移到头部
        auto node = cache[key];
        node->value = value;
        moveToHead(node);
    }
}

void LRUCache::addToHead(const std::shared_ptr<DLinkedNode>& node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
}

void LRUCache::removeNode(const std::shared_ptr<DLinkedNode>& node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LRUCache::moveToHead(const std::shared_ptr<DLinkedNode>& node) {
    removeNode(node);
    addToHead(node);
}

std::shared_ptr<DLinkedNode> LRUCache::removeTail() {
    auto node = tail->prev;
    removeNode(node);
    return node;
}

std::shared_ptr<DLinkedNode> LRUCache::getTail() {
    if (head->next == tail) {
        return {nullptr};
    }
    return tail->prev;
}

int LRUCache::size() const { return _size; }
