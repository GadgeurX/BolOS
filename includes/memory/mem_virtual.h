#ifndef MEM_VIRTUAL_H_
#define MEM_VIRTUAL_H_

#include "types.h"
#include "error.h"
#include "memory/memory.h"

void init_v_mem(u32 up_mem);

char *get_next_v_mem();
char *get_next_k_v_mem();
char *get_next_u_v_mem();

char *alloc_v_mem(u32 p_nb_page);
void free_v_mem(u32 p_nb_page);

#endif