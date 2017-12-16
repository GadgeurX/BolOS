#include "hardware/pic/pic.h"
#include "kernel_utils/video_text_utils.h"

void int_clock()
{
    byte bite = 0x5e;
    print_line("clock", &bite);
    PIC1_EOF_INT;
}

void int_default()
{
    PIC1_EOF_INT;
}

void int_keyboard()
{
    byte bite = 0x5e;
    print_line("keyboard", &bite);
    PIC1_EOF_INT;
}
