#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

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
	if(argc < 2) { printf("Needs 1 arguement... Try again."); return 0; }

	FILE *fin,*fout;
	clock_t start, end;
	char line[16], res[16];
	int linectr = 0, k, volchange[16], v = 0;
	
	factor = 1.0;
	
	fin 	= fopen(argv[1], "r");
	fout 	= fopen("outLookup", "w");
	
	// Will lower factor every 1/16th step
	for(k = 0; k < 16; volchange[k] = (NUM_ENTRIES/16) * k, k++);
	
	if(fin != NULL) {
		start = clock();
		
		//---------------------------------------------------------------------
		// PROCESSING
		while(fgets(line, 32, fin) != NULL) {
			if(linectr == volchange[v]) { // Reinitializes the array every 1/16th step
				if(linectr > 0) factor -= 0.0625;
				initializeLookup();
				v++;
			}
			
			int16_t scaledvolume = scaleVolume(atoi(line), factor);
			
			// Output to file
			//sprintf(res, "%.3f\t\t%d\n", factor, scaledvolume);
			//fputs(res, fout);
			
			linectr++;
			
			
		}
		//---------------------------------------------------------------------
		
		end = clock();
	
		printf("Program took %fms.", (double)end-start/CLOCKS_PER_SEC);
		
		fclose(fout);
		fclose(fin);
	} else { printf("Check source file parameter. Try again."); }
	
	return 0;
}