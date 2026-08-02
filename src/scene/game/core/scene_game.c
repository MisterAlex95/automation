#include <gb/gb.h>
#include "scene_game.h"
#include "../ui/menu/menu.h"
#include "game.h"
#include "graphics.h"
#include "timer.h"
#include "map.h"
#include "item.h"
#include "ui.h"
#include "../ui/input_handler.h"
#include "../ui/ui_manager.h"
#include "game_logic.h"
#include "scene_menu.h"
#include "../ui/game_cursor.h"
#include "../systems/render_system.h"
#include "camera.h"
#include "../world/viewport.h"
#include "../world/chunk_system.h"
#include "save_system.h"

static UBYTE load_from_save = 0;

void scene_game_set_load_mode(UBYTE from_save)
{
  load_from_save = from_save;
}

static void load(void)
{
  camera_init();

  if (load_from_save)
    load_game();
  else
    save_new_game();

  graphics_load_bg_tiles(mapTiles, SPRITE_VRAM_INDEX_TOTAL);
  graphics_load_ui_tiles(UITiles, UI_TILES_COUNT);
  graphics_load_sprite_tiles(itemsTiles, ITEMS_VRAM_INDEX_TOTAL);

  graphics_assign_sprite(UI_SPRITE_CURSOR, (UINT8)UI_CURSOR);
  graphics_hide_all_sprites();

  viewport_init();
  chunk_system_update();
  camera_update_all_entity_positions();

  graphics_move_sprite(UI_SPRITE_CURSOR, game.cursor_x * TILE_SIZE, game.cursor_y * TILE_SIZE);
  ui_draw_hud();
}

static void update(void)
{
  if (game.paused == 0 && game.won == 0)
  {
    game_chest_update();
    game_conveyor_belt_update();
    game_miners_update();
    chunk_system_update();
  }

  display_items();
  game_display_cursor();
  ui_draw_hud();
}

static void unload(void)
{
  save_game();
  graphics_clear();
  timer_reset();
  game_init();
  graphics_hide_all_sprites();
}

void display_items(void)
{
  render_display_items();
}

static void handle_input(UINT8 keys, UINT8 keys_prev)
{
  if (menu_is_open())
    menu_handle_input(keys, keys_prev);
  else
    input_handle_game_input(keys, keys_prev);
}

Scene scene_game = {load, update, unload, handle_input};
