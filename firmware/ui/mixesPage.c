#include "../drivers/button.h"
#include "../drivers/oled.h"
#include "../model/model.h"
#include "modelEditPage.h"
#include "mixEditPage.h"
#include "gui.h"

unsigned char page;
signed char mixesSelection;

void loadPage (unsigned char pageNumber) {
	unsigned char start;
	unsigned char end;
	unsigned char y;
	unsigned char xCursor;
	unsigned char source;
	unsigned char target;

	if (page == pageNumber) return; // skip

	page = pageNumber;

	y = 2;

	switch (pageNumber) {
		case 1:
			start = 0;
			end   = 6;
			break;
		case 2:
			start = 6;
			end   = 12;
	}

	for (unsigned char i=start; i<end; i++,y++) {
		oled_goto(8,y);
		if (i < MAX_MIXES) {
			oled_print_signed_number(i+1);
			oled_write_string(":");
			source = current_model.mix[i].input;
			target = current_model.mix[i].output;

			if (target < USER_CHANNELS) {
				oled_write_string(" o=");
				xCursor = oled_print_signed_number(target+1);
				oled_blank((6*2)-xCursor);

				oled_write_string("i=");
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

				oled_write_string(" s=");
				xCursor = oled_print_signed_number(current_model.mix[i].scale);
				oled_blank((6*3)-xCursor);

				if (current_model.mix[i].reverse) {
					oled_write_string(" R");
				}
				else {
					oled_blank(6*2);
				}
			}
			else {
				oled_write_string("-");
				oled_blank(127-20);
			}
		}
		else {
			oled_blank(120);
		}
	}
}

void loadMixesPage (unsigned char init) {
	page = 0;
	if (init) mixesSelection = 0;

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Mixes:");

	loadPage(1);
}

// View:
void updateMixesPage () {
	unsigned char selectIdx;

	if (mixesSelection < 6) {
		loadPage(1);
		selectIdx = mixesSelection;
	}
	else {
		loadPage(2);
		selectIdx = mixesSelection-6;
	}

	for (unsigned char i=0; i<6; i++) {
		oled_goto(0,i+2);
		if (i == selectIdx) {
			oled_write_string(ARROW);
		}
		else {
			oled_blank(6);
		}
	}
}

// Controller:
unsigned char handleMixesPage () {
	if (button_long_press(button2)) {
		loadMixEditPage(mixesSelection);
		return MIX_EDIT_PAGE;
	}
	else {
		mixesSelection = handleSelection(MAX_MIXES, mixesSelection);
	}

	if (button_long_press(button1)) {
		loadModelEditPage(0);
		return MODEL_EDIT_PAGE;
	}

	return MIXES_PAGE;
}
