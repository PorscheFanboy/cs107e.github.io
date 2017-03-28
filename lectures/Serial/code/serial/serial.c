#include "gpio.h"
#include "timer.h"

const int pin = 20;

#define BAUD 9600
#define DELAY (1000000/BAUD)

void bit(int val)
{
    gpio_write(pin, val);
    delay_us(DELAY);
}

void putc(int c)
{
    bit(0); // start bit
    // output 8-bits, lsb first
    for ( int i = 0; i < 8; i++ ) { 
        bit(c & 0x1);
        c >>= 1;
    }
    bit(1); // stop bit
    delay_us(2 * DELAY);
}

void puts(char *s)
{
    while (*s)
        putc(*s++);
}

void main(void)
{
    gpio_set_function(pin, GPIO_FUNC_OUTPUT);
    while (1) {
        puts("hello, laptop\n\r");
        delay_us(8 * DELAY);
    }
}

