#include "ui_manager.h"
#include "graphics.h"
#include "game.h"
#include "../world/game_map.h"
#include "../world/viewport.h"
#include "timer.h"
#include "constants.h"
#include "camera.h"

static UBYTE pause_overlay_dirty = 0;

void ui_draw_hud(void)
{
    ui_cursor_position();

    char buf[32];
    sprintf(buf, "S:%u  ", (unsigned)game.score);
    graphics_draw_text(12, SCREEN_TILE_HEIGHT - 1, buf);

    if (game.won)
    {
        graphics_draw_text(5, 8, "YOU WIN!");
        graphics_draw_text(3, 10, "START:Menu");
        pause_overlay_dirty = 1;
    }
    else if (game.paused)
    {
        graphics_draw_text(6, 8, "PAUSED");
        pause_overlay_dirty = 1;
    }
    else if (pause_overlay_dirty)
    {
        // printf writes into the BG tilemap — restore world tiles underneath
        viewport_restore_screen_rect(3, 8, 14, 3);
        pause_overlay_dirty = 0;
    }
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
    UBYTE wx = cursor_screen_to_world_x(game.cursor_x);
    UBYTE wy = cursor_screen_to_world_y(game.cursor_y);
    sprintf(buf, "(%u,%u)  ", (unsigned)wx, (unsigned)wy);
    graphics_draw_text(0, SCREEN_TILE_HEIGHT - 1, buf);
}

void ui_draw_miner_x_info(UBYTE x)
{
    miner_t *m = &get_miners()[x];
    char buf[32];
    sprintf(buf, "(%d,%d) R:%d C:%d  ", m->tile_x, m->tile_y, m->rate, m->cooldown);
    graphics_draw_text(0, SCREEN_TILE_HEIGHT - 4, buf);
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
    graphics_draw_text(0, SCREEN_TILE_HEIGHT - 2, buf);
}

void ui_draw_item_x_info(UBYTE x)
{
    item_t *item = &game.items[x];
    char buf[32];
    UBYTE tile_x = world_to_tile_x(item->world_x);
    UBYTE tile_y = world_to_tile_y(item->world_y);
    sprintf(buf, "(%d,%d)   (%d,%d)", item->world_x, item->world_y, tile_x, tile_y);
    graphics_draw_text(0, SCREEN_TILE_HEIGHT - 2, buf);
}

void ui_draw_tile_info_under_cursor(void)
{
    UBYTE wx = cursor_screen_to_world_x(game.cursor_x);
    UBYTE wy = cursor_screen_to_world_y(game.cursor_y);

    UBYTE tile = game_map_get_tile(wx, wy);
    UBYTE out_count = game_map_count_items_on_tile(wx, wy);

    char buf[32];
    sprintf(buf, "Tile: %d (%d items) ", tile, out_count);
    graphics_draw_text(0, SCREEN_TILE_HEIGHT - 1, buf);
}

void ui_draw_camera_debug(void)
{
    char buf[32];
    sprintf(buf, "Cam:(%u,%u)", (unsigned)camera_get_tile_x(), (unsigned)camera_get_tile_y());
    graphics_draw_text(0, SCREEN_TILE_HEIGHT - 2, buf);
}
