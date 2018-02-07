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

#endif
