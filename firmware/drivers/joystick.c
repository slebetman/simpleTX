#include "analog.h"
#include "../model/channels.h"

#define BAND_FILTER 2
#define DEADBAND 8

short stick_values[TOTAL_ANALOG_CHANNELS];

short read_stick(unsigned char channel) {
	short tmp;
	short comp;

	tmp = analog_get(channel);
	comp = stick_values[channel] - tmp;
	if (comp > BAND_FILTER || comp < -BAND_FILTER) {
		if ((tmp - center[channel]) < DEADBAND && (tmp - center[0]) > -DEADBAND) {
			tmp = center[channel];
		}
		stick_values[channel] = tmp;
	}

	return stick_values[channel] - center[channel];
}

#define CENTER_SAMPLES 16

void init_joystick () {
	unsigned char i;
	unsigned char j;

	for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
		center[i] = 0;
		analog_get_sync(i); // do a dummy read to clear rubbish values
	}

	for (j=0; j<CENTER_SAMPLES; j++) {
		for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
			center[i] += analog_get_sync(i);
		}
		for (i=255; i>0; i--) {} // short delay
	}

	for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
		center[i] = center[i] / CENTER_SAMPLES;
	}
}