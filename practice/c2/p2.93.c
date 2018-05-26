...
	if (exp == 0)
		return (f << 1) ^ (sign << 31);
	else if (exp < 254)
		return f + 0x800000;
	else
		return (sign << 31) ^ 0x7f800000;
...
