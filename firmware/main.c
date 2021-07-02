/* Assumes PIC18F2520 running at 32MHz */

#define _XTAL_FREQ 32000000

#include "config.h"

#include <xc.h>
#include <stdlib.h>
#include "common.h"
#include "cpuclock.h"
#include "ppmio.h"
#include "calculations.h"
#include "trim.h"
#include "init.h"
#include "oled.h"
#include "analog.h"

unsigned char tick; // timer tick (roughly 1ms using 24 MHz XTAL)
unsigned char frameTimer;

#define LEFT    DIGITAL1
#define RIGHT   DIGITAL2
#define FORWARD DIGITAL3
#define REVERSE DIGITAL4

#define BAND_FILTER 4
#define DEADBAND 10

bit led_state = 0;

int ADC_Read(int channel)
{
	int digital;
	ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100); /*channel 0 is selected i.e (CHS3CHS2CHS1CHS0=0000)
	and ADC is disabled i.e ADON=0*/
	ADCON0 |= ((1<<ADON)|(1<<GO)); /*Enable ADC and start conversion*/
	while(ADCON0bits.GO_nDONE==1); /*wait for End of conversion i.e. Go/done'=0 conversion completed*/
	digital = (ADRESH*256) | (ADRESL); /*Combine 8-bit LSB and 2-bit MSB*/
	return(digital);
}

void analog_process () {

}

void main(void)
{
	unsigned char tickTracker = tick;
	unsigned char buffer[4];
	int center[2];

	int x = 0;
	int seconds = 0;
	int tmp;
	int comp;

	initCpuClock();

	init();
	// initTrim();
	analog_init();

	oled_clear();
	oled_init();
	oled_goto(0,0);
	oled_write_string("Test Program");

	PORTAbits.RA4 = 1;

	center[0] = ADC_Read(0);
	center[1] = ADC_Read(1);
	center[0] = ADC_Read(0);

	while(1)
	{
		// if (frameTimer > 20) {
		// 	frameTimer = 0;

		// 	output_pulse[CHANNEL1] = 0;
		// 	output_pulse[CHANNEL2] = 0;
		// 	output_pulse[CHANNEL3] = 0;
			
		// 	trim(TRIM_SWITCH, NO_EXCEPTIONS);
			
		// 	startPPM(10, BEGIN);
		// }

		if (tickTracker !=  tick) {
			x += (tick - tickTracker) & 0xff;
			if (x >= 500) { // blink period == 1 second: 0.5 on, 0.5 off
				x = 0;
				seconds ++;

				if (led_state == 0) {
					led_state = 1;
					PORTAbits.RA4 = 1;
				}
				else {
					led_state = 0;
					PORTAbits.RA4 = 0;
				}

				oled_goto(0,7);
				oled_print_signed_number(seconds/2);
				oled_write_string("     ");
			}

			if (x%20 == 0) {
				tmp = (ADC_Read(0) + analog_values[0]) / 2;
				comp = analog_values[0] - tmp;
				if (comp > BAND_FILTER || comp < -BAND_FILTER) {
					if (tmp < DEADBAND && tmp > -DEADBAND) {
						tmp = 0;
					}
					analog_values[0] = tmp;
				}

				tmp = (ADC_Read(1) + analog_values[1]) / 2;
				comp = analog_values[1] - tmp;
				if (comp > BAND_FILTER || comp < -BAND_FILTER) {
					if (tmp < DEADBAND && tmp > -DEADBAND) {
						tmp = 0;
					}
					analog_values[1] = tmp;
				}

				oled_goto(0,3);
				oled_write_string("Analog 0: ");
				oled_print_signed_number(analog_values[0]-center[0]);
				oled_write_string("        ");

				oled_goto(0,4);
				oled_write_string("Analog 1: ");
				oled_print_signed_number(analog_values[1]-center[1]);
				oled_write_string("        ");
			}

			tickTracker = tick;
		}

		// analog_timer_interrupt_handler();
	}
}
