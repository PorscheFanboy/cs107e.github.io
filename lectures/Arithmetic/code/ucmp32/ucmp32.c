#include <stdint.h>

#include "register.h"
#include "printf.h"

extern uint32_t sub32(uint32_t a, uint32_t b);

void print(uint32_t a, uint32_t b)
{
    uint32_t c = sub32(a, b);
    uint32_t flags = GETCPSR();
    printf("%08x-%08x=%08x+%08x+1=%08x ", a, b, a, ~b, c );
    printf(" C=%d\n", !!(flags&CPSR_C));
}

void main(void)
{
    printf_init();

    printf("unsigned comparison\n");
    printf(">\n");
    print( 0x00000001, 0x00000000);
    print( 0xffffffff, 0x00000001);
    print( 0xffffffff, 0x00000000);
    printf("==\n");
    print( 0x00000000, 0x00000000);
    print( 0x00000001, 0x00000001);
    print( 0xffffffff, 0xffffffff);
    printf("<\n");
    print( 0x00000000, 0x00000001);
    print( 0x00000000, 0xffffffff);
    print( 0x00000001, 0xffffffff);
}
