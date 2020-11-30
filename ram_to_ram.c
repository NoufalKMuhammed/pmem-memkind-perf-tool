#include "run.h"
#include "globals.h"

#include <unistd.h>
#include <stdio.h>

void ram_to_ram_sequential()
{
	printf("\nSequential");
	char *src = ram_src_buf;
	char *dst = ram_dst_buf;
	timing_info_t *t = NULL;

	t = single_to_multi("SEQUENTIAL", src, dst);
	t = multi_to_multi("SEQUENTIAL", src, dst);
	t  = multi_to_single("SEQUENTIAL", src, dst);
}

void ram_to_ram_random()
{
	printf("\nRandom");
	char *src = ram_src_buf;
	char *dst = ram_dst_buf;
	timing_info_t *t = NULL;

	t = single_to_multi("RANDOM", src, dst);
	t = multi_to_multi("RANDOM", src, dst);
	t  = multi_to_single("RANDOM", src, dst);
}

void ram_to_ram()
{
	printf("\n\nDRAM to DRAM");
	ram_to_ram_sequential();
	ram_to_ram_random();
}
