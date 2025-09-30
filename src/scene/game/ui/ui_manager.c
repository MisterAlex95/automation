#include "ui_manager.h"
#include "graphics.h"
#include "game.h"
#include "../world/game_map.h"
#include "timer.h"
#include "constants.h"
#include "camera.h"

void ui_draw_hud(void)
{
    // ui_draw_tile_info_under_cursor();
    // ui_draw_nbr_active_items();
    ui_cursor_position();
    ui_draw_camera_debug();

    // ui_draw_miner_x_info(0);
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
    sprintf(buf, "(%d,%d)  ", game.cursor_x, game.cursor_y);
    graphics_draw_text(world_to_tile_x(camera_get_x()) + 0, world_to_tile_y(camera_get_y()) + SCREEN_TILE_HEIGHT - 3, buf);
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
    UBYTE cursor_pixel_x = screen_to_world_x(game.cursor_x * TILE_SIZE) - DEVICE_SPRITE_PX_OFFSET_X;
    UBYTE cursor_pixel_y = screen_to_world_y(game.cursor_y * TILE_SIZE) - DEVICE_SPRITE_PX_OFFSET_Y;

    UBYTE tile = game_map_get_tile_at_position(cursor_pixel_x, cursor_pixel_y);
    UBYTE out_count = 0;
    game_map_get_items_on_tile(world_to_tile_y(camera_get_y()) + game.cursor_x, world_to_tile_y(camera_get_y()) + game.cursor_y, &out_count);

    char buf[32];
    sprintf(buf, "Tile: %d (%d items) ", tile, out_count);
    graphics_draw_text(0, SCREEN_TILE_HEIGHT - 1, buf);
}

void ui_draw_camera_debug(void)
{
    char buf[32];
    sprintf(buf, "Cam:(%d,%d)", camera_get_x(), camera_get_y());
    graphics_draw_text(world_to_tile_x(camera_get_x()) + 0, world_to_tile_y(camera_get_y()) + SCREEN_TILE_HEIGHT - 4, buf);
}