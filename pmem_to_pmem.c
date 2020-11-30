#include "run.h"
#include "globals.h"

#include <unistd.h>
#include <stdio.h>

void pmem_to_pmem_sequential()
{
	printf("\nSequential");
	char *src = pmem_src_buf;
	char *dst = pmem_dst_buf;
	timing_info_t *t = NULL;

	t = single_to_multi("SEQUENTIAL", src, dst);
	t = multi_to_multi("SEQUENTIAL", src, dst);
	t  = multi_to_single("SEQUENTIAL", src, dst);
}

void pmem_to_pmem_random()
{
	printf("\nRandom");
	char *src = pmem_src_buf;
	char *dst = pmem_dst_buf;
	timing_info_t *t = NULL;

	t = single_to_multi("RANDOM", src, dst);
	t = multi_to_multi("RANDOM", src, dst);
	t  = multi_to_single("RANDOM", src, dst);
}

void pmem_to_pmem()
{
	printf("\n\nPMEM to PMEM");
	pmem_to_pmem_sequential();
	pmem_to_pmem_random();
}
