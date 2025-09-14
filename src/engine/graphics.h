#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <gb/gb.h>

#define START_X 8
#define START_Y 16

#define SCREEN_TILE_WIDTH 20
#define SCREEN_TILE_HEIGHT 18
#define TILE_SIZE 8

#define MAX_SPRITES 40

void graphics_init(void);
void graphics_clear(void);

void graphics_load_tiles(const unsigned char *tiles, UINT16 tile_count, UINT8 vram_index);
void graphics_draw_background(const unsigned char *map, UINT8 width, UINT8 height);

void graphics_load_sprite(const unsigned char *sprite_data, UINT8 vram_tile_index);
void graphics_load_sprites(const unsigned char *sprite_data, UINT8 vram_tile_index, UINT8 count);
void graphics_assign_sprite(UINT8 sprite_id, UINT8 vram_tile_index);
void graphics_move_sprite(UINT8 sprite_id, UINT8 x, UINT8 y);
void graphics_hide_sprite(UINT8 sprite_id);

void graphics_draw_text(UINT8 x, UINT8 y, const char *text);

// Optimized sprite management functions
void graphics_hide_all_sprites(void);
void graphics_batch_move_sprites(const UINT8 *sprite_ids, const UINT8 *x_positions, const UINT8 *y_positions, UINT8 count);

#endif // GRAPHICS_H
