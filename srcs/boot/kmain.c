#include "io/io.h"
#include "idt/idt.h"
#include "boot/boot.h"
#include "hardware/pic/pic.h"
#include "memory/memory.h"
#include "kernel_utils/motd.h"
#include "kernel_utils/video_text_utils.h"

void bos_kmain(s_boot_info * p_bif)
{
	init_driver(&i_abstract_video_api);
	i_abstract_video_api.clear_screen();
	byte param = 0x5;
	print_line(MOTD, &param);

	pic_init();
	idt_init();
	sti;

	init_memory(p_bif->mem_upper);

    while (1);
}
