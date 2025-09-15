#include "ui_manager.h"
#include "graphics.h"
#include "game.h"
#include "game_map.h"
#include "timer.h"

void ui_draw_hud(void)
{
    ui_draw_tile_info_under_cursor();
    ui_draw_nbr_active_items();
    // ui_cursor_position();
    // ui_draw_item_x_info(0);
    // ui_draw_timer();
}

void ui_draw_timer(void)
{
    char buf[32];
    sprintf(buf, "%d", timer_get_seconds());
    graphics_draw_text(SCREEN_TILE_WIDTH - 4, 1, buf);
}

void ui_cursor_position(void)
{
    char buf[32];
    sprintf(buf, "%d,%d  ", game.cursor_x, game.cursor_y);
    graphics_draw_text(1, SCREEN_TILE_HEIGHT - 1, buf);
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
    sprintf(buf, "Active: %d", count);
    graphics_draw_text(1, SCREEN_TILE_HEIGHT - 2, buf);
}

void ui_draw_item_x_info(UBYTE x)
{
    item_t *item = &game.items[x];
    char buf[32];
    sprintf(buf, "(%d,%d)   (%d,%d)", item->pos_x, item->pos_y, item->pos_x / TILE_SIZE, item->pos_y / TILE_SIZE);
    graphics_draw_text(1, SCREEN_TILE_HEIGHT - 2, buf);
}

void ui_draw_tile_info_under_cursor(void)
{
    UBYTE tile = game_map_get_tile_at_position((game.cursor_x * TILE_SIZE) - DEVICE_SPRITE_PX_OFFSET_X, (game.cursor_y * TILE_SIZE) - DEVICE_SPRITE_PX_OFFSET_Y);
    UBYTE out_count = 0;
    UBYTE *items_on_tile = game_map_get_items_on_tile(game.cursor_x, game.cursor_y, &out_count);

    char buf[32];
    sprintf(buf, "Tile: %d (%d items) ", tile, out_count);
    graphics_draw_text(1, SCREEN_TILE_HEIGHT - 1, buf);
}