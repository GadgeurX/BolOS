global _int_asm_clock, _int_asm_default, _int_asm_keyboard, _int_asm_divide_zero, _int_asm_inv_opcode
global _int_asm_dev_not_available, _int_asm_double_fault, _int_asm_inv_tss, _int_asm_seg_not_present, _int_asm_stack_segment_fault
global _int_asm_general_protection_fault, _int_asm_page_fault, _int_asm_align_fault

extern int_clock, int_default, int_keyboard, int_divide_zero, int_inv_opcode
extern int_dev_not_available, int_double_fault, int_inv_tss, int_seg_not_present, int_stack_segment_fault
extern int_general_protection_fault, int_page_fault, int_align_fault

%macro  SAVE_REGS 0
        pushad 
        push ds
        push es
        push fs
        push gs 
%endmacro

%macro  RESTORE_REGS 0
        pop gs
        pop fs
        pop es
        pop ds
        popad
%endmacro

_int_asm_divide_zero:
    SAVE_REGS
    call int_divide_zero
    RESTORE_REGS
    iret

_int_asm_inv_opcode:
    SAVE_REGS
    call int_inv_opcode
    RESTORE_REGS
    iret

_int_asm_dev_not_available:
    SAVE_REGS
    call int_dev_not_available
    RESTORE_REGS
    iret

_int_asm_double_fault:
    SAVE_REGS
    call int_double_fault
    RESTORE_REGS
    iret

_int_asm_inv_tss:
    SAVE_REGS
    call int_inv_tss
    RESTORE_REGS
    iret

_int_asm_seg_not_present:
    SAVE_REGS
    call int_seg_not_present
    RESTORE_REGS
    iret

_int_asm_stack_segment_fault:
    SAVE_REGS
    call int_stack_segment_fault
    RESTORE_REGS
    iret

_int_asm_general_protection_fault:
    SAVE_REGS
    call int_general_protection_fault
    RESTORE_REGS
    iret

_int_asm_page_fault:
    SAVE_REGS
    call int_page_fault
    RESTORE_REGS
    iret

_int_asm_align_fault:
    SAVE_REGS
    call int_align_fault
    RESTORE_REGS
    iret

_int_asm_default:
    SAVE_REGS
    call int_default
    RESTORE_REGS
    iret

_int_asm_clock:
    SAVE_REGS
    call int_clock
    RESTORE_REGS
    iret

_int_asm_keyboard:
    SAVE_REGS
    call int_keyboard
    RESTORE_REGS
    iret