#include "../common.h"
#include "../drivers/oled.h"
#include "../model/model.h"
#include "modelSelectPage.h"
#include "gui.h"

void loadChannelsPage () {
	unsigned char i;
	char modelName[NAME_SIZE+1];

	modelName[NAME_SIZE] = 0x00;

	for (i=0;i<NAME_SIZE;i++) {
		modelName[i] = current_model.name[i];
	}

	oled_clear();
	oled_goto(0,0);
	oled_write_string("[");
	oled_print_signed_number(current_model.id);
	oled_write_string("] ");
	oled_write_string(modelName);

	oled_goto(0,2);
	oled_write_string("CH0:");
	oled_goto(0,3);
	oled_write_string("CH1:");
	oled_goto(0,4);
	oled_write_string("CH2:");
	oled_goto(64,2);
	oled_write_string("CH3:");
	oled_goto(64,3);
	oled_write_string("CH4:");
	oled_goto(64,4);
	oled_write_string("CH5:");
}

// View:
void updateChannelsPage () {
	short xCursor;

	oled_goto(24,2);
	xCursor = oled_print_signed_number(output_channels[0]);
	oled_blank(36-xCursor);

	oled_goto(24,3);
	xCursor = oled_print_signed_number(output_channels[1]);
	oled_blank(36-xCursor);

	oled_goto(24,4);
	xCursor = oled_print_signed_number(output_channels[2]);
	oled_blank(36-xCursor);

	oled_goto(64+24,2);
	xCursor = oled_print_signed_number(output_channels[3]);
	oled_blank(36-xCursor);

	oled_goto(64+24,3);
	xCursor = oled_print_signed_number(output_channels[4]);
	oled_blank(36-xCursor);

	oled_goto(64+24,4);
	xCursor = oled_print_signed_number(output_channels[5]);
	oled_blank(36-xCursor);
}

// Controller:
unsigned char handleChannelsPage () {
	if (
		button_click(button1) ||
		button_click(button2) ||
		button_click(button3)
	) {
		loadModelSelectPage();
		return MODEL_SELECT_PAGE;
	}
	return CHANNELS_PAGE;
}