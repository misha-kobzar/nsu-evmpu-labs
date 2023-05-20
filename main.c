#include <stdio.h>
#include <time.h>

#define N 6000000000

int main()
{
	double pi = 0.0;
	double k = -1.0;

	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	for (int i = 0; i <= N; ++i) 
	{
		k *= -1;
		pi += (4 * k) / (2 * i + 1);
	}
	
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	printf("Time taken: %lf sec.\n", 
		   end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));

	return 0;
}

