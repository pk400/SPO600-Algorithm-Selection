#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define DEBUG 0 // 0=OFF 1=ON
#define NUM_ENTRIES 1550000
#define NUM_DIFF_SAMPLES 65536

float factor;
int16_t lookup[NUM_DIFF_SAMPLES];

void initializeLookup()
{
	int i;
	for(i = 1; i <= NUM_DIFF_SAMPLES; i++) {
		lookup[i] = i * factor;
	}
}

int16_t scaleVolume(int16_t sample, float vol)
{
	if(vol != factor)
		initializeLookup();
	return lookup[sample];
}

int main(int argc, char** argv)
{
	if(argc < 3) { printf("Needs 2 parameters... Try again."); return 0; }

	// Setup
	FILE *fin, *fout;
	clock_t start, end;
	char line[16], res[16];
	int counter = 0, k, volchange[16], v = 0;
	
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	factor = 1.0;
	
	// Will lower factor every 1/16th step
	for(k = 0; k < 16; volchange[k] = (NUM_ENTRIES/16) * k, k++);
	
	if(fin != NULL) {
		if(fout != NULL) {
			start = clock();
			
			// Process
			while(fgets(line, 32, fin) != NULL) {
				if(counter == volchange[v]) { // Reinitializes the array every 1/16th step
					if(counter > 0) factor -= 0.0625;
					initializeLookup();
					v++;
				}
				int16_t scaledvolume = scaleVolume(atoi(line), factor);
				counter++;
				
				#if DEBUG == 1
				sprintf(res, "%.3f\t\t%d\n", factor, scaleVolume(atoi(line), factor));
				fputs(res, fout);
				#endif
			}
			
			end = clock();
		
			printf("Program took %0.fms.", (double)end-start/CLOCKS_PER_SEC);
			
			// Clean
			fclose(fin);
			fclose(fout);
		} else { printf("Check destination file parameter. Try again."); }	
	} else { printf("Check source file parameter. Try again."); }
	
	return 0;
}