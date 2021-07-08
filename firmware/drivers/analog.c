#include <xc.h>
#include "analog-const.h"

#define BUFFER_SIZE 8
#define BUFFER_SIZE_DIV 3
#define BUFFER_SIZE_MASK 0x07

unsigned short analog_filter[TOTAL_ANALOG_CHANNELS];
unsigned short analog_buffer[TOTAL_ANALOG_CHANNELS][BUFFER_SIZE];
unsigned short analog_values[TOTAL_ANALOG_CHANNELS];
bit analog_mutex;
unsigned char current_channel;
unsigned char current_buffer;
short intervalTimer;
unsigned char analogState;
short analog_count;

void init_analog () {
	unsigned char i;
	unsigned char j;
	analog_mutex = 0;
	current_channel = 0;
	current_buffer = 0;
	intervalTimer = 0;
	analog_count = 0;
	
	TRISAbits.TRISA0 = 1; /*set as input port*/
	TRISAbits.TRISA1 = 1; /*set as input port*/
	TRISAbits.TRISA2 = 1; /*set as input port*/
	TRISAbits.TRISA3 = 1; /*set as input port*/
	ADCON1 = 0x0e; /*ref vtg is VDD and Configure pin as analog pin*/
	ADCON2 = 0b10001010; /*Right Justified, 2Tad and Fosc/32. */
	ADRESH = 0; /*Flush ADC output Register*/
	ADRESL = 0;

	for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
		analog_filter[i] = 0;
		for (j=0; j<BUFFER_SIZE; j++) {
			analog_buffer[i][j] = 0;
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
	ADCON0 |= ((1<<ADON)|(1<<GO)); // Enable ADC and start conversion
	while(ADCON0bits.GO_nDONE==1); // wait for End of conversion i.e. Go/done'=0 conversion completed
	digital = (ADRESH << 9) | (ADRESL << 1); // Treat analog value as 11 bit instead of 10.
	return(digital);
}

void analog_timer_interrupt_handler () {
	unsigned char i;
	short tmp;

	if (analog_mutex) return; // wait until analog_values are free
	
	switch (analogState) {
		case STATE_CONV:
			if (ADCON0bits.GO_nDONE==1) break;  // wait till GODONE bit is zero
			analogState = STATE_DONE;
			// no break
		case STATE_DONE:
			if (analog_mutex == 1) break;

			// Treat analog value as 11 bit instead of 10.
			// The low pass filter below will average the readings giving us extra resolution.
			tmp = (ADRESH << 9) | (ADRESL << 1);

			// Low pass filter from:
			// https://www.edn.com/a-simple-software-lowpass-filter-suits-embedded-system-applications/
			#define FILTER_SHIFT 4

			analog_filter[current_channel] =
				analog_filter[current_channel] -
				(analog_filter[current_channel] >> FILTER_SHIFT) +
				tmp;
			analog_buffer[current_channel][current_buffer] = analog_filter[current_channel] >> FILTER_SHIFT;

			tmp = 0;
			for (i=0;i<BUFFER_SIZE;i++) {
				tmp += analog_buffer[current_channel][i];
			}
			analog_values[current_channel] = tmp >> BUFFER_SIZE_DIV;

			analogState = STATE_IDLE;
			// no break
		case STATE_IDLE:
		case STATE_START:
			if (current_channel == 0) {
				analog_count++;
				current_buffer = (current_buffer + 1) & BUFFER_SIZE_MASK;
			}

			current_channel = (current_channel+1) % TOTAL_ANALOG_CHANNELS;

			ADCON0 =(ADCON0 & 0b11000011)|((current_channel<<2) & 0b00111100);
			ADCON0 |= ((1<<ADON)|(1<<GO)); /*Enable ADC and start conversion*/
			analogState = STATE_CONV;
			break;
		default:
			analogState = STATE_IDLE;
	}		
}

