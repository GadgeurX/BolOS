#ifndef MEMORY_H_
#define MEMORY_H_

#include "memory/mem_physic.h"
#include "memory/mem_virtual.h"
#include "memory/segmentation.h"
#include "kernel_utils/video_text_utils.h"
#include "memory/paging.h"

#define PAGE_SIZE 0x1000

#define ADDR_4_MO 0x400000
#define ADDR_12_MO 0xC00000

#define PAGE_12_MO 0xC00
#define PAGE_1_GO 0x40000
#define PAGE_4_GO 0x100000

void init_memory(u32 p_upper);

#endif

