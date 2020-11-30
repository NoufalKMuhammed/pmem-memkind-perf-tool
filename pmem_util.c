#include "../platform.h"

#if DEV_VM

#else
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

#define PMEM_MAX_SIZE (1024 * 1024 * 1024)

static char path[PATH_MAX]="/mnt/pmem/";
static struct memkind *pmem_kind = NULL;
static long long unsigned int start; 
static long long unsigned int end;



static void print_err_message(int err)
{
	char error_message[MEMKIND_ERROR_MESSAGE_SIZE];
	memkind_error_message(err, error_message, MEMKIND_ERROR_MESSAGE_SIZE);
	fprintf(stderr, "%s\n", error_message);
}



void release_pmem_buf()
{
	int err = 0;
	memkind_free(pmem_kind, pmem_src_buf);
	memkind_free(pmem_kind, pmem_dst_buf);
	err = memkind_destroy_kind(pmem_kind);
	if (err) {
		print_err_message(err);
		exit(1);
	}
}

void allocate_pmem_buf()
{
	printf("\nAllocating actual PMEM buffers...\n");
	int err = 0;
	int status = memkind_check_dax_path(path);
	if (!status) {
		// fprintf(stdout, "PMEM kind %s is on DAX-enabled file system.\n", path);
	} else {
		fprintf(stdout, "PMEM kind %s is not on DAX-enabled file system.\n", path);
	}

	// Create PMEM partition with specific size
	err = memkind_create_pmem(path, PMEM_MAX_SIZE, &pmem_kind);
	if (err) {
		print_err_message(err);
		exit(1);
	}

	pmem_src_buf = (char *)memkind_malloc(pmem_kind, buffer_size);
	if (pmem_src_buf == NULL) {
		fprintf(stderr, "Unable to allocate pmem_src_buf.\n");
		return;
	}
	pmem_dst_buf = (char *)memkind_malloc(pmem_kind, buffer_size);
	if (pmem_dst_buf == NULL) {
		fprintf(stderr, "Unable to allocate pmem_dst_buf.\n");
		exit(1);
	}
}
#endif
