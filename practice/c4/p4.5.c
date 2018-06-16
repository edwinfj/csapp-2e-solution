int absSum(int *Start, int Count)
{
	int sum = 0;
	while (Count) {
		sum += (*Start) < 0 ? -(*Start) : (*Start);
		Start++;
		Count--;
	}
	return sum;
}
