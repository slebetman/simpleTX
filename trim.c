#include <pic.h>
#include <htc.h>
#include "common.h"
#include "ppmio.h"

#define TOTAL_TRIM_SLOTS 10

bit trim_mode;
bit safeguard;
int output_trim[TOTAL_OUTPUT_CHANNELS];
int stick_center[TOTAL_OUTPUT_CHANNELS];
char trim_slot;
char trim_offset[TOTAL_TRIM_SLOTS] = {
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*0,
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*1,
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*2,
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*3,
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*4,
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*5,
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*6,
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*7,
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*8,
	TOTAL_OUTPUT_CHANNELS*sizeof(int)*9
};

void readTrim () {
	unsigned char i;
	int temp;
	
	for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
		temp = eeprom_read(i*2+trim_offset[trim_slot]);
		temp |= (int)eeprom_read(i*2+trim_offset[trim_slot]+1) << 8;
		output_trim[i] = temp;
	}
}

void setTrimSlot (char slot) {
	if (trim_slot != slot) {
		trim_slot =	 slot;
		readTrim();
	}
}

void initTrim () {
	trim_mode = 0;
	trim_slot = 0;
	safeguard = 0;
	readTrim();
}

#define NO_EXCEPTIONS -1
void trim (unsigned char on_switch, signed char exception) {
	unsigned char i;
	int temp;

	if (on_switch) {
		if (!trim_mode) {
			trim_mode = 1;
			for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
				stick_center[i] = output_pulse[i];
			}
		}
	
		// Left switch clears trim values:
		if (DIGITAL2 && safeguard) {
			for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
				output_trim[i] = 0;
			}
		}
		else {
			safeguard = 1;
			for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
				if (i != exception) {
	
					if (output_pulse[i]-stick_center[i] > 150) output_trim[i] += 1;
					if (output_pulse[i]-stick_center[i] > 600) output_trim[i] += 15;
					if (output_pulse[i]-stick_center[i] < -150) output_trim[i] -= 1;
					if (output_pulse[i]-stick_center[i] < -600) output_trim[i] -= 15;
		
					output_pulse[i] = stick_center[i];
				}
			}
		}
	}
	else if (trim_mode) {
		disableInterrupts();
		trim_mode = 0;
		safeguard = 0;
	
		for (i=0; i<TOTAL_OUTPUT_CHANNELS;i++) {
			temp = output_trim[i] & 0x00ff;
			eeprom_write(i*2+trim_offset[trim_slot],(unsigned char)temp);
			temp = output_trim[i] >> 8;
			eeprom_write(i*2+trim_offset[trim_slot]+1,(unsigned char)temp);
		}
		enableInterrupts();
		
		in_sync = 0;
	}
}
