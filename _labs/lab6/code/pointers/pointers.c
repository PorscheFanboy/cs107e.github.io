#include <stdio.h>
#include <string.h>

void main(void)
{
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


    int f[] = { 0, 1 };
    int g[] = { 2, 3, 4 };
    int *p[2] = { f, g };
    int *q = p[0];

    printf("f = %08x\n", (unsigned)f );
    printf("g = %08x\n", (unsigned)g );
    printf("p = %08x\n", (unsigned)p );
    printf("q = %08x\n", (unsigned)q );
    printf("p[0] = %08x\n", (unsigned)p[0] );
    printf("p[1] = %08x\n", (unsigned)p[1] );


    // // If you uncomment this code, what happens?
    // int (*e)[2] = { {0, 1}, {2, 3}};
    // // What if e is initialized like this?
    // // int (*e)[2] = 0;
    // printf("e = %08x\n", (unsigned)e );
    // printf("e[0] = %08x\n", (unsigned)e[0] );
    // printf("e[1] = %08x\n", (unsigned)e[1] );
    // printf("e[0][0] = %08x\n", (unsigned)e[0][0] );
    // printf("e[1][0] = %08x\n", (unsigned)e[1][0] );

}
