#include "stackprof.h"
#include "register.h"
#include "printf.h"
#include "timer.h"
#include "keyboard.h"
#include "console.h"

#define NROWS 20
#define NCOLS 20

void main(void) {
    // Every 10 ms. 4000-sample limit.
    stackprof_init(10000, 4000);

    keyboard_init();
    console_init(NROWS, NCOLS);

    system_enable_interrupts();

    stackprof_on();

    console_printf("Hello, there.\r\n");
    console_printf("does this work?\r\n");
    console_printf("\r\n");

    console_printf("> ");
    char c;
    while (1) {
        c = keyboard_read_char();
        console_putc(c);

        if (c == '\n') {
            break;
        }
    }
    console_printf("Done. Dumping profile now.");

    stackprof_off();

    stackprof_dump();
}
