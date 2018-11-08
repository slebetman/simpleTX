#include "model.h"

struct model current_model;

#define NAME_OFFSET 0
#define TRIM_OFFSET 10
#define MIX_OFFSET  14

#define SCALE_POLARITY_MASK 0x02
#define EXPO_POLARITY_MASK  0x01

void loadModel (char *eeprom_data) {
	unsigned char i;
	unsigned char raw_mix;
	unsigned char raw_scaling;
	
	for (i=0; i<10; i++) {
		current_model.name[i] = eeprom_data[NAME_OFFSET + i];
	}
	
	for (i=0; i<4; i++) {
		current_model.trim[i] = eeprom_data[TRIM_OFFSET + i];
	}
	
	for (i=0; i<8; i++) {
		raw_mix = eeprom_data[NAME_OFFSET + (i*2)];
		raw_scaling = eeprom_data[NAME_OFFSET + (i*2) + 1];
		
		current_model.mix[i].input = (raw_mix >> 5) & 0x07;
		current_model.mix[i].output = (raw_mix >> 2) & 0x07;
		
		current_model.mix[i].scale = ((raw_scaling >> 4) & 0x0f) * 10;
		current_model.mix[i].expo = (raw_scaling & 0x0f) * 10;
		
		if (raw_mix & SCALE_POLARITY_MASK) {
			current_model.mix[i].scale *= -1;
		}
		if (raw_mix & EXPO_POLARITY_MASK) {
			current_model.mix[i].expo *= -1;
		}
	}
}

void formatModelToEeprom (char *eeprom_data) {
	unsigned char i;
	unsigned char raw_mix = 0;
	unsigned char raw_scaling = 0;
	
	for (i=0; i<10; i++) {
		eeprom_data[NAME_OFFSET + i] = current_model.name[i];
	}
	
	for (i=0; i<4; i++) {
		eeprom_data[TRIM_OFFSET + i] = current_model.trim[i];
	}
	
	for (i=0; i<8; i++) {
		raw_mix |= (current_model.mix[i].input << 5);
		raw_mix |= (current_model.mix[i].output << 2);
		if (current_model.mix[i].scale < 0) {
			raw_mix |= 0x02;
		}
		if (current_model.mix[i].expo < 0) {
			raw_mix |= 0x01;
		}
		
		raw_scaling |= (current_model.mix[i].expo / 10);
		raw_scaling |= ((current_model.mix[i].scale / 10) << 4);
	
		eeprom_data[NAME_OFFSET + (i*2)] = raw_mix;
		eeprom_data[NAME_OFFSET + (i*2) + 1] = raw_scaling;
	}
}
