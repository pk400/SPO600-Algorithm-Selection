#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define VOL_CHANGE(N) 96875*N

float factor = 0.5;

int16_t scaleVolume(int16_t sample, float vol)
{
	return sample * vol;
}

int main(int argc, char** argv)
{
	if(!argv[1])
		return 0;

	// Setup
	FILE *fin, *fout;
	clock_t start, end;
	char line[32], res[32];
	
	fin 	= fopen(argv[1], "r");
	fout 	= fopen("out", "w");

	start = clock();
	
	// Process
	while(fgets(line, 32, fin) != NULL) {
		switch(counter) {
			case VOL_CHANGE(1): 	factor = 0.9; 	break;
			case VOL_CHANGE(2): 	factor = 0.8; 	break;
			case VOL_CHANGE(3): 	factor = 0.7; 	break;
			case VOL_CHANGE(4): 	factor = 0.6; 	break;
			case VOL_CHANGE(5): 	factor = 0.5; 	break;
			case VOL_CHANGE(6): 	factor = 0.4; 	break;
			case VOL_CHANGE(7): 	factor = 0.3; 	break;
			case VOL_CHANGE(8): 	factor = 0.2; 	break;
			case VOL_CHANGE(9): 	factor = 0.1; 	break;
			case VOL_CHANGE(10): 	factor = 0.125; break;
			case VOL_CHANGE(11): 	factor = 0.250; break;
			case VOL_CHANGE(12): 	factor = 0.789; break;
			case VOL_CHANGE(13): 	factor = 0.654; break;
			case VOL_CHANGE(14): 	factor = 0.456; break;
			case VOL_CHANGE(15): 	factor = 0.987; break;
		}
		sprintf(res, "%d\n", scaleVolume(atoi(line), factor));
		fputs(res, fout);
	}
	
	end = clock();
	
	printf("Program took %0.fms.", (double)end-start/CLOCKS_PER_SEC);
	
	// Clean
	fclose(fout);
	fclose(fin);
	
	return 0;
}