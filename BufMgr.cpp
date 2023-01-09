//
// Created by zzpus on 2023/1/6.
//

#include "BufMgr.h"

#include <algorithm>
#include <numeric>

BufMgr::BufMgr(int bufsize)
    : BUFFSIZE(bufsize),
      buf(bufsize),
      frame2page(bufsize),
      lruCache(bufsize),
      freeFrame(bufsize) {
    std::iota(freeFrame.begin(),
              freeFrame.end(),
              0); // free frame初始化为 0 ~ BUFFSIZE-1
    dsMgr.OpenFile(DBFILENAME);
}

BufMgr::~BufMgr() {
    printPerformance();
    WriteDirtys();
    dsMgr.CloseFile();
}

int BufMgr::FixPage(int page_id) {
    int frameId = lruCache.get(page_id);
    if (frameId != -1) {
        // page 在缓冲区中 命中次数+1
        ++hitCnt;
        return frameId;
    }
    // page 不在缓冲区中，调用SelectVictim
    ++ICnt;
    frameId = SelectVictim();
    RemoveBCB(frameId);
    buf[frameId] = dsMgr.ReadPage(page_id); // read page to buf
    frame2page[frameId].page_id = page_id;
    frame2page[frameId].dirty = 0;
    lruCache.put(page_id, frameId);
    return frameId;
}

int BufMgr::SelectVictim() {
    int frameId = -1;
    if (NumFreeFrames() > 0) {
        frameId = freeFrame.front();
        freeFrame.pop_front();
        return frameId;
    }
    // 没有空闲frame 需要lru替换
    frameId = lruCache.getTail().second;
    return frameId;
}

int BufMgr::NumFreeFrames() { return (int)freeFrame.size(); }

void BufMgr::RemoveBCB(int frame_id) {
    if (frame2page[frame_id].page_id != -1 && frame2page[frame_id].dirty) {
        ++OCnt;
        dsMgr.WritePage(frame_id, buf[frame_id]);
    }
    frame2page[frame_id].page_id = -1;
    frame2page[frame_id].dirty = 0;
}

void BufMgr::SetDirty(int frame_id) { frame2page[frame_id].dirty = 1; }

void BufMgr::WriteDirtys() {
    int cnt = 0;
    for (int i = 0; i < BUFFSIZE; ++i) {
        if (frame2page[i].page_id != -1 && frame2page[i].dirty) {
            ++cnt;
            dsMgr.WritePage(i, buf[i]);
        }
    }
    std::printf("Write back %d dirty pages to disk\n", cnt);
}

void BufMgr::PrintFrame(int frame_id) {
    std::printf("%d frame info\n", frame_id);
    std::printf("page id: %d\n", frame2page[frame_id].page_id);
    std::printf("dirty: %d\n", frame2page[frame_id].dirty);
}

void BufMgr::printPerformance() const {
    float hitRate = float(hitCnt) / RWCOUNT * 100;
    std::printf("Read Disk: %d, Write Disk: %d, Hit Rate: %.2f%%\n",
                ICnt,
                OCnt,
                hitRate);
}
const std::vector<bFrame>& BufMgr::buff() const { return buf; }

std::vector<bFrame>& BufMgr::buff() { return buf; }

int BufMgr::size() const { return BUFFSIZE; }
