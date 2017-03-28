#include "timer.h"
#include "uart.h"

void putc(int c)
{
    uart_putc(c);
}

void puts(char *s)
{
    while(*s)
        putc(*s++);
}

void main (void)
{
    uart_init(115200);
    while(1) {
        puts( "hello, laptop\n" );
        delay(1);
    }
}
