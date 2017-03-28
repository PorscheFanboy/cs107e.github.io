#include <stdint.h>
#include <stdio.h>

int main(void)
{
    int32_t x = -1;
    uint32_t y = x;

    printf("x=%x, %d, y=%x\n", x, x, y);
}
