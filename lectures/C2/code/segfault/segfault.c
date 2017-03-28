#include <stdio.h>

int main()
{
    int *mem = 0;

    for( int i = 0; i < 0x1000; i++ ) {
        printf("%d\n", i);
        mem[i] = 0;
    }
}

