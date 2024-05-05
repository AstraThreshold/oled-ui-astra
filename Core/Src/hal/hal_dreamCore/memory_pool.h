//
// Created by Fir on 2024/5/4 004.
//

#ifndef ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_MEMORY_POOL_H_
#define ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_MEMORY_POOL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---- C ----*/

#ifndef NULL
#define NULL 0
#endif
//内存参数设定. 可以取到4字节-32字节 记得在.cpp文件中同步修改内存池对齐大小
#define MEM_BLOCK_SIZE 32
//内存块大小为 32 字节
#define MEM_MAX_SIZE (13*1023)
//最大管理内存 13K
#define MEM_ALLOC_TABLE_SIZE (MEM_MAX_SIZE/MEM_BLOCK_SIZE) //内存表大小
//内存管理控制器
struct _m_malloc_dev {
  void (*init)();              //初始化
  unsigned char (*perused)();  //内存使用率
  unsigned char *memBase;      //内存池
  unsigned short *memMap;      //内存管理状态表
  unsigned char memRdy;        //内存管理是否就绪
};
extern struct _m_malloc_dev malloc_dev; //在 mallco.c 里面定义
void myMemset(void *s, unsigned char c, unsigned long count);
//设置内存
void myMemCpy(void *des, void *src, unsigned long n);//复制内存
void memInit(void);
//内存管理初始化函数(外/内部调用)
unsigned long memMalloc(unsigned long size);
//内存分配(内部调用)
unsigned char memFree(unsigned long offset);
//内存释放(内部调用)
unsigned char memPerused(void);
//得内存使用率(外/内部调用)

//用户调用函数
void myFree(void *ptr);
//内存释放(外部调用)
void *myMalloc(unsigned long size);
//内存分配(外部调用)
void *myReAlloc(void *ptr, unsigned long size);
//重新分配内存(外部调用)

/*---- C ----*/

#ifdef __cplusplus
}

/*---- Cpp ----*/


/*---- Cpp ----*/

#endif

#endif //ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_MEMORY_POOL_H_
