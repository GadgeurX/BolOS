#ifndef KMALLOC_H_
#define KMALLOC_H_

#include "memory/memory.h"
#include "types.h"

#define MALLOC_OFFSET 100
#define MALLOC_PAGE_SIZE 8192

typedef struct __attribute__((__packed__))   s_header
{
	u32  size;
	char    free;
	u32  offset;
}               t_header;

void *ksbrk(int nb_octect);
int init_ksbrk();
void *malloc(u32 size);

#endif