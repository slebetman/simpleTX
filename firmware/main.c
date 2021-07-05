/* Assumes PIC18F2520 running at 32MHz */

#define _XTAL_FREQ 32000000

#include "config.h"

#include <xc.h>
// #include <stdlib.h>
#include "common.h"
#include "cpuclock.h"
#include "ppmio.h"
#include "calculations.h"
#include "trim.h"
#include "init.h"
#include "oled.h"
#include "analog.h"
#include "channels.h"
#include "joystick.h"
#include "model.h"
#include "gui.h"
#include "mixer.h"
#include "eeprom.h"

unsigned char tick; // timer tick (roughly 1ms using 24 MHz XTAL)
unsigned char frameTimer;

void main(void)
{
	unsigned char modelID;

	initCpuClock();

	init();
	// initTrim();
	modelID = readEeprom(0xff);
	if (modelID >= MAX_MODELS) {
		modelID = 0;
	}
	loadModel(modelID);

	if (current_model.name[0] > '~' || current_model.name[0] < ' ') {
		// Invalid name, assume uninitialized:
		newModel();
	}

	initGUI();

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
	}
}
