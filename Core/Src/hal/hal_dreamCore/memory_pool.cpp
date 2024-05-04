//
// Created by Fir on 2024/5/4 004.
//

#include <cstddef>
#include "memory_pool.h"

//内存池(32 字节对齐)
__attribute__((aligned(32))) unsigned char memBase[MEM_MAX_SIZE];
//SRAM 内存池
//内存管理表
unsigned short memMapBase[MEM_ALLOC_TABLE_SIZE];
//SRAM 内存池 MAP
//内存管理参数
const unsigned long memTblSize = MEM_ALLOC_TABLE_SIZE;//内存表大小
const unsigned long memBlkSize = MEM_BLOCK_SIZE;
//内存分块大小
const unsigned long memSize = MEM_MAX_SIZE;
//内存总大小
//内存管理控制器
struct _m_malloc_dev malloc_dev =
    {
        memInit,               //内存初始化
        memPerused,        //内存使用率
        memBase,                    //内存池
        memMapBase,       //内存管理状态表
        0,                 //内存管理未就绪
    };

//复制内存
//*des:目的地址
//*src:源地址
//n:需要复制的内存长度(字节为单位)
void myMemCpy(void *des, void *src, unsigned long n) {
  unsigned char *xDes = (unsigned char *) des;
  unsigned char *xSrc = (unsigned char *) src;
  while (n--)*xDes++ = *xSrc++;
}

//设置内存
//*s:内存首地址
//c :要设置的值
//count:需要设置的内存大小(字节为单位)
void myMemset(void *s, unsigned char c, unsigned long count) {
  unsigned char *xS = (unsigned char *) s;
  while (count--)*xS++ = c;
}

//内存管理初始化
void memInit(void) {
  myMemset(malloc_dev.memMap, 0, memTblSize * 2);//内存状态表数据清零
  myMemset(malloc_dev.memBase, 0, memSize); //内存池所有数据清零
  malloc_dev.memRdy = 1;
//内存管理初始化 OK
}

//获取内存使用率
//返回值:使用率(0~100)
unsigned char memPerused(void) {
  unsigned long used = 0;
  unsigned long i;
  for (i = 0; i < memTblSize; i++) {
    if (malloc_dev.memMap[i]) used++;
  }
  return (used * 100) / (memTblSize);
}

//内存分配(内部调用)
//memx:所属内存块
//size:要分配的内存大小(字节)
//返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址
unsigned long memMalloc(unsigned long size) {
  signed long offset = 0;
  unsigned short nmemb; //需要的内存块数
  unsigned short cmemb = 0;//连续空内存块数
  unsigned long i;
  if (!malloc_dev.memRdy) malloc_dev.init(); //未初始化,先执行初始化
  if (size == 0) return 0XFFFFFFFF; //不需要分配
  nmemb = size / memBlkSize; //获取需要分配的连续内存块数
  if (size % memBlkSize) nmemb++;

  //搜索整个内存控制区
  for (offset = memTblSize - 1; offset >= 0; offset--) {
    if (!malloc_dev.memMap[offset]) cmemb++; //连续空内存块数增加
    else cmemb = 0; //连续内存块清零

    //找到了连续 nmemb 个空内存块
    if (cmemb == nmemb) {
      //标注内存块非空
      for (i = 0; i < nmemb; i++) malloc_dev.memMap[offset + i] = nmemb;
      return (offset * memBlkSize); //返回偏移地址
    }
  }
  return 0XFFFFFFFF;//未找到符合分配条件的内存块
}

//释放内存(内部调用)
//offset:内存地址偏移
//返回值:0,释放成功;1,释放失败;
unsigned char memFree(unsigned long offset) {
  int i;

  //未初始化,先执行初始化
  if (!malloc_dev.memRdy) {
    malloc_dev.init();
    return 1;//未初始化
  }

  //偏移在内存池内.
  if (offset < memSize) {
    int index = offset / memBlkSize; //偏移所在内存块号码
    int nMemB = malloc_dev.memMap[index];//内存块数量

    //内存块清零
    for (i = 0; i < nMemB; i++) malloc_dev.memMap[index + i] = 0;
    return 0;
  } else return 2;//偏移超区了.
}

//释放内存(外部调用)
//ptr:内存首地址
void myFree(void *ptr) {
  unsigned long offset;
  if (ptr == NULL)return;//地址为 0.
  offset = (unsigned long) ptr - (unsigned long) malloc_dev.memBase;
  memFree(offset); //释放内存
}

//分配内存(外部调用)
//size:内存大小(字节)
//返回值:分配到的内存首地址.
void *myMalloc(unsigned long size) {
  unsigned long offset;
  offset = memMalloc(size);
  if (offset == 0XFFFFFFFF) return NULL;
  else return (void *) ((unsigned long) malloc_dev.memBase + offset);
}

//重新分配内存(外部调用)
//*ptr:旧内存首地址
//size:要分配的内存大小(字节)
//返回值:新分配到的内存首地址.
void *myReAlloc(void *ptr, unsigned long size) {
  unsigned long offset;
  offset = memMalloc(size);
  if (offset == 0XFFFFFFFF) return NULL;
  else {
    //拷贝旧内存内容到新内存
    myMemCpy((void *) ((unsigned long) malloc_dev.memBase + offset), ptr, size);
    myFree(ptr); //释放旧内存
    return (void *) ((unsigned long) malloc_dev.memBase + offset); //返回新内存首地址
  }
}

void *operator new(std::size_t size) noexcept(false) {
  void *res;
  if (size == 0)
    size = 1;
  res = myMalloc(size);
  if (res) return res; //到这里的时候 res是null 所以一直卡在循环里
  //else return nullptr;
}

void operator delete(void *p) { myFree(p); }