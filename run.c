#include "run.h"
#include "globals.h"
#include "stdio.h"
#include "rdtsc_util.h"
#include <string.h>
#include <unistd.h>

void print_one_sec_rdtsc()
{
	timing_info.start = rdtsc_s(); 
	sleep(1);
	timing_info.end = rdtsc_e();
	timing_info.diff = (timing_info.end - timing_info.start);
}


unsigned int* get_indx_arr(char *order)
{
	if (strcmp(order, "SEQUENTIAL") == 0) {
		return sequential_indx_arr;
	}
	if (strcmp(order, "RANDOM") == 0) {
		return random_indx_arr;
	}
	printf("Wrong order: %s", order);
	exit(1);
}

timing_info_t* single_to_multi(char *order, char *src, char *dst)
{
	unsigned int *indx_arr = get_indx_arr(order);
	unsigned int iter; // iterations
	unsigned int i; // index
	
	iter = iterations;
	timing_info.start = rdtsc_s(); 
	while (iter--) {
		i = block_count;
		while (i--) {
			memcpy(dst + indx_arr[i], src, block_size);	
		}
	}
	timing_info.end = rdtsc_e();
	//  Return per operation run time, in nano seconds.
	//  It is observed that 2 rdtsc ticks in one nano second.
	timing_info.diff = (timing_info.end - timing_info.start) / iterations / block_count / 2 /* two rdtsc per nano second*/;
	printf("\nsingle_to_multi(ns)	: %llu ", timing_info.diff);
 	return &timing_info;
}

timing_info_t* multi_to_multi(char *order, char *src, char *dst)
{
	unsigned int *indx_arr = get_indx_arr(order);
	unsigned int iter; // iterations
	unsigned int i; // index
	
	iter = iterations;
	timing_info.start = rdtsc_s(); 
	while (iter--) {
		i = block_count;
		while (i--) {
			memcpy(dst + indx_arr[i], src + indx_arr[i], block_size);	
		}
	}
	timing_info.end = rdtsc_e();
	//  Return per operation run time, in nano seconds.
	//  It is observed that 2 rdtsc ticks in one nano second.
	timing_info.diff = (timing_info.end - timing_info.start) / iterations / block_count / 2 /* two rdtsc per nano second*/;
	printf("\nmulti_to_multi(ns)	: %llu ", timing_info.diff);
 	return &timing_info;
}

timing_info_t* multi_to_single(char *order, char *src, char *dst)
{
	unsigned int *indx_arr = get_indx_arr(order);
	unsigned int iter; // iterations
	unsigned int i; // index
	
	iter = iterations;
	timing_info.start = rdtsc_s(); 
	while (iter--) {
		i = block_count;
		while (i--) {
			memcpy(dst, src + indx_arr[i], block_size);	
		}
	}
	timing_info.end = rdtsc_e();
	//  Return per operation run time, in nano seconds.
	//  It is observed that 2 rdtsc ticks in one nano second.
	timing_info.diff = (timing_info.end - timing_info.start) / iterations / block_count / 2 /* two rdtsc per nano second*/;
	printf("\nmulti_to_single(ns)	: %llu ", timing_info.diff);
 	return &timing_info;
}


