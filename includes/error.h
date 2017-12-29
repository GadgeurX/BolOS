#ifndef ERROR_H_
#define ERROR_H_

#define BOS_OK 0
#define BOS_ERR_TRY_PRINT_OUT_OF_SCREEN -1
#define BOS_ERR_TRY_READ_OUT_OF_SCREEN -2
#define BOS_ERR_NOT_ENOUGH_PHYSIC_MEMORY -3
#define BOS_ERR_NOT_ENOUGH_VIRTUAL_MEMORY -4


/**
 * 
 *                   MESSAGE
 * 
 **/

#define BOS_ERR_MSG_WARNING "WARNING: "
#define BOS_ERR_MSG_ERROR "ERROR: "

#define BOS_ERR_MSG_INT_NOT_HANDLE "Interrupt not handled\n"
#define BOS_ERR_MSG_DIV_ZERO "Divide by zero\n"
#define BOS_ERR_MSG_INV_OPCODE "Invalid opcode\n"
#define BOS_ERR_MSG_DEV_NOT_AVAILABLE "Device not available\n"
#define BOS_ERR_MSG_DOUBLE_FAULT "Double fault\n"
#define BOS_ERR_MSG_INV_TSS "Invalid TSS\n"
#define BOS_ERR_MSG_SEG_FAULT "Segmentation fault\n"
#define BOS_ERR_MSG_STACK_SEG_FAULT "Stack segment fault\n"
#define BOS_ERR_MSG_GENERAL_PROTECTION_FAULT "General protection fault\n"
#define BOS_ERR_MSG_PAGE_FAULT "Page fault\n"
#define BOS_ERR_MSG_ALIGN_FAULT "Alignement fault\n"

#endif
