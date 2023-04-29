#pragma once
#include <stdint.h>
#define PMM_BLOCKS_PER_BYTE 8
#define PMM_BLOCK_SIZE 4096
#define PMM_BLOCK_ALIGN PMM_BLOCK_SIZE

static	uint32_t _pmm_memory_size;
static	uint32_t _pmm_used_blocks;
static	uint32_t _pmm_max_blocks;
static	uint32_t* _pmm_memory_map;