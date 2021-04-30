#ifndef GLOBALS_H
#define GLOBALS_H

extern unsigned int buffer_size;  
extern unsigned int block_size;
extern unsigned int block_count;
extern unsigned int iterations;
extern unsigned int seed;
extern char path[20];

extern unsigned int* sequential_indx_arr;
extern unsigned int* random_indx_arr;

extern char *ram_src_buf;
extern char *ram_dst_buf;
extern char *pmem_src_buf;
extern char *pmem_dst_buf;

typedef struct timing_info_s {
	long long unsigned int start;
	long long unsigned int end;
	long long unsigned int diff;
} timing_info_t;
extern timing_info_t timing_info;
#endif