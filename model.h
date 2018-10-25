struct mix {
	unsigned char input;
	unsigned char output;
	signed char scale;
	signed char expo;
}

struct model {
	unsigned char name[10];
	unsigned int trim[4];
	struct mix mix[8];
}

extern struct model current_model;

