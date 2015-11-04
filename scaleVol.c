#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ENTRIES 1550000

float factor;

int16_t scaleVolume(int16_t sample, float vol)
{
	return sample * vol;
}

int main(int argc, char** argv)
{
	if(argc < 2) { printf("Needs 1 arguement... Try again."); return 0; }

	FILE *fin, *fout;
	clock_t start, end;
	char line[32], res[32];
	int linectr = 0, k, volchange[16], v = 0;
	
	factor = 1.0;
	
	fin 	= fopen(argv[1], "r");
	fout 	= fopen("outScale", "w");

	for(k = 0; k < 16; volchange[k] = (NUM_ENTRIES/16) * k, k++);
	
	if(fin != NULL) {
		start = clock();
		
		//---------------------------------------------------------------------
		// PROCESSING
		while(fgets(line, 32, fin) != NULL) {
			if(linectr == volchange[v]) {
				if(linectr > 0) factor -= 0.0625;
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