extern bit trim_mode;
extern short output_trim[TOTAL_OUTPUT_CHANNELS];
extern short stick_center[TOTAL_OUTPUT_CHANNELS];

#define NO_EXCEPTIONS -1
#define EXCEPT
extern void trim (unsigned char on_switch, signed char exception);
extern void initTrim (void);
extern void setTrimSlot (char slot);