#include "../drivers/oled.h"

void loadSplashScreen () {
	for (unsigned short delay = 500;delay;delay--) {
		oled_goto(37,2);
		oled_write_string("Simple TX");
		oled_goto(54,4);
		oled_write_string("v1.3");
	}
}