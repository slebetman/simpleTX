/* Assumes PIC16F690 running at 24MHz */

#define _XTAL_FREQ 24000000

#include <pic.h>
#include <htc.h>
#include "config.h"
#include "pinout.h"
#include "txmod.h"
#include "ppmio.h"

#define enableInterrupts() GIE=1
#define disableInterrupts() GIE=0

extern void mix (void);
extern void expo (unsigned char, unsigned char);

unsigned char tick;          // timer tick (roughly 1ms using 24 MHz XTAL)

void initTimers(void)
{
	// Set up timer 0 for 1ms tick:
	T0CS = 0;
	
	PS2 = 1;
	PS1 = 0; // set prescaler to 32
	PS0 = 0;
	
	PSA = 0;
	T0IE = 1; // initialise timer interrupt.
	
	// Set up timer 1 for servo control:
	TMR1GE = 0;
	TMR1CS = 0; // use internal clock
	T1CKPS0 = 0;
	T1CKPS1 = 0; // disable prescaler
	T1SYNC = 1;
	PEIE = 1;
	
	// Clear timer interrupts:
	T0IF = 0;
	TMR1IF = 0;
}

void main(void)
{
	unsigned char debug_channel = 0;
	unsigned char i;
	
	TRISA = 0xFF;
	TRISB = 0x00;
	TRISC = 0xEF;
	ANSEL = 0x00;
	ANSELH = 0x00;
	in_sync = 0;
	
	initTimers();
	input_done = 0;
	tick = 0;
	enableInterrupts();

	// Init output_pulse array to sane defaults:
	for (i=0;i<TOTAL_OUTPUT_CHANNELS;i++) {	
		output_pulse[i] = SERVO_MIN;
	}

	while(1)
	{
		syncPPM();
	
		while(in_sync)
		{
			if (input_done) {
				input_done = 0;
				
				mix();
				
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
