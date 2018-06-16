
int absSum(int *Start, int Count)
{
	int sum = 0;
	while (Count) {
		if (*Start < 0)
			sum -= *Start;
		else
			sum += *Start;
		Start++;
		Count--;
	}
	return sum;
}
