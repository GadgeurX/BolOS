#include "video/implementations/bos_text_implem.h"

void clear_screen(void)
{
    int count =
	(g_resolution.x + g_resolution.y * get_screen_resolution().x) * 2;

    while (count >= 0)
	g_video[count--] = 0;
}

void set_screen_resolution(s_resolution p_resolution)
{
    p_resolution = p_resolution;
    // not implemented yet
}

s_resolution get_screen_resolution(void)
{
    return (g_resolution);
}

int print_char(char p_char, void *p_parameters, s_coords p_position)
{
    s_resolution screen_resolution = get_screen_resolution();

    if (p_position.y > screen_resolution.y || p_position.y < 0
	|| p_position.x > screen_resolution.x || p_position.x < 0)
    {
	return BOS_ERR_TRY_PRINT_OUT_OF_SCREEN;
    }

    int coord = ((p_position.y * screen_resolution.x) + p_position.x) * 2;
    char *param = p_parameters;

    g_video[coord] = p_char;
    g_video[coord + 1] = param[0];

    return BOS_OK;
}

int get_char(s_coords p_position, char* p_char, void* p_param)
{
    s_resolution screen_resolution = get_screen_resolution();

    if (p_position.y > screen_resolution.y || p_position.y < 0
	|| p_position.x > screen_resolution.x || p_position.x < 0)
    {
	return BOS_ERR_TRY_READ_OUT_OF_SCREEN;
    }

    int coord = ((p_position.y * screen_resolution.x) + p_position.x) * 2;

    *p_char = g_video[coord];
    *((char*)p_param) = g_video[coord + 1];

    return BOS_OK;
}

void clear_area(s_coords p_position, s_size p_size)
{
    byte char_data = 0;
    int initial_x = p_position.x;
    int initial_y = p_position.y;

    while (p_position.x < initial_x + p_size.x)
    {
	p_position.y = initial_y;
	while (p_position.y < initial_y + p_size.y)
	{
	    print_char('\0', &char_data, p_position);
	    p_position.y++;
	}
	p_position.x++;
    }
}

void init_driver(s_abstract_video_api * p_abstract_api)
{
    (*p_abstract_api).set_screen_resolution = set_screen_resolution;
    (*p_abstract_api).get_screen_resolution = get_screen_resolution;
    (*p_abstract_api).print_char = print_char;
    (*p_abstract_api).clear_screen = clear_screen;
    (*p_abstract_api).clear_area = clear_area;
    (*p_abstract_api).get_char = get_char;

    g_video_type = TEXT;
    g_video = VIDEO_MEM_ADDR;
    g_resolution.x = LINE_LENGTH;
    g_resolution.y = COLLUMN_NBR;
}

void dinit_driver(s_abstract_video_api * p_abstract_api)
{
    (*p_abstract_api).set_screen_resolution = NULL;
    (*p_abstract_api).get_screen_resolution = NULL;
    (*p_abstract_api).print_char = NULL;
    (*p_abstract_api).clear_screen = NULL;
    (*p_abstract_api).clear_area = NULL;
}
