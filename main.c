#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define AMOUNT 1000000

int16_t lookup[65536];
float factor;

int16_t simpleScale(int s, float sFactor)
{
	return sFactor > 0 && sFactor < 1 ? s * sFactor : s;
}

void initializeLookup() {
	int i;
	for(i = 0; i < 65536; i++) {
		lookup[i] = i * factor;
	}
}

int16_t arrayScale(int s, float sFactor)
{
	if(sFactor != factor) {
		factor = sFactor;
		initializeLookup();
	}
	return lookup[s];
}


int main()
{
	int i, j;
	factor = 0.5;

	srand(time(NULL));
	
	
	
	// SMPLE SCALING
	clock_t start1 = clock();
	for(i = 0; i <= AMOUNT; i++) {
		int16_t s = simpleScale(rand() % 100, factor);
	}
	clock_t end1 = clock();
	
	
	
	
	// SCALING WITH ARRAY
	initializeLookup();
	clock_t start2 = clock();
	for(j = 0; j <= AMOUNT; j++) {
		int16_t s = arrayScale(rand() % 100, factor);
	}
	clock_t end2 = clock();
	
	
	
	
	printf("Finished in about %.0fms\n", (double)end1 - start1/CLOCKS_PER_SEC);
	printf("Finished in about %.0fms\n", (double)end2 - start2/CLOCKS_PER_SEC);
	
	
	return 0;
}