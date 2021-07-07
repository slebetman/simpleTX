#include <xc.h>
#include "button-const.h"

void button_init (button *btn, unsigned char id) {
	btn->count = 0;
	btn->id = id;
	btn->state = 0;
}

unsigned char button_click (button *btn) {
	static bit value;

	value = 0;

	switch (btn->id) {
		case 1:
			value = PORTBbits.RB7;
			break;
		case 2:
			value = PORTBbits.RB4;
			break;
		case 3:
			value = PORTBbits.RB3;
			break;
	}

	switch (btn->state) {
		case 0:
			if (value == LOW) { // button clicked
				btn->count = 0;
				btn->state = 1;
				return 1;
			}
			break;
		case 1:
			if (value == HIGH) { // button unclicked
				btn->count = 0;
				btn->state = 2;
			}
			break;
		case 2:
			btn->count++;
			if (btn->count > 100) { // debounce
				btn->count = 0;
				btn->state = 0;
			}
			break;
	}
	return 0;
}


