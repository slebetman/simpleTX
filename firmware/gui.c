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
}

unsigned char updateGUI () {
	short tmp;

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
			oled_print_signed_number(update_count);
			oled_write_string("        ");
			update_count = 0;

			oled_goto(0,7);
			oled_write_string("Samples/s: ");
			oled_print_signed_number(tmp);
			oled_write_string("        ");
		}

		if (guiCount%50 == 5) {
			oled_goto(0,3);
			oled_write_string("CH0: ");
			oled_print_signed_number(channels[0]);
			oled_write_string("        ");

			oled_goto(0,4);
			oled_write_string("CH1: ");
			oled_print_signed_number(channels[1]);
			oled_write_string("        ");
		}

		return 1;
	}

	return 0;
}