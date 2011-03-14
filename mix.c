#include "txmod.h"

void mix(void)
{
	// simple copy mix as template:
	
	output_pulse[CHANNEL1].integer = input_pulse[CHANNEL1].integer;
	output_pulse[CHANNEL2].integer = input_pulse[CHANNEL2].integer;
	output_pulse[CHANNEL3].integer = input_pulse[CHANNEL3].integer;
	output_pulse[CHANNEL4].integer = input_pulse[CHANNEL4].integer;
}
