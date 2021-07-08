#define LOW 0
#define HIGH 1
typedef struct button {
	unsigned char id;
	short count;
	short longCount;
	char state;
	char longState;
} button;
