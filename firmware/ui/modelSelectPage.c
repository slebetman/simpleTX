#include "../common.h"
#include "../drivers/oled.h"
#include "../drivers/button.h"
#include "../drivers/eeprom.h"
#include "../model/model.h"
#include "gui.h"

void getModelFromEeprom (unsigned char id) {
	if (id == SAVED_MODEL) {
		id = readEeprom(0xff);
		if (id >= MAX_MODELS) {
			id = 0;
		}
	} else {
		if (id >= MAX_MODELS) {
			id = 0;
		}
		writeEeprom(0xff, id);
	}

	loadModel(id);
	loadHomePage();
}

void loadModelSelectPage() {
	unsigned char name[11];
	unsigned char xCursor;

	name[10] = 0;

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Models:");
	for (unsigned char i=0; i<MAX_MODELS; i++) {
		getModelName(i,name);
		oled_goto(8,i+2);
		oled_print_signed_number(i);
		oled_write_string(": ");

		if (current_model.name[0] > '~' || current_model.name[0] < ' ') {
			// Invalid name, assume uninitialized:
			xCursor = oled_write_string("-");
		}
		else {
			xCursor = oled_write_string(name);
		}

		if (current_model.id == i) {
			oled_blank(70-xCursor);
			oled_write_string(CHECK);
		}
	}
}

// View:
void updateModelSelectPage() {
	for (unsigned char i=0; i<MAX_MODELS; i++) {
		oled_goto(0,i+2);
		if (i == modelID) {
			oled_write_string(ARROW);
		}
		else {
			oled_blank(6);
		}
	}
}

// Controller:
unsigned char handleModelSelectPage() {
	if (button_click(button1)) {
		modelID--;
		if (modelID < 0) {
			modelID = MAX_MODELS-1;
		}
	}
	if (button_click(button2)) {
		modelID++;
		if (modelID >= MAX_MODELS) {
			modelID = 0;
		}
	}
	if (button_long_press(button2)) {
		getModelFromEeprom(modelID);
		return HOME_PAGE;
	}
	if (button_long_press(button1)) { // cancel
		loadHomePage();
		return HOME_PAGE;
	}

	return MODEL_SELECT_PAGE;
}
