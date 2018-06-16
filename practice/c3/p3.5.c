
void decode1(int *xp, int *yp, int *zp)
{
	int x = *xp;
	int y = *yp;
	int z = *zp;
	*yp = x;
	*zp = y;
	*xp = z;
}
