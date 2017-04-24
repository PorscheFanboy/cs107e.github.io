#include "gpio.h"
#include "timer.h"
#include "printf.h"

void main(void)
{
    printf_init();
    int num = 100;
    while (num >= 0) {
        printf("%d bottles of beer on the walll...\n\r", num);
        num--;
        delay_ms(100);
    }
}
