#ifndef PAGING_H_
#define PAGING_H_

#define PD0_P_ADDRESS 0x400000
#define PAGING_ENTRY 1024

#include "types.h"
#include "memory/mem_virtual.h"
#include "memory/mem_physic.h"

int pd_add_k_page(char *v_addr, char *p_addr);
u32 pd_rm_k_page(char *v_addr);
void init_k_paging();

void load_pd(u32* pd_addr);
void enable_paging();

#endif