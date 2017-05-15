#include <stdio.h>

int main() {
    int s = 1;
    unsigned u = 1;
    printf("(1 - 2), signed: %i (0x%x)\n", s - 2, s - 2);
    printf("(1 - 2), unsigned: %u (0x%x)\n", u - 2, u - 2);
    int ls = 0x7fffffff;
    int lu = 0xffffffff;
    printf("(largest + 1), signed: %i (0x%x)\n", ls + 1, ls + 1);
    printf("(largest + 1), unsigned: %u (0x%x)\n", lu + 1, lu + 1);

}
