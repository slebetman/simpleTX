#include "txmod.h"

void mix(void)
{
	// simple copy mix as template:
	
	output_pulse[0].integer = input_pulse[0].integer;
	output_pulse[1].integer = input_pulse[1].integer;
	output_pulse[2].integer = input_pulse[2].integer;
	output_pulse[3].integer = input_pulse[3].integer;
}
