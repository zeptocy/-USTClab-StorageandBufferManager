#include "BufMgr.h"
#include "TestBench.h"



int main() {
    initDBFile();
    TestBench(1024);
    printf("\n");

    TestBench(2048);
    printf("\n");

    TestBench(4096);
    printf("\n");

    TestBench(8192);
    printf("\n");

    TestBench(16384);
    printf("\n");

    TestBench(32768);
    printf("\n");

    TestBench(50000);
    printf("\n");

    return 0;
}
