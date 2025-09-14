#include <gb/gb.h>
#include "graphics.h"
#include "scene_menu.h"
#include "input.h"
#include "game.h"
#include "timer.h"

void main(void)
{
    CRITICAL
    {
        timer_init();
        graphics_init();
        input_init();
        game_init();
    }

    scene_set(&scene_menu);

    while (1)
    {
        vsync();

        // Timer
        timer_tick();

        // Input
        input_update(scene_current());

        // Scene
        scene_update();
    }
}
