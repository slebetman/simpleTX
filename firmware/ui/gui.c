#include "../common.h"
#include "../drivers/analog.h"
#include "../model/channels.h"
#include "../drivers/oled.h"
#include "../model/mixer.h"
#include "../model/model.h"

unsigned char guiTracker;
short guiCount;

void initGUI () {
	oled_clear();
	oled_init();
}

void loadChannelsPage (short modelId) {
	unsigned char i;
	char modelName[NAME_SIZE+1];

	guiTracker = tick;
	guiCount = 0;
	modelName[NAME_SIZE] = 0x00;

	for (i=0;i<NAME_SIZE;i++) {
		modelName[i] = current_model.name[i];
	}

	oled_clear();
	oled_goto(0,0);
	oled_write_string("[");
	oled_print_signed_number(modelId);
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

unsigned char updateGUI () {
	short tmp;
	short xCursor;

	if (guiTracker !=  tick) {
		guiCount += (tick-guiTracker) & 0xff;
		guiTracker = tick;

		if (guiCount >= 1000) { // blink period == 1 second: 0.5 on, 0.5 off
			guiCount -= 1000;
			tmp = analog_count;
			analog_count = 0;

			oled_goto(0,7);
			oled_write_string("Samples/s: ");
			xCursor = oled_print_signed_number(tmp);
			oled_blank((5*6)-xCursor);
		}

		if (guiCount%50 == 25) {
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

		return 1;
	}

	return 0;
}