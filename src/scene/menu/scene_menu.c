#include "scene_menu.h"
#include "../game/core/scene_game.h"
#include "../game/core/save_system.h"
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "math.h"
#include <gbdk/console.h>
#include <stdlib.h>

static UINT8 blink = 0;
static UINT8 show_title = 1;
static UINT8 selected_option = 0;
static UINT8 option_count = 2;

static void load(void)
{
  blink = 0;
  show_title = 1;
  selected_option = 0;
  option_count = save_exists() ? 3 : 2;
}

static void update(void)
{
  blink++;
  if (blink >= 45)
  {
    blink = 0;
    show_title = !show_title;
  }

  gotoxy(5, 2);
  if (show_title)
    printf("Automation");
  else
    printf("            ");

  gotoxy(5, 5);
  printf(selected_option == 0 ? "> New Game " : "  New Game ");

  if (option_count >= 3)
  {
    gotoxy(5, 7);
    printf(selected_option == 1 ? "> Continue " : "  Continue ");
    gotoxy(5, 9);
    printf(selected_option == 2 ? "> Quit     " : "  Quit     ");
  }
  else
  {
    gotoxy(5, 7);
    printf(selected_option == 1 ? "> Quit     " : "  Quit     ");
    gotoxy(5, 9);
    printf("            ");
  }
}

static void handle_input(UINT8 keys, UINT8 keys_prev)
{
  (void)keys_prev;

  if (keys & J_UP && !(keys_prev & J_UP))
    selected_option = selected_option == 0 ? (option_count - 1) : selected_option - 1;

  if (keys & J_DOWN && !(keys_prev & J_DOWN))
    selected_option = (selected_option + 1) % option_count;

  if ((keys & J_START && !(keys_prev & J_START)) || (keys & J_A && !(keys_prev & J_A)))
  {
    if (selected_option == 0)
    {
      scene_game_set_load_mode(0);
      scene_set(&scene_game);
    }
    else if (option_count >= 3 && selected_option == 1)
    {
      scene_game_set_load_mode(1);
      scene_set(&scene_game);
    }
    else
    {
      exit(0);
    }
  }
}

static void unload(void) { graphics_clear(); }

Scene scene_menu = {
    load,
    update,
    unload,
    handle_input,
};
