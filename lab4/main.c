#define N 6000000000

int main()
{
	double pi = 0.0;
	double k = -1.0;

	for (long i = 0; i <= N; i++)
	{
		k *= -1.0;
		pi += (4 * k) / (2 * i + 1);
	}

	return 0;
}