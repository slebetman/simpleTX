#include "common.h"
#include "ppmio.h"

unsigned int expo (unsigned int input, unsigned char percent /* 0-100 */) {
	#define X_RANGE 512L
	#define P_RANGE 100L

	long x;
	
	x = ((signed long)input-SERVO_CENTER);  // get stick position relative to center
	x = x*X_RANGE/(SERVO_RANGE/2); // scale down to -512/512
	
	// all calculations from this point on are signed 10 bits:

	// Thanks to Thus from rcgroups for this formula:	
	x = (
			x*x*x/65536*percent/(X_RANGE*X_RANGE/65536) +
			(P_RANGE-percent)*x + 
			P_RANGE/2
		) /
		P_RANGE;
	
	// now scale it back up to full servo pulse:
	
	x = x*(SERVO_RANGE/2)/X_RANGE;
	x += SERVO_CENTER;
	
	return (unsigned int)x;
}

unsigned int reverse (unsigned int input) {
	return SERVO_MAX+SERVO_RANGE-input;
}

void mix (unsigned int proportional, unsigned int differential, unsigned int* a, unsigned int* b) {
	int proportional_normalized, differential_normalized, differential_reverse;

	proportional_normalized = proportional-SERVO_MIN;
	differential_normalized = differential-SERVO_MIN;
	differential_reverse = SERVO_RANGE-differential_normalized;
	
	*a = (proportional_normalized+differential_normalized)/2+SERVO_MIN;
	*b = (proportional_normalized+differential_reverse)/2+SERVO_MIN;
}

void slowdown (unsigned int input, unsigned int* output, int increment) {
	if (increment > 0) {
		if (*output	< input) {
			*output += increment;
		}
	}
	else {
		if (*output > input) {
			*output += increment;
		}
	}
}

unsigned int scale (unsigned int input, unsigned int percent) {
	long temp;
	
	temp = (long)input-SERVO_CENTER;
	temp = temp*percent/100;
	
	return (unsigned int)temp+SERVO_CENTER;
}
