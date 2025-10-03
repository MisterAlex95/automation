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

static void load(void)
{
  camera_init();
  
  // Load BG tiles
  graphics_load_bg_tiles(mapTiles, SPRITE_VRAM_INDEX_TOTAL);
  graphics_draw_background(mapBackground, MAP_WIDTH, MAP_HEIGHT);

  // Load UI and item tiles
  graphics_load_ui_tiles(UITiles, UI_TILES_COUNT);
  graphics_load_sprite_tiles(itemsTiles, ITEMS_VRAM_INDEX_TOTAL);

  graphics_assign_sprite(UI_SPRITE_CURSOR, (UINT8)UI_CURSOR);
  graphics_hide_all_sprites();

  graphics_move_sprite(UI_SPRITE_CURSOR, game.cursor_x, game.cursor_y);
}

static void update(void)
{
  if (game.paused == 0)
  {
    game_chest_update();
    game_conveyor_belt_update();
    game_miners_update();
  }

  display_items();
  game_display_cursor();
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
  render_display_items();
}

static void handle_input(UINT8 keys, UINT8 keys_prev)
{
  if (game.menu_state == MENU_ORIENTATION_SELECTION || game.menu_state == MENU_TILE_SELECTION)
  {
    menu_handle_input(keys, keys_prev);
  }
  else
  {
    input_handle_game_input(keys, keys_prev);
  }
}

Scene scene_game = {load, update, unload, handle_input};