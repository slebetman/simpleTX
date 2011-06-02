#include <pic.h>
#include "ppmio.h"
#include "common.h"
#include "trim.h"

#define PPM_BLANK_CHECK 9 /* milliseconds */

signed char channel;
bit in_sync;
bit input_done;
int input_pulse[TOTAL_INPUT_CHANNELS];
int output_pulse[TOTAL_OUTPUT_CHANNELS];
int input_calibration[TOTAL_INPUT_CHANNELS];
bit input_calibrated;

void syncPPM (void) {
	/*
	 * Find the start of PPM frame by looking
	 * for the end of a PPM frame.
	 */   
	static bit last_ppm = 0;
	resetTick();
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
	int input_buffer;
	unsigned char delay;

	RA1 = 0;
	if (channel < TOTAL_INPUT_CHANNELS) {
		startCapture(CONTINUE);
		if (channel >= 0) {
			input_buffer = ((int)CCPR1H << 8) | CCPR1L;
			input_buffer = input_buffer-PULSE_CENTER;
			if (channel != CHANNEL3) {
				input_buffer = input_buffer-input_calibration[channel];
			}
			input_pulse[channel] = input_pulse[channel] + input_buffer;
			input_pulse[channel] /= 2;
		}
		else {
			resetTick();
		}
		channel++;
	}
	if (channel == TOTAL_INPUT_CHANNELS) {
		stopCapture();
		input_done = 1;
		
		if (!input_calibrated) {
			input_calibrated = 1;
			for (channel=0;channel<TOTAL_INPUT_CHANNELS;channel++) {
				if (channel != CHANNEL3) {
					input_calibration[channel] = input_pulse[channel];
				}
			}
		}
	}
	for (delay=100;delay--;) {
		NOP();
	}
	RA1 = 1;
}

void processOutput () {
	unsigned char delay;
	
	PPM_OUT = 0;
	RA0 = 0;
	if (channel < TOTAL_OUTPUT_CHANNELS) {
		startPPM(
			output_pulse[channel] + output_trim[channel] + PULSE_CENTER,
			CONTINUE
		);
		channel++;
	}
	else {
		stopPPM();
		if (tick >= 19 || tick <= 8) {
			in_sync = 0; // processing time was too long or too short
			             // signal main loop to re-sync with PPM input
		}
		else {
			startCapture(BEGIN);
		}
	}
	for (delay=100;delay--;) {
		NOP();
	}
	PPM_OUT = 1;
	RA0 = 1;
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

