#include "timer.h"
#include "uart.h"

void putchar(int c)
{
    uart_putc(c);
}

void puts(char *s)
{
    while(*s)
        putchar(*s++);
}

void main (void)
{
    uart_init();
    while(1) {
        puts( "hello, laptop\n" );
        delay(1);
    }
}
