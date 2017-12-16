#ifndef INT_H_
#define INT_H_

extern void _int_asm_default();
extern void _int_asm_clock();
extern void _int_asm_keyboard();

extern void _int_asm_divide_zero();
extern void _int_asm_inv_opcode();
extern void _int_asm_dev_not_available();
extern void _int_asm_double_fault();
extern void _int_asm_inv_tss();
extern void _int_asm_seg_not_present();
extern void _int_asm_stack_segment_fault();
extern void _int_asm_general_protection_fault();
extern void _int_asm_page_fault();
extern void _int_asm_align_fault();

#endif