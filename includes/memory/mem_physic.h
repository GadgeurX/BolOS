#ifndef MEM_PHYSIC_H_
#define MEM_PHYSIC_H_

#include "types.h"
#include "error.h"
#include "memory/memory.h"

void init_p_mem(u32 up_mem);

char *get_next_p_mem();

char *alloc_p_mem(u32 p_nb_page);
void free_p_mem(u32 p_nb_page);

#endif