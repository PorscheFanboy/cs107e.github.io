#include "gpio.h"
#include "uart.h"
#include "printf.h"

void main(void)
{
    gpio_init();
    uart_init();

    // multi-dimensional arrays and pointers
    int a[2][2] = { {0, 1}, {2, 3} };
    int *b = &a[0][0];
    int (*c)[2] = a;
    int (*d)[2][2] = &a;

    printf("a = %08x\n", (unsigned)a );
    printf("&a[0][0] = %08x\n", (unsigned)(&a[0][0]) );
    printf("&a[0][1] = %08x\n", (unsigned) &a[0][1]);

    printf("b = %08x\n", (unsigned)b );
    printf("b+1 = %08x\n", (unsigned)(b+1) );
    printf("b+2 = %08x\n", (unsigned)(b+2) );
    printf("&a[0] = %08x\n", (unsigned)(&a[0]) );
    printf("&a[1] = %08x\n", (unsigned)(&a[1]) );
    printf("c = %08x\n", (unsigned)c );
    printf("c+1 = %08x\n", (unsigned)(c+1) );
    printf("d = %08x\n", (unsigned)d );
    printf("d+1 = %08x\n", (unsigned)(d+1) );

    // single dimensional arrays and pointers
    int f[] = { 0, 1 };
    int g[] = { 2, 3, 4 };
    // will the following work?
    // int *h = {2, 3, 4};
    printf("f = %08x\n", (unsigned)f );
    printf("g = %08x\n", (unsigned)g );

    int *p[2] = { f, g };
    int *q = p[0];
    printf("p = %08x\n", (unsigned)p );
    printf("q = %08x\n", (unsigned)q );
    printf("p[0] = %08x\n", (unsigned)p[0] );
    printf("p[1] = %08x\n", (unsigned)p[1] );
}
