/* pinout assumes PIC16F690 */

#include <xc.h>

// PPM signal
#define PPM_OUT   PORTBbits.RB0
#define TX_BIND   PORTBbits.RB2
#define TX_POWER  PORTBbits.RB1

#define TX_BIND_DISABLED TX_BIND=1
#define TX_BIND_ENABLED  TX_BIND=0
#define TX_POWER_ON      TX_POWER=1
#define TX_POWER_OFF     TX_POWER=0

// Buttons
#define BUTTON1   PORTBbits.RB7
#define BUTTON2   PORTBbits.RB4
#define BUTTON3   PORTBbits.RB3

