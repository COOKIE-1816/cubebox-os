#include "pmm.h"

static	uint32_t _pmm_memory_size = 0;
static	uint32_t _pmm_blocks_used = 0;
static	uint32_t _pmm_blocks_max = 0;
static	uint32_t* _pmm_memoryMap = 0;

inline void pmm_memoryMap_set(int bit) {
	_pmm_memoryMap[bit / 32] |= (1 << (bit % 32));
}

inline void pmm_memoryMap_unset(int bit) {
	_pmm_memoryMap[bit / 32] &= ~(1 << (bit % 32));
}

inline bool pmm_memoryMap_test(int bit) {
	return _pmm_memoryMap[bit / 32] & (1 << (bit % 32));
}

int pmm_findUnallocatedBlock() {
	for (uint32_t i = 0; i < pmmngr_get_block_count() / 32; i++) {
		if (_mmngr_memory_map[i] != 0xffffffff) {
			for (int j = 0; j < 32; j++) {
				int bit = 1 << j;

				if (!(_mmngr_memory_map[i] & bit)) {
					return i * 4 * 8 + j;
				}
			}
		}
	}

	return -1;
}