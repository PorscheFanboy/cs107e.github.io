#ifndef ASSERT_H
#define ASSERT_H

#define assert(EXPR) \
    if(!EXPR) printf("Assertion failed: file %s, line %d: " #EXPR "\n", __FILE__, __LINE__);

#endif
