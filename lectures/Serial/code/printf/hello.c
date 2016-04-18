#include "timer.h"
#include "uart.h"
#include "printf.h"

void main (void)
{
    uart_init();
    while(1) {
        printf( "hello, laptop\n" );
        delay(1);
    }
}
