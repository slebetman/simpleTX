#include "common.h"
#include "ppmio.h"

unsigned int expo (unsigned int input, unsigned char k /* 0-100 */) {
	#define X_RANGE 512L
	#define K_RANGE 100L

	long x;
	
	x = ((signed long)input-SERVO_CENTER);  // get stick position relative to center
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
	
	return (unsigned int)x;
}

void mix(unsigned int proportional, unsigned int differential, unsigned int* a, unsigned int* b)
{
	int proportional_normalized, differential_normalized, differential_reverse;

	proportional_normalized = proportional-SERVO_MIN;
	differential_normalized = differential-SERVO_MIN;
	differential_reverse = SERVO_RANGE-differential_normalized;
	
	*a = (proportional_normalized+differential_normalized)/2+SERVO_MIN;
	*b = (proportional_normalized+differential_reverse)/2+SERVO_MIN;
}
