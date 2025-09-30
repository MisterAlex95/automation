#include <stdio.h>

#include "game.h"
#include "graphics.h"
#include "menu.h"
#include "ui.h"

void menu_show_tile_selection(void)
{
  menu_clear();
  game.menu_state = MENU_TILE_SELECTION;
  HIDE_WIN;
  SHOW_WIN;
  move_win(7, 120);

  graphics_draw_text(5, 1, "Select Tile:\n");

  const char *tile_names[] = {"NONE    ", "CONVEYOR", "MINER   ", "CHEST   ", "WALL    "};
  char tile_buffer[16];
  sprintf(tile_buffer, "> %s", tile_names[game.selected_tile]);
  graphics_draw_text(5, 3, tile_buffer);
  graphics_draw_text(5, 4, "A:OK B:Exit");
}

void menu_show_orientation_selection(void)
{
  menu_clear();
  game.menu_state = MENU_ORIENTATION_SELECTION;
  HIDE_WIN;
  SHOW_WIN;
  move_win(7, 120);

  graphics_draw_text(5, 1, "DIRECTION");

  const char *orient_text[] = {"UP   ", "RIGHT", "DOWN ", "LEFT "};
  char buffer[16];
  sprintf(buffer, "> %s", orient_text[game.cursor_direction]);
  graphics_draw_text(5, 3, buffer);
  graphics_draw_text(5, 4, "A:OK B:Back");
}

void menu_clear(void)
{
  fill_win_rect(0, 0, 31, 31, 0);
}
