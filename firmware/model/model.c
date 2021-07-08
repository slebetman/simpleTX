#include "model-const.h"
#include "../drivers/eeprom.h"
#include "channels.h"

struct model current_model;

unsigned char mixIsDisabled(unsigned char i) {
	if (current_model.mix[i].output >= USER_CHANNELS) {
		return 1;
	}
	else {
		return 0;
	}
}

void newModel () {
	unsigned char i;

	for (i=0; i<NAME_SIZE; i++) {
		current_model.name[i] = 0;
	}

	for (i=0; i<4; i++) {
		current_model.trim[i] = 0;
	}

	for (i=0; i<4; i++) {
		current_model.scale[i] = 100;
	}

	for (i=0; i<TOTAL_OUTPUT_CHANNELS; i++) {
		current_model.output_map[i] = 0;
	}
	
	for (i=0; i<MAX_MIXES; i++) {
		current_model.mix[i].input = 0;
		current_model.mix[i].output = 0x0f; // disabled
		
		current_model.mix[i].scale = 100;
		current_model.mix[i].expo = 0;
		
		current_model.mix[i].reverse = 0;
	}
}

void parseModelFromEeprom (unsigned char *eeprom_data) {
	unsigned char i;
	unsigned char raw_mix;
	unsigned char raw_scaling;
	unsigned char expo;
	unsigned char raw_map;
	
	for (i=0; i<NAME_SIZE; i++) {
		current_model.name[i] = eeprom_data[NAME_OFFSET + i];
	}
	
	for (i=0; i<4; i++) {
		current_model.trim[i] = (char)(eeprom_data[TRIM_OFFSET + i] * 4);
	}

	for (i=0; i<4; i++) {
		current_model.scale[i] = eeprom_data[SCALE_OFFSET + i];
	}

	for (i=0; i<(TOTAL_OUTPUT_CHANNELS/2); i++) {
		raw_map = eeprom_data[OUTPUT_MAP_OFFSET + i];
		current_model.output_map[i*2] = (raw_map & 0xf0) >> 4;
		current_model.output_map[(i*2) + 1] = raw_map & 0x0f;
	}
	
	for (i=0; i<MAX_MIXES; i++) {
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
		eeprom_data[TRIM_OFFSET + i] = (char)(current_model.trim[i] / 4); // sacrifice last two bits to get +512/-512
	}
}

void formatModelToEeprom (unsigned char *eeprom_data) {
	unsigned char i;
	unsigned char raw_mix = 0;
	unsigned char raw_scaling = 0;
	
	for (i=0; i<NAME_SIZE; i++) {
		eeprom_data[NAME_OFFSET + i] = current_model.name[i];
	}
	
	formatTrimToEeprom(eeprom_data);

	for (i=0; i<4; i++) {
		eeprom_data[SCALE_OFFSET + i] = current_model.scale[i];
	}

	for (i=0; i<(TOTAL_OUTPUT_CHANNELS/2); i++) {
		eeprom_data[OUTPUT_MAP_OFFSET + i] =
			((current_model.output_map[i*2] << 4) & 0xf0) |
			(current_model.output_map[(i*2) + 1] & 0x0f);
	}
	
	for (i=0; i<MAX_MIXES; i++) {
		raw_mix = ((current_model.mix[i].input & 0x0f) << 4) | (current_model.mix[i].output & 0x0f);
		
		raw_scaling = (current_model.mix[i].scale & 0x7f) | (current_model.mix[i].reverse << 7);
	
		eeprom_data[MIX_OFFSET + (i*3)] = raw_mix;
		eeprom_data[MIX_OFFSET + (i*3) + 1] = raw_scaling;
		eeprom_data[MIX_OFFSET + (i*3) + 2] = current_model.mix[i].expo;
	}
}

void loadModel (unsigned char model_id) {
	short eeprom_offset;
	unsigned char eeprom_buffer[MODEL_SIZE];

	eeprom_offset = MODEL_SIZE * model_id;

	for (short i = 0; i < MODEL_SIZE; i++) {
		eeprom_buffer[i] = readEeprom(eeprom_offset+i);
	}

	parseModelFromEeprom(eeprom_buffer);

	if (current_model.name[0] > '~' || current_model.name[0] < ' ') {
		// Invalid name, assume uninitialized:
		newModel();
	}
}

void saveModel (unsigned char model_id) {
	short eeprom_offset;
	unsigned char eeprom_buffer[MODEL_SIZE];

	eeprom_offset = MODEL_SIZE * model_id;

	formatModelToEeprom(eeprom_buffer);

	for (short i = 0; i < MODEL_SIZE; i++) {
		writeEeprom(eeprom_offset+i, eeprom_buffer[i]);
	}
}

void saveTrim (unsigned char model_id) {
	short eeprom_offset;
	unsigned char eeprom_buffer[MODEL_SIZE];

	eeprom_offset = MODEL_SIZE * model_id;

	formatTrimToEeprom(eeprom_buffer);

	for (short i = TRIM_OFFSET; i < SCALE_OFFSET; i++) {
		writeEeprom(eeprom_offset+i, eeprom_buffer[i]);
	}
}
