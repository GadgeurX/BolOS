#include "memory/paging.h"

u32 *pd0 = (u32*)PD0_P_ADDRESS;
u32 *pt0 = (u32*)PD0_P_ADDRESS + PAGE_SIZE;
u32 *pt1 = (u32*)PD0_P_ADDRESS + (PAGE_SIZE * 2);

void init_k_paging()
{
	int i;
	for (i = 0; i < PAGING_ENTRY; i++)
		pd0[i] = 0;
	for (i = 0; i < PAGING_ENTRY; i++)
		pt0[i] = (i * PAGE_SIZE) | 3;
	for (i = 0; i < PAGING_ENTRY; i++)
		pt1[i] = ((i * PAGE_SIZE) + ADDR_4_MO) | 3;

	pd0[0] = (u32)pt0 | 3;
	pd0[1] = (u32)pt1 | 3;
	pd0[1023] = (u32)pd0 | 3;

	load_pd(pd0);
	enable_paging();
}

char* add_k_table()
{
	char* p_addr = get_next_p_mem();
	if (p_addr == NULL)
		return NULL;
	return p_addr;
}

int pd_add_k_page(char *v_addr, char *p_addr)
{
	u32 nb_page = (u32)v_addr / PAGE_SIZE;

	u32 i_pde = nb_page / PAGING_ENTRY;
	u32 i_pte = nb_page % PAGING_ENTRY;

	u32* pde = (u32*)(0xFFC00000 + (1023 * PAGE_SIZE));
	pde += i_pde;

	if (*pde == 0)
	{
		char* table_p_addr = add_k_table();
		if (table_p_addr == NULL)
			return -1;
		*pde = (u32)table_p_addr | 3;
		u32* pt = (u32*)(0xFFC00000 + (i_pde * PAGE_SIZE));
		for (u32 i = 0; i < PAGING_ENTRY; i++)
			pt[i] = 0;
	}
	u32* pt = (u32*)(0xFFC00000 + (i_pde * PAGE_SIZE));
	pt[i_pte] = (u32)p_addr | 3;

	return 0;
}

u32 pd_rm_k_page(char *v_addr)
{
	u32 nb_page = (u32)v_addr / PAGE_SIZE;

	u32 i_pde = nb_page / PAGING_ENTRY;
	u32 i_pte = nb_page % PAGING_ENTRY;

	u32* pt = (u32*)(0xFFC00000 + (i_pde * PAGE_SIZE));

	nb_page = pt[i_pte] / PAGE_SIZE;
	pt[i_pte] = 0;
	free_p_mem(nb_page);

	return 0;
}

void load_pd(u32* pd_addr)
{
	asm("mov %0, %%eax \n \
		mov %%eax, %%cr3" :: "g" (pd_addr));
}

void enable_paging()
{
	asm("mov %cr0, %eax \n \
		or $0x80000000, %eax \n \
		mov %eax, %cr0");
}