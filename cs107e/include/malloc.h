#ifndef MALLOC_H
#define MALLOC_H

/*
 * Functions for dynamic allocation.
 *
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 * Mon Feb  5 20:02:27 PST 2018
 */
#include <stddef.h> // for size_t


/* Function: malloc
 * ----------------
 * Services a dynamic alloation request. Returns the 
 * address of a block of at least nybtes contiguous bytes
 * or NULL if the request cannot be satisifed.
 */
void *malloc(size_t nbytes);

/* Function: calloc
 * ----------------
 * Calls malloc to fulfill a request for a total of nbytes*nelems
 * bytes and fills the allocated meomry with bytes of value zero.
 */
void *calloc(size_t nbytes, size_t nelems);

/* Function: free
 * --------------
 * Deallocates the memory at an address. The ptr
 * argument is expected to an address that was previously
 * return by malloc and has not yet been freed. If this 
 * precondition is not satisified, the behavior is undefined.
 */
void free(void *ptr);

/* Function: realloc
 * -----------------
 * Changes the size of the allocation pointed to be old_ptr
 * to new_size and returns ptr. If there is not enough
 * room to enlarge the memory allocation pointed to by old_ptr,
 * realloc() creates a new allocation, copies as much of the
 * old data pointed to by ptr as will fit to the new allocation,
 * frees the old allocation, and returns a pointer to the
 * allocated memory.  The old_ptr argument is expected to an
 * address that was previously return by malloc and has not
 * yet been freed. If this precondition is not satisified,
 * the behavior is undefined.
 */
void *realloc(void *old_ptr, size_t new_size);

/* Function: malloc_check
 * ----------------------
 * If you are not doing the extension, you can leave this function
 * as-is (prints a message that check is unvailable).  For the 
 * extension, this function will search the heap and report on every 
 * in-use block with damaged red zones. Use this format like this
 * for each damaged block:
 *
 *    Address 0x00009f98 has damaged red zone(s): [457e107e] [107e107e
 *    Block of size 5 bytes, alllocated by
 *    #0 0x00008a0c at malloc+176
 *    #1 0x000084dc at heap_redzones+80
 *    #2 0x00008544 at main+
 */
void malloc_check (void);

#endif
