#include "memory/mem_physic.h"

char p_mem_map[0x20000];

void init_p_mem(u32 up_mem)
{
    u32 i = 0;
    while (i < PAGE_4_GO)
    {
		if (i < 2048 || i > up_mem / 4096)
			alloc_p_mem(i);
		else
			free_p_mem(i);
        i++;
    }
}

char *alloc_p_mem(u32 p_nb_page)
{
    u32 octect = p_nb_page / 8;
    u32 bit = p_nb_page % 8;
    p_mem_map[octect] |= 1UL << bit;
    return ((char*)(p_nb_page * 4096));
}

void free_p_mem(u32 p_nb_page)
{
    u32 octect = p_nb_page / 8;
    u32 bit = p_nb_page % 8;
    p_mem_map[octect] &= ~(1UL << bit);
}

char *get_next_p_mem()
{
    int i = 0;
    while (i < PAGE_4_GO)
    {
        u32 octect = i / 8;
        u32 bit_index = i % 8;
        char bit = (p_mem_map[octect] >> bit_index) & 1U;
		if (bit == 0)
			return alloc_p_mem(i);
        i++;
    }
    return (char *)NULL;
}