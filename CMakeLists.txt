cmake_minimum_required(VERSION 3.24)
project(StorageBufferManager)

set(CMAKE_CXX_STANDARD 11)

add_executable(StorageBufferManager main.cpp Def.h DSMgr.cpp DSMgr.h BufMgr.cpp BufMgr.h LRUCache.cpp LRUCache.h TestBench.h)
