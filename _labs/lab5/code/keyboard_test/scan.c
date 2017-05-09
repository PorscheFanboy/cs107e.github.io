#include "gpio.h"
#include "keyboard.h"
#include "uart.h"
#include "printf.h"

extern const int is_char[];
extern const char char_from_scan[];

void main(void) 
{
    gpio_init();
    keyboard_init();
    uart_init();
    printf_init();

    while (1) {
        int key = keyboard_read_scancode(); 
        printf("%02x", key );
        if( key < 0x80 && is_char[key] )
            printf(" (%c)\n", char_from_scan[key]);
        else
            printf("\n");
    }
}
