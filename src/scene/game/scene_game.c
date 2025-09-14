#include "scene_game.h"
#include "game.h"
#include "graphics.h"
#include "timer.h"
#include "map.h"
#include "item.h"
#include "ui.h"
#include "input_handler.h"
#include "ui_manager.h"
#include "game_logic.h"
#include "scene_menu.h"
#include <gb/gb.h>

static void load(void)
{
  // Load background tiles and map
  graphics_load_tiles(mapTiles, SPRITE_VRAM_INDEX_TOTAL, 0);
  graphics_draw_background(mapBackground, MAP_WIDTH, MAP_HEIGHT);

  graphics_load_sprite(cursorTile, SPRITE_VRAM_INDEX_CURSOR);
  graphics_load_sprite(itemsTiles, ITEMS_VRAM_INDEX_TOTAL);

  graphics_assign_sprite(UI_SPRITE_CURSOR, SPRITE_VRAM_INDEX_CURSOR);
  graphics_hide_all_sprites();

  graphics_move_sprite(UI_SPRITE_CURSOR, 88, 72);
}

static void update(void)
{
  game_conveyor_belt_update();
  display_items();
  ui_draw_hud();
}

static void unload(void)
{
  graphics_clear();
  timer_reset();
  game_init();
  graphics_hide_all_sprites();
}

void display_items(void)
{
  UINT8 sprite_ids[MAX_ITEMS] = {0};
  UINT8 x_positions[MAX_ITEMS] = {0};
  UINT8 y_positions[MAX_ITEMS] = {0};
  UINT8 count = 0;

  for (int i = 0; i < MAX_ITEMS; i++)
  {
    item_t *item = &game.items[i];
    if (item->type != ITEM_TYPE_NONE)
    {
      sprite_ids[count] = item->sprite_id;
      x_positions[count] = item->pos_x;
      y_positions[count] = item->pos_y;
      count++;
    }
  }
  graphics_batch_move_sprites(sprite_ids, x_positions, y_positions, count);
}

static void handle_input(UINT8 keys, UINT8 keys_prev)
{
  input_handle_game_input(keys, keys_prev);
}

Scene scene_game = {load, update, unload, handle_input};