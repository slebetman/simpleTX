#include "../drivers/oled.h"
#include "../model/model.h"
#include "modelEditPage.h"
#include "gui.h"

#define CHARSET_SIZE 38
#define DIGIT_START  27
char charset[CHARSET_SIZE+1] = " ABCDEFGHIJKLMNOPQRSTUVWXUZ0123456789-";

signed char idx;
signed char nameSelection;
bit capitalize;
bit edited;

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
	edited = 0;
	nameSelection = 0;
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
		if (i == nameSelection) {
			oled_write_string("^");
		}
		else {
			oled_write_string(" ");
		}
	}
}

void editLetterInName () {
	if (capitalize || idx == 0 || idx >= DIGIT_START) {
		current_model.name[nameSelection] = charset[idx];
	}
	else {
		current_model.name[nameSelection] = idx + 'a' -1;
	}
}

// Controller:
unsigned char handleNameEditPage () {
	if (button_click(button1)) {
		idx--;
		edited = 1;
		if (idx < 0) {
			idx = CHARSET_SIZE-1;
		}
		editLetterInName();
	}

	if (button_click(button2)) {
		idx++;
		edited = 1;
		if (idx >= CHARSET_SIZE) {
			idx = 0;
		}
		editLetterInName();
	}

	if (button_long_press(button2)) {
		editLetterInName();
		nameSelection++;
		if (nameSelection >= 10) {
			nameSelection = 0;
		}

		if (charset[idx] == ' ' || nameSelection == 0) {
			capitalize = 1;
		}
		else {
			capitalize = 0;
		}

		idx = findIdx(current_model.name[nameSelection]);
	}

	if (button_long_press(button1)) {
		if (edited) {
			saveModelName(current_model.id);
		}
		loadModelEditPage(0);
		return MODEL_EDIT_PAGE;
	}

	return NAME_EDIT_PAGE;
}
