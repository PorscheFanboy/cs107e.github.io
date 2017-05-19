#include "debounce.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"
#include "timer.h"
#include "uart.h"

int npresses = 0;
int BUTTON_PIN = GPIO_PIN25;

unsigned gread(unsigned pin) {
    return gpio_read(BUTTON_PIN);
}

void wait_for_press(void) {
    while (gread(BUTTON_PIN) == 0) {}
    while (gread(BUTTON_PIN) == 1) {}
    npresses++;
}

void main(void) {
    gpio_init();
    debounce_init(BUTTON_PIN);
    timer_init();
    printf_init();

    gpio_set_input(BUTTON_PIN);
    gpio_set_pullup(BUTTON_PIN);

    while (1) {
        wait_for_press();
        for( int i = 0; i < npresses; i++ )
            printf("+");
        printf("\n");
    }
}
