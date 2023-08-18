#include "kernel/memory.h"

inline void MemoryMap::set(int __bit) {
    mmu_memoryMap[__bit / 32] |= (1 << (__bit % 32));
}

inline void MemoryMap::unset(int __bit) {
    mmu_memoryMap[__bit / 32] &= ~ (1 << (__bit % 32));
}