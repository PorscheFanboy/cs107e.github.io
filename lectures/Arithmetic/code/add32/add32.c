#include <stdint.h>

#include "register.h"
#include "printf.h"

extern uint32_t add32(uint32_t a, uint32_t b);

void print(uint32_t a, uint32_t b)
{
    uint32_t c = add32(a, b);
    uint32_t flags = GETCPSR();
    printf("%08x + %08x = %08x : ", a, b, c );
    printf("Z=%d, C=%d\n", !!(flags&CPSR_Z), !!(flags&CPSR_C));
}

void main(void)
{
    printf_init();

    printf("add32\n");
    print( 0x00000000, 0x00000000);
    print( 0x00000000, 0x00000001);
    print( 0x00000001, 0x00000001);
    print( 0x00000002, 0x00000001);
    printf("...\n");
    print( 0xfffffffe, 0x00000001);
    print( 0xffffffff, 0x00000001);
    printf("...\n");
    print( 0xffffffff, 0xffffffff);
}
