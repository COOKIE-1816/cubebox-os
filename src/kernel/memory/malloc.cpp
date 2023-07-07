#include "kernel/tty.h"
#include "kernel/memory.h"
#include "stringt.h"

using namespace Kernel::TTY;

static uint32_t last_alloc = 0;
static uint32_t heap_end = 0;
static uint32_t heap_begin = 0;
//static uint32_t pheap_begin = 0;
//static uint32_t pheap_end = 0;
//static uint8_t* pheap_desc = 0;
static uint32_t memory_used = 0;

char* malloc(size_t __size) {
    if(!__size)
        return 0;
    
    uint8_t* mem = (uint8_t*) heap_begin;

    while((uint32_t) mem < last_alloc) {
        alloc_t* a = (alloc_t*) mem;

        if(!a->size)
            goto nalloc;
        
        if(!a->free) {
            mem += a->size;
            mem += sizeof(alloc_t);
            mem += 4;

            continue;
        }

        if(a->size >= __size) {
            a->free = 0;

            memset(mem + sizeof(alloc_t), 0, __size);
            memory_used += __size + sizeof(alloc_t);

            return (char*) (mem + sizeof(alloc_t));
        }

        mem += a->size;
        mem += sizeof(alloc_t);
        mem += 4;
    }

    nalloc:;

    if(last_alloc + __size + sizeof(alloc_t) >= heap_end) {
        writeString("malloc: Err: Out of memory.\n");
        return 0;
    }

    alloc_t* alloc = (alloc_t*) last_alloc;
    alloc->free = 0;
    alloc->size = __size;

    last_alloc += __size;
    last_alloc += sizeof(alloc_t);
    last_alloc += 4;

    memory_used += __size + 4 + sizeof(alloc_t);

    memset((char*) ((uint32_t) alloc + sizeof(alloc_t)), 0, __size);
    return (char*) ((uint32_t) alloc + sizeof(alloc_t));
}