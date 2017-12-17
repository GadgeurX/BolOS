#include "hardware/pic/pic.h"
#include "kernel_utils/video_text_utils.h"

void int_clock()
{
    PIC1_EOF_INT;
}

void int_default()
{
    byte attr = 0x0E;
    print(BOS_ERR_MSG_WARNING, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_INT_NOT_HANDLE, &attr);
    PIC1_EOF_INT;
}

void int_keyboard()
{
    byte attr = 0x0F;
    print_line("keyboard", &attr);
    PIC1_EOF_INT;
}

void int_divide_zero()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_DIV_ZERO, &attr);
    PIC1_EOF_INT;
}

void int_inv_opcode()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_INV_OPCODE, &attr);
    PIC1_EOF_INT;
}

void int_dev_not_available()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_DEV_NOT_AVAILABLE, &attr);
    PIC1_EOF_INT;
}

void int_double_fault()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_DOUBLE_FAULT, &attr);
    PIC1_EOF_INT;
}

void int_inv_tss()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_INV_TSS, &attr);
    PIC1_EOF_INT;
}

void int_seg_not_present()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_SEG_FAULT, &attr);
    PIC1_EOF_INT;
}

void int_stack_segment_fault()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_STACK_SEG_FAULT, &attr);
    PIC1_EOF_INT;
}

void int_general_protection_fault()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_GENERAL_PROTECTION_FAULT, &attr);
    PIC1_EOF_INT;
}

void int_page_fault()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_PAGE_FAULT, &attr);
    PIC1_EOF_INT;
}

void int_align_fault()
{
    byte attr = 0x0C;
    print(BOS_ERR_MSG_ERROR, &attr);
    attr = 0x0F;
    print(BOS_ERR_MSG_ALIGN_FAULT, &attr);
    PIC1_EOF_INT;
}
