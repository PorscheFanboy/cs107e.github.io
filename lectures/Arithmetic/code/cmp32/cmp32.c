#include <stdint.h>

#include "register.h"
#include "printf.h"

extern uint32_t sub32(uint32_t a, uint32_t b);

void print(uint32_t a, uint32_t b)
{
    uint32_t c = sub32(a, b);
    uint32_t flags = GETCPSR();
    printf("%08x - %08x = %08x: ", a, b, c );
    printf("N=%d, V=%d\n", !!(flags&CPSR_N), !!(flags&CPSR_V));
}

void main(void)
{
    printf_init();

    printf("signed comparison\n");

    printf(">\n");
    print( 0x7fffffff, 0x00000000);
    print( 0x00000000, 0x80000000);
    print( 0x7fffffff, 0x80000000);
    printf("==\n");
    print( 0x00000000, 0x00000000);
    print( 0x80000000, 0x80000000);
    print( 0x7fffffff, 0x7fffffff);
    printf("<\n");
    print( 0x00000000, 0x7fffffff);
    print( 0x80000000, 0x00000000);
    print( 0x80000000, 0x7fffffff);
}
