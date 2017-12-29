#include "memory/mem_virtual.h"

char v_mem_map[0x20000];

void init_v_mem(u32 up_mem)
{
	u32 i = 0;
	while (i < PAGE_4_GO)
	{
		if (i < 2048 || i > up_mem / 4096)
			alloc_v_mem(i);
		else
			free_v_mem(i);
		i++;
	}
}

char *alloc_v_mem(u32 p_nb_page)
{
    u32 octect = p_nb_page / 8;
    u32 bit = p_nb_page % 8;
    v_mem_map[octect] |= 1UL << bit;
    return ((char*)(p_nb_page * PAGE_SIZE));
}

void free_v_mem(u32 p_nb_page)
{
    u32 octect = p_nb_page / 8;
    u32 bit = p_nb_page % 8;
    v_mem_map[octect] &= ~(1UL << bit);
}

char *get_next_v_mem()
{
    int i = 0;
    while (i < PAGE_12_MO)
    {
        u32 octect = i / 8;
        u32 bit_index = i % 8;
        char bit = (v_mem_map[octect] >> bit_index) & 1U;
		if (bit == 0)
			return alloc_v_mem(i);
        i++;
    }
    return (char *)NULL;
}

char *get_next_k_v_mem()
{
	int i = PAGE_12_MO;
	while (i < PAGE_1_GO)
	{
		u32 octect = i / 8;
		u32 bit_index = i % 8;
		char bit = (v_mem_map[octect] >> bit_index) & 1U;
		if (bit == 0)
			return alloc_v_mem(i);
		i++;
	}
	return (char *)NULL;
}

char *get_next_u_v_mem()
{
	int i = PAGE_1_GO;
	while (i < PAGE_4_GO)
	{
		u32 octect = i / 8;
		u32 bit_index = i % 8;
		char bit = (v_mem_map[octect] >> bit_index) & 1U;
		if (bit == 0)
			return alloc_v_mem(i);
		i++;
	}
	return (char *)NULL;
}