#include "uart.h"

void main(void)
{
    uart_init();

    while (1) {
        unsigned int ch = uart_getc();
        if (ch == '\r') ch = '\n';
        uart_putc(ch);
    }
}
