#include "timer.h"
#include "uart.h"
#include "printf.h"

void main (void)
{
    uart_init();
    delay(2);
    while(1) {
        printf( "hello, laptop\n" );
        delay(1);
    }
}
