extern unsigned int expo (unsigned int input, unsigned char percent /* 0-100 */);
extern unsigned int reverse (unsigned int input);
extern void mix(unsigned int proportional, unsigned int differential, unsigned int* a, unsigned int* b);
extern void slowdown (unsigned int input, unsigned int* output, int increment);
extern unsigned int scale (unsigned int input, unsigned int percent);
