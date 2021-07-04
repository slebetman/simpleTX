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

unsigned char tick; // timer tick (roughly 1ms using 24 MHz XTAL)
unsigned char frameTimer;

#define LEFT    DIGITAL1
#define RIGHT   DIGITAL2
#define FORWARD DIGITAL3
#define REVERSE DIGITAL4

#define BAND_FILTER 2
#define DEADBAND 10

short stick_values[TOTAL_ANALOG_CHANNELS];

short read_stick(unsigned char channel) {
	short tmp;
	short comp;

	tmp = analog_get(channel);
	comp = stick_values[channel] - tmp;
	if (comp > BAND_FILTER || comp < -BAND_FILTER) {
		if ((tmp - center[channel]) < DEADBAND && (tmp - center[0]) > -DEADBAND) {
			tmp = center[channel];
		}
		stick_values[channel] = tmp;
	}

	return stick_values[channel] - center[channel];
}

#define CENTER_SAMPLES 16

void init_center () {
	unsigned char i;
	unsigned char j;

	for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
		center[i] = 0;
		analog_get_sync(i); // do a dummy read to clear rubbish values
	}

	for (j=0; j<CENTER_SAMPLES; j++) {
		for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
			center[i] += analog_get_sync(i);
		}
		for (i=255; i>0; i--) {} // short delay
	}

	for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
		center[i] = center[i] / CENTER_SAMPLES;
	}
}

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

	init_center();

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
