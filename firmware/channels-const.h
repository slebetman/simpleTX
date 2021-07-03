#define TOTAL_CHANNELS 16
#define USER_CHANNELS 12
#define TOTAL_OUTPUT_CHANNELS 8

#define ANALOG_CHANNEL(x) channels[USER_CHANNELS+x]

#define AILERON  ANALOG_CHANNEL(1)
#define ELEVATOR ANALOG_CHANNEL(0)
#define THROTTLE ANALOG_CHANNEL(2)
#define RUDDER   ANALOG_CHANNEL(3)


