#ifndef MMU_H
#define MMU_H

#define MMU_BLOCKS_PER_BYTE 8
#define MMU_BLOCK_SIZE      4096
#define MMU_BLOCK_ALIGN     MMU_BLOCK_SIZE

#include "kernel/kernel.h"

static u32  mmu_memory_size = 0;
static u32  mmu_usedBlocks  = 0;
static u32  mmu_maxBlocks   = 0;
static u32* mmu_memoryMap   = 0;


void mmap_set(int __bit);
void mmap_unset(int __bit);

int mmap_test(int __bit);

int mmap_firstFree();

void mmu_init(size_t __size, address_t __bitmap);
void mmu_initRegion(address_t __base, size_t __regionSize);
void mmu_uninitRegion(address_t __base, size_t __regionSize);

void free(void *__p);
void malloc();


#endif

