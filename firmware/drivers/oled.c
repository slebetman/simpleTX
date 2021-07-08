#include <xc.h>
#include "oled.h"
#include "font.h"

void i2c_OLED_send (unsigned char cmdOrData, const unsigned char *data, unsigned char length)
{
	unsigned char i;

	i2c_start();
	i2c_write(OLED_ADDRESS | I2C_WRITE_CMD);
	i2c_write(cmdOrData);
	
	for (i=0; i<length; i++) {
		i2c_write(data[i]);
	}
	
	i2c_master_ack(I2C_DATA_NOACK);
	i2c_stop();
}

void i2c_OLED_send_cmd (unsigned char cmd) {
	unsigned char cmdPtr[1];
	
	cmdPtr[0] = cmd;
	i2c_OLED_send(OLED_COMMAND, cmdPtr, 1);
}

void i2c_OLED_send_data (const unsigned char *data, unsigned char length) {
	i2c_OLED_send(OLED_DATA, data, length);
}

void oled_init () {
	const unsigned char pageAddressingCmd[2] = {0x20, 0x02};

	i2c_OLED_send_cmd(0xAE); // Set display OFF

	i2c_OLED_send_cmd(0xD5); // Set Display Clock Divide Ratio / OSC Frequency
	i2c_OLED_send_cmd(0x80); // Display Clock Divide Ratio / OSC Frequency

	i2c_OLED_send_cmd(0xA8); // Set Multiplex Ratio
	i2c_OLED_send_cmd(0x3F); // Multiplex Ratio for 128x64 (64-1)

	i2c_OLED_send_cmd(0xD3); // Set Display Offset
	i2c_OLED_send_cmd(0x00); // Display Offset

	// i2c_OLED_send_cmd(0x40); // Set Display Start Line
	i2c_OLED_send_cmd(0x00); // Set Display Start Line

	i2c_OLED_send_cmd(0x8D); // Set Charge Pump
	i2c_OLED_send_cmd(0x14); // Charge Pump (0x10 External, 0x14 Internal DC/DC)

	i2c_OLED_send_cmd(0x20); // Set Memory Mode
	i2c_OLED_send_cmd(0x00); // Horizontal Addressing

	i2c_OLED_send_cmd(0xA1); // Set Segment Re-Map
	i2c_OLED_send_cmd(0xC8); // Set Com Output Scan Direction

	i2c_OLED_send_cmd(0xDA); // Set COM Hardware Configuration
	i2c_OLED_send_cmd(0x12);

	i2c_OLED_send_cmd(0x81); // Set Contrast
	i2c_OLED_send_cmd(0x8F); // Contrast

	i2c_OLED_send_cmd(0xD9); // Set Pre-Charge Period
	i2c_OLED_send_cmd(0xF1); // Set Pre-Charge Period (0x22 External, 0xF1 Internal)

	i2c_OLED_send_cmd(0xDB); // Set VCOMH Deselect Level
	i2c_OLED_send_cmd(0x40); // VCOMH Deselect Level

	i2c_OLED_send_cmd(0xA4); // Set all pixels OFF
	i2c_OLED_send_cmd(0xA6); // Set display not inverted
	i2c_OLED_send_cmd(0xAF); // Set display On
	
	i2c_OLED_send(OLED_COMMAND, pageAddressingCmd, 2); // set page addressing mode
}

void oled_goto (unsigned char x, unsigned char y) {
	i2c_OLED_send_cmd(x & 0x0f); // set x coordinates
	i2c_OLED_send_cmd(0x10 | ((x >> 4) & 0x0f) ); // set x coordinates
	i2c_OLED_send_cmd(0xb0 | y); // set y coordinates
}

void oled_clear () {
	unsigned char y;
	unsigned char x;
	const unsigned char blank[8] = {0,0,0,0,0,0,0,0};

	i2c_OLED_send_cmd(0x00); // set x coordinates
	i2c_OLED_send_cmd(0x10); // set x coordinates

	for (y=0;y<8;y++) {
		i2c_OLED_send_cmd(0xb0 | y);   // set y coordinates
		for (x=0;x<128;x+=8) {
			i2c_OLED_send_data(blank, 8);
		}
	}
}

void oled_blank (short length) {
	short i;

	i2c_start();
	i2c_write(OLED_ADDRESS | I2C_WRITE_CMD);
	i2c_write(OLED_DATA);
	
	for (i=0; i<length; i++) {
		i2c_write(0x00);
	}
	
	i2c_master_ack(I2C_DATA_NOACK);
	i2c_stop();
}

short oled_write_string (const char *str) {
	short pixels = 0;
	unsigned char buffer[128];
	
	pixels = string2pixels(str, buffer, 128);
	i2c_OLED_send_data(buffer, pixels);

	return pixels;
}

short oled_print_hex (short n) {
	short pixels = 0;
	const char* hexchars = "0123456789abcdef";
	char hexbuf[5];
	unsigned char buffer[4*6];
	
	hexbuf[0] = hexchars[(n >> 12) & 0x000f];
	hexbuf[1] = hexchars[(n >> 8) & 0x000f];
	hexbuf[2] = hexchars[(n >> 4) & 0x000f];
	hexbuf[3] = hexchars[n & 0x000f];
	hexbuf[4] = 0x00; // NUL terminator

	pixels = string2pixels(hexbuf, buffer, 4*6);
	i2c_OLED_send_data(buffer, pixels);

	return pixels;
}

short oled_print_signed_number (short n) {
	short pixels = 0;
	char m;
	char idx = 0;
	static bit started;
	const char* numbers = "0123456789";
	char numbuf[7] = {0,0,0,0,0,0,0};
	unsigned char buffer[6*6];

	started = 0;
	
	if (n < 0) {
		n = -n;
		numbuf[idx] = '-';
		idx++;
	}
	if (n >= 10000) {
		started = 1;
		m = n/10000;
		n = n%10000;
		numbuf[idx] = numbers[m];
		idx++;
	}
	if (n >= 1000 || started) {
		started = 1;
		m = n/1000;
		n = n%1000;
		numbuf[idx] = numbers[m];
		idx++;
	}
	if (n >= 100 || started) {
		started = 1;
		m = n/100;
		n = n%100;
		numbuf[idx] = numbers[m];
		idx++;
	}
	if (n >= 10 || started) {
		started = 1;
		m = n/10;
		n = n%10;
		numbuf[idx] = numbers[m];
		idx++;
	}
	numbuf[idx] = numbers[n];
	
	pixels = string2pixels(numbuf, buffer, 6*6);
	i2c_OLED_send_data(buffer, pixels);
	return pixels;
}

