#include <memkind.h>
#include <unistd.h>
#include <malloc.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <string.h>

#include "globals.h"
#include "../platform.h"
#include "pmem_util.h"

void allocate_src_dst_memory()
{
	ram_src_buf = (char *)malloc(buffer_size);
	if (ram_src_buf == NULL) {
		printf("Unable to allocate ram buf");
		exit(1);
	}
	ram_dst_buf = (char *)malloc(buffer_size);
	if (ram_dst_buf == NULL) {
		printf("Unable to allocate ram buf");
		exit(1);
	}
#if DEV_VM
	// In dev vm, we use DRAM as pmem.
	pmem_src_buf = (char *)malloc(buffer_size);
	if (pmem_src_buf == NULL) {
		printf("Unable to allocate pmem buf");
		exit(1);
	}
	pmem_dst_buf = (char *)malloc(buffer_size);
	if (pmem_dst_buf == NULL) {
		printf("Unable to allocate pmem buf");
		exit(1);
	}
#else
  allocate_pmem_buf();	
#endif
}

void free_src_dst_memory()
{
	free(ram_src_buf);
	free(ram_dst_buf);
#if DEV_VM
	free(pmem_src_buf);
	free(pmem_dst_buf);
#else
	release_pmem_buf();
#endif
}

void warmup_src_dst_buffer()
{
	unsigned int i;

	char str[block_size];
	for (i = 0; i < block_size; i++) {
		str[i] = 'A';
	}

	for (i = 0; i < block_count; i++) {
		memcpy(ram_src_buf + (i * block_size), str, block_size);	
		memcpy(ram_dst_buf + (i * block_size), str, block_size);	
		memcpy(pmem_src_buf + (i * block_size), str, block_size);	
		memcpy(pmem_dst_buf + (i * block_size), str, block_size);	
	}
}

void allocate_indx_arr_memory()
{
	sequential_indx_arr = (unsigned int*) malloc (sizeof(unsigned int) * block_count);
	if (sequential_indx_arr == NULL) {
		printf("\n sequential_indx_arr malloc failed");
		exit(1);
	}
	random_indx_arr = malloc (sizeof(unsigned int) * block_count);
	if (random_indx_arr == NULL) {
		printf("\n random_indx_arr malloc failed");
		exit(1);
	}
}

void free_indx_arrays()
{
	free(sequential_indx_arr);
	free(random_indx_arr);
}

void set_indx_arrays()
{
	unsigned int i;

	for (i = 0; i < block_count; i++) {
		sequential_indx_arr[i] = i * block_size;
	}

	int r;
	srand(seed);
	for (i = 0; i < block_count; i++) {
		r = rand() % block_count;
		random_indx_arr[i] = r * block_size;
	}
}

void init()
{
	allocate_src_dst_memory();
	warmup_src_dst_buffer();
	allocate_indx_arr_memory();
	set_indx_arrays();
}

void release()
{
	free_indx_arrays();
	free_src_dst_memory();
}
