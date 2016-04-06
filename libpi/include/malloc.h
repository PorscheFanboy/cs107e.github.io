#ifndef MALLOC_H
#define MALLOC_H

/*
 * Dynamic memory allocation.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 *
 * Date: Feb 27, 2016
 */

#ifndef NULL
#define NULL 0
#endif

typedef unsigned long size_t;

extern void* malloc(size_t n);

#endif
