#include "model-const.h"
#include "eeprom.h"

struct model current_model;

void parseModelFromEeprom (unsigned char *eeprom_data) {
	unsigned char i;
	unsigned char raw_mix;
	unsigned char raw_scaling;
	unsigned char expo;
	unsigned char raw_map;
	
	for (i=0; i<10; i++) {
		current_model.name[i] = eeprom_data[NAME_OFFSET + i];
	}
	
	for (i=0; i<4; i++) {
		current_model.trim[i] = eeprom_data[TRIM_OFFSET + i];
	}

	for (i=0; i<4; i++) {
		current_model.scale[i] = eeprom_data[SCALE_OFFSET + i];
	}

	for (i=0; i<4; i++) {
		raw_map = eeprom_data[OUTPUT_MAP_OFFSET + i];
		current_model.output_map[i*2] = (raw_map & 0xf0) >> 4;
		current_model.output_map[(i*2) + 1] = raw_map & 0x0f;
	}
	
	for (i=0; i<8; i++) {
		raw_mix = eeprom_data[MIX_OFFSET + (i*3)];
		raw_scaling = eeprom_data[MIX_OFFSET + (i*3) + 1];
		expo = eeprom_data[MIX_OFFSET + (i*3) + 2];
		
		current_model.mix[i].input = (raw_mix >> 4) & 0x0f;
		current_model.mix[i].output = raw_mix & 0x0f;
		
		current_model.mix[i].scale = raw_scaling & (~REVERSE_MASK);
		current_model.mix[i].expo = expo;
		
		current_model.mix[i].reverse = (raw_scaling & REVERSE_MASK) >> 7;
	}
}

void formatTrimToEeprom (unsigned char *eeprom_data) {
	unsigned char i;
	
	for (i=0; i<4; i++) {
		eeprom_data[TRIM_OFFSET + i] = current_model.trim[i];
	}
}

void formatModelToEeprom (unsigned char *eeprom_data) {
	unsigned char i;
	unsigned char raw_mix = 0;
	unsigned char raw_scaling = 0;
	
	for (i=0; i<10; i++) {
		eeprom_data[NAME_OFFSET + i] = current_model.name[i];
	}
	
	formatTrimToEeprom(eeprom_data);

	for (i=0; i<4; i++) {
		eeprom_data[SCALE_OFFSET + i] = current_model.scale[i];
	}

	for (i=0; i<4; i++) {
		eeprom_data[OUTPUT_MAP_OFFSET + i] =
			((current_model.output_map[i*2] << 4) & 0xf0) |
			(current_model.output_map[(i*2) + 1] & 0x0f);
	}
	
	for (i=0; i<8; i++) {
		raw_mix = ((current_model.mix[i].input & 0x0f) << 4) | (current_model.mix[i].output & 0x0f);
		
		raw_scaling = (current_model.mix[i].scale & 0x7f) | (current_model.mix[i].reverse << 7);
	
		eeprom_data[MIX_OFFSET + (i*3)] = raw_mix;
		eeprom_data[MIX_OFFSET + (i*3) + 1] = raw_scaling;
		eeprom_data[MIX_OFFSET + (i*3) + 2] = current_model.mix[i].expo;
	}
}

void loadModel (unsigned char model_id) {
	int eeprom_offset;
	unsigned char eeprom_buffer[MODEL_SIZE];

	eeprom_offset = MODEL_SIZE * model_id;

	for (int i = 0; i < MODEL_SIZE; i++) {
		eeprom_buffer[i] = readEeprom(eeprom_offset+i);
	}

	parseModelFromEeprom(eeprom_buffer);
}

void saveModel (unsigned char model_id) {
	int eeprom_offset;
	unsigned char eeprom_buffer[MODEL_SIZE];

	eeprom_offset = MODEL_SIZE * model_id;

	formatModelToEeprom(eeprom_buffer);

	for (int i = 0; i < MODEL_SIZE; i++) {
		writeEeprom(eeprom_offset+i, eeprom_buffer[i]);
	}
}

void saveTrim (unsigned char model_id) {
	int eeprom_offset;
	unsigned char eeprom_buffer[MODEL_SIZE];

	eeprom_offset = MODEL_SIZE * model_id;

	formatTrimToEeprom(eeprom_buffer);

	for (int i = TRIM_OFFSET; i < SCALE_OFFSET; i++) {
		writeEeprom(eeprom_offset+i, eeprom_buffer[i]);
	}
}
