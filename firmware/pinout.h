/* pinout assumes PIC16F690 */

#include <xc.h>

// PPM signal
#define PPM_IN   PORTCbits.RC5
#define PPM_OUT  PORTCbits.RC4

// Analog/Potentiometer input
#define ANALOG1  PORTCbits.RC7
#define ANALOG2  PORTCbits.RC6
#define ANALOG3  PORTCbits.RC3

// Digital I/O
#define DIGITAL1 PORTBbits.RB4
#define DIGITAL2 PORTBbits.RB5
#define DIGITAL3 PORTBbits.RB6
#define DIGITAL4 PORTBbits.RB7
#define TRIM_SWITCH PORTCbits.RC2


