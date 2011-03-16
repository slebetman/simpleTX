#include <pic.h>
#include "ppmio.h"
#include "txmod.h"
#include "pinout.h"

#define PPM_BLANK_CHECK 5 /* milliseconds */

signed char channel;
bit in_sync;
bit input_done;

union intOrBytes input_pulse[TOTAL_INPUT_CHANNELS];
union intOrBytes output_pulse[TOTAL_OUTPUT_CHANNELS];

void syncPPM (void) {
	/*
	 * Find the start of PPM frame by looking
	 * for the end of a PPM frame.
	 */   
	static bit last_ppm = 0;
	while(1) {
		if (PPM_IN != last_ppm) {
			resetTick(); // reset tick counter
			last_ppm = PPM_IN;
		}
		if (tick > PPM_BLANK_CHECK) {
			// assume we are at the end of PPM frame
			in_sync = 1;
			startCapture(BEGIN);
			return;
		}
	}
}

void startPPM (union intOrBytes duration,signed char mode) {
	if (mode == BEGIN) {
		channel = 0;
	}
	duration.integer = 65535-duration.integer;
	TMR1H = duration.bytes.high;
	TMR1L = duration.bytes.low;
	TMR1IF = 0;
	TMR1IE = 1;
	TMR1ON = 1;
}

void startCapture (signed char mode) {
	if (mode == BEGIN) {
		channel = -1;
	}
	TMR1H = 0;
	TMR1L = 9;
	TMR1ON = 1;
	CCP1IF = 0;
	CCP1IE = 1;
	CCP1CON = 0x04;
}

void processInput () {
	if (channel < TOTAL_INPUT_CHANNELS) {
		if (channel >= 0) {
			input_pulse[channel].bytes.high = CCPR1H;
			input_pulse[channel].bytes.low  = CCPR1L;
		}
		channel++;
		startCapture(CONTINUE);
	}
	if (channel == TOTAL_INPUT_CHANNELS) {
		stopCapture();
		input_done = 1;
	}
}

void processOutput () {
	unsigned char delay;
	if (channel < TOTAL_OUTPUT_CHANNELS) {
		PPM_OUT = 0;
		startPPM(output_pulse[channel],CONTINUE);
		for (delay=100;delay--;) {
			NOP();
		}
		PPM_OUT = 1;
		channel++;
	}
	else {
		PPM_OUT = 0;
		stopPPM();
		for (delay=100;delay--;) {
			NOP();
		}
		PPM_OUT = 1;
		if (tick > 11) {
			in_sync = 0; // all the processing took too long, skip a frame
		}
		else {
			startCapture(BEGIN);
		}
	}
}

void interrupt HANDLER(void)
{
	if(CCP1IF)
	{
		processInput();
		CCP1IF = 0;
	}
	if(TMR1IF)
	{
		processOutput();
		TMR1IF = 0;
	}
	if(T0IF)
	{
		TMR0 = TICK_1MS;
		T0IF = 0;   // reset timer interrupt
		tick ++;
	}
}

