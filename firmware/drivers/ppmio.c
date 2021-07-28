#include <xc.h>
#include "../common.h"
#include "../model/trim.h"
#include "../model/channels.h"
#include "ppmio.h"

#define IRC_FUDGE_FACTOR 550 /* number of clocks before timer is set */
#define FRAME_FUDGE_FACTOR 4000

unsigned char ppmTracker;
signed char channel;
unsigned short output_pulse[TOTAL_OUTPUT_CHANNELS];
unsigned short currentFrameTime;
bit ppmState;

#define PPM_SIGNAL 0
#define PPM_WAIT   1

#define MARK  0
#define SPACE 1
#define GAP   65035 /* 65535 - 500 */

#pragma interrupt_level 1
#pragma interrupt_level 2
void startPPM (unsigned short duration) {	
	TMR1 = duration;

	TMR1IF = 0;
	TMR1IE = 1;
	TMR1ON = 1;
}

void processOutput () {
	unsigned char delay;
	DEBUG_OUT = 0;
	
	if (ppmState == PPM_SIGNAL) {
		if (channel < TOTAL_OUTPUT_CHANNELS) {
			startPPM(output_pulse[channel]);
			PPM_OUT = MARK;
			channel++;
		}
		else {
			startPPM(65535 - currentFrameTime);
			processPPM();
		}
	}
	else {
		startPPM(GAP);
		PPM_OUT = SPACE;
	}
	ppmState = !ppmState;
}

void processPPM () {
	short pulse;

	currentFrameTime = FRAME_TIME - FRAME_FUDGE_FACTOR;
	frameTimer = 0;
	DEBUG_OUT = 1;
	
	channel = 0;
	ppmState = PPM_SIGNAL;
	for (unsigned char i=0; i<TOTAL_OUTPUT_CHANNELS; i++) {
		pulse = output_channels[i] - IRC_FUDGE_FACTOR + PULSE_CENTER;
		output_pulse[i] = 65535 - pulse;
		currentFrameTime -= pulse;
	}
}

