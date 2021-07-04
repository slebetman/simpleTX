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

unsigned char tick; // timer tick (roughly 1ms using 24 MHz XTAL)
unsigned char frameTimer;

void main(void)
{
	initCpuClock();

	init();
	// initTrim();
	initGUI();

	newModel();

	current_model.name[0] = 'T';
	current_model.name[1] = 'e';
	current_model.name[2] = 's';
	current_model.name[3] = 't';

	// Elevon mix
	current_model.mix[0].input = USER_CHANNELS+0;
	current_model.mix[0].output = 0;
	current_model.mix[0].scale = 100;
	current_model.mix[0].expo = 0;
	current_model.mix[0].reverse = 0;
	current_model.mix[1].input = USER_CHANNELS+1;
	current_model.mix[1].output = 0;
	current_model.mix[1].scale = 100;
	current_model.mix[1].expo = 0;
	current_model.mix[1].reverse = 0;
	current_model.mix[2].input = USER_CHANNELS+0;
	current_model.mix[2].output = 1;
	current_model.mix[2].scale = 100;
	current_model.mix[2].expo = 0;
	current_model.mix[2].reverse = 1;
	current_model.mix[3].input = USER_CHANNELS+1;
	current_model.mix[3].output = 1;
	current_model.mix[3].scale = 100;
	current_model.mix[3].expo = 0;
	current_model.mix[3].reverse = 0;
	// Normal mix
	current_model.mix[4].input = USER_CHANNELS+0;
	current_model.mix[4].output = 2;
	current_model.mix[4].scale = 100;
	current_model.mix[4].expo = 0;
	current_model.mix[4].reverse = 0;
	current_model.mix[5].input = USER_CHANNELS+1;
	current_model.mix[5].output = 3;
	current_model.mix[5].scale = 100;
	current_model.mix[5].expo = 0;
	current_model.mix[5].reverse = 0;

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
