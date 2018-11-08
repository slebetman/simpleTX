#include <xc.h>
#include "i2c.h"

#define STATE_START    0x01
#define STATE_RESTART  0x02
#define STATE_TRANSMIT 0x04
#define STATE_STOP     0x08
#define STATE_ACK      0x10

unsigned char stateFlag;

void i2c_init(void) {
	stateFlag = 0;

	// Set SDA and SCL  as Input
	TRISCbits.TRISC3 = 1;
	TRISCbits.TRISC4 = 1;	

	// Initial the PIC18F14K22 MSSP Peripheral I2C Master Mode
	// I2C Master Clock Speed: 16000000 / ((4 * (SSPADD + 1)) = 16000000 / (4 * (39 + 1))
	SSPSTAT = 0x80;   // Slew Rate is disable for 100 kHz mode
	SSPCON1 = 0x28;   // Enable SDA and SCL, I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
	SSPCON2 = 0x00;   // Reset MSSP Control Register
	SSPADD = 39;      // Standard I2C Clock speed: 100 kHz	

	PIR1bits.SSPIF=0; // Clear MSSP Interrupt Flag
}

void i2c_idle ()
{
	// Wait I2C Bus and Status Idle (i.e. ACKEN, RCEN, PEN, RSEN, SEN)
	while (( SSPCON2 & 0x1F ) || ( SSPSTATbits.R_nW));
}

void i2c_start ()
{
	i2c_idle(); // Ensure the I2C module is idle
	SSPCON2bits.SEN = 1; // Start I2C Transmission
	while(SSPCON2bits.SEN);
}

void i2c_restart ()
{
	i2c_idle(); // Ensure the I2C module is idle
	SSPCON2bits.RSEN = 1; // ReStart I2C Transmission
	while(SSPCON2bits.RSEN);
}

void i2c_stop ()
{
	// Stop I2C Transmission
	SSPCON2bits.PEN = 1;
	while(SSPCON2bits.PEN);
}

unsigned char i2c_slave_ack ()
{
	// Return: 1 = Acknowledge was not received from slave
	//         0 = Acknowledge was received from slave
	return(SSPCON2bits.ACKSTAT);
}

void i2c_write (unsigned char data)
{
	// Send the Data to I2C Bus
	SSPBUF = data;
	if (SSPCON1bits.WCOL) return; // Check for write collision

	while(SSPSTATbits.BF); // Wait until write cycle is complete
	i2c_idle();            // Ensure the I2C module is idle
}

void i2c_master_ack (unsigned char ack_type)
{
	SSPCON2bits.ACKDT = ack_type; // 1 = Not Acknowledge, 0 = Acknowledge
	SSPCON2bits.ACKEN = 1;        // Enable Acknowledge
	while (SSPCON2bits.ACKEN == 1);
}

unsigned char i2c_read ()
{
	// Ensure the I2C module is idle
	i2c_idle();												 

	// Enable Receive Mode
	SSPCON2bits.RCEN = 1;   // Enable master for 1 byte reception
	while(!SSPSTATbits.BF); // Wait until buffer is full
	return(SSPBUF);
}

void i2c_interrupt() {

}
