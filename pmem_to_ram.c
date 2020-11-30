#include "run.h"
#include "globals.h"

#include <unistd.h>
#include <stdio.h>

void pmem_to_ram_sequential()
{
	printf("\nSequential");
	char *src = pmem_src_buf;
	char *dst = ram_dst_buf;
	timing_info_t *t = NULL;

	t = single_to_multi("SEQUENTIAL", src, dst);
	t = multi_to_multi("SEQUENTIAL", src, dst);
	t  = multi_to_single("SEQUENTIAL", src, dst);
}

void pmem_to_ram_random()
{
	printf("\nRandom");
	char *src = pmem_src_buf;
	char *dst = ram_dst_buf;
	timing_info_t *t = NULL;

	t = single_to_multi("RANDOM", src, dst);
	t = multi_to_multi("RANDOM", src, dst);
	t  = multi_to_single("RANDOM", src, dst);
}

void pmem_to_ram()
{
	printf("\n\nPMEM to DRAM");
	pmem_to_ram_sequential();
	pmem_to_ram_random();
}
