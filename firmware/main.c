/* Assumes PIC18F2520 running at 32MHz */

#define _XTAL_FREQ 32000000

#include "config.h"

#include <xc.h>
// #include <stdlib.h>
#include "button.h"
#include "common.h"
#include "cpuclock.h"
#include "ppmio.h"
#include "trim.h"
#include "init.h"
#include "oled.h"
#include "channels.h"
#include "model.h"
#include "gui.h"
#include "mixer.h"
#include "eeprom.h"

unsigned char tick; // timer tick (roughly 1ms)
unsigned char frameTimer;

button btn1;
button btn2;
button btn3;

button *button1 = &btn1;
button *button2 = &btn2;
button *button3 = &btn3;

#define SAVED_MODEL 0xff
unsigned char getModelFromEeprom (unsigned char id) {
	if (id == SAVED_MODEL) {
		id = readEeprom(0xff);
		if (id >= MAX_MODELS) {
			id = 0;
		}
	} else {
		if (id >= MAX_MODELS) {
			id = 0;
		}
		writeEeprom(0xff, id);
	}

	loadModel(id);
	loadChannelsPage(id);

	return id;
}

void main(void)
{
	short modelID;
	unsigned char tickTracker;
	tickTracker = tick;

	initCpuClock();

	button_init(button1,1);
	button_init(button2,2);
	button_init(button3,3);

	init();
	// initTrim();
	initGUI();

	modelID = getModelFromEeprom(SAVED_MODEL);

	while(1)
	{
		// if (frameTimer > 20) {
		// 	frameTimer = 0;

		// 	output_pulse[CHANNEL1] = 0;
		// 	output_pulse[CHANNEL2] = 0;
		// 	output_pulse[CHANNEL3] = 0;
			
		// 	trim(TRIM_SWITCH, NO_EXCEPTIONS);
			
		// 	startPPM(10, BEGIN);
		// }

		
		if (startMixer()) continue;

		if (updateGUI()) continue;

		processMixer();

		if (tickTracker != tick) {
			tickTracker = tick;
			if (button_click(button1)) {
				modelID--;
				if (modelID < 0) {
					modelID = MAX_MODELS-1;
				}
				getModelFromEeprom(modelID);
			}
			if (button_click(button2)) {
				modelID++;
				if (modelID >= MAX_MODELS) {
					modelID = 0;
				}
				getModelFromEeprom(modelID);
			}
		}
	}
}
