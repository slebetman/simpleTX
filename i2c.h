#include <xc.h>

// I2C Bus Control Definition
#define I2C_DATA_ACK 0
#define I2C_DATA_NOACK 1
#define I2C_WRITE_CMD 0
#define I2C_READ_CMD 1

#define I2C_REQ_ACK 0
#define I2C_REQ_NOACK 0

extern void i2c_init(void);
extern void i2c_idle ();
extern void i2c_start ();
extern void i2c_restart ();
extern void i2c_stop ();
extern unsigned char i2c_slave_ack ();
extern void i2c_write (unsigned char data);
extern void i2c_master_ack (unsigned char ack_type);
extern unsigned char i2c_read ();

