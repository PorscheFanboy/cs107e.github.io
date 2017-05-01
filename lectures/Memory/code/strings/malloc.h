#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

void malloc_init(void);

void *malloc(size_t sz);

void free(void *ptr);

#endif