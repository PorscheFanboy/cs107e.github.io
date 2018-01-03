#include <stdio.h>
#include "fs.h"

void timer_init() {}
void console_printf() {}
void delay_us() {}
void uart_putc(char c) { putchar(c); }

int main() {
    /*printf("hello\n");*/
    fs_init();
    fs_test(0);
}
