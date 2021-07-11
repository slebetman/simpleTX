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
signed char selection;

void loadMixEditPage (unsigned char mix) {
	mode = SELECT_MODE;
	mixIdx = mix;
	selection = OUT_SELECTED;

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Mix ");
	oled_print_signed_number(mixIdx);
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
	else if (i < 4) {
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
		xCursor = oled_print_signed_number(target);
		oled_blank((6*2)-xCursor);

		oled_goto(8+(6*8),3); // in
		if (source < USER_CHANNELS) {
			xCursor = oled_print_signed_number(source);
			oled_blank((6*2)-xCursor);
		}
		else {
			oled_write_string("J");
			oled_print_signed_number(source-USER_CHANNELS);
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
		if (selection == i) {
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
		mode = EDIT_MODE;
	}
	else {
		selection = handleSelection(5, selection);
	}

	if (button_long_press(button1)) {
		// save mix here?
		loadMixesPage(0);
		return MIXES_PAGE;
	}

	return MIX_EDIT_PAGE;
}

unsigned char handleMixEditMode () {
	switch (selection) {
		case OUT_SELECTED:
			break;
		case IN_SELECTED:
			break;
		case SCALE_SELECTED:
			break;
		case EXPO_SELECTED:
			break;
		case DIR_SELECTED:
			break;
		default:
			selection = OUT_SELECTED;
	}

	if (button_long_press(button1)) {
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
