
int min(int* ptr)
{
	int min = *ptr;
	for (int i = 0; i < 11; i++)
	{
		if (*ptr < min)
		{
			min = *ptr;
		}
		ptr++;
	}
	return min;
}
int max(int* ptr)
{
	int max = *ptr;
	for (int i = 0; i < 11; i++)
	{
		if (*ptr > max)
		{
			max = *ptr;
		}
		ptr++;
	}
	return max;
}