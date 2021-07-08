/* Assumes PIC18F2520 running at 32MHz */

#define _XTAL_FREQ 32000000

#include "hardware/config.h"

#include <xc.h>
// #include <stdlib.h>
#include "drivers/button.h"
#include "common.h"
#include "hardware/cpuclock.h"
#include "drivers/oled.h"
#include "drivers/ppmio.h"
#include "drivers/eeprom.h"
#include "model/trim.h"
#include "model/channels.h"
#include "model/model.h"
#include "model/mixer.h"
#include "ui/gui.h"
#include "init.h"

unsigned char tick; // timer tick (roughly 1ms)
unsigned char frameTimer;

void main(void)
{
	initCpuClock();

	init();
	// initTrim();
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
