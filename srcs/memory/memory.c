#include "memory/memory.h"
#include "memory/kmalloc.h"

void init_memory(u32 p_upper)
{
	p_upper *= 1024;

	byte param = 0x0F;
	print("INFO : Init physic RAM ", &param);
	init_p_mem(p_upper);
	param = 0x0A;
	print_line("OK", &param);

	param = 0x0F;
	print("INFO : Init virtual RAM ", &param);
	init_v_mem(p_upper);
	param = 0x0A;
	print_line("OK", &param);

	param = 0x0F;
	print("INFO : Init segmentation ", &param);
	segmentation_load();
	param = 0x0A;
	print_line("OK", &param);

	param = 0x0F;
	print("INFO : Init paging ", &param);
	init_k_paging();
	init_ksbrk();
	param = 0x0A;
	print_line("OK  ", &param);

	param = 0x0F;
	print("INFO : Memory ", &param);
	param = 0x0A;
	print("OK  ", &param);

	param = 0x0F;
	print("Available : ", &param);
	put_nbr(p_upper, &param);
	print_line(" octet", &param);
}