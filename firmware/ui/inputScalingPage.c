#include "../drivers/button.h"
#include "../drivers/oled.h"
#include "../model/model.h"
#include "modelEditPage.h"
#include "gui.h"

#define SELECT_MODE 0
#define EDIT_MODE   1

signed char selectedInput;
unsigned char mode;
signed char scaleSelection;
bit edited;

void loadInputScalingPage () {
	selectedInput = -1;
	scaleSelection = 0;
	edited = 0;
	mode = SELECT_MODE;

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Input scaling:");

	oled_goto(8,2);
	oled_write_string("EL:");
	oled_goto(8,3);
	oled_write_string("RD:");
	oled_goto(8,4);
	oled_write_string("TH:");
}

// View:
void updateInputScalingPage () {
	unsigned char xCursor;

	drawSelection(3, scaleSelection);

	for (unsigned char i=0; i<3; i++) {
		oled_goto(8+(6*3),2+i);
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

unsigned char handleScaleSelectMode () {
	if (button_long_press(button2)) {
		selectedInput = scaleSelection;
		tmp = current_model.scale[selectedInput];
		mode = EDIT_MODE;
	}
	else {
		scaleSelection = handleSelection(3, scaleSelection);
	}
	
	if (button_long_press(button1)) {
		if (edited) {
			saveModelScale(current_model.id);
		}
		loadModelEditPage(0);
		return MODEL_EDIT_PAGE;
	}

	return INPUT_SCALING_PAGE;
}

unsigned char handleScaleEditMode () {
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
	if (button_long_press(button1)) {
		current_model.scale[selectedInput] = tmp; // cancel changes
		selectedInput = -1;
		mode = SELECT_MODE;
	}
	else {
		current_model.scale[selectedInput] = scaling;

		if (button_long_press(button2)) {
			edited = 1;
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
			return handleScaleSelectMode();
		case EDIT_MODE:
			return handleScaleEditMode();
	}

	return INPUT_SCALING_PAGE;
}
