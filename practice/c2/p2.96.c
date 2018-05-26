float_bits float_i2f(int i) {
	unsigned mag = ~i + 1;
	int c1 = 0, c2 = 0;
	unsigned ret;

	while ((mag >> 23) > 1) {
		mag >>= 1;
		++c1;
	}
	while ((mag >> 23) < 1) {
		mag <<= 1;
		--c1;
	}
	
	ret = ((c1 + 127) << 23) ^ (mag & 0x7fffff);

	if (i < 0)
		return 0x80000000 | ret;
	else
		return ret;
}
