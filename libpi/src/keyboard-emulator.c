#include "keyboard-emulator.h"
#include "timer.h"
#include "gpio.h"
#include "ps2.h"

#define CLK GPIO_PIN23
#define DATA GPIO_PIN24
#define MAX_CHAR 255

#define BIT_TIME_US 33 //15kHz clock
#define SCANCODE_DELAY_US 100
#define AUTOREPEAT_DELAY_US 50000
#define KEY_DELAY_US 50000

void keyboard_emulator_init() {
	gpio_set_output(CLK);
	gpio_set_output(DATA);
}

void keyboard_write(char *char_seq) {
	for(char* ch = char_seq; *ch; ch++) {
		keyboard_write_char(*ch);
		delay_us(KEY_DELAY_US);
	}
}

void keyboard_write_char(char ch) {
	// Convert to lower-case for scancode lookup
	if ((ch >= 'A') && (ch <= 'Z')) {
		ch = ch - 'A' + 'a';
	}

	unsigned scancode = 0;
	if (ch == ' ') {
		scancode = KEY_SPACE;
	} else {
		for (int i = 0; i <= MAX_CHAR; i++) {
			if (char_from_scan[(int)i] == ch) {
				scancode = i;
				break;
			}
		}
	}

	keyboard_write_event(scancode, 1);
	keyboard_write_event(scancode, 0);
}

void keyboard_hold_key(unsigned scancode, unsigned time_us) {
	unsigned start_time = timer_get_time();
	while(timer_get_time() < (start_time + time_us)) {
		keyboard_write_event(scancode, 1);
		delay_us(AUTOREPEAT_DELAY_US);
	}
	keyboard_write_event(scancode, 0);
}

void keyboard_write_event(unsigned scancode, int down) {
	if (down) {
		keyboard_write_scancode(scancode);
	} else {
		keyboard_write_scancode(PS2_CODE_RELEASE);
		delay_us(SCANCODE_DELAY_US);
		keyboard_write_scancode(scancode);
	}
	delay_us(SCANCODE_DELAY_US);
}

static void toggle_clock() {
	delay_us(BIT_TIME_US);
	gpio_write(CLK, 0);
	delay_us(BIT_TIME_US);
	gpio_write(CLK, 1);
}

void keyboard_write_scancode(unsigned scancode) {
	unsigned parity = 1; //Odd parity

	// Start bit
	gpio_write(DATA, 0);
	toggle_clock();

	// Data bits
	for (int i=0; i < 8; i++) {
		unsigned bit = scancode & 1;
		gpio_write(DATA, bit);
		toggle_clock();
		parity ^= bit;
		scancode = scancode >> 1;
	}

	// Parity bit
	gpio_write(DATA, parity);
	toggle_clock();

	// Stop bit
	gpio_write(DATA, 1);
	toggle_clock();
}
