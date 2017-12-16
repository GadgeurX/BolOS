#include "idt/idt.h"
#include "interrupt/int.h"

void idt_set_entry(u16 p_gdt_desc, u32 p_addr, u8 p_type,
		   s_idt_entry * p_entry)
{
    p_entry->offset_1 = (p_addr & 0xffff);
    p_entry->selector = p_gdt_desc;
    p_entry->zero = 0;
    p_entry->type_attr = p_type;
    p_entry->offset_2 = (p_addr & 0xffff0000) >> 16;
}

void idt_init()
{
    s_idt_entry *idt = (s_idt_entry*)IDT_ADDRESS;

    for (int i = 0; i < IDT_NB_ENTRIES; i++)
	    idt_set_entry(0x08, (u32) _int_asm_default, INT_GATE, &idt[i]);

    idt_set_entry(0x08, (u32) _int_asm_divide_zero, INT_GATE, idt);
    idt_set_entry(0x08, (u32) _int_asm_inv_opcode, INT_GATE, &idt[6]);
    idt_set_entry(0x08, (u32) _int_asm_dev_not_available, INT_GATE, &idt[7]);
    idt_set_entry(0x08, (u32) _int_asm_double_fault, INT_GATE, &idt[8]);
    idt_set_entry(0x08, (u32) _int_asm_inv_tss, INT_GATE, &idt[10]);
    idt_set_entry(0x08, (u32) _int_asm_seg_not_present, INT_GATE, &idt[11]);
    idt_set_entry(0x08, (u32) _int_asm_stack_segment_fault, INT_GATE, &idt[12]);
    idt_set_entry(0x08, (u32) _int_asm_general_protection_fault, INT_GATE, &idt[13]);
    idt_set_entry(0x08, (u32) _int_asm_page_fault, INT_GATE, &idt[14]);
    idt_set_entry(0x08, (u32) _int_asm_align_fault, INT_GATE, &idt[17]);

    idt_set_entry(0x08, (u32) _int_asm_clock, INT_GATE, &idt[32]);
    idt_set_entry(0x08, (u32) _int_asm_keyboard, INT_GATE, &idt[33]);

    s_idt idt_desc;
    idt_desc.base = IDT_ADDRESS;
    idt_desc.limit = IDT_SIZE;

  asm("LIDTL %0" :: "g" (idt_desc));
}
