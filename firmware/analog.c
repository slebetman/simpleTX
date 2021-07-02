#include <xc.h>

#define ANALOG_CHANNEL0  0x00
#define ANALOG_CHANNEL1  0x04
#define ANALOG_CHANNEL2  0x08
#define ANALOG_CHANNEL3  0x0c
#define ANALOG_CHANNEL4  0x10
#define ANALOG_CHANNEL5  0x14
#define ANALOG_CHANNEL6  0x18
#define ANALOG_CHANNEL7  0x1c
#define ANALOG_CHANNEL8  0x20
#define ANALOG_CHANNEL9  0x24
#define ANALOG_CHANNEL10 0x28
#define ANALOG_CHANNEL11 0x2c
#define ANALOG_CHANNEL12 0x30

#define SAMPLE_RATE 1000

#define STATE_IDLE     0
#define STATE_START    1
#define STATE_WAIT_AQU 2
#define STATE_CONV     3
#define STATE_DONE     4

#define ADFM_JUSTIFY_RIGHT 0x80


unsigned short analog_values[2];
bit analog_mutex;
bit current_channel;
int intervalTimer;
unsigned char analogState;

void analog_init () {
	analog_mutex = 0;
	current_channel = 0;
	intervalTimer = 0;
	
	TRISAbits.TRISA0 = 1; /*set as input port*/
	TRISAbits.TRISA1 = 1; /*set as input port*/
	ADCON1 = 0x0e; /*ref vtg is VDD and Configure pin as analog pin*/
	ADCON2 = 0x92; /*Right Justified, 4Tad and Fosc/32. */
	ADRESH = 0; /*Flush ADC output Register*/
	ADRESL = 0;
	
	analogState = STATE_IDLE;
}

unsigned short analog_get (unsigned char channel) {
	unsigned short val;
	analog_mutex = 1;
	val = analog_values[channel];
	analog_mutex = 0;
	return val;
}

unsigned short analog_get_sync (unsigned int channel)
{
	int digital;
	ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100); /*channel 0 is selected i.e (CHS3CHS2CHS1CHS0=0000)
	and ADC is disabled i.e ADON=0*/
	ADCON0 |= ((1<<ADON)|(1<<GO)); /*Enable ADC and start conversion*/
	while(ADCON0bits.GO_nDONE==1); /*wait for End of conversion i.e. Go/done'=0 conversion completed*/
	digital = (ADRESH*256) | (ADRESL); /*Combine 8-bit LSB and 2-bit MSB*/
	return(digital);
}

void analog_timer_interrupt_handler () {
	intervalTimer++;
	if (analog_mutex) return; // wait until analog_values are free
	
	switch (analogState) {
		case STATE_IDLE:
			if (intervalTimer > SAMPLE_RATE) {
				intervalTimer = 0;
				analogState = STATE_START; 
			}
			break;
		case STATE_START:
			if (current_channel == 0) {
				current_channel = 1;
				ADCON0 =(ADCON0 & 0b11000011)|(ANALOG_CHANNEL1 & 0b00111100);
			}
			else {
				current_channel = 0;
				ADCON0 =(ADCON0 & 0b11000011)|(ANALOG_CHANNEL0 & 0b00111100);
			}
			analogState = STATE_WAIT_AQU;
			break;
		case STATE_WAIT_AQU:
			ADCON0 |= ((1<<ADON)|(1<<GO)); /*Enable ADC and start conversion*/
			analogState = STATE_CONV;
			break;
		case STATE_CONV:
			if (ADCON0bits.GO_nDONE==1) break;  // wait till GODONE bit is zero
			analogState = STATE_DONE;
			break;
		case STATE_DONE:
			if (current_channel == 0) {
				analog_values[0] = (ADRESH << 8) | ADRESL;
			}
			else {
				analog_values[1] = (ADRESH << 8) | ADRESL;
			}
			analogState = STATE_IDLE;
			break;
		default:
			analogState = STATE_IDLE;
	}		
}

