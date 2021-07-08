#include <xc.h>
#include "button-const.h"

void button_init (button *btn, unsigned char id) {
	btn->id = id;
	btn->count = 0;
	btn->longCount = 0;
	btn->state = 0;
	btn->longState = 0;
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
					if (btn->count < 1000) {
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
			if (btn->count > 200) { // debounce
				btn->count = 0;
				btn->state = 0;
			}
			break;
	}
	return 0;
}

unsigned char button_long_click (button *btn) {
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

	switch (btn->longState) {
		case 0:
			if (value == LOW) { // button clicked
				btn->longCount++;
				if (btn->longCount >= 1000) { // one second press
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
			if (btn->longCount > 200) { // debounce
				btn->longCount = 0;
				btn->longState = 0;
			}
			break;
	}
	return 0;
}


