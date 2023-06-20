#ifndef _CB_MEMORY_H_
#define _CB_MEMORY_H_

#include <stddef.h>
#include <stdint.h>

static uint32_t last_alloc = 0;
static uint32_t heap_end = 0;
static uint32_t heap_begin = 0;
static uint32_t pheap_begin = 0;
static uint32_t pheap_end = 0;
static uint8_t* pheap_desc = 0;
static uint32_t memory_used = 0;

/*typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;*/

typedef struct block {
    size_t size;
    struct block* next;
    int free;
} block;

typedef block alloc_t;

static block* head = NULL;

char* malloc(size_t __size);
void free(void* __ptr);

#endif