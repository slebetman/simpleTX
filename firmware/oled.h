#include <xc.h>
#include "i2c.h"

#define OLED_ADDRESS 0x78
// #define OLED_ADDRESS 0x3c
// #define OLED_ADDRESS 0x3d
#define OLED_COMMAND 0x00
#define OLED_DATA    0x40
#define oled_send i2c_OLED_send_data

extern void i2c_OLED_send (
	unsigned char cmdOrData, const unsigned char *data, unsigned char length
);
extern void i2c_OLED_send_cmd (unsigned char cmd);
extern void i2c_OLED_send_data (const unsigned char *data, unsigned char length);
extern void oled_init ();
extern void oled_goto (unsigned char x, unsigned char y);
extern void oled_clear ();
extern void oled_write_string (const char *str);
extern void oled_print_signed_number (int);
extern void oled_print_hex (int);
