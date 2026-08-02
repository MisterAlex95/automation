#include <stdio.h>

#include "game.h"
#include "graphics.h"
#include "menu.h"
#include "input.h"

#define MENU_WIN_X 7
#define MENU_WIN_Y 104

static void menu_draw_frame(void)
{
  graphics_fill_window_rect(0, 0, 20, 6, 0);
  graphics_move_window(MENU_WIN_X, MENU_WIN_Y);
  graphics_show_window();
}

void menu_show_tile_selection(void)
{
  game.menu_state = MENU_TILE_SELECTION;
  menu_draw_frame();

  graphics_draw_window_text(1, 0, "Select Tile:");

  const char *tile_names[] = {
      "ERASE   ", "CONVEYOR", "MINER   ", "CHEST   ", "WALL    ", "SPLITTER"};
  char tile_buffer[16];
  sprintf(tile_buffer, "> %s", tile_names[game.selected_tile]);
  graphics_draw_window_text(1, 2, tile_buffer);
  graphics_draw_window_text(1, 3, "A:OK B:Exit");
}

void menu_show_orientation_selection(void)
{
  game.menu_state = MENU_ORIENTATION_SELECTION;
  menu_draw_frame();

  graphics_draw_window_text(1, 0, "DIRECTION");

  const char *orient_text[] = {"UP   ", "RIGHT", "DOWN ", "LEFT "};
  char buffer[16];
  sprintf(buffer, "> %s", orient_text[game.cursor_direction]);
  graphics_draw_window_text(1, 2, buffer);
  graphics_draw_window_text(1, 3, "A:OK B:Back");
}

void menu_clear(void)
{
  graphics_fill_window_rect(0, 0, 32, 32, 0);
}

void menu_close(void)
{
  game.menu_state = MENU_NONE;
  menu_clear();
  graphics_hide_window();
}

UBYTE menu_is_open(void)
{
  return game.menu_state != MENU_NONE;
}

void menu_handle_input(UINT8 keys, UINT8 keys_prev)
{
  (void)keys;
  (void)keys_prev;
  UINT8 pressed = input_get_pressed();

  if (game.menu_state == MENU_NONE)
    return;

  if (game.menu_state == MENU_TILE_SELECTION)
  {
    if (pressed & J_UP)
    {
      if (game.selected_tile == 0)
        game.selected_tile = TILE_TYPE_COUNT - 1;
      else
        game.selected_tile--;
      menu_show_tile_selection();
    }
    if (pressed & J_DOWN)
    {
      game.selected_tile = (game.selected_tile + 1) % TILE_TYPE_COUNT;
      menu_show_tile_selection();
    }
    if (pressed & J_A)
      menu_show_orientation_selection();
    if (pressed & J_B)
      menu_close();
  }
  else if (game.menu_state == MENU_ORIENTATION_SELECTION)
  {
    if (pressed & J_LEFT)
    {
      game.cursor_direction = (game.cursor_direction + 3) % 4;
      menu_show_orientation_selection();
    }
    if (pressed & J_RIGHT)
    {
      game.cursor_direction = (game.cursor_direction + 1) % 4;
      menu_show_orientation_selection();
    }
    if (pressed & J_A)
      menu_close();
    if (pressed & J_B)
      menu_show_tile_selection();
  }
}
