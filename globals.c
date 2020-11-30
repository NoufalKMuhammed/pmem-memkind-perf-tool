#include "globals.h"

#define BLOCK_SIZE 8192
#define BLOCK_COUNT 2048

unsigned int block_size = BLOCK_SIZE;
unsigned int block_count = BLOCK_COUNT;
unsigned int buffer_size = BLOCK_SIZE * BLOCK_COUNT;  
unsigned int iterations = 1000;
unsigned int seed = 123;

unsigned int* sequential_indx_arr;
unsigned int* random_indx_arr;

char *ram_src_buf;
char *ram_dst_buf;
char *pmem_src_buf;
char *pmem_dst_buf;

timing_info_t timing_info; 
