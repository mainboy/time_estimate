#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "clock.h"
static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;

void access_counter(unsigned *hi, unsigned *lo)
{
	asm(
		"rdtsc; movl %%edx,%0; movl %%eax,%1"
		: "=r" (*hi), "=r" (*lo)
		: /*No input*/
		: "%edx", "%eax");
}

// set init time
void start_counter()
{
	access_counter(&cyc_hi, &cyc_lo);
}

// get time interval
double get_counter()
{
	unsigned ncyc_hi, ncyc_lo;
	unsigned hi, lo, borrow;
	double result;

	access_counter(&ncyc_hi, &ncyc_lo);

	lo = ncyc_lo - cyc_lo;
	borrow = lo > ncyc_lo;
	hi = ncyc_hi - cyc_hi - borrow;
	result = (double) hi * (1 << 30) * 4 + lo;
	if (result < 0) {
		fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
	}

	return result;
}

double mhz(int verbose, int sleeptime)
{
	double rate;

	start_counter();
	sleep(sleeptime);
	rate = get_counter();
	if (verbose)
		printf("Processor clock rate = %.1f MHz\n", rate);
	return rate;
}
