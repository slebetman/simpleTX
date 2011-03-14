/* Assumes PIC16F690 running at 24MHz */

#define _XTAL_FREQ 24000000

#include <pic.h>
#include <htc.h>
#include "config.h"
#include "pinout.h"
#include "txmod.h"

#define enableInterrupts() GIE=1
#define disableInterrupts() GIE=0
#define stopCapture() CCP1IE=0;CCP1CON=0x00
#define stopPPM() TMR1IE=0;TMR1ON=0

extern void mix (void);
extern void expo (unsigned char, unsigned char);

unsigned char tick;          // timer tick (roughly 1ms using 24 MHz XTAL)
#define TICK_1MS 70
#define resetTick() tick=0;TMR0=TICK_1MS

bit in_sync;
bit input_done;

signed char channel; // which servo channel to pulse
unsigned char count;

union intOrBytes input_pulse[TOTAL_INPUT_CHANNELS];
union intOrBytes output_pulse[TOTAL_OUTPUT_CHANNELS];

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

#define BEGIN 0
#define CONTINUE 1


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
		count++;
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

void main(void)
{
	#define PPM_BLANK_CHECK 5
	static bit last_ppm = 0;
	unsigned char debug_channel = 0;
	unsigned char i;
	
	union intOrBytes temp = {0};
	
	TRISA = 0xFF;
	TRISB = 0x00;
	TRISC = 0xEF;
	ANSEL = 0x00;
	ANSELH = 0x00;
	count = 0;
	in_sync = 0;
	
	initTimers();
	input_done = 0;
	tick = 0;
	enableInterrupts();
	
	output_pulse[CHANNEL5].integer = SERVO_MIN;
	output_pulse[CHANNEL6].integer = SERVO_MIN;

	while(1)
	{
		/*
		 * Find the start of PPM frame by looking
		 * for the end of a PPM frame.
		 */
		 
		if (PPM_IN != last_ppm) {
			resetTick(); // reset tick counter
			last_ppm = PPM_IN;
		}
		if (tick > PPM_BLANK_CHECK) {
			// assume we are at the end of PPM frame
			in_sync = 1;
			startCapture(BEGIN);
		}
	
		while(in_sync)
		{
			if (input_done) {
				input_done = 0;
				resetTick();

				mix();
				
				temp.integer = 10;
				startPPM(temp,BEGIN);
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
