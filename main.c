#include <stdio.h>
#include <time.h>

signed short scaleVolume(int sample, float sFactor)
{
	return sFactor > 0 && sFactor < 1 ? sample * sFactor : sample;
}

void newFactor(unsigned int *arr, float factor)
{
	printf("\nCHANGED -> %f\n", factor);
	if(factor <= 0 && factor >= 1.0) {
		factor = 1.0;
	}
	
	int i;
	for(i = 0; i < 65536; i++) {
		arr[i] = (rand() % 100 - 0);
		arr[i] *= factor;
		//printf("%d : %d\n", i, arr[i]);
	}
}

int main()
{
	int i;
	int j;
	unsigned int arr[65536];
	
	srand(time(NULL));
	
	// NORMAL SCALING
	clock_t start1 = clock();
	for(i = 0; i <= 1000000; i++) {
		unsigned int sampleSize =  ((unsigned int)(rand() % 100 -0));
		float scaleFactor = 0.5;
		scaleVolume(rand() % 100, scaleFactor);
		//printf("%d\n", n);
	}
	printf("Finished in about %.0fms\n", (double)clock() - start1/CLOCKS_PER_SEC);
	
	// SCALING WITH ARRAY
	newFactor(arr, /*(float)(rand() % 1)*/0.5);
	clock_t start2 = clock();
	for(j = 0; j < 65536; j++) {
		printf("%d : %d\n", j, arr[j]);
	}
	printf("Finished in about %.0fms\n", (double)clock() - start2/CLOCKS_PER_SEC);
	
	
	return 0;
}