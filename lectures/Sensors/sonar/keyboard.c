#include <stdio.h>
#include "gpio.h"
#include "ps2.h"
#include "gpioextra.h"
#include "keyboard.h"
#include "uart.h"

const unsigned CLK  = GPIO_PIN23;
const unsigned DATA = GPIO_PIN24; 

void wait_for_falling_clock_edge() {
  while(gpio_read(CLK) == 0) {}
  while(gpio_read(CLK) == 1) {}
}

void keyboard_init(void) {
  gpio_set_function(CLK, GPIO_FUNC_INPUT); 
  gpio_set_pullup(CLK); 
 
  gpio_set_function(DATA, GPIO_FUNC_INPUT); 
  gpio_set_pullup(DATA); 
}

int keyboard_read_scancode(void) {
  // FIXME: Implement this function during lab5.
  unsigned start, data, parity, stop;

  wait_for_falling_clock_edge();
  start = gpio_read(DATA);

  data = 0;
  int i, computed_parity = 1;
  for(i = 0; i < 8; i++) {
  	wait_for_falling_clock_edge();
        unsigned x = gpio_read(DATA);
  	data |= x << i;
        computed_parity ^= x;
  }
  
  wait_for_falling_clock_edge();
  parity = gpio_read(DATA);

  wait_for_falling_clock_edge();
  stop = gpio_read(DATA);
  
  // printf("got: start=%d, data=%x, parity=%d (computed=%d), stop=%d\n", start, data, parity, computed_parity, stop);
  if(start != 0) 
	printf("XXX invalid start bit=1\n");
  if(stop != 1) 
	printf("XXX invalid stop bit=0\n");
  if(computed_parity != parity)
	printf("XXX computed parity = %x, sent parity = %x\n",
		computed_parity, parity);
  return data;
}

key_event_t keyboard_read_event(void) {
  key_event_t event;
  unsigned x = keyboard_read_scancode();
  if(x == 0xE0)
	return keyboard_read_event();
  else if(x == 0xF0) {
    event.down = 0;
    event.code = keyboard_read_scancode();
  } else {
    event.down = 1;
    event.code = x;
  }
  // printf("down=%d, code=%c\n",event.down, char_from_scan[event.code]);
  return event;
}

int is_special(unsigned char code) {
	switch(code) {
	case KEY_LEFT_SHIFT: 
		return KEY_MOD_LEFT_SHIFT;
	case KEY_RIGHT_SHIFT: 
		return KEY_MOD_RIGHT_SHIFT;
	case KEY_LEFT_CONTROL: 
		return KEY_MOD_LEFT_CTRL;
	case KEY_LEFT_ALT: 
		return KEY_MOD_LEFT_ALT;
	// need to get from keyboard
	// case KEY_RIGHT_ALT: return KEY_MOD_RIGHT_ALT;
	// case KEY_RIGHT_CONTROL: return KEY_MOD_RIGHT_CTRL;
	default: return 0;
	}
}


// read until we get a non-control down
key_press_t keyboard_read_press(void) {
	static int caps_lock_down = 0;

	key_press_t p;
  	p.modifiers = caps_lock_down;

  	// if up is a control, then we remove the modifier.
  	while(1) {
		unsigned x;
  		key_event_t k = keyboard_read_event();
		if(!k.down) {
			// remove modifier if any, otherwise ignore.
			if((x = is_special(k.code)))
				p.modifiers &= ~x;
		} else { 
			if((x = is_special(k.code)))
				p.modifiers |= x;
			else if(k.code == KEY_CAPS) {
				if(!caps_lock_down) {
					caps_lock_down = KEY_MOD_CAPS;
					p.modifiers |= caps_lock_down;
				} else {
					p.modifiers &= ~caps_lock_down;
					caps_lock_down = 0;
				}
			} else {
				p.code = k.code;
#if 0
  				printf("modifiers=%x, code=%c\n", p.modifiers, 
						char_from_scan[p.code]);
#endif
				return p;
			}
		}
  	}
}

char keyboard_read_char(void) {
	static int newline = 0;

	if(newline) {
		newline = 0;
		return '\n';
	}

	key_press_t p = keyboard_read_press();

	char c = char_from_scan[p.code];
	if(c == '\n') {
		newline = 1;
		return '\r';
	}
	if(is_char[p.code]) {
		unsigned shiftcaps = KEY_MOD_SHIFT|KEY_MOD_CAPS;
		if(p.modifiers & shiftcaps) {
			// if both, then do nothing.
			if((shiftcaps & p.modifiers) == shiftcaps) 
				return c;
			return shift_char_from_scan[p.code];
		}
	}
	return c;
}
