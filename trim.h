extern bit trim_mode;
extern int output_trim[TOTAL_OUTPUT_CHANNELS];
extern int stick_center[TOTAL_OUTPUT_CHANNELS];

#define NO_EXCEPTIONS -1
extern void trimMode (signed char exception);
extern bit saveTrim (void);
extern void initTrim (void);