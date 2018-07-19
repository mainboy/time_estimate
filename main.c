
#include <stdio.h>
#include "clock.h"

int main() {
	double rate=mhz(0, 1);
	int sum = 0, i, nums = 1000;
	start_counter();
	for (i=0; i < nums; i++) sum += i;
	printf("time = %lf\n", get_counter()/rate);
	return 0;
}

