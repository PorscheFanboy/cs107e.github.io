#include "gpio.h"
#include "printf.h"
#include "keyboard.h"
#include "timer.h"
#include "interrupts.h"

void main(void) {
    keyboard_init();
    printf_init();
    timer_init();
    system_enable_interrupts();

    while (1) {
        int key = keyboard_read_scancode(); 
        printf("%02x ", key );
	if (key != 0xf0 && key != 0xe0) {
            printf("\n");
	}
    }
}
