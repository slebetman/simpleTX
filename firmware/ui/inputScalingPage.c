#include "../drivers/button.h"
#include "../drivers/oled.h"
#include "../model/model.h"
#include "modelEditPage.h"
#include "gui.h"

#define SELECT_MODE 0
#define EDIT_MODE   1

signed char selectedInput;
unsigned char mode;
unsigned char tmp;

void loadInputScalingPage () {
	selectedInput = -1;
	selection = 0;
	mode = SELECT_MODE;

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Input scaling:");

	for (unsigned char i=0; i<4; i++) {
		oled_goto(8,i+2);
		oled_print_signed_number(i);
		oled_write_string(": ");
	}
}

// View:
void updateInputScalingPage () {
	unsigned char xCursor;

	updateSelection(4);

	for (unsigned char i=0; i<4; i++) {
		oled_goto(8+(6*2),2+i);
		if (selectedInput == i) {
			oled_write_string("[");
		}
		else {
			oled_blank(6);
		}
		xCursor = oled_print_signed_number(current_model.scale[i]);
		xCursor += oled_write_string("%");
		oled_blank(30-xCursor);
		if (selectedInput == i) {
			oled_write_string("]");
		}
		else {
			oled_blank(6);
		}
	}
}

unsigned char handleSelectMode () {
	handleSelection(4);

	if (button_long_click(button2)) {
		selectedInput = selection;
		tmp = current_model.scale[selectedInput];
		mode = EDIT_MODE;
	}
	if (button_long_click(button1)) {
		loadModelEditPage();
		return MODEL_EDIT_PAGE;
	}

	return INPUT_SCALING_PAGE;
}

unsigned char handleEditMode () {
	unsigned char scaling = current_model.scale[selectedInput];
	if (button_click(button1)) {
		if (scaling > 0) {
			scaling --;
		}
	}
	if (button_click(button2)) {
		if (scaling < 127) {
			scaling ++;
		}
	}
	if (button_long_click(button1)) {
		current_model.scale[selectedInput] = tmp; // cancel changes
		selectedInput = -1;
		mode = SELECT_MODE;
	}
	else {
		current_model.scale[selectedInput] = scaling;

		if (button_long_click(button2)) {
			// should save to eeprom here??
			selectedInput = -1;
			mode = SELECT_MODE;
		}
	}

	return INPUT_SCALING_PAGE;
}

// Controller:
unsigned char handleInputScalingPage () {
	switch (mode) {
		case SELECT_MODE:
			return handleSelectMode();
		case EDIT_MODE:
			return handleEditMode();
	}

	return INPUT_SCALING_PAGE;
}
