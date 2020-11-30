#include "run.h"
#include "globals.h"

#include <unistd.h>
#include <stdio.h>

void ram_to_pmem_sequential()
{
	printf("\nSequential");
	char *src = ram_src_buf;
	char *dst = pmem_dst_buf;
	timing_info_t *t = NULL;

	t = single_to_multi("SEQUENTIAL", src, dst);
	t = multi_to_multi("SEQUENTIAL", src, dst);
	t  = multi_to_single("SEQUENTIAL", src, dst);
}

void ram_to_pmem_random()
{
	printf("\nRandom");
	char *src = ram_src_buf;
	char *dst = pmem_dst_buf;
	timing_info_t *t = NULL;

	t = single_to_multi("RANDOM", src, dst);
	t = multi_to_multi("RANDOM", src, dst);
	t  = multi_to_single("RANDOM", src, dst);
}

void ram_to_pmem()
{
	printf("\n\nDRAM to PMEM");
	ram_to_pmem_sequential();
	ram_to_pmem_random();
}
