...
	if (exp == 0xff)
		return f;
	else if (exp > 1)
		return f - 0x800000;
	else {
		unsigned ff = f & 0x7fffffff;
		unsigned carry = (ff & 0x1) && (ff & 0x2);	
		return (sign << 31) ^ ((ff >> 1) + carry);
...
