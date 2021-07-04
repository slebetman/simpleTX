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
#include "model.h"

unsigned char tick; // timer tick (roughly 1ms using 24 MHz XTAL)
unsigned char frameTimer;

void main(void)
{
	unsigned char tickTracker = tick;
	unsigned char buffer[4];
	unsigned char i;

	short x = 0;
	short seconds = 0;
	short tmp;
	short update_count = 0;

	struct mix thisMix;

	initCpuClock();

	init();
	// initTrim();

	oled_clear();
	oled_init();
	oled_goto(0,0);
	oled_write_string("Test Program");

	newModel();

	current_model.name[0] = 'T';
	current_model.name[1] = 'e';
	current_model.name[2] = 's';
	current_model.name[3] = 't';

	// // Normal mix
	// current_model.mix[0].input = USER_CHANNELS+0;
	// current_model.mix[0].output = 0;
	// current_model.mix[0].scale = 100;
	// current_model.mix[0].expo = 0;
	// current_model.mix[0].reverse = 0;
	// current_model.mix[1].input = USER_CHANNELS+1;
	// current_model.mix[1].output = 1;
	// current_model.mix[1].scale = 100;
	// current_model.mix[1].expo = 0;
	// current_model.mix[1].reverse = 0;

	// Elevon mix
	current_model.mix[0].input = USER_CHANNELS+0;
	current_model.mix[0].output = 0;
	current_model.mix[0].scale = 50;
	current_model.mix[0].expo = 0;
	current_model.mix[0].reverse = 0;
	current_model.mix[1].input = USER_CHANNELS+1;
	current_model.mix[1].output = 0;
	current_model.mix[1].scale = 50;
	current_model.mix[1].expo = 0;
	current_model.mix[1].reverse = 0;
	current_model.mix[2].input = USER_CHANNELS+0;
	current_model.mix[2].output = 1;
	current_model.mix[2].scale = 50;
	current_model.mix[2].expo = 0;
	current_model.mix[2].reverse = 1;
	current_model.mix[3].input = USER_CHANNELS+1;
	current_model.mix[3].output = 1;
	current_model.mix[3].scale = 50;
	current_model.mix[3].expo = 0;
	current_model.mix[3].reverse = 0;

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

				oled_goto(0,6);
				oled_write_string("Updates/second: ");
				oled_print_signed_number(update_count);
				oled_write_string("        ");
				update_count = 0;

				oled_goto(0,7);
				oled_write_string("Samples/second: ");
				oled_print_signed_number(tmp);
				oled_write_string("        ");
			}

			if (x%20 == 0) {
				update_count ++;

				for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
					tmp = read_stick(i) + current_model.trim[i];
					tmp = scale(tmp, current_model.scale[i]);
					ANALOG_CHANNEL(i) = tmp;
				}

				unsigned char channel_mix_count[USER_CHANNELS];
				for (i=0; i<USER_CHANNELS; i++) {
					channel_mix_count[i] = 0;
					channels[i] = 0;
				}

				for (i=0; i<MAX_MIXES; i++) {
					if (mixIsDisabled(i)) continue;

					thisMix.expo = current_model.mix[i].expo;
					thisMix.input = current_model.mix[i].input;
					thisMix.output = current_model.mix[i].output;
					thisMix.reverse = current_model.mix[i].reverse;
					thisMix.scale = current_model.mix[i].scale;

					tmp = channels[thisMix.input];

					if (thisMix.reverse) tmp = -tmp;

					tmp = scale(tmp, thisMix.scale);

					if (thisMix.expo > 0) {
						tmp = expo(tmp, thisMix.expo);
					}

					channels[thisMix.output] += tmp;
					channel_mix_count[thisMix.output] ++;
				}

				for (i=0; i<USER_CHANNELS; i++) {
					channels[i] = channels[i] / channel_mix_count[i];
				}

				oled_goto(0,3);
				oled_write_string("Analog 0: ");
				oled_print_signed_number(channels[0]);
				oled_write_string("        ");

				oled_goto(0,4);
				oled_write_string("Analog 1: ");
				oled_print_signed_number(channels[1]);
				oled_write_string("        ");
			}

			tickTracker = tick;
		}
	}
}
