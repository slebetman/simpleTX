/* Assumes PIC18F2520 running at 32MHz */

#define _XTAL_FREQ 32000000

#include "config.h"

#include <xc.h>
#include <stdlib.h>
#include "common.h"
#include "cpuclock.h"
#include "ppmio.h"
#include "calculations.h"
#include "trim.h"
#include "init.h"
#include "oled.h"

unsigned char tick; // timer tick (roughly 1ms using 24 MHz XTAL)
unsigned char frameTimer;

#define LEFT    DIGITAL1
#define RIGHT   DIGITAL2
#define FORWARD DIGITAL3
#define REVERSE DIGITAL4

bit led_state = 0;

void main(void)
{
	unsigned char tickTracker = tick;
	unsigned char buffer[4];

	int x = 0;
	int seconds = 0;

	initCpuClock();

	init();
	// initTrim();

	oled_clear();
	oled_init();
	oled_goto(0,0);
	oled_write_string("Test Program");

	PORTAbits.RA4 = 1;

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
			if (x >= 500) { // blink period == 1 second: 0.5 on, 0.5 off
				x = 0;
				seconds ++;

				if (led_state == 0) {
					led_state = 1;
					PORTAbits.RA4 = 1;
				}
				else {
					led_state = 0;
					PORTAbits.RA4 = 0;
				}

				oled_goto(2,3);
				oled_print_signed_number(seconds/2);
				oled_write_string("     ");
			}

			tickTracker = tick;
		}
	}
}
