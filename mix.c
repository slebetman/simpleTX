#include "txmod.h"
#include "ppmio.h"

void mix(void)
{
	// simple copy mix as template:
	
	output_pulse[CHANNEL1] = input_pulse[AILERON];
	output_pulse[CHANNEL2] = input_pulse[ELEVATOR];
	output_pulse[CHANNEL3] = input_pulse[THROTTLE];
	output_pulse[CHANNEL4] = input_pulse[RUDDER];
}
