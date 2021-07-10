#include "../drivers/oled.h"
#include "../drivers/button.h"
#include "inputScalingPage.h"
#include "nameEditPage.h"
#include "outputMappingPage.h"
#include "gui.h"

#define MODEL_NAME     0
#define INPUT_SCALING  1
#define OUTPUT_MAP     2
#define MIXING         3

// View:
void loadModelEditPage () {
	selection = 0;

	oled_clear();
	oled_goto(0,0);
	oled_write_string("Edit Model:");

	oled_goto(8,2);
	oled_write_string("Model name");
	oled_goto(8,3);
	oled_write_string("Input scaling");
	oled_goto(8,4);
	oled_write_string("Output map");
	oled_goto(8,5);
	oled_write_string("Mixing");
}

void updateModelEditPage () {
	updateSelection(4);
}

// Controller:
unsigned char handleModelEditPage () {
	handleSelection(4);

	if (button_long_press(button2)) {
		switch (selection) {
			case MODEL_NAME:
				loadNameEditPage();
				return NAME_EDIT_PAGE;
			case INPUT_SCALING:
				loadInputScalingPage();
				return INPUT_SCALING_PAGE;
			case OUTPUT_MAP:
				loadOutputMappingPage();
				return OUTPUT_MAP_PAGE;
			case MIXING:
				break;
		}
	}
	if (button_long_press(button1)) {
		loadHomePage();
		return HOME_PAGE;
	}

	return MODEL_EDIT_PAGE;
}
