#include "../common.h"
#include "../drivers/ppmio.h"

short expo (short input, unsigned char percent /* 0-100 */) {
	#define X_RANGE 512L
	#define P_RANGE 100L

	long x;
	
	x = (signed long)input/2; // scale down to -512/512
	                                  // we're assuming 11 bit input
	
	// all calculations from this point on are signed 10 bits:

	// Thanks to Thus from rcgroups for this formula:	
	x = (
			x*x*x/512*percent/(X_RANGE*X_RANGE/512) +
			(P_RANGE-percent)*x + 
			P_RANGE/2
		) /
		P_RANGE;
	
	// now scale it back up to full range:
	
	x = x*2;
	
	return (short)x;
}

void slowdown (short input, short* output, short increment) {
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

short scale (short input, unsigned short percent) {
	long temp;
	
	temp = (long)input*percent/100;
	
	return (short)temp;
}

void limit (short *x, short pos, short neg) {
	if (*x > pos) *x = pos;
	if (*x < neg) *x = neg;
}
