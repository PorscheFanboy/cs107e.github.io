#include "uart.h"

void main(void)
{
    uart_init();

    while(1) {        
        unsigned int ch=uart_getc();
        if(ch=='\n')
            ch = '\r';
        uart_putc(ch);
    }
}
