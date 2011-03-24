/* Assumes PIC16F690 running at 24MHz */

#define _XTAL_FREQ 24000000

#include <pic.h>
#include <htc.h>
#include "config.h"
#include "common.h"
#include "ppmio.h"
#include "calculations.h"
#include "init.h"

unsigned char tick; // timer tick (roughly 1ms using 24 MHz XTAL)

void main(void)
{
	unsigned int flap_position = 0, temp;
	init();

	while(1)
	{
		syncPPM();
	
		while(in_sync)
		{
			if (input_done) {
				input_done = 0;

				temp = AILERON;				
				if (SWITCH4) {
					AILERON = expo(AILERON, 65);
				}
				
				if (SWITCH1) { // ===================================== ELEVON
					output_pulse[CHANNEL3] = THROTTLE;
					output_pulse[CHANNEL4] = RUDDER;
					mix(AILERON, ELEVATOR,
						&output_pulse[CHANNEL1], &output_pulse[CHANNEL2]);
				}
				else if (SWITCH2) { // ================================ FLAPPERON
					output_pulse[CHANNEL4] = ELEVATOR;
					output_pulse[CHANNEL3] = THROTTLE;
					if (DIGITAL1) {
						slowdown(2500, &flap_position, 70);
					}
					else {
						slowdown(0, &flap_position, -70);
					}
					mix(AILERON, flap_position+SERVO_CENTER,
						&output_pulse[CHANNEL1], &output_pulse[CHANNEL2]);
				}
				else if (SWITCH3) { // ================================ SAILBOAT
					output_pulse[CHANNEL1] = AILERON;
					output_pulse[CHANNEL3] = scale(THROTTLE, 170)+400;
				}
				else { // ============================================= NORMAL
					output_pulse[CHANNEL1] = AILERON;
					output_pulse[CHANNEL2] = ELEVATOR;
					output_pulse[CHANNEL3] = THROTTLE;
					output_pulse[CHANNEL4] = RUDDER;
				}
				AILERON = temp; // restore AILERON in case expo is on
				
				startPPM(10, BEGIN);
			}
		}
	}
}
