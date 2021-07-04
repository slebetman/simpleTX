/* Assumes PIC18F2520 running at 32MHz */

#define _XTAL_FREQ 32000000

#include "config.h"

#include <xc.h>
// #include <stdlib.h>
#include "common.h"
#include "cpuclock.h"
#include "ppmio.h"
#include "calculations.h"
#include "trim.h"
#include "init.h"
#include "oled.h"
#include "analog.h"
#include "channels.h"
#include "joystick.h"

unsigned char tick; // timer tick (roughly 1ms using 24 MHz XTAL)
unsigned char frameTimer;

void main(void)
{
	unsigned char tickTracker = tick;
	unsigned char buffer[4];

	short x = 0;
	short seconds = 0;
	short tmp;

	initCpuClock();

	init();
	// initTrim();

	oled_clear();
	oled_init();
	oled_goto(0,0);
	oled_write_string("Test Program");

	while(1)
	{
		// if (frameTimer > 20) {
		// 	frameTimer = 0;

		// 	output_pulse[CHANNEL1] = 0;
		// 	output_pulse[CHANNEL2] = 0;
		// 	output_pulse[CHANNEL3] = 0;
			
		// 	trim(TRIM_SWITCH, NO_EXCEPTIONS);
			
		// 	startPPM(10, BEGIN);
		// }

		if (tickTracker !=  tick) {
			x += (tick - tickTracker) & 0xff;
			if (x >= 1000) { // blink period == 1 second: 0.5 on, 0.5 off
				x = 0;
				seconds ++;
				tmp = analog_count;
				analog_count = 0;

				oled_goto(0,7);
				oled_write_string("Samples/second: ");
				oled_print_signed_number(tmp);
				oled_write_string("        ");
			}

			if (x%20 == 0) {
				for (unsigned char i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
					ANALOG_CHANNEL(i) = read_stick(i);
				}

				oled_goto(0,3);
				oled_write_string("Analog 0: ");
				oled_print_signed_number(ANALOG_CHANNEL(0));
				oled_write_string("        ");

				oled_goto(0,4);
				oled_write_string("Analog 1: ");
				oled_print_signed_number(ANALOG_CHANNEL(1));
				oled_write_string("        ");
			}

			tickTracker = tick;
		}
	}
}
