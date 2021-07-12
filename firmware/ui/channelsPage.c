#include "../common.h"
#include "../drivers/oled.h"
#include "../model/model.h"
#include "modelSelectPage.h"
#include "modelEditPage.h"
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
	xCursor = (output_channels[0] / 64) + 16;
	oled_bar(0x18,0x18,1);
	oled_bar(0x10,0x08,xCursor-1);
	oled_bar(0x7e,0x7e,2);
	oled_bar(0x10,0x08,31-xCursor);
	oled_bar(0x18,0x18,1);

	oled_goto(24,3);
	xCursor = (output_channels[1] / 64) + 16;
	oled_bar(0x18,0x18,1);
	oled_bar(0x10,0x08,xCursor-1);
	oled_bar(0x7e,0x7e,2);
	oled_bar(0x10,0x08,31-xCursor);
	oled_bar(0x18,0x18,1);

	oled_goto(24,4);
	xCursor = (output_channels[2] / 64) + 16;
	oled_bar(0x18,0x18,1);
	oled_bar(0x10,0x08,xCursor-1);
	oled_bar(0x7e,0x7e,2);
	oled_bar(0x10,0x08,31-xCursor);
	oled_bar(0x18,0x18,1);

	oled_goto(64+24,2);
	xCursor = (output_channels[3] / 64) + 16;
	oled_bar(0x18,0x18,1);
	oled_bar(0x10,0x08,xCursor-1);
	oled_bar(0x7e,0x7e,2);
	oled_bar(0x10,0x08,31-xCursor);
	oled_bar(0x18,0x18,1);

	oled_goto(64+24,3);
	xCursor = (output_channels[4] / 64) + 16;
	oled_bar(0x18,0x18,1);
	oled_bar(0x10,0x08,xCursor-1);
	oled_bar(0x7e,0x7e,2);
	oled_bar(0x10,0x08,31-xCursor);
	oled_bar(0x18,0x18,1);

	oled_goto(64+24,4);
	xCursor = (output_channels[5] / 64) + 16;
	oled_bar(0x18,0x18,1);
	oled_bar(0x10,0x08,xCursor-1);
	oled_bar(0x7e,0x7e,2);
	oled_bar(0x10,0x08,31-xCursor);
	oled_bar(0x18,0x18,1);
}

// Controller:
unsigned char handleChannelsPage () {
	if (button_click(button1)) {
		loadModelSelectPage();
		return MODEL_SELECT_PAGE;
	}
	if (button_click(button2)) {
		loadModelEditPage(1);
		return MODEL_EDIT_PAGE;
	}
	return CHANNELS_PAGE;
}