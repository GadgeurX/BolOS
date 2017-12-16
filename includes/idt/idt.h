#ifndef IDT_H_
#define IDT_H_

#define INT_GATE 0x8E
#define IDT_ADDRESS 0x08
#define IDT_NB_ENTRIES 255
#define IDT_SIZE 0x3FC0

#include "types.h"

typedef struct {
   u16 offset_1;
   u16 selector;
   u8 zero;
   u8 type_attr;
   u16 offset_2;
} __attribute__ ((packed)) s_idt_entry;

typedef struct {
   u16 limit;
   u32 base;
} __attribute__ ((packed)) s_idt;

void idt_init();

#endif