#include "../drivers/button.h"
#include "../drivers/oled.h"
#include "../model/model.h"
#include "mixesPage.h"
#include "gui.h"

#define SELECT_MODE 0
#define EDIT_MODE   1

#define OUT_SELECTED    0
#define IN_SELECTED     1
#define SCALE_SELECTED  2
#define EXPO_SELECTED   3
#define DIR_SELECTED    4

unsigned char mode;
unsigned char mixIdx;
signed char mixSelection;
bit edited;

void loadMixEditPage (unsigned char mix) {
	mode = SELECT_MODE;
	mixIdx = mix;
	edited = 0;
	mixSelection = OUT_SELECTED;

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Mix ");
	oled_print_signed_number(mixIdx+1);
	oled_write_string(":");

	oled_goto(8,2);
	oled_write_string("Out   :");

	oled_goto(8,3);
	oled_write_string("In    :");

	oled_goto(8,4);
	oled_write_string("Scale :");

	oled_goto(8,5);
	oled_write_string("Expo  :");

	oled_goto(8,6);
	oled_write_string("Direction :");
}

void drawSelector (unsigned char i, const char *left, const char *right) {
	if (i < 2) {
		oled_goto(8+(6*7),i+2);
		oled_write_string(left);
		oled_goto(8+(6*10),i+2);
		oled_write_string(right);
	}
	else if (i == 2) {
		oled_goto(8+(6*7),i+2);
		oled_write_string(left);
		oled_goto(8+(6*12),i+2);
		oled_write_string(right);
	}
	else if (i == 3) {
		oled_goto(8+(6*7),i+2);
		oled_write_string(left);
		oled_goto(8+(6*11),i+2);
		oled_write_string(right);
	}
	else {
		oled_goto(8+(6*11),i+2);
		oled_write_string(left);
		oled_goto(8+(6*19),i+2);
		oled_write_string(right);
	}
}

// View:
void updateMixEditPage () {
	unsigned char i;
	unsigned char xCursor;
	unsigned char source;
	unsigned char target;

	source = current_model.mix[mixIdx].input;
	target = current_model.mix[mixIdx].output;

	if (target < USER_CHANNELS) {
		oled_goto(8+(6*8),2); // out
		xCursor = oled_print_signed_number(target+1);
		oled_blank((6*2)-xCursor);

		oled_goto(8+(6*8),3); // in
		if (source < USER_CHANNELS) {
			xCursor = oled_print_signed_number(source+1);
			oled_blank((6*2)-xCursor);
		}
		else if (source == 12) {
			oled_write_string("el");
		}
		else if (source == 13) {
			oled_write_string("rd");
		}
		else if (source == 14) {
			oled_write_string("th");
		}

		oled_goto(8+(6*8),4); // scale
		xCursor = oled_print_signed_number(current_model.mix[mixIdx].scale);
		xCursor += oled_write_string("%");
		oled_blank((6*4)-xCursor);

		oled_goto(8+(6*8),5); // expo
		xCursor = oled_print_signed_number(current_model.mix[mixIdx].expo);
		oled_blank((6*3)-xCursor);

		oled_goto(8+(6*12),6); // direction
		if (current_model.mix[mixIdx].reverse) {
			oled_write_string("reverse");
		}
		else {
			oled_write_string("normal ");
		}
	}
	else {
		oled_goto(8+(6*8),2);
		oled_write_string("- ");

		oled_goto(8+(6*8),3);
		oled_write_string("- ");

		oled_goto(8+(6*8),4);
		oled_write_string("-   ");

		oled_goto(8+(6*8),5);
		oled_write_string("-  ");

		oled_goto(8+(6*12),6);
		oled_write_string("-      ");
	}

	for (i=0; i<5; i++) {
		if (mixSelection == i) {
			oled_goto(0,i+2);
			oled_write_string(ARROW);

			if (mode == EDIT_MODE) {
				drawSelector(i,"[","]");
			}
			else {
				drawSelector(i," "," ");
			}
		}
		else {
			oled_goto(0,i+2);
			oled_blank(6);

			drawSelector(i," "," ");
		}
	}
}

unsigned char handleMixSelectMode () {
	if (button_long_press(button2)) {
		switch (mixSelection) {
			case OUT_SELECTED:
				tmp = current_model.mix[mixIdx].output;
				break;
			case IN_SELECTED:
				tmp = current_model.mix[mixIdx].input;
				break;
			case SCALE_SELECTED:
				tmp = current_model.mix[mixIdx].scale;
				break;
			case EXPO_SELECTED:
				tmp = current_model.mix[mixIdx].expo;
				break;
			case DIR_SELECTED:
				tmp = current_model.mix[mixIdx].reverse;
				break;
		}
		mode = EDIT_MODE;
	}
	else {
		mixSelection = handleSelection(5, mixSelection);
	}

	if (button_long_press(button1)) {
		saveModelMixes(current_model.id);
		loadMixesPage(0);
		return MIXES_PAGE;
	}

	return MIX_EDIT_PAGE;
}

unsigned char handleMixEditMode () {
	unsigned char out;

	switch (mixSelection) {
		case OUT_SELECTED:
			out = current_model.mix[mixIdx].output;
			if (out >= USER_CHANNELS) {
				out = USER_CHANNELS;
			}
			out = handleSelection(USER_CHANNELS+1,out);
			if (out == USER_CHANNELS) {
				out = 0xf;
			}
			current_model.mix[mixIdx].output = out;
			break;
		case IN_SELECTED:
			current_model.mix[mixIdx].input
				= handleSelection(TOTAL_CHANNELS-1,current_model.mix[mixIdx].input);
			break;
		case SCALE_SELECTED:
			current_model.mix[mixIdx].scale
				= handleSelection(127,current_model.mix[mixIdx].scale);
			break;
		case EXPO_SELECTED:
			current_model.mix[mixIdx].expo
				= handleSelection(100,current_model.mix[mixIdx].expo);
			break;
		case DIR_SELECTED:
			current_model.mix[mixIdx].reverse
				= handleSelection(2,current_model.mix[mixIdx].reverse);
			break;
		default:
			mixSelection = OUT_SELECTED;
	}

	if (button_long_press(button2)) {
		edited = 1;
		mode = SELECT_MODE;
	}

	if (button_long_press(button1)) {
		switch (mixSelection) { // cancel changes:
			case OUT_SELECTED:
				current_model.mix[mixIdx].output = tmp;
				break;
			case IN_SELECTED:
				current_model.mix[mixIdx].input = tmp;
				break;
			case SCALE_SELECTED:
				current_model.mix[mixIdx].scale = tmp;
				break;
			case EXPO_SELECTED:
				current_model.mix[mixIdx].expo = tmp;
				break;
			case DIR_SELECTED:
				current_model.mix[mixIdx].reverse = tmp;
				break;
		}
		mode = SELECT_MODE;
	}

	return MIX_EDIT_PAGE;
}

// Controller:
unsigned char handleMixEditPage () {
	switch (mode) {
		case SELECT_MODE:
			return handleMixSelectMode();
		case EDIT_MODE:
			return handleMixEditMode();
	}

	return MIX_EDIT_PAGE;
}
