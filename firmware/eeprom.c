#include <xc.h>

unsigned char readEeprom (unsigned int address) {
	EEADR = (address & 0x0ff);
	EECON1bits.CFGS = 0;
	EECON1bits.EEPGD = 0;
	EECON1bits.RD = 1;
	return (EEDATA);  // return with read byte
}

void writeEeprom (unsigned int address, unsigned char data) {
	EEADR = (address & 0x0ff);
	EEDATA = data;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1;
	INTCONbits.GIE = 0;
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	while(EECON1bits.WR);
	INTCONbits.GIE = 1;
	EECON1bits.WREN = 0;
}