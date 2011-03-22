/* pinout assumes PIC16F690 */

#include <pic.h>

// PPM signal
#define PPM_IN   RC5
#define PPM_OUT  RC4

// Analog/Potentiometer input
#define ANALOG1  RC7
#define ANALOG2  RC6
#define ANALOG3  RC3

// Digital I/O
#define DIGITAL1 RB5
#define DIGITAL2 RB6
#define DIGITAL3 RB7
//#define DIGITAL4 RB7
                       /* accidentally broke off DIGITAL1
                        * so now we have only 3 ports
                        */
#define SWITCH1  RA2
#define SWITCH2  RC1
#define SWITCH3  RC0
#define SWITCH4  RC2

#define LED_DATA DIGITAL1
#define LED_CLOCK DIGITAL2
#define LED_LATCH DIGITAL3

