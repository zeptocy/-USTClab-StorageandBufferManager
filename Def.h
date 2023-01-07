//
// Created by zzpus on 2023/1/6.
//

#ifndef STORAGEBUFFERMANAGER_DEF_H
#define STORAGEBUFFERMANAGER_DEF_H

constexpr char DBFILENAME[] = {"data.dbf"};
// constexpr int DEFBUFSIZE = 2048;//已将buff size 的初始化移到缓冲区管理器中
constexpr int FRAMESIZE = 4096;
constexpr int MAXPAGES = 100000; // 本实验 MAXPAGES = 50,000
constexpr int RWCOUNT = 500000;

// 实际存储page的地方//
struct bFrame {
    char field[FRAMESIZE];
};

// BCB结构体//
struct BCB {
    int page_id = -1;
    int dirty = 0;
};

#endif // STORAGEBUFFERMANAGER_DEF_H
