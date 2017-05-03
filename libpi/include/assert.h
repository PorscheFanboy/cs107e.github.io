#ifndef ASSERT_H
#define ASSERT_H

extern void abort_assert(int, char *, char *, int);

#define assert(EXPR) abort_assert((EXPR), #EXPR, __FILE__, __LINE__);

#endif
