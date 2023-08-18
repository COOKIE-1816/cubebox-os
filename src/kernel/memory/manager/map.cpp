#include "kernel/memory.h"

inline void MemoryMap::set(int __bit) {
    mmu_memoryMap[__bit / 32] |= (1 << (__bit % 32));
}

inline void MemoryMap::unset(int __bit) {
    mmu_memoryMap[__bit / 32] &= ~ (1 << (__bit % 32));
}

inline int MemoryMap::test(int __bit) {
    return mmu_memoryMap[__bit / 32] & (1 << (__bit % 32));
}

inline int MemoryMap::firstFree() {
    for (u32 i = 0; i < mmu_getBlockCount() / 32; i++)
        if (mmu_memoryMap[i] != 0xffffffff)
            for (int j = 0; j < 32; j++) {
                int bit = 1 << j;

                if (!(mmu_memoryMap[i] & bit) )
                    return i * 4 * 8 + j;
            }
 
// error
    return -1;
}