#include "gpio.h"
#include "timer.h"
#include "printf.h"

void main(void)
{
    int num = 100;
    while (num >= 0) {
        printf("%d bottles of beer on the wall, %d bottles of beer.\n\r", 
            num, num);
        printf("Take one down and pass it around, %d bottles of beer on the wall.\n\r", 
            num);
        num--;
        delay_ms(100);
    }
}
