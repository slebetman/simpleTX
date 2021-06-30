#include <xc.h>

void initCpuClock () {
	OSCCONbits.IDLEN = 1;

	// Use primary oscillator as system clock
	OSCCONbits.SCS1 = 0;
	OSCCONbits.SCS0 = 0;

	// Set to 8MHz
	OSCCONbits.IRCF2 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF0 = 1;

	OSCTUNEbits.INTSRC = 1;

	// Enable PLL for 32MHz
	OSCTUNEbits.PLLEN  = 1;
}