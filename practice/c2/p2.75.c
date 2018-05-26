unsigned unsigned_high_prod(unsigned x, unsigned y) {
	int smask = 1 << ((sizeof(unsigned) << 3) - 1);
	int s_prod = signed_high_prod(x, y);
	(smask & x) && (s_prod += y);
	(smask & y) && (s_prod += x);
	return s_prod;	
}
