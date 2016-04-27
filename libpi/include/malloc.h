#ifndef MALLOC_H
#define MALLOC_H

// It's great to be able to use NULL.
#ifndef NULL
#define NULL 0
#endif

// Bringing this type in from stddef.h.
typedef unsigned long size_t;

// Simple roundup function: works for powers of two.
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))
#define REDZONE_SIZE  16
#define REDZONE_VALUE 0xDEADBEEF
#define REDZONE_EXTENSION_SIZE 8
// The redzone allocation header.
// If you want to add additional fields to the
// header, you can use the 8 bytes of memory
// allocated in the extensions field.
struct rz_header {
    size_t alloc_size;
    const char *file;
    int line;
    const char *func;
    unsigned char extensions[REDZONE_EXTENSION_SIZE];
};

#ifdef REDZONE_MALLOC
#define malloc(n) _rzmalloc(n, __FILE__, __LINE__, __func__)
void *_rzmalloc(size_t n, const char *file, int line, const char *func);
int rz_check();
#else
#define malloc(n) _malloc(n)
void *_malloc(size_t n);
#endif

#endif /* !MALLOC_H */
