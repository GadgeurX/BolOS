#include "memory/kmalloc.h"

void *sub_ksbrk(u32 nb_octect, char* kernel_heap)
{
	char* new_heap = kernel_heap - nb_octect;
	u32 current_nb_page = (u32)kernel_heap / PAGE_SIZE;
	u32 new_nb_page = (u32)new_heap / PAGE_SIZE;

	u32 nb_page_to_add = current_nb_page - new_nb_page;

	for (u32 i = 0; i < nb_page_to_add; i++) {
		pd_rm_k_page(kernel_heap);
		kernel_heap -= PAGE_SIZE;
	}

	return new_heap;
}

void *add_ksbrk(u32 nb_octect, char* kernel_heap)
{
	char* new_heap = kernel_heap + nb_octect;
	u32 current_nb_page = (u32)kernel_heap / PAGE_SIZE;
	u32 new_nb_page = (u32)new_heap / PAGE_SIZE;

	u32 nb_page_to_add = new_nb_page - current_nb_page;

	for (u32 i = 0; i < nb_page_to_add; i++) {
		char* p_addr = get_next_p_mem();
		if (p_addr == NULL)
			return NULL;
		char* v_addr = get_next_k_v_mem();
		if (v_addr == NULL)
			return NULL;
		int k_page = pd_add_k_page(v_addr, p_addr);
		if (k_page < 0)
			return NULL;
	}

	return new_heap;
}

int init_ksbrk()
{
	char* p_addr = get_next_p_mem();
	if (p_addr == NULL)
		return BOS_ERR_NOT_ENOUGH_PHYSIC_MEMORY;
	char* v_addr = get_next_k_v_mem();
	if (v_addr == NULL)
		return BOS_ERR_NOT_ENOUGH_VIRTUAL_MEMORY;
	int k_page = pd_add_k_page(v_addr, p_addr);
	if (k_page < 0)
		return BOS_ERR_NOT_ENOUGH_VIRTUAL_MEMORY;
	char* kernel_heap = (char*)ADDR_12_MO;
	int i = 0;
	while (i < 255)
		kernel_heap[i++] = 0;
	return 0;
}

void *ksbrk(int nb_octect)
{
	static char* kernel_heap = (char*)ADDR_12_MO;
	if (nb_octect == 0)
		return kernel_heap;
	if (nb_octect > 0)
		kernel_heap = add_ksbrk(nb_octect, kernel_heap);
	else
		kernel_heap = sub_ksbrk(-nb_octect, kernel_heap);
	load_pd((u32*)PD0_P_ADDRESS);
	return kernel_heap;
}

void *get_end(void *ptr)
{
	static void	*end = NULL;
	if (ptr != NULL)
		end = ptr;
	return (end);
}

char is_new_block(t_header *head)
{
	if (head->free == 0 && head->size == 0 && head->offset == 0)
		return (1);
	return (0);
}

char is_free_block(t_header *head)
{
	if (head->free == 0)
		return (1);
	return (0);
}

char as_space(t_header *head, u32 s)
{
	if (head->size > s)
		return (1);
	return (0);
}

void *add_mem(u32 nb_bloc)
{
	void	*current_ptr;
	void	*ptr;
	u32	i;

	i = 1;
	current_ptr = ksbrk(0);
	ptr = ksbrk(nb_bloc * MALLOC_PAGE_SIZE);
	if (ptr == NULL)
		return NULL;
	while (i < nb_bloc * MALLOC_PAGE_SIZE)
	{
		((char*)current_ptr)[i] = 0;
		i++;
	}
	return ptr;
}

char is_free_or_new_block(t_header **head, u32 size)
{
	if (is_new_block(*head))
	{
		add_mem(((size + sizeof(t_header) + MALLOC_OFFSET) / MALLOC_PAGE_SIZE) + 1);
		(*head)->free = 1;
		(*head)->size = size;
		(*head)->offset = MALLOC_OFFSET;
		return (1);
	}
	else if (is_free_block(*head) && as_space(*head, size))
	{
		(*head)->free = 1;
		(*head)->offset += (*head)->size - size;
		(*head)->size = size;
		return (1);
	}
	return (0);
}

void *malloc(u32 size)
{
	void		*start;
	t_header	*head;

	start = (char*)ADDR_12_MO;
	if (get_end(NULL) == NULL)
		get_end((void*)(ADDR_12_MO + MALLOC_PAGE_SIZE));
	head = start;
	while (((void*)head) + sizeof(t_header) + head->size + head->offset <= get_end(NULL))
	{
		if (is_free_or_new_block(&head, size) == 1)
			return (void*)(head + sizeof(t_header));
		head = (t_header*)(((char*)head) + sizeof(t_header) + head->size + head->offset);
	}
	return NULL;
}