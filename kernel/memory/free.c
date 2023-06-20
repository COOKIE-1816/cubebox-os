#include "kernel/memory.h"

void free(void* __ptr) {
    if(__ptr == NULL)
        return;

    block* blk = (block*) ((char*) __ptr + sizeof(block));

    blk->free = 1;

    block* nextBlk = blk->next;
    block* prevBlk = head;
    
    if(nextBlk && nextBlk->free) {
        // Merge adjectent free memory blocks.
        blk->size += nextBlk->size + sizeof(block);
        blk->next = nextBlk->next;
    }

    while(prevBlk && prevBlk->next != blk)
        prevBlk = prevBlk->next;
    
    if(prevBlk && prevBlk->size) {
        prevBlk->size += blk->size + sizeof(block);
        prevBlk->next = blk->next;

        blk = prevBlk;
    }

}