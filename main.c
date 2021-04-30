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

#include "init.h"
#include "globals.h"
#include "ram_to_ram.h"
#include "ram_to_pmem.h"
#include "pmem_to_ram.h"
#include "pmem_to_pmem.h"

void parse_args(int argc, char *argv[])
{
	int i;
	for (i = optind; i < argc; i++)
	{
		char *str = argv[i];
		char *val = strchr (str, '=');
		if (val == NULL)
		{
			printf("\nUnknown arguments: %s", argv[i]);
			printf("\nExample: ./a.out block_size=512 block_count=2048 \
					iterations=100 seed=123 path=/mnt/pmem\n");
			exit(1);
		}
		val++;
		char *name = strtok(str, "=");

		if ( strcmp(name, "block_size") == 0) {
			block_size = atoi(val);
			continue;
		}
		if ( strcmp(name, "block_count") == 0) {
			block_count = atoi(val);
			continue;
		}
		if ( strcmp(name, "iterations") == 0) {
			iterations = atoi(val);
			continue;
		}
		if ( strcmp(name, "seed") == 0) {
			seed = atoi(val);
			continue;
		}
		if ( strcmp(name, "path") == 0) {

			memcpy(path, val, strlen(val) + 1);
			continue;
		}
		printf("\nUnknown arguments: %s", argv[i]);
		printf("\nExample: ./a.out block_size=512 block_count=2048 iterations=100 \
				seed=123 path=/mnt/pmem\n");
		exit(1);
	}
}

void print_params()
{
	printf("\nblock_size=%u, block_count=%u, iterations=%u, seed=%u, path=%s",
			block_size, block_count, iterations, seed, path);
}

void set_buffer_size()
{
	buffer_size = block_size * block_count;
}

int main(int argc, char *argv[])
{
	parse_args(argc, argv);
	print_params();
	set_buffer_size();
	init();

	ram_to_ram();
	ram_to_pmem();
	pmem_to_ram();
	pmem_to_pmem();

	release();
	return 0;
}
