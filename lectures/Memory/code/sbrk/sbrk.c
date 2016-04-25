#include "malloc.h"

extern int __bss_end__;

// Simple roundup function: works for powers of two.
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))

static void *heap = (void *)&__bss_end__;

void *sbrk(size_t n) {
    n = roundup(n, 8);
    void *alloc = (void *)heap;
    heap += n;

    return alloc;
}
