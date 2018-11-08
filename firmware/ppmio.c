#include <xc.h>
#include "ppmio.h"
#include "common.h"
#include "trim.h"

#define PPM_BLANK_CHECK 9 /* milliseconds */

signed char channel;
int output_pulse[TOTAL_OUTPUT_CHANNELS];

void startPPM (unsigned int duration,signed char mode) {
	if (mode == BEGIN) {
		channel = 0;
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
	PORTAbits.RA0 = 0;
	if (channel < TOTAL_OUTPUT_CHANNELS) {
		startPPM(
			output_pulse[channel] + output_trim[channel] + PULSE_CENTER,
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
	PORTAbits.RA0 = 1;
}

