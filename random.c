#include <stdio.h>
#include <time.h>

int main()
{
	int i;
	for(i = 0; i <= 1550000; i++) {
		printf("%d\n", rand());
	}
	
	return 0;
}