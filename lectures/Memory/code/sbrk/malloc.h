#ifndef MALLOC_H
#define MALLOC_H

#ifndef NULL
#define NULL 0
#endif

// Bringing this type in from stddef.h.
typedef unsigned long size_t;

void *sbrk(size_t n);
void *malloc(size_t n);

#endif
