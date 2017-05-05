#ifndef MALLOC_H
#define MALLOC_H
/*
 * Dynamic memory allocation/deallocation
 */

#include <stddef.h> // for size_t


/* Function: malloc_init
 * ---------------------
 * Initializes the heap to its starting empty state.
 * This function must be called by a client before 
 * making any allocation requests. 
 * Total is the total number of bytes that the heap
 * should reserve to service requests. A heap of
 * 1-2 MB (or less) will typically suffice for our programs.
 * Note that malloc_init can also be used to reset
 * the heap back to the empty state (invalidates all 
 * existing blocks).
 */
void malloc_init(size_t total);


/* Function: malloc
 * ----------------
 * Services a dynamic alloation request. Returns the 
 * address of a block of at least sz contiguous bytes
 * or NULL if the request cannot be satisifed.
 */
void *malloc(size_t sz);


/* Function: free
 * --------------
 * Deallocates the memory at an address. The ptr
 * argument is expected to an address that was previously
 * return by malloc and has not yet been freed. If this 
 * precondition is not satisified, the behavior is undefined.
 */
void free(void *ptr);


#ifdef LEAK_DETECTOR

/* Function: leak_report
 * --------------
 * Prints a list of all remaining allocations, using this format
 * for each block:
 *
 *     8 bytes are lost, allocated by
 *     #0 0x8d80 at malloc+140
 *     #1 0x865c at enqueue+28
 *     #2 0x8470 at heap_extended+52
 */
void leak_report();

#endif

#endif
