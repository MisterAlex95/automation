#include "input.h"

static UINT8 last_keys = 0;
static UINT8 current_keys = 0;

void input_init(void)
{
    last_keys = 0;
    current_keys = 0;
}

void input_update(Scene *current_scene)
{
    current_keys = joypad();

    if (current_scene && current_scene->handle_input)
    {
        current_scene->handle_input(current_keys, last_keys);
    }

    last_keys = current_keys;
}

UINT8 input_get_pressed(void)
{
    return current_keys & ~last_keys;
}

UINT8 input_get_released(void)
{
    return ~current_keys & last_keys;
}
