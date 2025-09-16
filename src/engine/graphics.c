#include <gbdk/console.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "graphics.h"

void graphics_init(void)
{
    DISPLAY_OFF;
    SPRITES_8x8;
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

// Background functions

void graphics_clear(void)
{
    static const UINT8 blank_tile = 0;
    for (UINT8 y = 0; y < SCREEN_TILE_HEIGHT; y++)
    {
        for (UINT8 x = 0; x < SCREEN_TILE_WIDTH; x++)
        {
            set_bkg_tiles(x, y, 1, 1, &blank_tile);
        }
    }
}

void graphics_load_tiles(const unsigned char *tiles, UINT16 tile_count, UINT8 vram_index)
{
    set_bkg_data(vram_index, tile_count, tiles);
}

void graphics_draw_background(const unsigned char *map, UINT8 width, UINT8 height)
{
    set_bkg_tiles(0, 0, width, height, map);
}

// Sprite functions

void graphics_load_sprite(const unsigned char *sprite_data, UINT8 vram_tile_index)
{
    set_sprite_data(vram_tile_index, 1, sprite_data);
}

void graphics_load_sprites(const unsigned char *sprite_data, UINT8 vram_tile_index, UINT8 count)
{
    set_sprite_data(vram_tile_index, count, sprite_data);
}

void graphics_assign_sprite(UINT8 sprite_id, UINT8 vram_tile_index)
{
    set_sprite_tile(sprite_id, vram_tile_index);
}

void graphics_move_sprite(UINT8 sprite_id, UINT8 x, UINT8 y)
{
    move_sprite(sprite_id, x, y);
}

void graphics_hide_sprite(UINT8 sprite_id)
{
    move_sprite(sprite_id, 255U, 255U);
}

void graphics_draw_text(UINT8 x, UINT8 y, const char *text)
{
    gotoxy(x, y);
    printf("%s", text);
}

void graphics_hide_all_sprites(void)
{
    for (UINT8 i = 0; i < MAX_SPRITES; i++)
    {
        move_sprite(i, 255U, 255U);
    }
}

void graphics_batch_move_sprites(const UINT8 *sprite_ids, const UINT8 *x_positions, const UINT8 *y_positions, UINT8 count)
{
    for (UINT8 i = 0; i < count; i++)
    {
        move_sprite(sprite_ids[i], x_positions[i], y_positions[i]);
    }
}

// Window functions

void graphics_load_window_tiles(const unsigned char *tiles, UINT16 tile_count, UINT8 vram_index)
{
    set_win_data(vram_index, tile_count, tiles);
}

void graphics_draw_window(const unsigned char *map, UINT8 width, UINT8 height)
{
    set_win_tiles(0, 0, width, height, map);
}

void graphics_show_window(void)
{
    SHOW_WIN;
}

void graphics_hide_window(void)
{
    HIDE_WIN;
}

void graphics_move_window(UINT8 x, UINT8 y)
{
    // Offset
    // WX_REG = x + 7; WY_REG = y;
    move_win(x, y);
}