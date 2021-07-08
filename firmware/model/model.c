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

void getModelName (unsigned char model_id, unsigned char *name) {
	short eeprom_offset;

	eeprom_offset = MODEL_SIZE * model_id;

	for (short i = 0; i < NAME_SIZE; i++) {
		name[i] = readEeprom(eeprom_offset+i);
	}
}

void loadModel (unsigned char model_id) {
	short eeprom_offset;	unsigned char i;
	unsigned char raw_mix;
	unsigned char raw_scaling;
	unsigned char expo;
	unsigned char raw_map;

	eeprom_offset = MODEL_SIZE * model_id;

	current_model.id = model_id;

	getModelName(model_id, current_model.name);

	if (current_model.name[0] > '~' || current_model.name[0] < ' ') {
		// Invalid name, assume uninitialized:
		newModel();
	}
	else {
		for (i=0; i<4; i++) {
			current_model.trim[i] = (char)(readEeprom(eeprom_offset+TRIM_OFFSET + i) * 4);
		}

		for (i=0; i<4; i++) {
			current_model.scale[i] = readEeprom(eeprom_offset + SCALE_OFFSET + i);
		}

		for (i=0; i<(TOTAL_OUTPUT_CHANNELS/2); i++) {
			raw_map = readEeprom(eeprom_offset + OUTPUT_MAP_OFFSET + i);
			current_model.output_map[i*2] = (raw_map & 0xf0) >> 4;
			current_model.output_map[(i*2) + 1] = raw_map & 0x0f;
		}
		
		for (i=0; i<MAX_MIXES; i++) {
			raw_mix = readEeprom(eeprom_offset + MIX_OFFSET + (i*3));
			raw_scaling = readEeprom(eeprom_offset + MIX_OFFSET + (i*3) + 1);
			expo = readEeprom(eeprom_offset + MIX_OFFSET + (i*3) + 2);
			
			current_model.mix[i].input = (raw_mix >> 4) & 0x0f;
			current_model.mix[i].output = raw_mix & 0x0f;
			
			current_model.mix[i].scale = raw_scaling & (~REVERSE_MASK);
			current_model.mix[i].expo = expo;
			
			current_model.mix[i].reverse = (raw_scaling & REVERSE_MASK) >> 7;
		}
	}
}

void saveTrim (unsigned char model_id) {
	short eeprom_offset;
	unsigned char i;

	eeprom_offset = MODEL_SIZE * model_id;

	
	for (i=0; i<4; i++) {
		writeEeprom(eeprom_offset + TRIM_OFFSET + i, (char)(current_model.trim[i] / 4)); // sacrifice last two bits to get +512/-512
	}
}

void saveModel (unsigned char model_id) {
	short eeprom_offset;
	unsigned char i;
	unsigned char raw_mix = 0;
	unsigned char raw_scaling = 0;
	
	eeprom_offset = MODEL_SIZE * model_id;
	
	for (i=0; i<NAME_SIZE; i++) {
		writeEeprom(eeprom_offset + NAME_OFFSET + i, current_model.name[i]);
	}
	
	saveTrim(model_id);

	for (i=0; i<4; i++) {
		writeEeprom(eeprom_offset + SCALE_OFFSET + i, current_model.scale[i]);
	}

	for (i=0; i<(TOTAL_OUTPUT_CHANNELS/2); i++) {
		writeEeprom(eeprom_offset + OUTPUT_MAP_OFFSET + i, (
			((current_model.output_map[i*2] << 4) & 0xf0) |
			(current_model.output_map[(i*2) + 1] & 0x0f)
		));
	}
	
	for (i=0; i<MAX_MIXES; i++) {
		raw_mix = ((current_model.mix[i].input & 0x0f) << 4) | (current_model.mix[i].output & 0x0f);
		
		raw_scaling = (current_model.mix[i].scale & 0x7f) | (current_model.mix[i].reverse << 7);
	
		writeEeprom(eeprom_offset + MIX_OFFSET + (i*3), raw_mix);
		writeEeprom(eeprom_offset + MIX_OFFSET + (i*3) + 1, raw_scaling);
		writeEeprom(eeprom_offset + MIX_OFFSET + (i*3) + 2, current_model.mix[i].expo);
	}
}

