#include "console.h"
#include "interrupts.h"
#include "armtimer.h"
#include "timer.h"

static volatile unsigned int n_timer_interrupts = 0;
static volatile unsigned int a = 0;
static volatile unsigned int b = 0;

void timer_vector(int pc) {
    armtimer_clear_interrupt();
    n_timer_interrupts++;
    a++;
    b++;
    if (a != b) {
        console_printf("VIOLATION (%06d): a=%d,b=%d\n", n_timer_interrupts, a, b);
        delay(3);
    }
}

void main() {
    console_init(20, 40);
    armtimer_init();
    armtimer_start(0x10);
    timer_init();
    system_enable_interrupts();

    while (1) {
//        system_disable_interrupts();
        a++;
        b++;
//        system_enable_interrupts();
    }
}
