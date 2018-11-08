/* Assumes PIC18F2520 running at 24MHz */

#define _XTAL_FREQ 24000000

#include <xc.h>
#include <stdlib.h>
#include "config.h"
#include "common.h"
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

void main(void)
{
	oled_init();
	oled_goto(0,0);
	oled_clear();
	oled_write_string("Hello world!");

	init();
	initTrim();

	while(1)
	{
		if (frameTimer > 20) {
			frameTimer = 0;

			output_pulse[CHANNEL1] = 0;
			output_pulse[CHANNEL2] = 0;
			output_pulse[CHANNEL3] = 0;
			
			trim(TRIM_SWITCH, NO_EXCEPTIONS);
			
			startPPM(10, BEGIN);
		}
	}
}
