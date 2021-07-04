#include <xc.h>
#include "analog-const.h"

unsigned short analog_buffer[TOTAL_ANALOG_CHANNELS][3];
unsigned short analog_values[TOTAL_ANALOG_CHANNELS];
bit analog_mutex;
unsigned char current_buffer;
unsigned char current_channel;
short intervalTimer;
unsigned char analogState;
short analog_count;

void analog_init () {
	unsigned char i;
	analog_mutex = 0;
	current_channel = 0;
	intervalTimer = 0;
	analog_count = 0;
	
	TRISAbits.TRISA0 = 1; /*set as input port*/
	TRISAbits.TRISA1 = 1; /*set as input port*/
	ADCON1 = 0x0e; /*ref vtg is VDD and Configure pin as analog pin*/
	ADCON2 = 0b10001010; /*Right Justified, 2Tad and Fosc/32. */
	ADRESH = 0; /*Flush ADC output Register*/
	ADRESL = 0;

	for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
		for (current_buffer=0;current_buffer<2;current_buffer++) {
			analog_buffer[i][current_buffer] = 0;
		}
	}
	
	analogState = STATE_IDLE;
}

unsigned short analog_get (unsigned char channel) {
	unsigned short val;
	analog_mutex = 1;
	val = analog_values[channel];
	analog_mutex = 0;
	return val;
}

unsigned short analog_get_sync (unsigned char channel)
{
	short digital;
	ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100); // Select channel
	ADCON0 |= ((1<<ADON)|(1<<GO)); /*Enable ADC and start conversion*/
	while(ADCON0bits.GO_nDONE==1); /*wait for End of conversion i.e. Go/done'=0 conversion completed*/
	digital = (ADRESH << 9) | (ADRESL << 1); /*Combine 8-bit LSB and 2-bit MSB*/
	return(digital);
}

void analog_timer_interrupt_handler () {
	short tmp;

	if (analog_mutex) return; // wait until analog_values are free
	
	switch (analogState) {
		case STATE_IDLE:
		case STATE_START:
			if (current_channel == 0) {
				analog_count++;

				switch (current_buffer)
				{
					case 0: current_buffer = 1; break;
					case 1: current_buffer = 2; break;
					default: current_buffer = 0;
				}
			}

			current_channel = (current_channel+1) % TOTAL_ANALOG_CHANNELS;

			ADCON0 =(ADCON0 & 0b11000011)|((current_channel<<2) & 0b00111100);
			ADCON0 |= ((1<<ADON)|(1<<GO)); /*Enable ADC and start conversion*/
			analogState = STATE_CONV;
			break;
		case STATE_CONV:
			if (ADCON0bits.GO_nDONE==1) break;  // wait till GODONE bit is zero
			analogState = STATE_DONE;
			break;
		case STATE_DONE:
			if (analog_mutex == 1) break;
			tmp = (ADRESH << 9) | (ADRESL << 1);
			analog_values[current_channel] = (
				analog_buffer[current_channel][0] +
				analog_buffer[current_channel][1] +
				analog_buffer[current_channel][2] +
				tmp
			) / 4;
			analog_buffer[current_channel][current_buffer] = tmp;
			analogState = STATE_IDLE;
			break;
		default:
			analogState = STATE_IDLE;
	}		
}

