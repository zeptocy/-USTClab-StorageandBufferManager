//
// Created by zzpus on 2023/1/6.
//

#include "DSMgr.h"


//DSMgr::DSMgr(){
//
//}

int DSMgr::OpenFile(const char filename[]) {
    file = fopen(filename, "r+");
    return file != nullptr;
}

int DSMgr::CloseFile() { return fclose(file); }

bFrame DSMgr::ReadPage(int page_id) {
    bFrame bf_ds{};
    fseek(file, page_id * FRAMESIZE, SEEK_SET);
    fread(&bf_ds, sizeof(bf_ds), 1, file);
    return bf_ds;
}

size_t DSMgr::WritePage(int page_id, const bFrame& frm) {
    fseek(file, page_id * FRAMESIZE, SEEK_SET);
    return fwrite(&frm, sizeof(frm), 1, file);
}

