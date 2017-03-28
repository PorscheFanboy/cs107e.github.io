#include "malloc.h"

void main()
{
    void *p = sbrk(16);
    (void)p;
}
