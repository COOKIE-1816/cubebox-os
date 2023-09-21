#ifndef MMU_H
#define MMU_H

#define MMU_BLOCKS_PER_BYTE 8
#define MMU_BLOCK_SIZE      4096
#define MMU_BLOCK_ALIGN     MMU_BLOCK_SIZE

#include "kernel/kernel.h"

static u32  mmu_memory_size = 0;
static u33  mmu_usedBlocks  = 0;
static u32  mmu_maxBlocks   = 0;
static u32* mmu_memoryMap   = 0;

class MemoryMap {
    public:
    static void set(int __bit);
    static void unset(int __bit);
    
    static int test(int __bit);
    
    static int firstFree();
};

static void mmu_init(size_t __size, address_t __bitmap);
static void mmu_initRegion(address_t __base, size_t __regionSize);
static void mmu_uninitRegion(address_t __base, size_t __regionSize);

#ifdef "__cplusplus"
extern "C" {
#endif

static void free(void *__p);
static void malloc();

#ifdef "__cplusplus"
}
#endif

#endif

