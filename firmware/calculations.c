#include "common.h"
#include "ppmio.h"

int expo (int input, unsigned char percent /* 0-100 */) {
	#define X_RANGE 512L
	#define P_RANGE 100L

	long x;
	
	x = (signed long)input*X_RANGE/(SERVO_RANGE/2); // scale down to -512/512
	
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
	
	return (int)x;
}

void mix (int proportional, int differential, int* a, int* b) {
	*a = (proportional+differential)/2;
	*b = (proportional-differential)/2;
}

void slowdown (int input, int* output, int increment) {
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

int scale (int input, unsigned int percent) {
	long temp;
	
	temp = (long)input*percent/100;
	
	return (int)temp;
}

void limit (int *x, int pos, int neg) {
	if (*x > pos) *x = pos;
	if (*x < neg) *x = neg;
}
