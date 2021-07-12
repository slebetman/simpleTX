/* Assumes PIC18F2520 running at 32MHz */

#define _XTAL_FREQ 32000000

#include <xc.h>
#include <htc.h>
#include "common.h"
#include "drivers/ppmio.h"
#include "drivers/i2c.h"
#include "drivers/analog.h"
#include "drivers/joystick.h"
#include "model/channels.h"
#include "model/mixer.h"

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
	T1CKPS1 = 0; // 1:4 prescale - timer is exactly 0.5us at 32MHz
	             // Note: Since our joystick signal is +/-1024 this means that at 0.5us
				 //       we have roughly full resolution between 1ms to 2ms.
				 //       This also means we can nicely set the 16 bit counter for
				 //       servo timings. Max time we can set would be 32ms which is also
				 //       in the order of magnitude of the CPPM frame.
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
	TRISB = 0xFF;
	TRISC = 0xEF;
	RBPU = 0;
}

void initGlobals (void) {
	unsigned char i;
	
	tick = 0;
	frameTimer = 0;

	// Init output_pulse array to sane defaults:
	for (i=0;i<TOTAL_OUTPUT_CHANNELS;i++) {	
		output_channels[i] = 0;
	}
}

void init (void) {
	initTimers();
	initIO();
	initGlobals();
	i2c_init();
	init_analog();
	init_joystick();
	initMixer();
	enableInterrupts();
}
