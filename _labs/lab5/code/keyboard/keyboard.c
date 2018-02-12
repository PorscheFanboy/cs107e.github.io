#include "gpio.h"
#include "ps2.h"
#include "gpioextra.h"
#include "keyboard.h"

static const unsigned CLK  = GPIO_PIN23;
static const unsigned DATA = GPIO_PIN24; 

void keyboard_init(void) 
{
    gpio_set_input(CLK);
    gpio_set_pullup(CLK); 
 
    gpio_set_input(DATA);
    gpio_set_pullup(DATA); 
}

static void wait_for_falling_clock_edge() 
{
    while (gpio_read(CLK) == 0) {}
    while (gpio_read(CLK) == 1) {}
}

unsigned char keyboard_read_scancode(void) 
{
    // TODO: Implement this function during lab5!
    return 0xff;
}

int keyboard_read_sequence(unsigned char seq[])
{
    // the given implementation below assumes a sequence is one byte long
    // Although this is often the case, is not true for all key actions.
    // What actions generate a sequence of length 2?  What about length 3?
    // Figure out what those cases are and extend this code to
    // recognize them and read the full sequence.
    seq[0] = keyboard_read_scancode();
    return 1;
}

key_event_t keyboard_read_event(void) 
{
    key_event_t event;
    return event;
}

unsigned char keyboard_read_next(void) 
{
    return 'x';
}
