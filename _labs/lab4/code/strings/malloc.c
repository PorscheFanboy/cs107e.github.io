#include "malloc.h"

// Pat's simple "bump allocator" from lecture that 
// just increments the heap segment to allocate space
// never recycles memory (free is a no-op)


extern int __bss_end__;

// Simple roundup function: works for powers of two.
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))

static void *heap = (void *)&__bss_end__;

void malloc_init(void) {
}

void *malloc(size_t n) {
    n = roundup(n, 8);
    void *alloc = heap;
    heap += n;

    return alloc;
}

void free(void *ptr) {
}
