int cread(int *xp) {
	return (xp ? *xp : 0);
}

int cread_alt(int *xp) {
	int ret;
	if (xp)
		ret = *xp;
	else
		ret =  0;
	return ret;
}
