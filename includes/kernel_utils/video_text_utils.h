#ifndef VIDEO_TEXT_UTILS_H_
#define VIDEO_TEXT_UTILS_H_

#include "video/implementations/bos_text_implem.h"

void print_line(char *p_str, void* p_param);
void print(char *p_str, void *p_param);
void scroll_up();
int	put_nbr(int n, void *p_param);
void put_char(char p_str, void *p_param);

#endif