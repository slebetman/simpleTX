#include <pic.h>
#include <htc.h>
#include "common.h"
#include "ppmio.h"

bit trim_mode;
int output_trim[TOTAL_OUTPUT_CHANNELS];
int stick_center[TOTAL_OUTPUT_CHANNELS];

void initTrim (void) {
	unsigned char i;
	int temp;
	
	trim_mode = 0;
	
	for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
		temp = eeprom_read(i*2);
		temp |= (int)eeprom_read(i*2+1) << 8;
		output_trim[i] = temp;
	}
}

#define NO_EXCEPTIONS -1
void trimMode (signed char exception) {
	unsigned char i;

	if (!trim_mode) {
		trim_mode = 1;
		for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
			stick_center[i] = output_pulse[i];
		}
	}
	
	// Left switch clears trim values:
	if (DIGITAL2) {
		for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
			output_trim[i] = 0;
		}
	}
	else {
		for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
			if (i != exception) {
	
				if (output_pulse[i]-stick_center[i] > 200) output_trim[i] += 5;
				if (output_pulse[i]-stick_center[i] > 1000) output_trim[i] += 20;
				if (output_pulse[i]-stick_center[i] < -200) output_trim[i] -= 5;
				if (output_pulse[i]-stick_center[i] < -1000) output_trim[i] -= 20;
		
				output_pulse[i] = stick_center[i];
			}
		}
	}
}

bit saveTrim (void) {
	unsigned char i;
	int temp;

	if (trim_mode) {
		disableInterrupts();
		trim_mode = 0;
	
		for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
			temp = output_trim[i] & 0x00ff;
			eeprom_write(i*2,(unsigned char)temp);
			temp = output_trim[i] >> 8;
			eeprom_write(i*2+1,(unsigned char)temp);
		}
		enableInterrupts();
		return 1;
	}
	return 0;
}
