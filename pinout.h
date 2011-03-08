/* pinout assumes PIC16F690 */

// PPM signal
#define PPM_IN   RC5
#define PPM_OUT  RC4

// Analog/Potentiometer input
#define ANALOG1  RC3
#define ANALOG2  RC6
#define ANALOG3  RC7

// Digital I/O
#define DIGITAL1 RB7
#define DIGITAL2 RB6
#define DIGITAL3 RB5
#define DIGITAL4 RB4
#define SWITCH1  RA2
#define SWITCH2  RC1
#define SWITCH3  RC0
#define SWITCH4  RC2

#define LED_DATA DIGITAL1
#define LED_CLOCK DIGITAL2
#define LED_LATCH DIGITAL3

