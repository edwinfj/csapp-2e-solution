#include "p.h"

float_bits float_negate(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xff;
	unsigned frac = f & 0x7fffff;

	if (exp == 0xff && frac != 0)
		return f;
	else
		return (1 << 31) ^ f;
}
