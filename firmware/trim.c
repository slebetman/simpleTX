#include <xc.h>
#include <htc.h>
#include "common.h"
#include "ppmio.h"
#include "eeprom.h"
#include "model.h"

bit trim_mode;
bit safeguard;
short output_trim[TOTAL_OUTPUT_CHANNELS];
short stick_center[TOTAL_OUTPUT_CHANNELS];

#define NO_EXCEPTIONS -1
void trim (unsigned char on_switch, signed char exception) {
	unsigned char i;
	short temp;

	if (on_switch) {
		if (!trim_mode) {
			trim_mode = 1;
			for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
				stick_center[i] = output_pulse[i];
			}
		}
	
		// Left switch clears trim values:
		if (DIGITAL2 && safeguard) {
			for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
				output_trim[i] = 0;
			}
		}
		else {
			safeguard = 1;
			for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
				if (i != exception) {
	
					if (output_pulse[i]-stick_center[i] > 150) output_trim[i] += 1;
					if (output_pulse[i]-stick_center[i] > 600) output_trim[i] += 15;
					if (output_pulse[i]-stick_center[i] < -150) output_trim[i] -= 1;
					if (output_pulse[i]-stick_center[i] < -600) output_trim[i] -= 15;
		
					output_pulse[i] = stick_center[i];
				}
			}
		}
	}
	else if (trim_mode) {
		disableInterrupts();
		trim_mode = 0;
		safeguard = 0;
	
		// save trim here
		enableInterrupts();
	}
}
