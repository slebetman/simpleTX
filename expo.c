#include "txmod.h"

#define X_RANGE 512L
#define K_RANGE 100L

void expo (unsigned char channel, unsigned char k /* 0-100 */) {
	long x;
	
	x = ((signed long)input_pulse[channel].integer-SERVO_CENTER);  // get stick position relative to center
	x = x*X_RANGE/(SERVO_RANGE/2); // scale down to -512/512
	
	// all calculations from this point on are signed 10 bits:

	// Thanks to Thus from rcgroups for this formula:	
	x = (
			x*x*x/65536*k/(X_RANGE*X_RANGE/65536) +
			(K_RANGE-k)*x + 
			K_RANGE/2
		) /
		K_RANGE;
	
	// now scale it back up to full servo pulse:
	
	x = x*(SERVO_RANGE/2)/X_RANGE;
	x += SERVO_CENTER;
	
	input_pulse[channel].integer = (unsigned int)x;
}