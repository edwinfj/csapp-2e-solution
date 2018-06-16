int switch3(int *p1, int *p2, mode_t action)
{
	int result = 0;
	switch (action) {
		case MODE_A:
			result = *p1;
			*p1 = *p2;
			break;
		case MODE_B:
			result = *p2 + *p1;
			*p2 = result;
			break;
		case MODE_C:
			*p2 = 15;
			result = *p1;
			break;
		case MODE_D:
			*p2 = *p1;
			result = 17;
			break;
		case MODE_E:
			result = 17;
			break;
		default:
			result = -1;
	}
	return result;
}

