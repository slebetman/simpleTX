extern bit trim_mode;
extern int output_trim[TOTAL_OUTPUT_CHANNELS];
extern int stick_center[TOTAL_OUTPUT_CHANNELS];

#define NO_EXCEPTIONS -1
#define EXCEPT
extern void trim (unsigned char on_switch, signed char exception);
extern void initTrim (void);
extern void setTrimSlot (char slot);