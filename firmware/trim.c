#include <xc.h>
#include <htc.h>
#include "common.h"
#include "eeprom.h"
#include "model.h"
#include "channels.h"

bit trim_mode;
bit safeguard;
short input_trim[TOTAL_ANALOG_CHANNELS];
short stick_center[TOTAL_ANALOG_CHANNELS];

#define NO_EXCEPTIONS -1
void trim (unsigned char on_switch, signed char exception) {
	unsigned char i;
	short temp;

	if (on_switch) {
		if (!trim_mode) {
			trim_mode = 1;
			for (i=0; i<TOTAL_ANALOG_CHANNELS;i++) {
				stick_center[i] = ANALOG_CHANNEL(i);
			}
		}
	
		// Left switch clears trim values:
		if (DIGITAL2 && safeguard) {
			for (i=0; i<TOTAL_ANALOG_CHANNELS;i++) {
				input_trim[i] = 0;
			}
		}
		else {
			safeguard = 1;
			for (i=0; i<TOTAL_ANALOG_CHANNELS;i++) {
				if (i != exception) {
	
					if (ANALOG_CHANNEL(i)-stick_center[i] > 150) input_trim[i] += 1;
					if (ANALOG_CHANNEL(i)-stick_center[i] > 600) input_trim[i] += 15;
					if (ANALOG_CHANNEL(i)-stick_center[i] < -150) input_trim[i] -= 1;
					if (ANALOG_CHANNEL(i)-stick_center[i] < -600) input_trim[i] -= 15;
		
					ANALOG_CHANNEL(i) = stick_center[i];
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
