//
// Created by zzpus on 2023/1/7.
//

#ifndef STORAGEBUFFERMANAGER_TESTBENCH_H
#define STORAGEBUFFERMANAGER_TESTBENCH_H

#include "BufMgr.h"

#include <cstring>
#include <fstream>

/**
 * 初始化数据库磁盘文件，已存在且size吻合则跳过，否则创建文件
 */
void initDBFile() {
    FILE* dbFile = fopen(DBFILENAME, "r");
    if (dbFile) {
        ftell(dbFile);
        fseek(dbFile, 0, SEEK_END);
        auto fsize = ftell(dbFile);
        fclose(dbFile);
        printf("Database file size: %ld KB\n", fsize / 1024);
        if (fsize == MAXPAGES * FRAMESIZE) {
            printf("ADB file existed\n");
            return;
        }
    }
    printf("Creating adb file...\n");
    dbFile = fopen(DBFILENAME, "w+");
    char dbData[MAXPAGES];
    memset(dbData, '0', sizeof(dbData));
    for (int i = 0; i < FRAMESIZE; ++i) {
        fwrite(dbData, sizeof(dbData), 1, dbFile);
    }
    fclose(dbFile);
}

/**
 * 创建一个 buffSize 大小的缓冲区及其管理器，测试系统性能
 * @param buffSize
 */
void TestBench(int buffSize) {
    BufMgr bufMgr(buffSize);

    std::ifstream cmdFile("data-5w-50w-zipf.txt");

    if (!cmdFile.is_open()) {
        perror("open data-5w-50w-zipf.txt error\n");
        exit(1);
    }

    clock_t startTime = 0, finishTime = 0;

    startTime = clock();
    while (cmdFile) {
        int opCode = -1, pageId = -1;
        char ch;
        cmdFile >> opCode >> ch >> pageId;
        switch (opCode) {
        case 0: {                   // read
            bufMgr.FixPage(pageId); // FixPage
            break;
        }
        case 1: { // write
            int fid = bufMgr.FixPage(pageId);
            bufMgr.SetDirty(fid); // 修改脏位
            for (int i = 0; i < 1000; ++i) {
                // 模拟写操作
                bufMgr.buff()[fid].field[i] = 'w';
            }
            break;
        }
        default:
            break;
        }
    }
    finishTime = clock();
    cmdFile.close();
    printf("Buffer size: %d, Run Time: %.2fs\n",
           bufMgr.size(),
           double(finishTime - startTime) / CLOCKS_PER_SEC);
}

#endif // STORAGEBUFFERMANAGER_TESTBENCH_H
