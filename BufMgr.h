//
// Created by zzpus on 2023/1/6.
//

#ifndef STORAGEBUFFERMANAGER_BUFMGR_H
#define STORAGEBUFFERMANAGER_BUFMGR_H

#include "DSMgr.h"
#include "Def.h"
#include "LRUCache.h"

#include <deque>
#include <vector>

class BufMgr {
  public:
    // 生成一个缓冲管理器，大小为bufsize，默认2048
    explicit BufMgr(int bufsize = 2048);
    ~BufMgr();
    /**
     * 将page读入缓冲区，如果已在缓冲区，返回页框号，否则找一个空闲frame或者换出lru尾部frame
     * @param page_id
     * @return 返回存page的页框号
     */
    int FixPage(int page_id);
    // 空闲frame数目
    int NumFreeFrames();
    // 没有空闲frame时从lru中换一片
    int SelectVictim();

    /**
     * 从缓冲区中移除指定frame，如果frame被修改过，将数据写回对应页
     * @param frame_id
     */
    void RemoveBCB(int frame_id);
    // 将frame_id对应的page脏位置1
    void SetDirty(int frame_id);
    // 程序结束时，将脏位为1的page写回磁盘
    void WriteDirtys();
    // 打印指定frame的信息{page，dirty}
    void PrintFrame(int frame_id);

    const std::vector<bFrame>& buff() const;

    std::vector<bFrame>& buff();
    // 返回缓冲区大小
    int size() const;

    // void NewPage FixNewPage();
    // int UnfixPage(int page_id);
    // int Hash(int page_id);
    // void RemoveLRUEle(int frid);
    // void UnsetDirty(int frame_id);

  private:
    const int BUFFSIZE{2048};    // 缓冲区大小，默认为2048
    std::vector<bFrame> buf;     // buffer
    std::vector<BCB> frame2page; // 存储着frame->BCB(page)的数据
    LRUCache lruCache;           // lru内部包含 page(key) -> frame(getValue)
    std::deque<int> freeFrame;   // 存储空闲frame id
    DSMgr dsMgr{};
    int ICnt{}, OCnt{}, hitCnt{};
    // 程序结束时打印bufMgr性能
    void printPerformance() const;
};

#endif // STORAGEBUFFERMANAGER_BUFMGR_H
