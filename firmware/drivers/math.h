extern unsigned short u_mult_16 (unsigned short a, unsigned short b);

#define mult_16(a,b) ((signed short)u_mult_16(a,b))
