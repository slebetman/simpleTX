#include "common.h"
#include "analog.h"
#include "channels.h"
#include "oled.h"
#include "mixer.h"

unsigned char guiTracker;
short seconds;
short guiCount;

void initGUI () {
	guiTracker = tick;
	seconds = 0;
	guiCount = 0;

	oled_clear();
	oled_init();
	oled_goto(0,0);
	oled_write_string("Test Program");

	oled_goto(0,3);
	oled_write_string("CH0:");
	oled_goto(0,4);
	oled_write_string("CH1:");
	oled_goto(64,3);
	oled_write_string("CH2:");
	oled_goto(64,4);
	oled_write_string("CH3:");
}

unsigned char updateGUI () {
	short tmp;
	short xCursor;

	if (guiTracker !=  tick) {
		guiCount += (tick-guiTracker) & 0xff;
		guiTracker = tick;

		if (guiCount >= 1000) { // blink period == 1 second: 0.5 on, 0.5 off
			guiCount = 0;
			seconds ++;
			tmp = analog_count;
			analog_count = 0;

			oled_goto(0,6);
			oled_write_string("Updates/s: ");
			xCursor = oled_print_signed_number(update_count);
			oled_blank((3*6)-xCursor);
			update_count = 0;

			oled_goto(0,7);
			oled_write_string("Samples/s: ");
			xCursor = oled_print_signed_number(tmp);
			oled_blank((3*6)-xCursor);
		}

		if (guiCount%50 == 5) {
			oled_goto(6*4,3);
			xCursor = oled_print_signed_number(channels[0]);
			oled_blank((5*6)-xCursor);

			oled_goto(6*4,4);
			xCursor = oled_print_signed_number(channels[1]);
			oled_blank((5*6)-xCursor);
		
			oled_goto(6*4+64,3);
			xCursor = oled_print_signed_number(channels[2]);
			oled_blank((5*6)-xCursor);

			oled_goto(6*4+64,4);
			xCursor = oled_print_signed_number(channels[3]);
			oled_blank((5*6)-xCursor);
		}

		return 1;
	}

	return 0;
}