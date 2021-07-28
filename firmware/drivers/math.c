struct bytes16 {
	unsigned char low;
	unsigned char high;
};

union uShortWord {
	struct bytes16 asBytes;
	unsigned short asShort;
};

union shortWord {
	struct bytes16 asBytes;
	short asShort;
};

unsigned short u_mult_16 (unsigned short a, unsigned short b) {
	union uShortWord _a;
	union uShortWord _b;
	unsigned short result_low;
	unsigned short result_high;

	_a.asShort = a;
	_b.asShort = b;

	result_high = _a.asBytes.high * _b.asBytes.low + _b.asBytes.high * _a.asBytes.low;
	result_low = _a.asBytes.low * _b.asBytes.low;

	return (result_high << 8) + result_low;
}
