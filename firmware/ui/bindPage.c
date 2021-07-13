#include "../common.h"
#include "../hardware/pinout.h"
#include "../drivers/oled.h"
#include "modelEditPage.h"
#include "gui.h"

#define WAIT     0
#define INIT     1
#define BINDING  2
#define STOP     3
#define END      4

unsigned char bindTimer;
unsigned char bindState;

void drawBindSplash () {
	oled_clear();
	oled_goto(15,4);
	oled_write_string("Reconfiguring TX");
}

void drawBar (unsigned char value) {
	unsigned char barLength = value*6;

	oled_goto(3,5);
	i2c_OLED_send_data("\xfc",1);
	oled_bar(0xd4,0xac, barLength);
	oled_bar(0x84,0x84, 120-barLength);
	i2c_OLED_send_data("\xfc",1);
}

void loadBindPage () {
	bindTimer = 0;
	bindState = WAIT;

	TX_POWER_OFF;

	oled_clear();
	oled_goto(36,3);
	oled_write_string("TX is off");
	oled_goto(15,5);
	oled_write_string("Click any button");
	oled_goto(39,6);
	oled_write_string("to start");
}

void updateBindPage () { // runs at 20Hz
	switch (bindState) {
		case WAIT:
			break;
		case INIT:
			if (bindTimer > 20) { // one second
				bindTimer = 0;
				bindState = BINDING;
				TX_POWER_ON;

				oled_clear();
				oled_goto(36,3);
				oled_write_string("BIND MODE");
				oled_goto(15,5);
				oled_write_string("Click any button");
				oled_goto(42,6);
				oled_write_string("to stop");
			}
			else {
				bindTimer++;
				drawBar(bindTimer);
			}
			break;
		case BINDING:
			break;
		case STOP:
			if (bindTimer > 20) { // one second
				bindTimer = 0;
				bindState = END;
				TX_POWER_ON;
			}
			else {
				bindTimer++;
				drawBar(bindTimer);
			}
			break;
	}
}

unsigned char handleBindPage () {
	switch (bindState) {
		case WAIT:
			if (button_click(button1) || button_click(button2)) {
				bindTimer = 0;
				bindState = INIT;
				TX_POWER_OFF;
				TX_BIND_ENABLED;
				drawBindSplash();
			}
			break;
		case BINDING:
			if (button_click(button1) || button_click(button2)) {
				bindTimer = 0;
				bindState = STOP;
				TX_POWER_OFF;
				TX_BIND_DISABLED;
				drawBindSplash();
			}
			break;
		case END:
			loadModelEditPage(0);
			return MODEL_EDIT_PAGE;
	}

	return BIND_PAGE;
}
