#include "analog.h"
#include "../model/channels.h"

#define BAND_FILTER 1
#define DEADBAND 4

short stick_values[TOTAL_ANALOG_CHANNELS];

short read_stick(unsigned char channel) {
	short tmp;
	short comp;

	tmp = analog_get(channel);
	if (channel < TOTAL_JOYSTICK_CHANNELS) {
		comp = stick_values[channel] - tmp;
		if (comp > BAND_FILTER || comp < -BAND_FILTER) {
			comp = tmp - center[channel];
			if (comp < DEADBAND && comp > -DEADBAND) {
				tmp = center[channel];
			}
			stick_values[channel] = tmp;
		}

		return stick_values[channel] - center[channel];
	}
	else {
		// Throttle slider:
		stick_values[channel] = tmp;
		return stick_values[channel] - 1024;
	}
}

#define CENTER_SAMPLES 16
#define CENTER_SAMPLES_DIV 4

void init_joystick () {
	unsigned char i;
	unsigned char j;

	for (i=0; i<TOTAL_JOYSTICK_CHANNELS; i++) {
		center[i] = 0;
		analog_get_sync(i); // do a dummy read to clear rubbish values
	}

	for (j=0; j<CENTER_SAMPLES; j++) {
		for (i=0; i<TOTAL_JOYSTICK_CHANNELS; i++) {
			center[i] += analog_get_sync(i);
		}
		for (i=255; i>0; i--) {} // short delay
	}

	for (i=0; i<TOTAL_JOYSTICK_CHANNELS; i++) {
		center[i] = center[i] >> CENTER_SAMPLES_DIV; // divide by 16
	}
}