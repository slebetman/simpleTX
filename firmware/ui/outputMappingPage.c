#include "../drivers/button.h"
#include "../drivers/oled.h"
#include "../model/model.h"
#include "modelEditPage.h"
#include "gui.h"

#define SELECT_MODE  0
#define EDIT_MODE    1

unsigned char mode;
signed char mapSelection;
bit edited;

void loadOutputMappingPage () {
	mapSelection = 0;
	edited = 0;
	mode = SELECT_MODE;

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Output map:");

	oled_goto(0+8,2);
	oled_write_string("CH0:");
	oled_goto(0+8,3);
	oled_write_string("CH1:");
	oled_goto(0+8,4);
	oled_write_string("CH2:");
	oled_goto(64+8,2);
	oled_write_string("CH3:");
	oled_goto(64+8,3);
	oled_write_string("CH4:");
	oled_goto(64+8,4);
	oled_write_string("CH5:");
}

void printOutputMap (unsigned char idx) {
	unsigned char source;
	short xCursor;
	
	source = current_model.output_map[idx];
	if (mode == EDIT_MODE && idx == mapSelection) {
		oled_write_string("[");
	}
	else {
		oled_write_string(" ");
	}
	if (source >= USER_CHANNELS) {
		xCursor = oled_write_string("-");
	}
	else {
		xCursor = oled_print_signed_number(source);
	}
	oled_blank(((6*2)+1)-xCursor);
	if (mode == EDIT_MODE && idx == mapSelection) {
		oled_write_string("]");
	}
	else {
		oled_write_string(" ");
	}
}

// View:
void updateOutputMappingPage () {
	unsigned char i;
	short xCursor;

	oled_goto(32,2);
	printOutputMap(0);

	oled_goto(32,3);
	printOutputMap(1);

	oled_goto(32,4);
	printOutputMap(2);

	oled_goto(64+32,2);
	printOutputMap(3);

	oled_goto(64+32,3);
	printOutputMap(4);

	oled_goto(64+32,4);
	printOutputMap(5);

	for (i=0; i<3; i++) {
		oled_goto(0,2+i);
		if (i == mapSelection) {
			oled_write_string(ARROW);
		}
		else {
			oled_blank(6);
		}
	}
	for (i=3; i<6; i++) {
		oled_goto(64,2+i-3);
		if (i == mapSelection) {
			oled_write_string(ARROW);
		}
		else {
			oled_blank(6);
		}
	}
}

unsigned char handleMapSelectMode () {
	if (button_long_press(button1)) {
		if (edited) {
			saveModelOutputMap(current_model.id);
		}
		loadModelEditPage(0);
		return MODEL_EDIT_PAGE;
	}

	if (button_long_press(button2)) {
		tmp = current_model.output_map[mapSelection];
		mode = EDIT_MODE;
	}
	else {
		mapSelection = handleSelection(6, mapSelection);
	}
	return OUTPUT_MAP_PAGE;
}

unsigned char handleMapEditMode () {
	signed char map;
	map = current_model.output_map[mapSelection];
	if (map > USER_CHANNELS) {
		map = USER_CHANNELS;
	}
	map = handleSelection(USER_CHANNELS+1, map);
	if (map >= USER_CHANNELS) {
		map = 0xf;
	}
	current_model.output_map[mapSelection] = map;

	if (button_long_press(button1)) {
		current_model.output_map[mapSelection] = tmp; // cancel changes
		mode = SELECT_MODE;
	}

	if (button_long_press(button2)) {
		edited = 1;
		mode = SELECT_MODE;
	}
	return OUTPUT_MAP_PAGE;
}

// Controller:
unsigned char handleOutputMappingPage () {
	switch (mode) {
		case SELECT_MODE:
			return handleMapSelectMode();
		case EDIT_MODE:
			return handleMapEditMode();
	}

	return OUTPUT_MAP_PAGE;
}
