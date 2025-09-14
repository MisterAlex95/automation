#include "ui_manager.h"
#include "graphics.h"
#include "timer.h"

void ui_draw_hud(void)
{
    // ui_draw_timer();
    // ui_draw_score();
    // ui_draw_nbr_active_items();
}

void ui_draw_timer(void)
{
    char buf[32];
    sprintf(buf, "%d", timer_get_seconds());
    graphics_draw_text(SCREEN_TILE_WIDTH - 4, 1, buf);
}

void ui_draw_score(void)
{
    char buf[32];
    sprintf(buf, "%d", game.score);
    graphics_draw_text(6, 1, buf);
}

void ui_draw_nbr_active_items(void)
{
    int count = 0;
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (game.items[i].type != ITEM_TYPE_NONE)
            count++;
    }
    char buf[32];
    sprintf(buf, "%d", count);
    graphics_draw_text(1, 1, buf);
}
