/* Assumes PIC16F690 running at 24MHz */

#define _XTAL_FREQ 24000000

#include <pic.h>
#include <htc.h>
#include "config.h"
#include "common.h"
#include "ppmio.h"
#include "calculations.h"
#include "init.h"

unsigned char tick;          // timer tick (roughly 1ms using 24 MHz XTAL)

void main(void)
{
	unsigned char debug_channel = 0;
	unsigned char i;
	
	init();

	while(1)
	{
		syncPPM();
	
		while(in_sync)
		{
			if (input_done) {
				input_done = 0;
				
				output_pulse[CHANNEL1] = input_pulse[CHANNEL1];
				output_pulse[CHANNEL2] = input_pulse[CHANNEL2];
				output_pulse[CHANNEL3] = input_pulse[CHANNEL3];
				output_pulse[CHANNEL4] = input_pulse[CHANNEL4];
	
				
				startPPM(10,BEGIN);
			}
			debug_channel = 0;
			if (SWITCH1) {
				debug_channel |= 1;
			}
			if (SWITCH2) {
				debug_channel |= 2;
			}
		}
	}
}
