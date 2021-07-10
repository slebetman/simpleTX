#include "../drivers/button.h"
#include "../drivers/oled.h"
#include "../model/model.h"
#include "modelEditPage.h"
#include "gui.h"

#define SELECT_MODE  0
#define EDIT_MODE    1

unsigned char mode;
unsigned char tmp;

void loadOutputMappingPage () {
	selection = 0;
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
	if (mode == EDIT_MODE && idx == selection) {
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
	if (mode == EDIT_MODE && idx == selection) {
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
		if (i == selection) {
			oled_write_string(ARROW);
		}
		else {
			oled_blank(6);
		}
	}
	for (i=3; i<6; i++) {
		oled_goto(64,2+i-3);
		if (i == selection) {
			oled_write_string(ARROW);
		}
		else {
			oled_blank(6);
		}
	}
}

unsigned char handleMapSelectMode () {
	handleSelection(6);

	if (button_long_press(button1)) {
		saveModelOutputMap(current_model.id);
		loadModelEditPage();
		return MODEL_EDIT_PAGE;
	}

	if (button_long_press(button2)) {
		tmp = current_model.output_map[selection];
		mode = EDIT_MODE;
	}
	return OUTPUT_MAP_PAGE;
}

unsigned char handleMapEditMode () {
	signed char map;
	map = current_model.output_map[selection];
	if (map > USER_CHANNELS) {
		map = USER_CHANNELS;
	}
	if (button_click(button1)) {
		map--;
		if (map < 0) {
			map = USER_CHANNELS;
		}
	}
	if (button_click(button2)) {
		map++;
		if (map > USER_CHANNELS) {
			map = 0;
		}
	}
	if (map >= USER_CHANNELS) {
		map = 0xf;
	}
	current_model.output_map[selection] = map;

	if (button_long_press(button1)) {
		current_model.output_map[selection] = tmp; // cancel changes
		mode = SELECT_MODE;
	}

	if (button_long_press(button2)) {
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
