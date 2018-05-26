int float_f2i(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xff;
	unsigned frac = f & 0x7fffff;
	int tmin = 0x80000000;
	unsigned ret = frac | (1 << 23);

	if (exp == 0xff)
		return tmin;
	else if (exp == 0)
		return 0;
	else if (exp - 150 >= 0 && exp - 150 <= 7)
		ret <<= (exp - 150);
	else if (exp - 150 > 7)
		return tmin;
	else 
		ret >>= 150 - exp;

	(sign) && (ret = ~ret + 1);
	return ret;
}	
