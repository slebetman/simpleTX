#include "common.h"
#include "analog.h"
#include "channels.h"
#include "oled.h"
#include "mixer.h"
#include "model.h"

unsigned char guiTracker;
short seconds;
short guiCount;

void initGUI () {
	unsigned char i;
	char modelName[NAME_SIZE+1];

	guiTracker = tick;
	seconds = 0;
	guiCount = 0;
	modelName[NAME_SIZE] = 0x00;

	for (i=0;i<NAME_SIZE;i++) {
		modelName[i] = current_model.name[i];
	}

	oled_clear();
	oled_init();
	oled_goto(0,0);
	oled_write_string(modelName);

	oled_goto(0,2);
	oled_write_string("CH0:");
	oled_goto(0,3);
	oled_write_string("CH1:");
	oled_goto(64,2);
	oled_write_string("CH2:");
	oled_goto(64,3);
	oled_write_string("CH3:");
}

unsigned char updateGUI () {
	short tmp;
	short xCursor;

	if (guiTracker !=  tick) {
		guiCount += (tick-guiTracker) & 0xff;
		guiTracker = tick;

		if (guiCount >= 1000) { // blink period == 1 second: 0.5 on, 0.5 off
			guiCount -= 1000;
			seconds ++;
			tmp = analog_count;
			analog_count = 0;

			oled_goto(0,6);
			oled_write_string("Updates/s: ");
			xCursor = oled_print_signed_number(update_count);
			oled_blank((5*6)-xCursor);
			update_count = 0;

			oled_goto(0,7);
			oled_write_string("Samples/s: ");
			xCursor = oled_print_signed_number(tmp);
			oled_blank((5*6)-xCursor);
		}

		if (guiCount%50 == 1) {
			oled_goto(6*4,2);
			xCursor = oled_print_signed_number(channels[0]);
			oled_blank((5*6)-xCursor);

			oled_goto(6*4,3);
			xCursor = oled_print_signed_number(channels[1]);
			oled_blank((5*6)-xCursor);
		}

		if (guiCount%50 == 2) {
			oled_goto(64+(6*4),2);
			xCursor = oled_print_signed_number(channels[2]);
			oled_blank((5*6)-xCursor);

			oled_goto(64+(6*4),3);
			xCursor = oled_print_signed_number(channels[3]);
			oled_blank((5*6)-xCursor);
		}

		return 1;
	}

	return 0;
}