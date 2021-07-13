#include <xc.h>
#include "../common.h"
#include "../model/trim.h"
#include "../model/channels.h"
#include "ppmio.h"

#define PPM_BLANK_CHECK 9 /* milliseconds */
#define IRC_FUDGE_FACTOR 15 /* number of clocks before timer is set */

unsigned char ppmTracker;
signed char channel;
short output_pulse[TOTAL_OUTPUT_CHANNELS];

#pragma interrupt_level 1
#pragma interrupt_level 2
void startPPM (unsigned short duration,signed char mode) {
	if (mode == BEGIN) {
		channel = 0;
		for (unsigned char i=0; i<TOTAL_OUTPUT_CHANNELS; i++) {
			output_pulse[i] = output_channels[i] - IRC_FUDGE_FACTOR;
		}
	}
	duration = 65535-duration;
	TMR1H = duration >> 8;
	TMR1L = duration;
	TMR1IF = 0;
	TMR1IE = 1;
	TMR1ON = 1;
}

void processOutput () {
	unsigned char delay;
	
	PPM_OUT = 0;
	if (channel < TOTAL_OUTPUT_CHANNELS) {
		startPPM(
			output_pulse[channel] + PULSE_CENTER,
			CONTINUE
		);
		channel++;
	}
	else {
		stopPPM();
	}
	for (delay=100;delay--;) {
		NOP();
	}
	PPM_OUT = 1;
}

unsigned char processPPM () {
	if (ppmTracker != tick) { // 1ms
		frameTimer += (tick-ppmTracker) & 0xff;
		ppmTracker = tick;

		if (frameTimer > 20) {
			frameTimer = 0;
			disableInterrupts();	
			startPPM(10, BEGIN);
			enableInterrupts();
			return 1;
		}
	}
	return 0;
}

