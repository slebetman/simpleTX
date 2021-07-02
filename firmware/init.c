/* Assumes PIC18F2520 running at 32MHz */

#define _XTAL_FREQ 32000000

#include <xc.h>
#include <htc.h>
#include "common.h"
#include "ppmio.h"
#include "i2c.h"
#include "analog.h"

void initTimers (void) {
	// Set up timer 0 for 1ms tick:
	T0CS = 0;

	T0SE = 0;
	
	T0PS2 = 1;
	T0PS1 = 0; // set prescaler to 32
	T0PS0 = 0;

	T08BIT = 1;
	
	PSA = 0;
	TMR0IE = 1; // initialise timer interrupt.
	
	// Set up timer 1 for servo control:
	// TMR1GE = 0;
	TMR1CS = 0; // use internal clock
	T1CKPS0 = 0;
	T1CKPS1 = 0; // 1:4 prescale
	T1SYNC = 1; // disable external sync
	
	// Set up timer 3 for microsecond async timings.
	TMR3CS = 0; // use internal clock
	T3CKPS0 = 0;
	T3CKPS1 = 0; // disable prescaler
	T3SYNC = 1; // disable external sync
	T3CCP1 = 0;
	T3CCP2 = 0;
	
	TMR3IE = 1; // initialise timer 3 interrupt.

	PEIE = 1;

	// Enable timers
	TMR0ON = 1;	
	TMR1ON = 1;
	TMR3ON = 1;
	
	// Clear timer interrupts:
	TMR0IF = 0;
	TMR1IF = 0;
	TMR3IF = 1;
}

void initIO (void) {
	TRISA = 0x03;
	TRISB = 0xF0;
	TRISC = 0xEF;
	RBPU = 0;
}

void initGlobals (void) {
	unsigned char i;
	
	tick = 0;
	frameTimer = 0;

	// Init output_pulse array to sane defaults:
	for (i=0;i<TOTAL_OUTPUT_CHANNELS;i++) {	
		output_pulse[i] = SERVO_MIN;
	}
}

void init (void) {
	// analog_init();
	initTimers();
	initIO();
	initGlobals();
	i2c_init();
	enableInterrupts();
}
