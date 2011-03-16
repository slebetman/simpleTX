#include "txmod.h"
#include "ppmio.h"

void mix(void)
{
	// simple copy mix as template:
	
	output_pulse[CHANNEL1].integer = input_pulse[AILERON].integer;
	output_pulse[CHANNEL2].integer = input_pulse[ELEVATOR].integer;
	output_pulse[CHANNEL3].integer = input_pulse[THROTTLE].integer;
	output_pulse[CHANNEL4].integer = input_pulse[RUDDER].integer;
}
