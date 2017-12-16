#include "kernel_utils/video_text_utils.h"

void scroll_up()
{
    s_coords cursor;
    cursor.x = 0;
    
    while (cursor.x < i_abstract_video_api.get_screen_resolution().x)
    {
        cursor.y = 0;
        while (cursor.y < i_abstract_video_api.get_screen_resolution().y)
        {
            char character = 0;
            char attr = 0;
            i_abstract_video_api.get_char(cursor, &character, &attr);
            cursor.y--;
            i_abstract_video_api.print_char(character, &attr, cursor);
            cursor.y += 2;
        }
        cursor.x++;
    }
}

void print(char *p_str, void *p_param)
{
    static s_coords cursor;
    while (*p_str != 0)
    {
        if (*p_str == '\n')
        {
            cursor.x = 0;
            if (cursor.y < i_abstract_video_api.get_screen_resolution().y)
                cursor.y++;
            else
                scroll_up();
        }
        else
            i_abstract_video_api.print_char(*p_str, p_param, cursor);
        cursor.x++;
        p_str++;
    }
}

void print_line(char *p_str, void *p_param)
{
    print(p_str, p_param);
    print("\n", 0);
}
