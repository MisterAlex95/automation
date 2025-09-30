#include <stdio.h>

#include "game.h"
#include "graphics.h"
#include "menu.h"

void menu_show_tile_selection(void)
{
  game.menu_state = MENU_TILE_SELECTION;
  SHOW_WIN;
  move_win(7, 120);

  graphics_draw_text(0, 0, "Select Tile:\n");

  char tile_buffer[16];
  sprintf(tile_buffer, "> %d.        \n", game.selected_tile);
  graphics_draw_text(0, 1, tile_buffer);
  graphics_draw_text(0, 2, "A:OK B:Exit");
}

void menu_show_orientation_selection(void)
{
  game.menu_state = MENU_ORIENTATION_SELECTION;
  SHOW_WIN;
  move_win(7, 120);

  graphics_draw_text(0, 0, "Orientation:\n");

  const char *orient_text[] = {"UP", "RIGHT", "DOWN", "LEFT"};
  char buffer[16];
  sprintf(buffer, "> %s       \n", orient_text[game.cursor_direction]);
  graphics_draw_text(0, 1, buffer);
  graphics_draw_text(0, 2, "A:OK B:Back");
}

void menu_clear(void)
{
  fill_win_rect(0, 0, 31, 31, ' ');
}
