#include "../common.h"
#include "../drivers/oled.h"
#include "../drivers/button.h"
#include "../drivers/eeprom.h"
#include "../model/model.h"
#include "channelsPage.h"
#include "gui.h"

#define ARROW "~"

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
	loadChannelsPage();
}

void loadModelSelectPage() {
	unsigned char name[11];
	name[10] = 0;

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Models:");
	for (unsigned char i=0; i<MAX_MODELS; i++) {
		getModelName(i,name);
		oled_goto(8,i+2);
		oled_write_string("[");
		oled_print_signed_number(i);
		oled_write_string("] ");

		if (current_model.name[0] > '~' || current_model.name[0] < ' ') {
			// Invalid name, assume uninitialized:
			oled_write_string("-");
		}
		else {
			oled_write_string(name);
		}

		if (modelID == i) {
			oled_goto(0,i+2);
			oled_write_string(ARROW);
		}
	}
}

// View:
void updateModelSelectPage() {
	// do nothing
}

// Controller:
unsigned char handleModelSelectPage() {
	// if (button_click(button1)) {
	// 	modelID--;
	// 	if (modelID < 0) {
	// 		modelID = MAX_MODELS-1;
	// 	}
	// 	loadModelSelectPage();
	// }
	if (button_click(button1)) {
		modelID++;
		if (modelID >= MAX_MODELS) {
			modelID = 0;
		}
		loadModelSelectPage();
	}
	if (button_click(button2)) {
		getModelFromEeprom(modelID);
		return CHANNELS_PAGE;
	}

	return MODEL_SELECT_PAGE;
}
