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
    cursor.x = 0;
	cursor.y = i_abstract_video_api.get_screen_resolution().y - 1;
    while (cursor.x < i_abstract_video_api.get_screen_resolution().x)
    {
        char attr = 0;
        i_abstract_video_api.print_char(0, &attr, cursor);
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
            if (cursor.y < i_abstract_video_api.get_screen_resolution().y - 1)
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

void put_char(char p_str, void *p_param)
{
	char str[2];
	str[0] = p_str;
	str[1] = 0;
	print(str, p_param);
}

void print_line(char *p_str, void *p_param)
{
    print(p_str, p_param);
    print("\n", 0);
}

int	put_nbr(int n, void *p_param)
{
	if (n < 0)
	{
		put_char('-', p_param);
		n = -n;
	}
	if (n >= 10)
	{
		put_nbr(n / 10, p_param);
		put_char(n % 10 + '0', p_param);
	}
	if (n < 10)
	{
		put_char(n % 10 + '0', p_param);
	}
	return (n);
}
