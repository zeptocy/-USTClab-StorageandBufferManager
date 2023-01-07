//
// Created by zzpus on 2023/1/6.
//

#ifndef STORAGEBUFFERMANAGER_DSMGR_H
#define STORAGEBUFFERMANAGER_DSMGR_H

#include "Def.h"

#include <cstdio>

class DSMgr {
  public:
    //    DSMgr();
    //打开数据库磁盘文件
    int OpenFile(const char filename[]);
    //关闭数据库磁盘文件
    int CloseFile();
    //读取指定页
    bFrame ReadPage(int page_id);
    //将frame写会指定页
    size_t WritePage(int frame_id,const bFrame& frm);

//    int Seek(int offset, int pos);

//    FILE* GetFile();
//
//    void IncNumPages();
//
//    int GetNumPages();
//
//    void SetUse(int index, int use_bit);
//
//    int GetUse(int index);

  private:
    FILE* file{};
    int numPages{};
    //    int pages[MAXPAGES]{};
};

#endif // STORAGEBUFFERMANAGER_DSMGR_H
