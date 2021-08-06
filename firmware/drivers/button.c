#include <xc.h>
#include "../hardware/pinout.h"
#include "button-const.h"

#define LONG_CLICK 750

void button_reset (button *btn) {
	btn->count = 0;
	btn->longCount = 0;
	btn->state = 0;
	btn->longState = 0;
}

void button_init (button *btn, unsigned char id) {
	btn->id = id;
	button_reset(btn);
}

unsigned char button_click (button *btn) {
	static bit value;

	value = 0;

	switch (btn->id) {
		case 1:
			value = BUTTON1;
			break;
		case 2:
			value = BUTTON2;
			break;
		case 3:
			value = BUTTON3;
			break;
		case 4:
			value = BUTTON4;
			break;
	}

	switch (btn->state) {
		case 0:
			if (value == LOW) { // button clicked
				btn->count++;
				if (btn->count > 2) {
					btn->count = 0;
					btn->state = 1;
				}
			}
			else {
				btn->count = 0; // reject spurious signals
			}
			break;
		case 1:
			if (btn->count < 2000) {
				btn->count ++;
			}
			if (value == HIGH) { // button unclicked
				if (btn->count > 2) {
					btn->state = 2;
					if (btn->count < LONG_CLICK) {
						btn->count = 0;
						return 1;
					}
					else {
						btn->count = 0;
					}
				}
			}
			break;
		case 2:
			btn->count++;
			if (btn->count > 50) { // debounce
				button_reset(btn);
			}
			break;
	}
	return 0;
}

unsigned char button_long_press (button *btn) {
	static bit value;

	value = 0;

	switch (btn->id) {
		case 1:
			value = BUTTON1;
			break;
		case 2:
			value = BUTTON2;
			break;
		case 3:
			value = BUTTON3;
			break;
		case 4:
			value = BUTTON4;
			break;
	}

	switch (btn->longState) {
		case 0:
			if (value == LOW) { // button clicked
				btn->longCount++;
				if (btn->longCount >= LONG_CLICK) { // one second press
					btn->longCount = 0;
					btn->longState = 1;
					return 1;
				}
			}
			else {
				btn->longCount = 0; // reject spurious signals
			}
			break;
		case 1:
			if (btn->longCount < 10) {
				btn->longCount ++;
			}
			if (value == HIGH) { // button unclicked
				if (btn->longCount > 2) {
					btn->longCount = 0;
					btn->longState = 2;
				}
			}
			break;
		case 2:
			btn->longCount++;
			if (btn->longCount > 50) { // debounce
				
			}
			break;
	}
	return 0;
}


