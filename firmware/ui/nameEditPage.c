#include "../drivers/oled.h"
#include "../model/model.h"
#include "modelEditPage.h"
#include "gui.h"

#define CHARSET_SIZE 38
#define DIGIT_START  27
char charset[CHARSET_SIZE+1] = " ABCDEFGHIJKLMNOPQRSTUVWXUZ0123456789-";

signed char idx;
bit capitalize;

signed char findIdx (char x) {
	unsigned char i;
	for (i=0; i<CHARSET_SIZE; i++) {
		if (charset[i] == x) {
			return i;
		}
	}
	return 0;
}

void loadNameEditPage () {
	capitalize = 1;
	selection = 0;
	idx = findIdx(current_model.name[0]);

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Name:");

	oled_goto(34-6,3);
	oled_write_string("[");
	oled_goto(34+(6*10),3);
	oled_write_string("]");
}

// View:
void updateNameEditPage () {
	unsigned char i;
	char buffer[2];
	buffer[1] = 0;
	
	oled_goto(34,3);
	if (current_model.name[0] < '~' && current_model.name[0] >= ' ') {
		for (i=0; i<10; i++) {
			buffer[0] = current_model.name[i];
			if (buffer[0] < '~') {
				oled_write_string(buffer);
			}
			else {
				oled_write_string("*");
			}
		}
	}

	oled_goto(34,4);
	for (i=0; i<10; i++) {
		if (i == selection) {
			oled_write_string("^");
		}
		else {
			oled_write_string(" ");
		}
	}
}

void editLetterInName () {
	if (capitalize || idx == 0 || idx >= DIGIT_START) {
		current_model.name[selection] = charset[idx];
	}
	else {
		current_model.name[selection] = idx + 'a' -1;
	}
}

// Controller:
unsigned char handleNameEditPage () {
	if (button_click(button1)) {
		idx--;
		if (idx < 0) {
			idx = CHARSET_SIZE-1;
		}
		editLetterInName();
	}

	if (button_click(button2)) {
		idx++;
		if (idx >= CHARSET_SIZE) {
			idx = 0;
		}
		editLetterInName();
	}

	if (button_long_press(button2)) {
		editLetterInName();
		selection++;
		if (selection >= 10) {
			selection = 0;
		}

		if (charset[idx] == ' ' || selection == 0) {
			capitalize = 1;
		}
		else {
			capitalize = 0;
		}

		idx = findIdx(current_model.name[selection]);
	}

	if (button_long_press(button1)) {
		// save model name??
		loadModelEditPage();
		return MODEL_EDIT_PAGE;
	}

	return NAME_EDIT_PAGE;
}
