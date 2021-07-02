#define ANALOG_CHANNEL0  0x00
#define ANALOG_CHANNEL1  0x04
#define ANALOG_CHANNEL2  0x08
#define ANALOG_CHANNEL3  0x0c
#define ANALOG_CHANNEL4  0x10
#define ANALOG_CHANNEL5  0x14
#define ANALOG_CHANNEL6  0x18
#define ANALOG_CHANNEL7  0x1c
#define ANALOG_CHANNEL8  0x20
#define ANALOG_CHANNEL9  0x24
#define ANALOG_CHANNEL10 0x28
#define ANALOG_CHANNEL11 0x2c
#define ANALOG_CHANNEL12 0x30

#define SAMPLE_RATE 1000

#define STATE_IDLE     0
#define STATE_START    1
#define STATE_WAIT_AQU 2
#define STATE_CONV     3
#define STATE_DONE     4

#define ADFM_JUSTIFY_RIGHT 0x80


extern unsigned short analog_values[2];
extern bit analog_mutex;

extern void analog_init ();
extern unsigned short analog_get (unsigned char channel);
extern unsigned short analog_get_sync (unsigned int channel);
extern void analog_timer_interrupt_handler ();

