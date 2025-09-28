#include "scene_menu.h"
#include "../game/core/scene_game.h"
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "math.h"
#include <gbdk/console.h>

static UINT8 blink = 0;
static UINT8 show_title = 1;
static UINT8 selected_option = 0;

static void load(void) {
  // Load tile if needed
}

static void update(void) {
  // Blinking method
  blink++;
  if (blink >= 45) {
    blink = 0;
    show_title = !show_title;
  }

  // title
  gotoxy(5, 2);
  if (show_title)
    printf("Automation");
  else
    printf("            ");

  // Ugly display of the menu :D
  gotoxy(5, 5);
  printf(selected_option == 0 ? "> Play" : "  Play");
  gotoxy(5, 7);
  printf(selected_option == 1 ? "> Quit" : "  Quit");
}

static void handle_input(UINT8 keys, UINT8 keys_prev) {
  (void)keys_prev;

  if (keys & J_UP)
    selected_option = MAX(selected_option - 1, 0);

  if (keys & J_DOWN)
    selected_option = MIN(selected_option + 1, 1);

  if (keys & J_START) {
    if (selected_option == 0) {
      scene_set(&scene_game);
    } else {
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
