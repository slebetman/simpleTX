#include "../common.h"
#include "../drivers/analog.h"
#include "../drivers/button.h"
#include "../drivers/oled.h"
#include "../drivers/eeprom.h"
#include "../model/channels.h"
#include "../model/mixer.h"
#include "../model/model.h"
#include "gui-const.h"
#include "splashScreen.h"
#include "channelsPage.h"
#include "modelSelectPage.h"
#include "modelEditPage.h"
#include "inputScalingPage.h"
#include "nameEditPage.h"
#include "mixesPage.h"
#include "mixEditPage.h"

unsigned char guiTracker;
short guiCount;

button btn1;
button btn2;
button btn3;

button *button1 = &btn1;
button *button2 = &btn2;
button *button3 = &btn3;

signed char modelID;
signed char selection;
unsigned char guiState;

void initGUI () {
	guiTracker = tick;
	guiCount = 0;
	guiState = CHANNELS_PAGE;
	oled_clear();
	oled_init();

	button_init(button1,1);
	button_init(button2,2);
	button_init(button3,3);

	loadSplashScreen();

	getModelFromEeprom(SAVED_MODEL);
	modelID = current_model.id;
}

void handleSelection (unsigned char totalOptions) {
	if (button_click(button1)) {
		selection--;
		if (selection < 0) {
			selection = totalOptions-1;
		}
	}
	if (button_click(button2)) {
		selection++;
		if (selection >= totalOptions) {
			selection = 0;
		}
	}
}

void updateSelection (unsigned char totalOptions) {
	for (unsigned char i=0; i<totalOptions; i++) {
		oled_goto(0,i+2);
		if (i == selection) {
			oled_write_string(ARROW);
		}
		else {
			oled_blank(6);
		}
	}
}

void loadHomePage () {
	loadChannelsPage();
}

unsigned char updateGUI () {
	short tmp;
	short xCursor;

	if (guiTracker !=  tick) {
		guiCount += (tick-guiTracker) & 0xff;
		guiTracker = tick;

		if (guiCount >= 1000) { // update every second
			guiCount -= 1000;
			tmp = analog_count;
			analog_count = 0;

			if (guiState == CHANNELS_PAGE) {
				oled_goto(0,7);
				oled_write_string("Samples/s: ");
				xCursor = oled_print_signed_number(tmp);
				oled_blank((5*6)-xCursor);
			}
		}

		// View:
		if (guiCount%50 == 25) {
			switch (guiState) {
				case CHANNELS_PAGE:
					updateChannelsPage();
					break;
				case MODEL_SELECT_PAGE:
					updateModelSelectPage();
					break;
				case MODEL_EDIT_PAGE:
					updateModelEditPage();
					break;
				case INPUT_SCALING_PAGE:
					updateInputScalingPage();
					break;
				case NAME_EDIT_PAGE:
					updateNameEditPage();
					break;
				case MIXES_PAGE:
					updateMixesPage();
					break;
				case MIX_EDIT_PAGE:
					updateMixEditPage();
					break;
			}
		}

		// Controller:
		switch (guiState) {
			case CHANNELS_PAGE:
				guiState = handleChannelsPage();
				break;
			case MODEL_SELECT_PAGE:
				guiState = handleModelSelectPage();
				break;
			case MODEL_EDIT_PAGE:
				guiState = handleModelEditPage();
				break;
			case INPUT_SCALING_PAGE:
				guiState = handleInputScalingPage();
				break;
			case NAME_EDIT_PAGE:
				guiState = handleNameEditPage();
				break;
			case MIXES_PAGE:
				guiState = handleMixesPage();
				break;
			case MIX_EDIT_PAGE:
				guiState = handleMixEditPage();
				break;
			default:
				guiState = CHANNELS_PAGE;
		}

		return 1;
	}

	return 0;
}