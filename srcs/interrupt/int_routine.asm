global _int_asm_clock, _int_asm_default, _int_asm_keyboard
extern int_clock, int_default, int_keyboard

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