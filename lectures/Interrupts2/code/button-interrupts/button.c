#include "gpio.h"
#include "gpioextra.h"
#include "gpioevent.h"
#include "console.h"
#include "circular.h"
#include "interrupts.h"

#define LINE_SIZE 39

static cir_t* cir;

void button_vector(int pc) {
    cir_enqueue(cir, pc);
    gpio_clear_event(GPIO_PIN21);
}

void main() {
    gpio_init();
    cir = cir_new();

    console_init(40, 40);

    unsigned int index = 0;
    char line[60];
    line[0] = 0;
    int last_pc = 0;
    gpio_set_input(GPIO_PIN21);
    gpio_set_pullup(GPIO_PIN21);
    gpio_detect_falling_edge(GPIO_PIN21);
    interrupts_enable(INTERRUPTS_GPIO3);

    system_enable_interrupts();

    while (1) {
        console_printf("Button pushes: %s\nLast PC: %x\n\n", line, last_pc);
        last_pc = cir_dequeue(cir);
        line[index] = '+';
        line[++index] = 0;
        if (index >= 60) {
            index = 0;
        }
    }
}
